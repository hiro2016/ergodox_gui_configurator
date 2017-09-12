#include "action_layer.h"
enum macro_keycodes {
  //QK_MOD_TAP            = 0x6000,
  // QK_MOD_TAP_MAX        = 0x71FFF,
  // Edited to:
  // QK_MOD_TAP_MAX        = 0x7100,
  //>>> '{0:08b}'.format(0x7100)
  //'111000100000000'
  //>>> '{0:08b}'.format(0x6000)
  //'110000000000000'
  //>>> int('0x6000',16)
  //24576
  //>>> hex(24576+256)
  //'0x6100'
  //>>> hex(24576+256+256)
  //'0x6200'
  //
  // Lower 8 bits 
  // and [10:14] are usable.
  //>>> '{0:08b}'.format(0x6100)
  //'110000100000000'
  //DLT_LAYER_TAP = 0x6100, 
  //DLT_LAYER_MAX = 0x6200,

  //>>> '{0:08b}'.format(0x9100)
  //'1001000100000000'
  //
  //#using [10:14], so max value will be
  //>>'{0:08b}'.format(0x9100|(7<<9))
  //'1001111100000000'
  //>>>hex(0x9100|(7<<9))
  //'0x9f00'
  DLT_LAYER_TAP = 0x9100, 
  DLT_LAYER_MAX = 0x9f00,
};

#define GET_DLT_LAYER(kc) ((kc >> 9) & 0x7)
#define DLT(layer,kc) (kc | DLT_LAYER_TAP | ((layer & 0x7) << 9))
//#define DLT(layer,kc) (kc | DLT_LAYER_TAP | (layer & 0xf) << 9)

#define DLT_MODE_SHORTPRESS_AND_KEYPRESS_DETECTED 1
//DLT key down, then a key pressed but not released before DLT key release
//DLT down and the key tap dif < 60, a request for sending a key in a different layer.
#define DLT_MODE_LONGPRESS_AND_KEYPRESS_DETECTED 2
//DLT key down, anothere key tapped, SLT key released 
//A request for LT functionality.
#define DLT_MODE_LT 3
//DLT key tapped.
//A requeset for sending a key.
#define DLT_MODE_SINGLE_TAP 4

bool prv_key_up = true;
int16_t dlt_timer = 0;
keypos_t prv_keypos;//8col, 8row
keypos_t dlt_toggler;//until this key is released, do not re- toggle dlt layer
bool dlt_on = false;
uint8_t dlt_start_layer = 0;
uint8_t dlt_layer_to_toggle = 0;

typedef union {
  uint16_t code;
  struct action_custom_layer_tap {
      uint8_t  code   :8;
      uint8_t  filler :1;
      uint8_t  val    :3;
      uint8_t  kind   :4;
  } layer_tap;
  struct action_custom_key {
      uint8_t  code   :8;
      uint8_t  mods   :4;
      uint8_t  kind   :4;
  } key;
} custom_action_t;


void inline _send_key(uint32_t layer, keypos_t key ){
  uint16_t keycode = keymap_key_to_keycode(layer,key);
  //detect shift
  //For the time being supporting shift only
  //    /* Modifiers */
  //KC_LCTRL            = 0xE0,
  //KC_LSHIFT, //'11100001'
  //KC_LALT,
  //KC_LGUI,
  //KC_RCTRL,
  //KC_RSHIFT,//0xe5, '11100101'
  //KC_RALT,
  //KC_RGUI,
  //
  //I'm getting "00010010" does not match the definition...
    /* NOTE: 0xE8-FF are used for internal special purpose */
  register_code(keycode & 0xff);
  unregister_code(keycode & 0xff);
}

