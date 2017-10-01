#define CLT_ACCEPTABLE_DELAY 180
uint16_t clt_layer = 0;
bool clt_pressed = false;
uint16_t clt_timer = 0;

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
*  combo partner macro key press ++++
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
* combo partner macro has to do:
*   1. register_code or call another macro
*
* For cases 2 and 3, partner macro should check 
* clt_pressed and clt_timer and decide and do 
* things; partner macro is also responsible to set ctl_pressed
* to false.
 *
 * for case 1 and 4, normal layer switching takes care of everything
 * save whether or not send CLT single tap keycode. The decision is
 * made based on whether another key was pressed after CLT key press.
 * */
bool process_combo_lt(uint16_t keycode, keyrecord_t *record){
  if(record->event.pressed){
    layer_on(clt_layer);
    clt_pressed = true;
    clt_timer = pre_dlt_idling_time;
    return true;
  }else{
    layer_off(clt_layer);
    if(clt_interrupted){
      layer_off(clt_layer);
      layer_off(clt_layer2);
      clt_interrupted = false;
      clt_pressed = false;
      return false;
    }
    if(CLT_ACCEPTABLE_DELAY > \
        (TIMER_DIFF_16(clt_timer,pre_pre_dlt_idling_time))\
        //check if no key press after CLT key press
        && (pre_dlt_idling_time == clt_timer)){
      //another key was pressed immidiately before CLT key and the
      //time approximity is close enough to treat this as a combo
      //request.
      //case 2 and 3. if macro key is already up, then clt_pressed 
      //is already set to false. Otherwise it will be set to false, 
      //do nothing.
    }else if(pre_dlt_idling_time == clt_timer) {
      // No key pressed while the caller key down 
      // or immidiately before the caller key down 

      // Below is not gonna work, caller is macro
      /*_send_key(biton32(layer_state),record->event.key);*/

      // Handle OSL
      if(keycode >= QK_ONE_SHOT_LAYER && keycode < QK_ONE_SHOT_LAYER_MAX){
        /*[>register_code16 did not work<]*/
        /*[>register_code16(keycode);<]*/
        /*[>unregister_code16(keycode);<]*/
        action_t action;
        action.code = ACTION_LAYER_ONESHOT(keycode);
        /*//order matters*/
        layer_on(action.layer_tap.val);
        set_oneshot_layer(action.layer_tap.val,ONESHOT_START);
        clear_oneshot_layer_state(ONESHOT_PRESSED);//key up
      }else{
        // register tapped alone time keycode
        register_code(keycode & 0xff);
        unregister_code(keycode & 0xff);
      }
      /*register_code16(keycode & 0xff);*/
      /*unregister_code16(keycode & 0xff);*/
      clt_pressed = false;
    } else{
      //case 4 and 1
      clt_pressed = false;
    }
  }
  return true;
}


