#include "input_que.c"
//#define CLT_ACCEPTABLE_DELAY 60
#define CLT_ACCEPTABLE_DELAY 30
/*#define CLT_ACCEPTABLE_DELAY 0*/
/*#define CLT_DEBUG_PRINT*/

uint16_t clt_layer = 0;
bool clt_pressed = false;
uint16_t clt_timer = 0;

keypos_t last_keypressed = {128,128};
// For modified mizunara thumb key key layer 
// shifting.
//
// Added to use clt emitter like a lct receiver.
// When another CLT emitter is pressed while a clt 
// emitter key is still down, this
// value is set to true and process_combo_lt
// returns false.
//
// A macro calling process_combo_lt can 
// loot at that return value and act on that.
// No GUI editor support.
// For hand coding only.
bool clt_interrupted = false;
uint16_t clt_layer2 = 0;//needed to shift layer after middle finger key shifted layer.

#define LAST_TWO_KEYPRESSES_OCCURED_WITHIN_INTERVAL\
  CLT_ACCEPTABLE_DELAY>(TIMER_DIFF_16(clt_timer,pre_pre_dlt_idling_time)) 

//State evaluation happens at keyrelease time.
enum CLT_STATE{
  /*CLT_RECEPTOR_ALONE_TAPPED,//request for current the layer keycode */
  CLT_EMITTER_ALONE_TAPPED,//request for oneshot layer
  CLT_EMITTER_TAP_DELAYED,
  //User pressed emitter key sometime after receptor key
  //e.g. 
  //A pressed, then right thumb cluster ENT pressed in 200ms.
  CLT_EMITTER_TAP_BEFORE_RECEPTOR,
  //Layer changed temporarily then a keycode in that layer has been sent. 
  CLT_EMITTER_INTERRUPTED,
  // clt_interrupted flag is set to true while Emitter key was down.
};

void clt_send_key(uint16_t keycode){
			keyrecord_t record;
			action_t action;
			action.code = keycode;
			record.event.pressed = true;
			record.event.time = timer_read();
      if(keycode >= QK_ONE_SHOT_LAYER && keycode < QK_ONE_SHOT_LAYER_MAX){
        /*[>register_code16 did not work<]*/
        /*[>register_code16(keycode);<]*/
        /*[>unregister_code16(keycode);<]*/
#ifdef CLT_DEBUG_PRINT
        print("clt_send_key called(onesht_layer)\n");
#endif
        action.code = ACTION_LAYER_ONESHOT(keycode);
        /*//order matters*/
        layer_on(action.layer_tap.val);
        set_oneshot_layer(action.layer_tap.val,ONESHOT_START);
        clear_oneshot_layer_state(ONESHOT_PRESSED);//key up
      } else if(QK_MACRO <= keycode && keycode <QK_MACRO_MAX){
#ifdef CLT_DEBUG_PRINT
        print("clt_send_key(macro) called(not oneshot)\n");
#endif
				record.event.key = (keypos_t){128,128};//passing a random number set
        action_get_macro(&record,action.func.id, action.func.id);
        record.event.pressed = false;
        action_get_macro(&record,action.func.id, action.func.id);
      } else{
#ifdef CLT_DEBUG_PRINT
        print("clt_send_key(usage id) called(not oneshot)\n");
#endif
				/*process_record(keycode,&record);*/
				/*record.event.pressed = false;*/
				/*process_record(keycode,&record);*/

				// The below is real messy but register_code 
				// nor register_code16 work for `LSFT(KC_A)`
				// etc. 
				// The below does not cover other modifier types.
				switch(keycode>>8){
					case(0x2):
						register_code(KC_LSHIFT);
						register_code(keycode & 0xff);
						unregister_code(keycode & 0xff);
						unregister_code(KC_LSHIFT);
						break;
					case(0x12):
						register_code(KC_LSHIFT);
						register_code(keycode & 0xff);
						unregister_code(keycode & 0xff);
						unregister_code(KC_LSHIFT);
						break;
					default:
						register_code(keycode & 0xff);
						unregister_code(keycode & 0xff);
				}
      }
}

