#define CLT_ACCEPTABLE_DELAY 180 
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
      if(keycode >= QK_ONE_SHOT_LAYER && keycode < QK_ONE_SHOT_LAYER_MAX){
        /*[>register_code16 did not work<]*/
        /*[>register_code16(keycode);<]*/
        /*[>unregister_code16(keycode);<]*/
        print("os\n");
        action_t action;
        action.code = ACTION_LAYER_ONESHOT(keycode);
        /*//order matters*/
        layer_on(action.layer_tap.val);
        set_oneshot_layer(action.layer_tap.val,ONESHOT_START);
        clear_oneshot_layer_state(ONESHOT_PRESSED);//key up
      }else{
        print("rc\n");
        register_code(keycode & 0xff);
        unregister_code(keycode & 0xff);
        clear_keyboard();
      }
}

int clt_get_state(keyrecord_t *record){
  print_val_dec(last_keypressed);
  print_val_dec(record->event.key);
  print_val_dec(clt_interrupted);
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
      // laste recorded keypress and this key release are for the same key.
      // No key pressed while this clt emitter key down 
      // or immidiately before the key down 
      return CLT_EMITTER_ALONE_TAPPED;
    }
  return CLT_EMITTER_TAP_BEFORE_RECEPTOR;
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
  }
  layer_off(clt_layer);
  switch(clt_get_state(record)){
    case CLT_EMITTER_INTERRUPTED:
      print("clt_i\n");
      // if CLT emitter that is to be interrupted 
      // has been released, this should not be called.
      // If CLT emitter interruptor get return value false
      // for process_combo_lt, then the emitter to be 
      // interrupted has not been released yet.
      layer_off(clt_layer);
      layer_off(clt_layer2);
      clt_interrupted = false;
      clt_pressed = false;
      clear_keyboard();
      return false;
    case CLT_EMITTER_TAP_DELAYED:
      //another key was pressed immidiately before CLT emitter key and the
      //time approximity is close enough to treat two key press events as a 
      //combo request.
      //case 2 and 3. if macro key is already up, then clt_pressed 
      //is already set to false. Otherwise it will be set to false, 
      //by the macro key release event, so do nothing.
      print("sm");
      return true;
    case CLT_EMITTER_ALONE_TAPPED:
      print("clt==p");
      // No key pressed while the key down 
      // or immidiately before the key down 
      // Below is not gonna work, caller is macro
      /*_send_key(biton32(layer_state),record->event.key);*/
      // Handle OSL
      /*register_code16(keycode & 0xff);*/
      /*unregister_code16(keycode & 0xff);*/
      clt_send_key(keycode);
      clt_pressed = false;
      return true;
    case CLT_EMITTER_TAP_BEFORE_RECEPTOR:
      print("4");
      clt_pressed = false;
      return true;
    default:
      print("should never be called");
  }
  return true;
}


