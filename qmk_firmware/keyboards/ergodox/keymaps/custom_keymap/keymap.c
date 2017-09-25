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
 M(96),0x3a,0x3b,0x3c,0x3d,0x3e,KC_TRNS,
0x2b,0x33,0x36,DLT(2, 0x37),0x13,0x1c,0x39,
LSFT(0x87),0x04,0x12,M(95),DLT(4, 0x18),0x0c,
0xe1,RSFT(0x24),0x14,M(94),M(93),0x1b,KC_TRNS,
0xe4,0xe3,0xe6,TO(2),TO(1),
TO(5),KC_TRNS,
KC_TRNS,
M(92),0x4c,0x29,
 
 M(99),KC_TRNS,KC_TRNS,RSFT(0x33),KC_TRNS,LALT(LSFT(0x1b)),0x87,
LALT(0x54),0x09,0x0a,LT(2, 0x06),0x15,0x0f,0x38,
0x07,DLT(4, 0x0b),M(98),0x11,0x16,0x2d,
KC_TRNS,0x05,0x10,0x1a,0x19,CTL_T(0x1d),0xe5,
TT(0),0x50,0x4f,0x51,0x52,
0x4b,KC_TRNS,
KC_TRNS,
0x2b,0x2a,M(97) ),
[1] = KEYMAP(  
 0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,0x40,
KC_TRNS,KC_TRNS,KC_TRNS,0x37,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 0x41,0x42,0x53,0x54,0x46,0x56,KC_TRNS,
KC_TRNS,0x55,0x5f,0x60,0x61,0x56,KC_TRNS,
0x62,0x5c,0x5d,0x5e,0x57,KC_TRNS,
KC_TRNS,0x54,0x59,0x5a,0x5b,0x58,KC_TRNS,
TO(0),0x62,0x63,0x63,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS ),
[2] = KEYMAP(  
 0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,0x40,
KC_TRNS,0x56,0x8b,0x35,0x8a,0x58,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 RESET,0x41,0x42,0x43,0x44,0x45,KC_TRNS,
KC_TRNS,KC_TRNS,0x4b,0x52,LCTL(0x54),KC_TRNS,KC_TRNS,
KC_TRNS,0x50,0x51,0x4f,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,0x4e,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
TT(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS ),
[3] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,RSFT(0x36),0x57,LSFT(0x38),KC_TRNS,KC_TRNS,
KC_TRNS,LSFT(0x22),RSFT(0x89),LSFT(0x2d),RSFT(0x1e),RSFT(0x2e),
KC_TRNS,0x89,LSFT(0x37),0x56,RSFT(0x23),KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,RSFT(0x2f),RSFT(0x20),LSFT(0x30),LSFT(0x31),KC_TRNS,KC_TRNS,
KC_TRNS,0x55,RSFT(0x25),RSFT(0x26),KC_TRNS,KC_TRNS,
KC_TRNS,0x2e,LSFT(0x21),0x30,0x31,KC_TRNS,KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS ),
[4] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,0x2f,0x34,0x2a,KC_TRNS,KC_TRNS,
KC_TRNS,0x58,0x2c,0x29,0x33,KC_TRNS,
KC_TRNS,KC_TRNS,0x2b,0x1c,0x1b,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,TO(5),0x54,0x0f,KC_TRNS,KC_TRNS,
0x4c,TO(0),0x87,0x16,0x39,KC_TRNS,
KC_TRNS,KC_TRNS,0x05,0x09,0x1d,KC_TRNS,KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS ),
[5] = KEYMAP(  
 M(75),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,M(74),M(73),M(72),M(71),M(70),KC_TRNS,
0x2f,M(69),M(68),M(67),M(66),M(65),
0xe1,M(64),M(63),M(62),M(61),M(60),KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
M(59),0x4c,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,0x2a,
KC_TRNS,M(91),M(90),M(89),M(88),M(87),KC_TRNS,
M(86),M(85),M(84),M(83),M(82),0x30,
KC_TRNS,M(81),M(80),M(79),M(78),M(77),0xe5,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,M(76) ),
[6] = KEYMAP(  
 KC_TRNS,0x1e,0x1f,0x20,0x21,0x22,KC_TRNS,
KC_TRNS,0x34,RSFT(0x36),RSFT(0x37),RSFT(0x13),RSFT(0x1c),KC_TRNS,
KC_TRNS,RSFT(0x04),LSFT(0x12),LSFT(0x08),RSFT(0x18),LSFT(0x0c),
KC_TRNS,RSFT(0x1f),LSFT(0x14),LSFT(0x0d),RSFT(0x0e),LSFT(0x1b),KC_TRNS,
0xe4,0xe3,0xe6,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 KC_TRNS,0x23,0x24,0x25,0x26,0x27,KC_TRNS,
KC_TRNS,RSFT(0x09),LSFT(0x0a),RSFT(0x06),RSFT(0x15),RSFT(0x0f),KC_TRNS,
RSFT(0x07),RSFT(0x0b),RSFT(0x17),RSFT(0x11),RSFT(0x16),LSFT(0x87),
KC_TRNS,RSFT(0x05),RSFT(0x10),RSFT(0x1a),RSFT(0x19),RSFT(0x1d),KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS ),
[7] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,0x19,0x06,M(54),0x33,0x2d,KC_TRNS,
KC_TRNS,0x1e,0x36,M(53),0x1b,0x1f,
KC_TRNS,M(52),M(51),0x13,0x25,0x2e,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,0x22,0x34,0x38,0x31,0x87,KC_TRNS,
0x10,0x04,LSFT(0x89),0x11,0x24,KC_TRNS,
KC_TRNS,0x27,M(58),M(57),M(56),M(55),KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS ),
[8] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,M(41),M(40),0x56,M(39),M(38),KC_TRNS,
KC_TRNS,M(37),M(36),0x56,0x56,0x56,
KC_TRNS,KC_TRNS,KC_TRNS,M(35),M(34),M(33),KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,0x56,0x56,M(50),KC_TRNS,M(49),KC_TRNS,
KC_TRNS,M(48),KC_TRNS,M(47),KC_TRNS,KC_TRNS,
KC_TRNS,M(46),M(45),M(44),M(43),M(42),KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS ),
[9] = KEYMAP(  
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
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};



