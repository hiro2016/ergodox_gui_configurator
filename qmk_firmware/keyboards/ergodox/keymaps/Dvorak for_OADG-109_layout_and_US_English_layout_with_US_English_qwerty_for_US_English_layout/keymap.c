#include "ergodox.h"
//#include "action_layer.h"
//#include "version.h"
#include "delayed_lt.c"
#include "delayed_lt_macro_support.c"
#include "combo_lt.c"

#define BASE 0 // default layer
#define SYMB 1 // symbols #define MDIA 2 // media keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP(  
 0x35,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
0x2b,M(127),0x36,0x37,0x13,0x1c,0x39,
LSFT(0x87),0x04,0x12,SFT_T(0x08),0x18,0x0c,
0xe1,M(126),0x14,0x0d,M(125),0x1b,0x57,
0xe4,0xe3,0xe6,TO(9),TO(3),
TO(2),0x57,
KC_TRNS,
LT(7, 0x2c),0x4c,0x29,
 
 0x40,0x41,0x42,0x43,0x44,0x45,0x87,
TO(7),0x09,0x0a,LT(9, 0x06),0x15,0x0f,0x38,
0x07,0x0b,SFT_T(0x17),0x11,0x16,0x2d,
TO(1),0x05,0x10,0x1a,0x19,CTL_T(0x1d),0xe5,
TO(0),0x50,0x4f,0x51,0x52,
0x4b,KC_TRNS,
KC_TRNS,
0x2b,0x2a,LT(7, 0x58) ),
[1] = KEYMAP(  
 0x35,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
0x2b,0x34,0x36,0x37,0x13,0x1c,0x39,
RSFT(0x2d),0x04,0x12,SFT_T(0x08),0x18,0x0c,
0xe1,0x33,0x14,0x0d,M(124),0x1b,0x57,
0xe4,0xe3,0xe6,TO(9),TO(4),
TO(2),0x57,
KC_TRNS,
LT(8, 0x2c),0x4c,0x29,
 
 0x40,0x41,0x42,0x43,0x44,0x45,0x31,
TO(8),0x09,0x0a,LT(9, 0x06),0x15,0x0f,0x38,
0x07,0x0b,SFT_T(0x17),0x11,0x16,0x2d,
TO(1),0x05,0x10,0x1a,0x19,CTL_T(0x1d),0xe5,
TO(0),0x50,0x4f,0x51,0x52,
0x4b,KC_TRNS,
KC_TRNS,
0x2b,0x2a,LT(8, 0x58) ),
[2] = KEYMAP(  
 0x35,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
0x2b,0x14,0x1a,0x08,0x15,0x17,0x56,
0x39,0x04,0x16,0x07,0x09,0x0a,
0xe1,CTL_T(0x1d),0x1b,0x06,DLT(4, 0x19),0x05,0x56,
0xe4,0xe3,0xe6,TO(9),TO(4),
0x48,0x4d,
KC_TRNS,
LT(8, 0x2c),0x4c,0x29,
 
 0x40,0x41,0x42,0x43,0x44,0x56,0x57,
TO(1),0x1c,0x18,LT(9, 0x0c),0x12,0x13,0x31,
0x0b,0x0d,0x0e,0x0f,0x33,0x34,
TO(8),0x11,0x10,0x36,0x37,CTL_T(0x38),0xe5,
TO(0),0x50,0x4f,0x51,0x52,
0x4b,0x65,
KC_TRNS,
0x45,0x2a,LT(8, 0x58) ),
[3] = KEYMAP(  
 0x56,0x1e,0x56,0x56,0x56,0x56,0x56,
0x2b,LSFT(0x89),0x04,0x05,0x06,LSFT(0x36),TO(2),
0x39,0x2e,0x36,0x37,0x1b,LSFT(0x2e),
0x33,LSFT(0x23),0x07,0x08,0x09,LSFT(0x37),0x56,
0xe4,0xe3,0xe6,TO(9),TO(3),
0x48,0x4d,
KC_TRNS,
LT(7, 0x2c),0x4c,0x29,
 
 0x56,0x56,0x53,0x54,0x55,0x56,LSFT(0x38),
TO(1),0x55,0x5f,LT(9, 0x60),0x61,LSFT(0x2d),0x87,
0x62,0x5c,0x5d,0x5e,0x57,RSFT(0x1f),
TO(7),0x56,0x59,0x5a,0x5b,0x58,0x34,
TO(0),0x62,0x63,0x58,0x58,
0x4b,0x65,
KC_TRNS,
0x45,0x2a,LT(7, 0x58) ),
[4] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
0x2b,LSFT(0x31),0x04,0x05,0x06,LSFT(0x36),0x56,
0x39,LSFT(0x23),0x36,0x37,0x1b,LSFT(0x35),
0x33,RSFT(0x24),0x07,0x08,0x09,RSFT(0x37),KC_TRNS,
0xe4,0xe3,0xe6,TO(9),TO(4),
0x48,0x4d,
KC_TRNS,
LT(8, 0x2c),0x4c,0x29,
 
 KC_TRNS,KC_TRNS,0x53,0x54,0x55,0x56,RSFT(0x38),