bool inline _action_delayed_lt_released(uint16_t keycode, keyrecord_t *record){
  // A flag for controlling the input handling downstream.
  uint8_t mode = 0;

#define IS_KEYPOS_SAME(keyone,keytwo)  ((keyone.col==keytwo.col)&&(keyone.row==keytwo.row))
#define ANOTHER_KEY_PRESSED (!IS_KEYPOS_SAME(prv_keypos, record->event.key))
  /*bool anotherKeyPressed = !(prv_keypos.col == record->event.key.col &&\
                           prv_keypos.row == record->event.key.row);*/
    
  int16_t held_down_time = timer_elapsed(dlt_timer);
  //IS_KEYPOS_SAME(record->event.key,prv_keypos);
  //print_val_bin8(anotherKeyPressed);
  if (ANOTHER_KEY_PRESSED){
    //DLT key was held down long enough? 
    //non DLT key pressed during DLT key press, is that non DLT key released yet?
    if ((held_down_time > 200) && !prv_key_up){
      //longer than 160 apparently means LT request
      mode = DLT_MODE_LONGPRESS_AND_KEYPRESS_DETECTED;
      print("sslt long press and keydown1\n");
    }else if(held_down_time > 200 && prv_key_up){
      //  full LT input cycle completed
      mode = DLT_MODE_LT;
      print("lt mode\n");
    }else{
      // A key pressed detected while DLT key was down, 
      // but DLT keypress as whole was too short.
      // Must be an unintentionl simultaneous key press.
      // set a flag to send the key in the default layer.
      mode = DLT_MODE_SHORTPRESS_AND_KEYPRESS_DETECTED; 
      print("short_sslt_and_another_key_down\n");
    }
  }else if(held_down_time > 300){
    mode = DLT_MODE_LT;
    print("lt mode\n");
  }else{
  // A single key tap 
    mode = DLT_MODE_SINGLE_TAP;
    print("single tap\n");
  }
    
  custom_action_t action;
  action.code = keycode;//mods are not available for dlt, bit section used for layer number.
  switch(mode){
    case DLT_MODE_SHORTPRESS_AND_KEYPRESS_DETECTED:
      //An unintentional simultaneous key press
      register_code(action.key.code);
      unregister_code(action.key.code );
      _send_key(dlt_start_layer,prv_keypos);
      break;
    case DLT_MODE_LONGPRESS_AND_KEYPRESS_DETECTED:
      //Premature lt key release
      _send_key(dlt_layer_to_toggle, prv_keypos);
      break;
    case DLT_MODE_LT:
      //full lt cycle completed
      break;
    case DLT_MODE_SINGLE_TAP:
      //single tap
      /*print_val_bin8(prv_keypos.col);*/
      /*print_val_bin8(prv_keypos.row);*/
      /*print_val_bin8(record->event.key.col);*/
      /*print_val_bin8(record->event.key.row);*/
      register_code(action.key.code);
      unregister_code(action.key.code );
      break;
    }
  return true;
}

bool inline process_action_delayed_lt(uint16_t keycode, keyrecord_t *record){
  //keycode contain the keycode found in the toggled on layer and not 
  //the before-dlt-key-pressed-layer keycode.
  //
  if(dlt_on){
    //upstream code sets higher 8bits of the keycode to all zero
    //for DLT key release. Re-fetcheng keycode.
	if(IS_KEYPOS_SAME(record->event.key, dlt_toggler)){    
		keycode = keymap_key_to_keycode(dlt_start_layer, record->event.key);
	}
    //action_for_key does not work, it returns bits all set to zero aciton.
    //print_val_bin16(keycode);
    //print(" - raw keycode printed\n");
  }
  switch(keycode&(~0xff)){
    case DLT_LAYER_TAP ... DLT_LAYER_MAX:
      if(record->event.pressed){
        dlt_start_layer = biton32(layer_state);
        dlt_layer_to_toggle = GET_DLT_LAYER(keycode);
        prv_key_up=true;//stack empty, no need to worry about releasing key
        dlt_toggler = record->event.key;
        prv_keypos = record->event.key;//used to check is new key is pressed
        dlt_timer = record->event.time;
        dlt_on = true;
        layer_on(dlt_layer_to_toggle);
      }else{
        _action_delayed_lt_released(keycode, record);
        layer_off(dlt_layer_to_toggle);
        dlt_timer = 0;
        dlt_on = false;
      }
      return false;
    default:
      if(!dlt_on) return true;// dlt is off
      if(record->event.pressed){
        prv_key_up = false;
        prv_keypos = record->event.key;
      // Do not send a keypress immidiately when dlt key is being pressed down. 
      // So when dlt key is up, the non-dlt key press event can be evaluated 
      // and then released before dlt key.
      // But if a tap was made while dlt was key down, then report that tap. 
      //
        return false;
      }else{//key release
            //Capturing a key release for a key that was pressed down
            //before DLT key was pressed causes extra keys to be 
            //send to pc. The line below prevents that.
            //If no key has been pressed since SSLT key pressed 
            //prv_key_up must be true.
            if(prv_key_up) return true;

            //LT cycle completed
            //SSLT is used as LT
            prv_key_up = true;
            //uint16_t kc = keymap_key_to_keycode(dlt_layer_to_toggle,prv_keypos);
            //print_val_bin16(kc);
            _send_key(dlt_layer_to_toggle,prv_keypos);
            return false;
        }
  }
  return true;
};