uint16_t gui_macro_editor_timer_99 = 0;










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
        
    case 99:
        if(record->event.pressed){
            gui_macro_editor_timer_99 = record->event.time;
        }else{
            if(200<timer_elapsed(gui_macro_editor_timer_99)){
                register_code(0x0b);
{ uint8_t ms = 16; while (ms--) wait_ms(1); }
unregister_code(0x0b);

register_code(0x08);
{ uint8_t ms = 16; while (ms--) wait_ms(1); }
unregister_code(0x08);

register_code(0x0f);
{ uint8_t ms = 53; while (ms--) wait_ms(1); }
unregister_code(0x0f);

register_code(0x0f);
{ uint8_t ms = 86; while (ms--) wait_ms(1); }
unregister_code(0x0f);

register_code(0x12);
{ uint8_t ms = 113; while (ms--) wait_ms(1); }
unregister_code(0x12);

register_code(0x2c);
{ uint8_t ms = 18; while (ms--) wait_ms(1); }
unregister_code(0x2c);

register_code(0x0f);
{ uint8_t ms = 126; while (ms--) wait_ms(1); }
unregister_code(0x0f);

register_code(0x12);
{ uint8_t ms = 122; while (ms--) wait_ms(1); }
unregister_code(0x12);

register_code(0x11);
{ uint8_t ms = 99; while (ms--) wait_ms(1); }
unregister_code(0x11);

register_code(0x0a);
{ uint8_t ms = 101; while (ms--) wait_ms(1); }
unregister_code(0x0a);

register_code(0x2c);
{ uint8_t ms = 22; while (ms--) wait_ms(1); }
unregister_code(0x2c);

register_code(0x17);
{ uint8_t ms = 20; while (ms--) wait_ms(1); }
unregister_code(0x17);

register_code(0x04);
{ uint8_t ms = 96; while (ms--) wait_ms(1); }
unregister_code(0x04);

register_code(0x13);
{ uint8_t ms = 93; while (ms--) wait_ms(1); }
unregister_code(0x13);

            }else{
                register_code(0x16);
{ uint8_t ms = 119; while (ms--) wait_ms(1); }
unregister_code(0x16);

register_code(0x0b);
{ uint8_t ms = 21; while (ms--) wait_ms(1); }
unregister_code(0x0b);

register_code(0x12);
{ uint8_t ms = 24; while (ms--) wait_ms(1); }
unregister_code(0x12);

register_code(0x15);
{ uint8_t ms = 129; while (ms--) wait_ms(1); }
unregister_code(0x15);

register_code(0x17);
{ uint8_t ms = 20; while (ms--) wait_ms(1); }
unregister_code(0x17);

register_code(0x2c);
{ uint8_t ms = 24; while (ms--) wait_ms(1); }
unregister_code(0x2c);

register_code(0x17);
{ uint8_t ms = 21; while (ms--) wait_ms(1); }
unregister_code(0x17);

register_code(0x04);
{ uint8_t ms = 109; while (ms--) wait_ms(1); }
unregister_code(0x04);

register_code(0x13);
{ uint8_t ms = 103; while (ms--) wait_ms(1); }
unregister_code(0x13);

            }
        }
        break;
    

    case 98:
        if(record->event.pressed){
uint16_t kc = DLT(6,0x17);
dlt_threshold = 200;
dlt_threshold_key_not_up = 200;
dlt_hold_decreased_by = 60;
dlt_hold_increased_by = 25;
dlt_pre_keypress_idling = 100;
process_action_delayed_lt_from_macro(kc,record);
}else{
uint16_t kc = DLT(0,0x17);
process_action_delayed_lt_from_macro(kc,record);
dlt_reset();}
        break;
    

    case 97:
        if(record->event.pressed){
uint16_t kc = DLT(3,0x58);
dlt_threshold = 200;
dlt_threshold_key_not_up = 200;
dlt_hold_decreased_by = 0;
dlt_hold_increased_by = 0;
dlt_pre_keypress_idling = 90;
process_action_delayed_lt_from_macro(kc,record);
}else{
uint16_t kc = DLT(3,0x58);
process_action_delayed_lt_from_macro(kc,record);
dlt_reset();}
        break;
    

    case 96:
        if(record->event.pressed){
            if(layer_state != 1<<5){
                layer_state = 1<<5;
            }else{layer_state = 0;}
            register_code(0x35);
            unregister_code(0x35);

        
        }
        break;
    

    case 95:
        if(record->event.pressed){
uint16_t kc = DLT(6,0x08);
dlt_threshold = 200;
dlt_threshold_key_not_up = 200;
dlt_hold_decreased_by = 60;
dlt_hold_increased_by = 25;
dlt_pre_keypress_idling = 100;
process_action_delayed_lt_from_macro(kc,record);
}else{
uint16_t kc = DLT(6,0x08);
process_action_delayed_lt_from_macro(kc,record);
dlt_reset();}
        break;
    

    case 94:
        if(record->event.pressed){
uint16_t kc = DLT(2,0x0d);
dlt_threshold = 200;
dlt_threshold_key_not_up = 200;
dlt_hold_decreased_by = 25;
dlt_hold_increased_by = 60;
dlt_pre_keypress_idling = 90;
process_action_delayed_lt_from_macro(kc,record);
}else{
uint16_t kc = DLT(2,0x0d);
process_action_delayed_lt_from_macro(kc,record);
dlt_reset();}
        break;
    

    case 93:
        if(record->event.pressed){
uint16_t kc = DLT(1,0x0e);
dlt_threshold = 200;
dlt_threshold_key_not_up = 200;
dlt_hold_decreased_by = 60;
dlt_hold_increased_by = 25;
dlt_pre_keypress_idling = 100;
process_action_delayed_lt_from_macro(kc,record);
}else{
uint16_t kc = DLT(0,0x0e);
process_action_delayed_lt_from_macro(kc,record);
dlt_reset();}
        break;
    

    case 92:
        if(record->event.pressed){
uint16_t kc = DLT(3,0x2c);
dlt_threshold = 200;
dlt_threshold_key_not_up = 200;
dlt_hold_decreased_by = 0;
dlt_hold_increased_by = 0;
dlt_pre_keypress_idling = 90;
process_action_delayed_lt_from_macro(kc,record);
}else{
uint16_t kc = DLT(3,0x2c);
process_action_delayed_lt_from_macro(kc,record);
dlt_reset();}
        break;
    





    case 91:
        //ki
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x0a);
unregister_code(0x0a);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 90:
        //no
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x0e);

