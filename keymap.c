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
 M(126),0x3a,0x3b,0x3c,0x3d,0x3e,KC_TRNS,
0x2b,M(125),0x36,LT(2, 0x37),0x13,0x1c,0x39,
LSFT(0x87),0x04,0x12,SFT_T(0x08),DLT(4, 0x18),0x0c,
0xe1,M(124),0x14,0x0d,M(123),0x1b,TO(3),
0xe4,0xe3,0xe6,TO(2),TO(5),
TO(5),TO(3),
KC_TRNS,
M(122),0x4c,0x29,
 
 0x2d,KC_TRNS,KC_TRNS,0x57,KC_TRNS,LALT(LSFT(0x1b)),0x87,
TO(3),0x09,0x0a,LT(2, 0x06),0x15,0x0f,0x38,
0x07,DLT(4, 0x0b),SFT_T(0x17),0x11,0x16,0x2d,
TO(1),0x05,0x10,0x1a,0x19,CTL_T(0x1d),0xe5,
TO(0),0x50,0x4f,0x51,0x52,
0x4b,KC_TRNS,
KC_TRNS,
0x2b,0x2a,M(127) ),
[1] = KEYMAP(  
 M(101),M(100),M(99),M(98),M(97),M(96),M(95),
0x2b,M(94),M(93),M(92),M(91),M(90),KC_TRNS,
OSL(2),M(89),M(88),M(87),M(86),M(85),
OSL(5),M(84),M(83),M(82),M(81),M(80),0x56,
OSL(6),0xe3,0xe6,TG(2),TG(5),
KC_TRNS,KC_TRNS,
KC_TRNS,
M(79),0x4c,KC_TRNS,
 
 M(121),M(120),M(119),M(118),M(117),0x56,0x57,
TO(6),M(116),M(115),M(114),M(113),0x22,0x38,
M(112),M(111),M(110),M(109),M(108),OSL(3),
KC_TRNS,M(107),M(106),M(105),M(104),M(103),0xe5,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,M(102) ),
[2] = KEYMAP(  
 0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,0x40,
KC_TRNS,KC_TRNS,0x8b,0x35,0x8a,0x58,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,TO(0),
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
0x2c,0x4c,KC_TRNS,
 
 RESET,0x41,0x42,0x43,0x44,0x45,KC_TRNS,
KC_TRNS,KC_TRNS,0x4b,0x52,LCTL(0x54),KC_TRNS,KC_TRNS,
KC_TRNS,0x50,0x51,0x4f,KC_TRNS,KC_TRNS,
TO(1),KC_TRNS,0x4e,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,0x58 ),
[3] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,0x89,RSFT(0x36),0x57,LSFT(0x38),0x2f,KC_TRNS,
RSFT(0x87),LSFT(0x22),RSFT(0x89),LSFT(0x2d),RSFT(0x1e),RSFT(0x2e),
0x33,RSFT(0x87),LSFT(0x37),0x56,RSFT(0x23),0x34,TO(3),
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
0x2c,0x4c,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,RSFT(0x2f),RSFT(0x20),LSFT(0x30),LSFT(0x31),LSFT(0x24),0x56,
0x87,0x55,RSFT(0x25),RSFT(0x26),0x38,LSFT(0x1f),
TO(1),0x2e,LSFT(0x21),0x30,0x31,0x37,KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,0x58 ),
[4] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,0x2f,0x34,0x2a,KC_TRNS,KC_TRNS,
KC_TRNS,0x58,0x2c,0x29,0x33,KC_TRNS,
KC_TRNS,KC_TRNS,0x2b,0x1c,0x1b,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
0x2c,0x4c,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,M(78),0x54,M(77),KC_TRNS,KC_TRNS,
0x4c,M(76),0x87,M(75),0x39,KC_TRNS,
KC_TRNS,KC_TRNS,0x05,0x09,0x1d,KC_TRNS,KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,0x58 ),
[5] = KEYMAP(  
 0x56,0x1e,0x56,0x56,0x56,0x56,0x56,
0x2b,LSFT(0x89),0x04,0x05,0x06,LSFT(0x36),0x33,
0x39,LSFT(0x2e),0x36,0x37,0x1b,LSFT(0x2e),
0xe1,LSFT(0x23),0x07,0x08,0x09,LSFT(0x37),TO(3),
0xe4,0xe3,0xe6,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
0x2c,0x4c,0x29,
 
 0x56,0x56,0x53,0x54,0x55,0x56,LSFT(0x38),
0x34,0x55,0x5f,0x60,0x61,0x2d,0x87,
0x62,0x5c,0x5d,0x5e,0x57,M(74),
TO(1),0x56,0x59,0x5a,0x5b,0x58,0xe5,
TO(0),0x62,0x63,0x58,0x58,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,0x58 ),
[6] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
0x2b,M(59),M(58),0x57,M(57),M(56),TO(1),
M(55),M(54),M(53),M(52),M(51),M(50),
OSL(8),M(49),M(48),0x56,M(47),M(46),KC_TRNS,
0xe4,0xe3,0xe6,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,M(73),M(72),KC_TRNS,KC_TRNS,
KC_TRNS,M(71),M(70),LSFT(0x30),LSFT(0x31),M(69),KC_TRNS,
M(68),0x55,M(67),M(66),0x54,M(65),
TO(1),M(64),M(63),M(62),M(61),M(60),OSL(8),
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS ),
[7] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,0x56,M(39),M(38),0x2d,0x56,KC_TRNS,
KC_TRNS,0x20,0x34,0x15,0x23,0x1b,
KC_TRNS,0x56,M(37),M(36),0x2e,0x56,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
M(35),0x4c,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,0x56,M(45),M(44),LSFT(0x24),0x2f,KC_TRNS,
0x19,0x1d,0x15,0x27,0x0d,KC_TRNS,
KC_TRNS,0x56,M(43),M(42),RSFT(0x25),M(41),KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,M(40) ),
[8] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,M(24),M(23),M(22),M(21),0x56,KC_TRNS,
KC_TRNS,0x12,0x13,0x27,0x87,0x06,
KC_TRNS,M(20),RSFT(0x22),M(19),M(18),0x56,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
M(17),0x4c,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,0x56,M(34),M(33),M(32),0x30,KC_TRNS,
M(31),M(30),0x34,0x13,M(29),KC_TRNS,
KC_TRNS,0x56,M(28),M(27),LSFT(0x21),M(26),KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,M(25) ),
[9] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,M(14),0x36,M(13),KC_TRNS,KC_TRNS,
KC_TRNS,0x24,M(12),0x1f,0x26,0x25,
KC_TRNS,0x56,0x56,0x56,0x56,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
0x2c,0x4c,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,0x31,0x04,0x38,KC_TRNS,KC_TRNS,
0x1e,0x11,M(16),0x0f,M(15),KC_TRNS,
KC_TRNS,KC_TRNS,0x56,0x2d,0x2d,0x2d,KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,0x58 ),
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
        //DLT(3,return)
