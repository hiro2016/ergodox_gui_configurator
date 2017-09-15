/*
 * Added as calling process_action_delayed_lt from macro results in forever loop
 * due to keymap_key_to_keycode function call.
 * The differences:
 * - No keymap_key_to_keycode as it only returns macro keycode here.
 * - Using pre_pre_dlt_idling_time instead of pre_dlt_idling_time
 *    process_action_delayed_lt already has set pre_dlt_idling_time 
 *    to the time macro was pressed.
 *
 * Interestingly for macros, key tap's held down time appear differently in macros. 
 * 
 * */

bool inline process_action_delayed_lt_from_macro(uint16_t keycode, keyrecord_t *record){
#ifdef DLT_DEBUG_PRINT
      print("process action delayed lt from macro called\n");
#endif
  if(dlt_on){
    //Ending DLT layer toggle.
    if(IS_KEYPOS_SAME(record->event.key, dlt_toggler)){    
#ifdef DLT_DEBUG_PRINT
      print("layer toggle off\n");
#endif
      //keycode variable contains the hid usage id found in the toggled 
      //layer and not the value found in before-dlt-key-pressed-layer.
      layer_off(dlt_layer_to_toggle);
      //dlt_timer = 0;//not needed
      dlt_on = false;
      _action_delayed_lt_released(keycode, record);
      //pre_pre_dlt_idling_time holds last pressed key time,
      //so timer works for the nex round.
      pre_dlt_idling_time = pre_pre_dlt_idling_time;
      return false;
    }

    //upstream code sets higher 8bits of the keycode to all zero
    //for DLT key release. Re-fetcheng keycode.
    //action_for_key does not work, it returns action_t whose 
    //higher 8 bits all set to zeros.
    //print_val_bin16(keycode);
    //print(" - raw keycode printed\n");
  }else{
    //dlt_on is false
    if(record->event.pressed){
      //DLT action not request, let other functions handle this.
      if(!((keycode&(~0xff))>=DLT_LAYER_TAP && 
          (keycode&(~0xff))<DLT_LAYER_MAX)){
        //This timer has already been taken care of by 
        //managed by process_action_delayed_lt.
        //pre_dlt_idling_time = record->event.time;
        return true;
      }
      //DLT action request, turning it on.
      //pre_dlt_idling_time has already been set by 
      //process_action_delayed_lt to the time 
      //the macro key that called this function was pressed.
      //swaping it to the key before that.
      uint16_t t = pre_pre_dlt_idling_time;
      //swap
      t = pre_dlt_idling_time;
      pre_dlt_idling_time = pre_pre_dlt_idling_time;
      pre_pre_dlt_idling_time = t;
      _action_delayed_lt_pressed(keycode, record);
      layer_on(dlt_layer_to_toggle);
      dlt_on = true;
#ifdef DLT_DEBUG_PRINT
      print("layer toggle on\n");
#endif
      return false;
    }else{
      //DLT captures key presses while it's on.
      //If there is non-DLT key pressed and not released
      //at the time DLT key release. DLT generates key 
      //release event for that key.
      //But the actual key is still pressed down and 
      //waiting to be released, so key release will 
      //be registered twice.
      //The line below prevents that.
      if(DLT_IS_KEYRELASE_FILTER_ENABLED(prv_keypos)){
#ifdef DLT_DEBUG_PRINT
        print("filtering keyrelease");
#endif
        DLT_DISABLE_KEYRELEASE_FILTER(prv_keypos);
        return false;
      }
      return true;
    }
  }


  // Only called while dlt_on is true.
  // Capturing and uncapture non-dlt keypresses.
  // This part is handled by process_action_delayed_lt
  //if(record->event.pressed){
    //prv_key_up = false;
    //prv_keypos = record->event.key;

    //This part is handled by process_action_delayed_lt.
    //Since pre_dlt_idling_time is in use, use 
    //pre_pre_dlt_idling_time to record key press time.
    //pre_pre_dlt_idling_time = record->event.time;
    //
    // Do not send a keypress immidiately while dlt key is being 
    // held to allow later evaluation of non-dlt key press events  
    // when DLT key is released.
    //
    // But taps must be registered. 
    //return false;
  //}else{
    //key releases handled here.
    //Capturing a key release for a key that was pressed 
    //before DLT key was pressed causes extra keys to be 
    //registered. The line below prevents that.
    //prv_key_up is true when no key has been pressed since 
    //DLT key pressed 
    //macro does not have key position, 
    //if(prv_key_up) return true;

    //LT cycle completed
    //SSLT is used as LT
    //prv_key_up = true;
    //uint16_t kc = keymap_key_to_keycode(dlt_layer_to_toggle,prv_keypos);
    //print_val_bin16(kc);
    //_send_key(dlt_layer_to_toggle,prv_keypos);
    //return false;
  //}
  return true;
};
