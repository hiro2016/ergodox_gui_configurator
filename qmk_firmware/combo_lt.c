#define CLT_ACCEPTABLE_DELAY 150
uint16_t clt_layer = 0;
bool clt_pressed = false;
uint16_t clt_timer = 0;


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
void process_combo_lt(uint16_t keycode, keyrecord_t *record){
  if(record->event.pressed){
    layer_on(clt_layer);
    clt_pressed = true;
    clt_timer = pre_dlt_idling_time;
  }else{
    layer_off(clt_layer);
    if(CLT_ACCEPTABLE_DELAY > \
        (TIMER_DIFF_16(clt_timer,pre_pre_dlt_idling_time))\
        //no key press after CLT key press
        && (pre_dlt_idling_time == clt_timer)){
      //another key was pressed immidiately before CLT key and the
      //time approximity is close enough to treat this as a combo
      //request.
      //case 2 and 3. if macro key is already up, then clt_pressed 
      //is set to false. Otherwise it will be set to false, do nothing.
    }else if(pre_dlt_idling_time == clt_timer) {
      // No key pressed while the caller key down 
      // or immidiately before the caller key down 
      register_code16(keycode & 0xff);
      unregister_code16(keycode & 0xff);
      clt_pressed = false;
    } else{
      //case 4 and 1
      clt_pressed = false;
    }
  }
}