//DLT(3,return)
//DLT(3,return)
if(record->event.pressed){
uint16_t kc = DLT(3,0x58);
dlt_threshold = 120;
dlt_threshold_key_not_up = 120;
dlt_hold_decreased_by = 0;
dlt_hold_increased_by = 0;
dlt_pre_keypress_idling = 90;
process_action_delayed_lt_from_macro(kc,record);
}else{
uint16_t kc = DLT(3,0x58);
process_action_delayed_lt_from_macro(kc,record);
dlt_reset();}
        break;
    

    case 126:
        //switch
//switch
//switch
//switch
if(record->event.pressed){
            register_code(0x35);

unregister_code(0x35);
layer_move(1);

        }
        break;
    

    case 125:
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
    

    case 124:
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
    

    case 123:
        //DLT(5,k)
if(record->event.pressed){
uint16_t kc = DLT(5,0x0e);
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
    

    case 122:
        //DLT(3,Space)
//DLT(3,Space)
//DLT(3,Space)
//DLT(3,Space)
if(record->event.pressed){
uint16_t kc = DLT(3,0x2c);
dlt_threshold = 120;
dlt_threshold_key_not_up = 120;
dlt_hold_decreased_by = 0;
dlt_hold_increased_by = 0;
dlt_pre_keypress_idling = 90;
process_action_delayed_lt_from_macro(kc,record);
}else{
uint16_t kc = DLT(3,0x2c);
process_action_delayed_lt_from_macro(kc,record);
dlt_reset();}
        break;
    

    case 121:
        //`
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x2f);

unregister_code(0x2f);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 120:
        //[
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0x30);

unregister_code(0x30);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 119:
        //]
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0x31);

unregister_code(0x31);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 118:
        //(
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x25);

unregister_code(0x25);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 117:
        //)
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x26);

unregister_code(0x26);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 116:
        //re
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x33);

unregister_code(0x33);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 115:
        //xtu