unregister_code(0x0e);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 89:
        //ku
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x0b);

unregister_code(0x0b);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 88:
        //a
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x20);

unregister_code(0x20);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 87:
        //zi
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x07);

unregister_code(0x07);

register_code(0x2f);

unregister_code(0x2f);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 86:
        //wo
if(!record->event.pressed){
if(!clt_pressed){
register_code(0xe1);
register_code(0x27);

unregister_code(0x27);

unregister_code(0xe1);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 85:
        //i
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x08);

unregister_code(0x08);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 84:
        //u
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x21);

unregister_code(0x21);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 83:
        //si
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x07);

unregister_code(0x07);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 82:
        //nn
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x1c);

unregister_code(0x1c);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 81:
        //su
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x15);

unregister_code(0x15);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 80:
        //tu
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x1d);

unregister_code(0x1d);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 79:
        //,
if(!record->event.pressed){
if(!clt_pressed){
register_code(0xe1);
register_code(0x36);

unregister_code(0x36);

unregister_code(0xe1);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 78:
        //.
if(!record->event.pressed){
if(!clt_pressed){
register_code(0xe1);
register_code(0x37);

unregister_code(0x37);

unregister_code(0xe1);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 77:
        //ga
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x17);

unregister_code(0x17);

register_code(0x2f);

unregister_code(0x2f);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 76:
        //DLT(7,ret)
//DLT(7,ret)
clt_layer = 7;
process_combo_lt(0x58, record);
break;
        break;
    

    case 75:
        if(record->event.pressed){
            if(layer_state != 1<<5){
                layer_state = 1<<5;
            }else{layer_state = 0;}
            register_code(0x35);
            unregister_code(0x35);

        
        }
        break;
    

    case 74:
        //ra
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x12);

unregister_code(0x12);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 73:
        //ru
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x37);

unregister_code(0x37);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 72:
        //ko
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x05);

