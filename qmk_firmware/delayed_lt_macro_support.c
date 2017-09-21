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
      
      layer_off(dlt_layer_to_toggle);
      dlt_on = false;
      //here hid id generated in macro is available
      _handle_action_delayed_lt_released( 
          keycode,_get_action_for_delayed_lt_released(keycode,record));
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
        //timer below has already been taken care of by 
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

      //if shift key is being pressed down, do not start dlt action.
      if(dlt_no_layer_toggle_while_modifier_on && \
          (keyboard_report->mods != 0)){
        register_code(keycode & 0xff);
      }else{
        //DLT action request, turning it on.
        _action_delayed_lt_pressed(keycode, record);
        layer_on(dlt_layer_to_toggle);
        dlt_on = true;
#ifdef DLT_DEBUG_PRINT
        print("layer toggle on\n");
#endif
      }
      return false;
    }else{
      //DLT captures key presses while it's on.
      //If there is non-DLT key pressed and not released
      //at the time DLT key release. DLT generates key 
      //release event for that key.
      //But the actual key is still pressed down and 
      //waiting to be released, so key release will 
      //be registered twice.
      //
      //But the above is handled is process_action_delayed_lt and not here.
      //Only time this section is called is when modifier prevented dlt to 
      //be turned on and key release signal needs to be registered for hid
      //usage id.
        unregister_code(keycode & 0xff);
        return false;
      }
      return true;
    }
  
  // Section below part is handled by process_action_delayed_lt
  // Save one exception; when this function is called while 
  // non-macro DLT is active, not as a DLT action requst/layer 
  // toggle request but as a requst to simply register the assigned
  // keycode.
  if(record->event.pressed){
    register_code(keycode & 0xff);//using _send_key triggers recursive loop
    unregister_code(keycode & 0xff);
  }

  // Only called while dlt_on is true.
  // Capturing and uncapture non-dlt keypresses.
  //
  /*if(record->event.pressed){*/
    /*prv_key_up = false;*/
    /*prv_keypos = record->event.key;*/

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
    /*return false;*/
  /*}else{*/
    //key releases handled here.
    //Capturing a key release for a key that was pressed 
    //before DLT key was pressed causes extra keys to be 
    //registered. The line below prevents that.
    //prv_key_up is true when no key has been pressed since 
    //DLT key pressed 
    /*if(prv_key_up) return true;*/

    //LT cycle completed
    //SSLT is used as LT
    /*prv_key_up = true;*/
    /*uint16_t kc = keymap_key_to_keycode(dlt_layer_to_toggle,prv_keypos);*/
    //print_val_bin16(kc);
    //
    //When macro calls macro, it's because keycode is not available
    /*_send_key(dlt_layer_to_toggle,prv_keypos);*/
    /*return false;*/
  /*}*/
  return true;
};