if(!record->event.pressed){
if(!clt_pressed){
register_code(0xe5);
register_code(0x1d);

unregister_code(0x1d);

unregister_code(0xe5);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 114:
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
    

    case 113:
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
    

    case 112:
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
    

    case 111:
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
    

    case 110:
        //CLT7

if(record->event.pressed){
clt_layer = 7;
}
if(!process_combo_lt(OSL(7), record)){
    _send_key(clt_layer, record->event.key);
}
break;
        break;
    

    case 109:
        //CLT8
if(record->event.pressed){
clt_layer = 8;
}
if(!process_combo_lt(OSL(8), record)){
    _send_key(clt_layer, record->event.key);
}
break;
        break;
    

    case 108:
        //e
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
    

    case 107:
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
    

    case 106:
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
    

    case 105:
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
    

    case 104:
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
    

    case 103:
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
    

    case 102:
        //CLT9 ret

if(clt_pressed){
//handles a case where a midle finger key is pressed
//before thumb key.
    if(record->event.pressed){
        clt_interrupted = true;
        clt_layer2 = clt_layer;
        clt_layer = 9;
    }
}else{
    if(record->event.pressed) {clt_layer = 9;}
}
if(!process_combo_lt(0x58, record)){
//this key is released before the mindle finger key
if(clt_pressed) clt_interrupted = true;

}
break;
        break;
    

    case 101:
        //switch
//switch

//switch

        if(record->event.pressed){

            register_code(0x35);

unregister_code(0x35);
layer_move(0);

        }
        break;
    

    case 100:
        //?
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x38);

unregister_code(0x38);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 99:
        //　\　
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0x87);

unregister_code(0x87);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 98:
        //~
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x2e);

unregister_code(0x2e);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 97:
        //「
if(record->event.pressed){
            register_code(0xe1);
register_code(0x30);

unregister_code(0x30);

unregister_code(0xe1);

        }
        break;
    

    case 96:
        //」
if(record->event.pressed){
            register_code(0xe1);
register_code(0x31);

unregister_code(0x31);

unregister_code(0xe1);

        }
        break;
    

    case 95:
        //=
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x2d);

unregister_code(0x2d);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 94:
        //mo
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x10);

unregister_code(0x10);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 93:
        //ni
//ru
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
    

    case 92:
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
    

    case 91:
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
    

    case 90:
        //de
//zi
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
    

    case 89:
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
    

    case 88:
        //CLT8
//CLT7
if(record->event.pressed){
clt_layer = 8;
}

if(!process_combo_lt(OSL(8), record)){
    //Called when thumb key is pressed after this key.
    _send_key(clt_layer, record->event.key);
}
break;
        break;
    

    case 87:
        //CLT7
//CLT7
if(record->event.pressed){
clt_layer = 7;
}

if(!process_combo_lt(OSL(7), record)){
    //Called when thumb key is pressed after this key.
    _send_key(clt_layer, record->event.key);
}
break;
        break;
    

    case 86:
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
    

    case 85:
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
    

    case 84:
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
    

    case 83:
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
    

    case 82:
        //da
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x14);

unregister_code(0x14);

register_code(0x2f);

unregister_code(0x2f);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 81:
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
    

    case 80:
        //xyo
if(!record->event.pressed){
if(!clt_pressed){
register_code(0xe1);
register_code(0x26);

unregister_code(0x26);

unregister_code(0xe1);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 79:
        //CLT9 space

if(clt_pressed){
//handle case where a midle finger key is pressed
//before thumb key.
    if(record->event.pressed){
        clt_interrupted = true;
        clt_layer2 = clt_layer;
        clt_layer = 9;
    }
}else{
    if(record->event.pressed) {clt_layer = 9;}
}

if(!process_combo_lt(0x2c, record)){
//this key is released before the mindle finger key
if(clt_pressed) clt_interrupted = true;
}
break;
        break;
    



    case 78:
        //vim add ;
if(record->event.pressed){
            register_code(0x29);

unregister_code(0x29);

register_code(0xe1);
register_code(0x04);

unregister_code(0x04);

unregister_code(0xe1);

register_code(0x33);

unregister_code(0x33);

register_code(0x29);

unregister_code(0x29);

        }
        break;
    

    case 77:
        //IDE aimp
if(record->event.pressed){
            register_code(0xe6);
register_code(0x58);

unregister_code(0x58);

unregister_code(0xe6);

        }
        break;
    

    case 76:
        //IDE acomp
if(record->event.pressed){
            register_code(0xe6);
register_code(0x38);

unregister_code(0x38);

unregister_code(0xe6);

        }
        break;
    

    case 75:
        //vim ac
if(record->event.pressed){
            register_code(0xe4);
register_code(0x11);

unregister_code(0x11);

unregister_code(0xe4);

        }
        break;
    

    case 74:
        //' "
//' "
if(record->event.pressed){

if(keyboard_report->mods & (2|32)){
register_mods(2);
register_code(0x1f);
unregister_code(0x1f);
unregister_mods(2);
}else{
register_mods(2);
register_code(0x24);
unregister_code(0x24);
unregister_mods(2);
}
}
        break;
    

    case 73:
        //{
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x30);

unregister_code(0x30);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 72:
        //}
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x31);