unregister_code(0x05);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 71:
        //ha
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x09);

unregister_code(0x09);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 70:
        //de
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x1a);

unregister_code(0x1a);

register_code(0x2f);

unregister_code(0x2f);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 69:
        //ta
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x14);

unregister_code(0x14);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 68:
        //to
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x16);

unregister_code(0x16);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 67:
        //ka
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x17);

unregister_code(0x17);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 66:
        //te
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x1a);

unregister_code(0x1a);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 65:
        //o
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x23);

unregister_code(0x23);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 64:
        //ma
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x0d);

unregister_code(0x0d);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 63:
        //ri
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x0f);

unregister_code(0x0f);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 62:
        //ni
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x0c);

unregister_code(0x0c);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 61:
        //na
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x18);

unregister_code(0x18);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 60:
        //yo
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x26);

unregister_code(0x26);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 59:
        //DLT7space
clt_layer = 7;
process_combo_lt(0x2c, record);
break;
        break;
    


    case 58:
        if(record->event.pressed){

            register_code(0x1f);
unregister_code(0x1f);

register_code(0x2f);
unregister_code(0x2f);

        }
        break;
    

    case 57:
        if(record->event.pressed){

            register_code(0x34);
unregister_code(0x34);

register_code(0x2f);
unregister_code(0x2f);

        
        }
        break;
    

    case 56:
        if(record->event.pressed){

            register_code(0x1d);
unregister_code(0x1d);

register_code(0x18);
unregister_code(0x18);

        
        }
        break;
    

    case 55:
        if(record->event.pressed){
            register_code(0x0a);
unregister_code(0x0a);

register_code(0x2f);
unregister_code(0x2f);

        
        }
        break;
    

    case 54:
        if(record->event.pressed){
            register_code(0x19);
unregister_code(0x19);

register_code(0x2f);
unregister_code(0x2f);

        
        }
        break;
    

    case 53:
        if(record->event.pressed){

            register_code(0x16);
unregister_code(0x16);

register_code(0x2f);
unregister_code(0x2f);

        
        }
        break;
    

    case 52:
        if(record->event.pressed){

            register_code(0x09);
unregister_code(0x09);

register_code(0x2f);
unregister_code(0x2f);

        
        }
        break;
    

    case 51:
        if(record->event.pressed){

            register_code(0x05);
unregister_code(0x05);

register_code(0x2f);
unregister_code(0x2f);

        }
        break;
    

    case 50:
        if(record->event.pressed){
            //timer_place_holder
        }else{
            
        if(!record->event.pressed){
            register_code(0x0b);
unregister_code(0x0b);

register_code(0x2f);
unregister_code(0x2f);

        }
        
        }
        break;
    

    case 49:
        if(record->event.pressed){

            register_code(0x19);
unregister_code(0x19);

register_code(0x30);
unregister_code(0x30);

        
        }
        break;
    

    case 48:
        if(record->event.pressed){

            register_code(0x04);
unregister_code(0x04);

register_code(0x2f);
unregister_code(0x2f);

        
        
        }
        break;
    

    case 47:
        if(record->event.pressed){
            //timer_place_holder
        }else{
            
        if(!record->event.pressed){
            register_code(0x2d);
unregister_code(0x2d);

register_code(0x30);
unregister_code(0x30);

        }
        
        }
        break;
    

    case 46:
        if(record->event.pressed){

            register_code(0x15);
unregister_code(0x15);

register_code(0x2f);
unregister_code(0x2f);

        
        }
        break;
    

    case 45:
        if(record->event.pressed){

            register_code(0x1d);
unregister_code(0x1d);

register_code(0x2f);
unregister_code(0x2f);

        
        }
        break;
    

    case 44:
        if(record->event.pressed){

            register_code(0x2e);
unregister_code(0x2e);

register_code(0x30);
unregister_code(0x30);

        
        }
        break;
    

    case 43:
        if(record->event.pressed){
            //timer_place_holder
        }else{
            
        if(!record->event.pressed){
            register_code(0x09);
unregister_code(0x09);

register_code(0x30);
unregister_code(0x30);

        }
        
        }
        break;
    

    case 42:
        if(record->event.pressed){
            //timer_place_holder
        }else{
            
        if(!record->event.pressed){
            register_code(0x1f);
unregister_code(0x1f);

register_code(0x30);
unregister_code(0x30);

        }
        
        }
        break;
    

    case 41:
        if(record->event.pressed){

            register_code(0x19);
unregister_code(0x19);

register_code(0x2f);
unregister_code(0x2f);
        
        
        }
        break;
    

    case 40:
        if(record->event.pressed){
 
            register_code(0x06);
unregister_code(0x06);

register_code(0x2f);
unregister_code(0x2f);

        
        
        }
        break;
    

    case 39:
        if(record->event.pressed){

            register_code(0x09);
unregister_code(0x09);

register_code(0x2f);
unregister_code(0x2f);

        
        
        }
        break;
    

    case 38:
        if(record->event.pressed){

            register_code(0x2d);
unregister_code(0x2d);

register_code(0x2f);
unregister_code(0x2f);


        }
        break;
    

    case 37:
        if(record->event.pressed){

            register_code(0x14);
unregister_code(0x14);

register_code(0x2f);
unregister_code(0x2f);

        
        }
        break;
    

    case 36:
        if(record->event.pressed){

            register_code(0x16);
unregister_code(0x16);

register_code(0x2f);
unregister_code(0x2f);

        
        
        }
        break;
    

    case 35:
        if(record->event.pressed){

            register_code(0x13);
unregister_code(0x13);

register_code(0x2f);
unregister_code(0x2f);

        
        
        }
        break;
    

    case 34:
        if(record->event.pressed){
    
            register_code(0x1b);
unregister_code(0x1b);

register_code(0x2f);
unregister_code(0x2f);
        
        }
        break;
    

    case 33:
        if(record->event.pressed){
   
            register_code(0x2e);
unregister_code(0x2e);

register_code(0x2f);
unregister_code(0x2f);

        
        
        }
        break;
    

      }
    return MACRO_NONE;
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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