int clt_get_state(keyrecord_t *record){
  /*print_val_dec(last_keypressed);*/
  /*print_val_dec(record->event.key);*/
  /*print_val_dec(clt_interrupted);*/
    if(clt_interrupted){
      return CLT_EMITTER_INTERRUPTED;
    }else if(LAST_TWO_KEYPRESSES_OCCURED_WITHIN_INTERVAL
        //check if no key press after CLT key press
        && IS_KEYPOS_SAME(last_keypressed, record->event.key)){
      //another key was pressed immidiately before CLT key and the
      //time approximity is close enough to treat this as a combo
      //request.
      //
      //case 2 and 3. if receptor key is already up, then clt_pressed 
      //is already set to false. Otherwise it will be set to false, 
      //by the receptor key release event, so do nothing.
      return CLT_EMITTER_TAP_DELAYED;
    }else if(IS_KEYPOS_SAME(last_keypressed, record->event.key)) {
      // last recorded keypress and this key release are for the same key.
      // No key pressed while this clt emitter key down 
      // or immidiately before the key down 
      return CLT_EMITTER_ALONE_TAPPED;
    }
  //Emitter key is pressed first to change layer.
  return CLT_EMITTER_TAP_BEFORE_RECEPTOR;
}
        


void clt_send_keycode_in_que_up_to(uint16_t id){
  //do nothing if the input has already been handled/registered.
  if(!is_in_input_que(id)) return;

  for(uint8_t count = 4; count>0;--count){
    quantum_state_input v = shift_input();
    // macro id 0 is assumed not used.
    // In this context, 0 denotes nothing.
    if(v.id == 0) continue; 
    clt_send_key(v.default_keycode);
  }
}

/*
 * Handles all key press events prior to switching layer so as to
 * make sure the order of key press dectates the order of key 
 * inputs rather than the order of key release.
 *
 * Returns true if clt receptor key has already been 
 * pressed within the interval less than CLT_ACCEPTABLE_DELAY.
 * */
bool handle_keys_in_que_and_check_clt_action_performed(void){
#ifdef CLT_DEBUG_PRINT
        print("---entered handle_keys_in_que_and_check_clt_action_performed---\n");
#endif
  // start handling from oldest
  for(uint8_t count = 4; count>0;--count){
    quantum_state_input v = shift_input();
    /*print_val_dec(v.id);*/
    if(v.id == 0) continue;
    //last input
    if(count == 1){
      bool use_default = timer_elapsed(v.time)>CLT_ACCEPTABLE_DELAY;
      if(use_default){
        clt_send_key(v.default_keycode);
#ifdef CLT_DEBUG_PRINT
        print("sent default key code\n");
        print("---leaving handle_keys_in_que_and_check_clt_action_performed---\n");
#endif
        return false;
      }else{
        clt_send_key(keymap_key_to_keycode(clt_layer, v.keypos));
#ifdef CLT_DEBUG_PRINT
        print("sent toggled layer key code\n");
        print("---leaving handle_keys_in_que_and_check_clt_action_performed---\n");
#endif
        return true;
      }
    }
    //other than the last key pressed
    clt_send_key(v.default_keycode);
  }
  return false;
}


// action key cannot be used to in combination with macro
/*uint16_t prv_key_down_time = 0;*/
/*uint16_t prv_prv_key_down_time = 0;*/
/*enum clt_keycode{*/
/*// >>> int('1010000000000000',2)*/
  /*COMBO_LAYER_TAP = 0xa000;//40960*/
  /*COMBO_LAYER_TAP_MAX = 0xa0ff;//40960 + 255*/
/*};*/
/*#define GET_CLT_LAYER(kc) ((kc >> 8) & 0x7)*/
/*#define CLT(layer,kc) (kc | CLT_LAYER_TAP | ((layer & 0xf) << 8))*/


/*
 * combo key press patters.
*  main combo key ----
*  combo receptor macro key press ++++
* Cases to consider:
*
*     1. 
*         ----
*          ++++
*        another layer turned on first, callee knows nothing of clt
*        need to set clt_pressed to false
*     2.
*          ----
*         ++++
*     3. 
*          --
*         ++++
*        must not set clt_pressed to false
*     4.
*         ----
*          ++ 
*        another layer turned on first, callee knows nothing of clt
*        need to set clt_pressed to false
*
* Since moving register_code and unregister_code lines
* from macro is a bit of trouble, giving up making this 
* an action code.
*
* combo receptor macro has to do:
*   1. register_code or call another macro
*
* For cases 2 and 3, receptor macro should check 
* clt_pressed and clt_timer and do 
* things; receptor macro should take care of setting ctl_pressed
* to false.
 *
 * With case 1 and 4, normal layer switching takes care of everything
 * save whether or not send CLT single tap keycode. The decision is
 * made based on whether another key was pressed after CLT key press.
 * */