unregister_code(0x31);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 71:
        //`
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x2f);

unregister_code(0x2f);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 70:
        //#
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x20);

unregister_code(0x20);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 69:
        //'
//'
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x24);

unregister_code(0x24);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 68:
        //backslash
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0x38);

unregister_code(0x38);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 67:
        //(
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x25);

unregister_code(0x25);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 66:
        //)
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x26);

unregister_code(0x26);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 65:
        //"
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x1f);

unregister_code(0x1f);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 64:
        //^
//^
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0x2e);

unregister_code(0x2e);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 63:
        //$
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x21);

unregister_code(0x21);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 62:
        //[
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0x30);

unregister_code(0x30);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 61:
        //]
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0x31);

unregister_code(0x31);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 60:
        //.
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0x37);

unregister_code(0x37);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 59:
        //¥
if(record->event.pressed){
            register_code(0x89);

unregister_code(0x89);

        }
        break;
    

    case 58:
        //<
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x36);

unregister_code(0x36);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 57:
        //?

if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x38);

unregister_code(0x38);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 56:
        //@
//@
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0x2f);

unregister_code(0x2f);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 55:
        //_
//_
//_
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x87);

unregister_code(0x87);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 54:
        //%
//%
//%
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x22);

unregister_code(0x22);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 53:
        //|
//|
//|
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x89);

unregister_code(0x89);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 52:
        //=
//=
//=
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x2d);

unregister_code(0x2d);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 51:
        //!
//!
//!
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe5);
register_code(0x1e);

unregister_code(0x1e);

unregister_code(0xe5);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 50:
        //~
//~
//~
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x2e);

unregister_code(0x2e);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 49:
        //_
//_
//_
//_
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x87);

unregister_code(0x87);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 48:
        //>
//>
//>
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x37);

unregister_code(0x37);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 47:
        //and
//and
//and
//&
//&ち
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x23);

unregister_code(0x23);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 46:
        //:
//:
//:
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0x34);