TO(1),0x55,0x5f,LT(9, 0x60),0x61,0x2e,0x31,
0x62,0x5c,0x5d,0x5e,0x57,0x34,
TO(8),0x54,0x59,0x5a,0x5b,0x58,RSFT(0x33),
TO(1),0x62,0x63,0x58,0x58,
0x4b,0x65,
KC_TRNS,
0x45,0x2a,LT(8, 0x58) ),
[5] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS ),
[6] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS ),
[7] = KEYMAP(  
 KC_TRNS,0x1e,0x1f,0x20,0x21,0x22,RSFT(0x2e),
KC_TRNS,0x89,RSFT(0x36),0x57,LSFT(0x38),0x2f,KC_TRNS,
RSFT(0x87),LSFT(0x22),RSFT(0x89),LSFT(0x2d),RSFT(0x1e),RSFT(0x2e),
0x33,RSFT(0x87),LSFT(0x37),0x56,RSFT(0x23),0x34,TO(3),
0xe4,0xe3,0xe6,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
0x2c,0x4c,KC_TRNS,
 
 0x57,0x23,0x24,0x25,0x26,0x27,KC_TRNS,
KC_TRNS,RSFT(0x2f),RSFT(0x20),LSFT(0x30),LSFT(0x31),LSFT(0x24),0x56,
0x87,0x55,RSFT(0x25),RSFT(0x26),0x38,LSFT(0x1f),
TO(1),0x2e,LSFT(0x21),0x30,0x31,0x37,KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,0x58 ),
[8] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,RSFT(0x36),0x57,LSFT(0x38),RSFT(0x1f),KC_TRNS,
LSFT(0x2d),LSFT(0x22),LSFT(0x31),0x2e,LSFT(0x1e),LSFT(0x35),
0x33,LSFT(0x2d),LSFT(0x37),0x56,LSFT(0x24),LSFT(0x33),KC_TRNS,
0xe4,0xe3,0xe6,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,0x35,LSFT(0x20),LSFT(0x2f),LSFT(0x30),0x34,KC_TRNS,
0x31,0x55,LSFT(0x26),LSFT(0x27),0x38,LSFT(0x34),
KC_TRNS,LSFT(0x23),LSFT(0x21),LSFT(0x2f),LSFT(0x30),0x37,KC_TRNS,
TO(1),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS ),
[9] = KEYMAP(  
 KC_TRNS,0x3a,0x3b,0x3c,0x3d,0x3e,KC_TRNS,
KC_TRNS,0x58,0x4b,0x52,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,0x8b,0x50,0x51,0x4f,0x8a,
0xe1,KC_TRNS,0x4e,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 RESET,0x3f,0x40,0x41,0x42,0x43,0x44,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,OSL(9),
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,0xe5,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
0x45,KC_TRNS,KC_TRNS ),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};














const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  // MACRODOWN only works in this function
      switch(id) {
//        case 0:
//        if (record->event.pressed) {
//          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
//        }
//        break;
//        case 1:
//        if (record->event.pressed) { // For resetting EEPROM
//          eeconfig_init();
//        }
//        break;
        
    case 127:
        //' "
//' "
if(record->event.pressed){
if(keyboard_report->mods & (2|32)){
// " 
register_code(0x1f);
unregister_code(0x1f);
}else{
// ' 
register_code(0xe1);
register_code(0x24);
unregister_code(0x24);
unregister_code(0xe1);
}
}
        break;
    

    case 126:
        //; :
if(record->event.pressed){
if(keyboard_report->mods&(2|32)){
uint8_t temp = keyboard_report->mods&(2|32);
unregister_mods(temp);
register_code(0x34);
unregister_code(0x34);
register_mods(temp);
}else{
register_code(0x33);
unregister_code(0x33);
}
}
        break;
    

    case 125:
        //DLT(3,k)
//DLT(3,k)
//DLT(3,k)
if(record->event.pressed){
uint16_t kc = DLT(3,0x0e);
dlt_threshold = 200;
dlt_threshold_key_not_up = 200;
dlt_hold_decreased_by = 60;
dlt_hold_increased_by = 25;
dlt_pre_keypress_idling = 100;
process_action_delayed_lt_from_macro(kc,record);
}else{
uint16_t kc = DLT(3,0x0e);
process_action_delayed_lt_from_macro(kc,record);
dlt_reset();}
        break;
    

    case 124:
        //DLT(4,k)
if(record->event.pressed){
uint16_t kc = DLT(4,0x0e);
dlt_threshold = 200;
dlt_threshold_key_not_up = 200;
dlt_hold_decreased_by = 25;
dlt_hold_increased_by = 40;
dlt_pre_keypress_idling = 90;
process_action_delayed_lt_from_macro(kc,record);
}else{
uint16_t kc = DLT(4,0x0e);
process_action_delayed_lt_from_macro(kc,record);
dlt_reset();}
        break;
    








      }
    return MACRO_NONE;
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if(record->event.pressed) last_keypressed = record->event.key;
  if(!process_action_delayed_lt(keycode,record)) return false;

  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
//    case VRSN:
//      if (record->event.pressed) {
//        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
//      }
//      return false;
//      break;
    case RGB_SLD:
      if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
          rgblight_mode(1);
        #endif
      }
      return false;
      break;
  }
  return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

};