bool process_combo_lt(uint16_t keycode, keyrecord_t *record){
#ifdef CLT_DEBUG_PRINT
    print("----process_combo_lt_emitter---\n");
    print("clt key: event.pressed is ");
    print_val_dec(record->event.pressed);
#endif

  if(record->event.pressed){
    //send everything in the que
    // empty all keypress events in qeue and ignore their release events.
    // If  timer_elapsed(key_press_timestamp_of_qeued_key) < CLT_ACCEPTABLE_DELAY,
    // send keycode found in clt layer.
    if(handle_keys_in_que_and_check_clt_action_performed()){
      // Another key press event with a timestamp 
      // sufficiently close to the timer_read() result
      // found.
      //
      // Preventing the caller key from sending its defualt keycode
      // at its release time; only switches layer.
      clt_interrupted = true;    
    }
    layer_on(clt_layer);
    clt_pressed = true;
    clt_timer = pre_dlt_idling_time;
#ifdef CLT_DEBUG_PRINT
    print_val_dec(clt_interrupted);
    print("-----------combo lt emitter end--------------\n");
#endif
    return true;
  }
#ifdef CLT_DEBUG_PRINT
  else{
    print_val_dec(clt_interrupted);
  }
#endif


  layer_off(clt_layer);
  switch(clt_get_state(record)){
    case CLT_EMITTER_INTERRUPTED:
      // CLT emitter has been interrupted:
      //  A CLT receptor key has been pressed immidiately before 
      //  CLT emitter key or immidiately after.  
      //
      // The release of CLT emitter key that called this function
      // should not call register_code. 
      //
      // defualt keycode is only `register_code`ed when uninterrupted:
#ifdef CLT_DEBUG_PRINT
      print("clt_emitter_interrupted, not taped alone\n");
#endif
      // If CLT emitter is released before the interruptor, 
      // primarily CLT receptor, this block is not called.
      //
      layer_off(clt_layer);
      layer_off(clt_layer2);
      clt_interrupted = false;
      clt_pressed = false;
      /*clear_keyboard();*/
      // The return value of for process_combo_lt has been false
      // means the emitter to be interrupted has not been released 
      // yet.
#ifdef CLT_DEBUG_PRINT
    print("---------exiting process_combo_lt_emitter----------------\n");
#endif
      return true; // released event is consumed here, do nothing downstream.
    case CLT_EMITTER_TAP_DELAYED:
      //another key was pressed immidiately before CLT emitter key and the
      //time approximity is close enough to treat two key press events as a 
      //combo request.
      //case 2 and 3. if macro key is already up, then clt_pressed 
      //is already set to false. Otherwise it will be set to false, 
      //by the macro key release event, so do nothing.

#ifdef CLT_DEBUG_PRINT
      print("clt_emitter_tap_delayed clt emitter key is pressed after receptor.\n");
      print("---------exiting process_combo_lt_emitter----------------\n");
#endif
      return true;
    case CLT_EMITTER_ALONE_TAPPED:
#ifdef CLT_DEBUG_PRINT
      print("CLT key alone is tapped\n");
#endif
      // No key pressed while the key down 
      // or immidiately before the key down 
      // Below is not gonna work, caller is macro
      /*_send_key(biton32(layer_state),record->event.key);*/
      // Handle OSL
      /*register_code16(keycode & 0xff);*/
      /*unregister_code16(keycode & 0xff);*/
      clt_send_key(keycode);
      clt_pressed = false;
#ifdef CLT_DEBUG_PRINT
      print("---------exiting process_combo_lt_emitter----------------\n");
#endif
      return true;
    case CLT_EMITTER_TAP_BEFORE_RECEPTOR:
#ifdef CLT_DEBUG_PRINT
      print("CLT emitter key is pressed and then receptor key \
is pressed before clt emitter key up.\n");
#endif
      clt_pressed = false;
#ifdef CLT_DEBUG_PRINT
      print("---------exiting process_combo_lt_emitter----------------\n");
#endif
      return true;
    default:
#ifdef CLT_DEBUG_PRINT
      print("should never be called");
#endif
      break;
  }
#ifdef CLT_DEBUG_PRINT
      print("---------exiting process_combo_lt_emitter----------------\n");
#endif
  return true;
}

void process_combo_lt_receptor(keyrecord_t *record, uint8_t id, uint16_t keycode ){
  // id is a macro id;ranges from 0 to 255.
  // should reserve 255, 254 for normal input and functions.
#ifdef CLT_DEBUG_PRINT
  print("----process_combo_lt_receptor---\n");
  print_val_dec(keycode);
  print_val_dec(id);
  print_val_dec(record->event.pressed);
  print_val_dec(record->event.key);
  print("--------------\n");
#endif
  if(record->event.pressed){
    //id, default keycode, keypos, keypressed time
    enque_input(id, keycode ,record->event.key, timer_read());
  }else{
    clt_send_keycode_in_que_up_to(id);
  }
}