unregister_code(0x34);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 45:
        //pu

        if(record->event.pressed){

            register_code(0x1f);

unregister_code(0x1f);

register_code(0x30);

unregister_code(0x30);

        
        
        }
        break;
    

    case 44:
        //bu

        if(record->event.pressed){

            register_code(0x1f);

unregister_code(0x1f);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        break;
    

    case 43:
        //xo
if(record->event.pressed){
            register_code(0xe1);
register_code(0x23);

unregister_code(0x23);

unregister_code(0xe1);

        }
        break;
    

    case 42:
        //pe

        if(record->event.pressed){

            register_code(0x2e);

unregister_code(0x2e);

register_code(0x30);

unregister_code(0x30);

        
        
        }
        break;
    

    case 41:
        //pi
if(record->event.pressed){
            register_code(0x19);

unregister_code(0x19);

register_code(0x30);

unregister_code(0x30);

        }
        break;
    

    case 40:
        //CLT9 return
if(clt_pressed){
//handles a case where a midle finger key is pressed
//before thumb key.
    if(record->event.pressed){
        clt_interrupted = true;
        clt_layer2 = clt_layer;
        clt_layer = 9;
    }
}else{
    if(record->event.pressed) {clt_layer = 9;}
}
if(!process_combo_lt(0x58, record)){
//this key is released before the mindle finger key
if(clt_pressed) clt_interrupted = true;

}
break;
        break;
    

    case 39:
        //du

        if(record->event.pressed){

            register_code(0x1d);

unregister_code(0x1d);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        break;
    

    case 38:
        //bo

        if(record->event.pressed){


            register_code(0x2d);

unregister_code(0x2d);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        break;
    

    case 37:
        //go
if(record->event.pressed){
            register_code(0x05);

unregister_code(0x05);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 36:
        //ze
//ze

        if(record->event.pressed){

            register_code(0x13);

unregister_code(0x13);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        break;
    

    case 35:
        //CLT9 space
if(clt_pressed){
//handle case where a midle finger key is pressed
//before thumb key.
    if(record->event.pressed){
        clt_interrupted = true;
        clt_layer2 = clt_layer;
        clt_layer = 9;
    }
}else{
    if(record->event.pressed) {clt_layer = 9;}
}

if(!process_combo_lt(0x2c, record)){
//this key is released before the mindle finger key
if(clt_pressed) clt_interrupted = true;
}
break;
        break;
    

    case 34:
        //po

        if(record->event.pressed){

            register_code(0x2d);

unregister_code(0x2d);

register_code(0x30);

unregister_code(0x30);

        
        
        }
        break;
    

    case 33:
        //ba

        if(record->event.pressed){

            register_code(0x09);

unregister_code(0x09);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 32:
        //zu

        if(record->event.pressed){

            register_code(0x15);

unregister_code(0x15);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        break;
    

    case 31:
        //gi

        if(record->event.pressed){

            register_code(0x0a);

unregister_code(0x0a);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        break;
    

    case 30:
        //-

        if(record->event.pressed){

            register_code(0xe1);
register_code(0x89);

unregister_code(0x89);

unregister_code(0xe1);

        
        
        }
        break;
    

    case 29:
        //wo

        if(record->event.pressed){

            register_code(0xe1);
register_code(0x27);

unregister_code(0x27);

unregister_code(0xe1);

        
        
        }
        break;
    

    case 28:
        //pa
if(record->event.pressed){
            register_code(0x09);

unregister_code(0x09);

register_code(0x30);

unregister_code(0x30);

        }
        break;
    

    case 27:
        //wu
if(record->event.pressed){
            register_code(0x21);

unregister_code(0x21);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 26:
        //di

        if(record->event.pressed){
 
            register_code(0x04);

unregister_code(0x04);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        break;
    

    case 25:
        //CLT9 return
if(clt_pressed){
//handles a case where a midle finger key is pressed
//before thumb key.
    if(record->event.pressed){
        clt_interrupted = true;
        clt_layer2 = clt_layer;
        clt_layer = 9;
    }
}else{
    if(record->event.pressed) {clt_layer = 9;}
}
if(!process_combo_lt(0x58, record)){
//this key is released before the mindle finger key
if(clt_pressed) clt_interrupted = true;

}
break;
        break;
    

    case 24:
        //be

        if(record->event.pressed){

            register_code(0x2e);

unregister_code(0x2e);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        break;
    

    case 23:
        //xi

        if(record->event.pressed){

            register_code(0xe5);
register_code(0x08);

unregister_code(0x08);

unregister_code(0xe5);

        
        
        }
        break;
    

    case 22:
        //xa

        if(record->event.pressed){

            register_code(0xe5);
register_code(0x20);

unregister_code(0x20);

unregister_code(0xe5);

        
        
        }
        break;
    

    case 21:
        //do

        if(record->event.pressed){

            register_code(0x16);

unregister_code(0x16);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        break;
    

    case 20:
        //be
if(record->event.pressed){
            register_code(0x2e);

unregister_code(0x2e);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 19:
        //zo
if(record->event.pressed){
            register_code(0x06);

unregister_code(0x06);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 18:
        //za
if(record->event.pressed){
            register_code(0x1b);

unregister_code(0x1b);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 17:
        //CLT9 space
if(clt_pressed){
//handle case where a midle finger key is pressed
//before thumb key.
    if(record->event.pressed){
        clt_interrupted = true;
        clt_layer2 = clt_layer;
        clt_layer = 9;
    }
}else{
    if(record->event.pressed) {clt_layer = 9;}
}

if(!process_combo_lt(0x2c, record)){
//this key is released before the mindle finger key
if(clt_pressed) clt_interrupted = true;
}
break;
        break;
    

    case 16:
        //zi
if(record->event.pressed){
            register_code(0x07);

unregister_code(0x07);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 15:
        //gu
if(record->event.pressed){
            register_code(0x0b);

unregister_code(0x0b);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 14:
        //bi
if(record->event.pressed){
            register_code(0x19);

unregister_code(0x19);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 13:
        //?
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0xe1);
register_code(0x38);

unregister_code(0x38);

unregister_code(0xe1);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 12:
        //ge
if(record->event.pressed){
            register_code(0x34);

unregister_code(0x34);

register_code(0x2f);

unregister_code(0x2f);

        }
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

