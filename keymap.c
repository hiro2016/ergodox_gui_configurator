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
 0x35,LSFT(0x1e),LSFT(0x2f),RSFT(0x20),LSFT(0x21),RSFT(0x22),LSFT(0x2f),
0x2b,0x14,0x1a,0x08,0x15,0x17,TO(1),
0x39,0x04,0x16,0x07,0x09,0x0a,
0xe1,CTL_T(0x1d),0x1b,0x06,DLT(3, 0x19),0x05,0x56,
0xe4,0xe3,0xe6,TO(9),TO(3),
0x48,0x4d,
KC_TRNS,
LT(7, 0x2c),0x4c,0x29,
 
 LSFT(0x2d),RSFT(0x2e),RSFT(0x23),RSFT(0x55),RSFT(0x25),LSFT(0x26),LSFT(0x87),
0x56,0x1c,0x18,LT(9, 0x0c),0x12,0x13,M(127),
0x0b,0x0d,0x0e,0x0f,M(126),M(125),
TO(7),0x11,0x10,0x36,0x37,CTL_T(0x38),0xe5,
TO(0),0x50,0x4f,0x51,0x52,
0x4b,0x65,
KC_TRNS,
0x45,0x2a,LT(7, 0x58) ),
[1] = KEYMAP(  
 0x35,M(103),M(102),M(101),M(100),M(99),KC_TRNS,
0x2b,M(98),M(97),M(96),M(95),M(94),TO(1),
OSL(3),M(93),M(92),M(91),M(90),M(89),
OSL(8),M(88),M(87),M(86),M(85),M(84),0x56,
0xe4,0xe3,0xe6,TO(9),TO(3),
0x48,0x4d,
KC_TRNS,
M(83),0x4c,0x29,
 
 0x56,M(124),M(123),M(122),M(121),0x56,0x57,
0x56,M(120),M(119),M(118),M(117),M(116),M(115),
M(114),M(113),M(112),M(111),M(110),OSL(9),
TO(8),M(109),M(108),M(107),M(106),M(105),LT(8, 0x89),
TO(0),0x50,0x4f,0x51,0x52,
0x4b,0x58,
KC_TRNS,
0x8b,0x2a,M(104) ),
[2] = KEYMAP(  
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
[3] = KEYMAP(  
 0x56,0x1e,0x56,0x56,0x56,0x56,0x56,
0x2b,LSFT(0x89),0x04,0x05,0x06,LSFT(0x36),TO(2),
OSL(3),0x2e,0x36,0x37,0x1b,LSFT(0x2e),
0x33,LSFT(0x23),0x07,0x08,0x09,LSFT(0x37),0x56,
0xe4,0xe3,0xe6,TO(9),TO(3),
0x48,0x4d,
KC_TRNS,
LT(7, 0x2c),0x4c,0x29,
 
 0x56,0x56,0x53,0x54,0x55,0x56,LSFT(0x38),
TO(1),0x55,0x5f,0x60,0x61,LSFT(0x2d),0x87,
0x62,0x5c,0x5d,0x5e,0x57,RSFT(0x1f),
TO(7),0x56,0x59,0x5a,0x5b,0x58,0x34,
TO(0),0x62,0x63,0x58,0x58,
0x4b,0x65,
KC_TRNS,
0x45,0x2a,LT(7, 0x58) ),
[4] = KEYMAP(  
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
[5] = KEYMAP(  
 KC_TRNS,0x3a,0x3b,0x3c,0x3d,0x3e,KC_TRNS,
KC_TRNS,M(69),0x22,0x0f,RSFT(0x24),0x33,KC_TRNS,
KC_TRNS,RSFT(0x27),0x20,0x18,M(68),0x10,
KC_TRNS,RSFT(0x21),LSFT(0x89),0x87,0x24,RSFT(0x08),KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 KC_TRNS,0x3f,0x40,0x41,0x42,0x43,0x44,
KC_TRNS,M(82),M(81),M(80),M(79),M(78),KC_TRNS,
M(77),M(76),M(75),M(74),KC_TRNS,KC_TRNS,
KC_TRNS,M(73),M(72),M(71),M(70),0x2f,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
0x45,KC_TRNS,KC_TRNS ),
[6] = KEYMAP(  
 KC_TRNS,0x3a,0x3b,0x3c,0x3d,0x3e,KC_TRNS,
KC_TRNS,0x30,M(66),M(65),M(64),M(63),KC_TRNS,
KC_TRNS,M(62),M(61),M(60),M(59),M(58),
KC_TRNS,KC_TRNS,M(57),M(56),M(55),M(54),KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 KC_TRNS,0x3f,0x40,0x41,0x42,0x43,0x44,
KC_TRNS,0x26,0x0c,0x37,0x0d,RSFT(0x22),KC_TRNS,
0x11,0x23,0x0e,RSFT(0x26),RSFT(0x1d),KC_TRNS,
KC_TRNS,0x1e,0x25,0x31,0x27,M(67),KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
0x45,KC_TRNS,KC_TRNS ),
[7] = KEYMAP(  
 KC_TRNS,0x1e,0x1f,0x20,0x21,0x22,RSFT(0x2e),
KC_TRNS,0x89,RSFT(0x36),0x57,LSFT(0x38),0x2f,KC_TRNS,
RSFT(0x87),LSFT(0x22),RSFT(0x89),LSFT(0x2d),RSFT(0x1e),RSFT(0x2e),
KC_TRNS,RSFT(0x87),LSFT(0x37),0x56,RSFT(0x23),0x34,TO(3),
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
0x2b,M(39),M(38),0x57,M(37),M(36),TO(1),
M(35),M(34),M(33),M(32),M(31),M(30),
OSL(8),M(29),M(28),0x56,M(27),M(26),KC_TRNS,
0xe4,0xe3,0xe6,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,M(53),M(52),KC_TRNS,KC_TRNS,
KC_TRNS,M(51),M(50),LSFT(0x30),LSFT(0x31),M(49),KC_TRNS,
M(48),0x55,M(47),M(46),0x54,M(45),
TO(8),M(44),M(43),M(42),M(41),M(40),OSL(8),
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
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
        //\ |
//\ |

if(record->event.pressed){

if(keyboard_report->mods & (2|32)){
//shift key being pressed down
register_code(0x89);
unregister_code(0x89);
}else{
register_code(0x87);
unregister_code(0x87);
}
}
        break;
    

    case 126:
        //; :

if(record->event.pressed){
print_val_dec(keyboard_report->mods);
if(keyboard_report->mods &(2|32)){
uint8_t temp = keyboard_report->mods & (2|32); 
//clear_mods();
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
        //' "
//' "
if(record->event.pressed){
//print_val_dec(keyboard_report->mods);
if(keyboard_report->mods & (2|32)){
register_code(0x1f);
unregister_code(0x1f);
}else{
register_mods(2);
register_code(0x24);
unregister_code(0x24);
clear_keyboard();
unregister_mods(2);
}
}
        break;
    

    case 124:
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
    

    case 123:
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
    

    case 122:
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
    

    case 121:
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
    

    case 120:
        //ら
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
    

    case 119:
        //ち
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x04);

unregister_code(0x04);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 118:
        //く
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
    

    case 117:
        //つ
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
    

    case 116:
        //、
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
    

    case 115:
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
    

    case 114:
        //は
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
    

    case 113:
        //と
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
        //き
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
        //い
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
    

    case 110:
        //ん
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
    

    case 109:
        //め
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x38);

unregister_code(0x38);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 108:
        //そ
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x06);

unregister_code(0x06);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 107:
        //ね
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x36);

unregister_code(0x36);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 106:
        //ほ
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x2d);

unregister_code(0x2d);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 105:
        //・
if(!record->event.pressed){
if(!clt_pressed){
register_code(0xe5);
register_code(0x38);

unregister_code(0x38);

unregister_code(0xe5);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 104:
        //clt(5,ret)
clt_layer = 5;
process_combo_lt(0x58, record);
break;
        break;
    

    case 103:
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
    

    case 102:
        ///
if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0x38);

unregister_code(0x38);

register_code(0x39);

unregister_code(0x39);

        }
        break;
    

    case 101:
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
    

    case 100:
        //「
if(record->event.pressed){
            register_code(0xe1);
register_code(0x30);

unregister_code(0x30);

unregister_code(0xe1);

        }
        break;
    

    case 99:
        //」
if(record->event.pressed){
            register_code(0xe1);
register_code(0x31);

unregister_code(0x31);

unregister_code(0xe1);

        }
        break;
    

    case 98:
        //。
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
    

    case 97:
        //か
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
    

    case 96:
        //た
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
    

    case 95:
        //こ
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
    

    case 94:
        //さ
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x1b);

unregister_code(0x1b);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 93:
        //う
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
    

    case 92:
        //し
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
    

    case 91:
        //て
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
        //け
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x34);

unregister_code(0x34);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 89:
        //せ
//undefined
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x13);

unregister_code(0x13);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 88:
        //.
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x39);

unregister_code(0x39);

register_code(0x37);

unregister_code(0x37);

register_code(0x39);

unregister_code(0x39);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 87:
        //ひ
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x19);

unregister_code(0x19);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 86:
        //す
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
    

    case 85:
        //ふ
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x1f);

unregister_code(0x1f);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 84:
        //へ
if(!record->event.pressed){
if(!clt_pressed){
register_code(0x2e);

unregister_code(0x2e);

}else{
_send_key(clt_layer,record->event.key);
clt_pressed = false;
}
}
break;
        break;
    

    case 83:
        //clt(6,space)
clt_layer = 6;
process_combo_lt(0x2c, record);
break;
        break;
    




    case 82:
        //ぱ
if(record->event.pressed){
            register_code(0x09);

unregister_code(0x09);

register_code(0x30);

unregister_code(0x30);

        }
        break;
    

    case 81:
        //ぢ
if(record->event.pressed){
            register_code(0x04);

unregister_code(0x04);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 80:
        //ぐ
if(record->event.pressed){
            register_code(0x0b);

unregister_code(0x0b);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 79:
        //づ
if(record->event.pressed){
            register_code(0x1d);

unregister_code(0x1d);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 78:
        //ぴ
if(record->event.pressed){
            register_code(0x19);

unregister_code(0x19);

register_code(0x30);

unregister_code(0x30);

        }
        break;
    

    case 77:
        //ば
if(record->event.pressed){
            register_code(0x09);

unregister_code(0x09);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 76:
        //ど
if(record->event.pressed){
            register_code(0x16);

unregister_code(0x16);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 75:
        //ぎ
if(record->event.pressed){
            register_code(0x0a);

unregister_code(0x0a);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 74:
        //ぽ
if(record->event.pressed){
            register_code(0x2d);

unregister_code(0x2d);

register_code(0x30);

unregister_code(0x30);

        }
        break;
    

    case 73:
        //ぷ
if(record->event.pressed){
            register_code(0x1f);

unregister_code(0x1f);

register_code(0x30);

unregister_code(0x30);

        }
        break;
    

    case 72:
        //ぞ
if(record->event.pressed){
            register_code(0x06);

unregister_code(0x06);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 71:
        //ぺ
if(record->event.pressed){
            register_code(0x2e);

unregister_code(0x2e);

register_code(0x30);

unregister_code(0x30);

        }
        break;
    

    case 70:
        //ぼ
if(record->event.pressed){
            register_code(0x2d);

unregister_code(0x2d);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 69:
        //ぁ
if(record->event.pressed){
            register_code(0xe5);
register_code(0x20);

unregister_code(0x20);

unregister_code(0xe5);

        }
        break;
    

    case 68:
        //ゅ
if(record->event.pressed){
            register_code(0xe1);
register_code(0x25);

unregister_code(0x25);

unregister_code(0xe1);

        }
        break;
    

    case 67:
        //ぉ
if(record->event.pressed){
            register_code(0xe5);
register_code(0x23);

unregister_code(0x23);

unregister_code(0xe5);

        }
        break;
    

    case 66:
        //が
if(record->event.pressed){
            register_code(0x17);

unregister_code(0x17);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 65:
        //だ
if(record->event.pressed){
            register_code(0x14);

unregister_code(0x14);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 64:
        //ご
if(record->event.pressed){
            register_code(0x05);

unregister_code(0x05);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 63:
        //ざ
if(record->event.pressed){
            register_code(0x1b);

unregister_code(0x1b);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 62:
        //ヴ
if(record->event.pressed){
            register_code(0x21);

unregister_code(0x21);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 61:
        //じ
if(record->event.pressed){
            register_code(0x07);

unregister_code(0x07);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 60:
        //で
if(record->event.pressed){
            register_code(0x1a);

unregister_code(0x1a);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 59:
        //げ
if(record->event.pressed){
            register_code(0x34);

unregister_code(0x34);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 58:
        //ぜ
if(record->event.pressed){
            register_code(0x13);

unregister_code(0x13);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 57:
        //び
if(record->event.pressed){
            register_code(0x19);

unregister_code(0x19);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 56:
        //ず
if(record->event.pressed){
            register_code(0x15);

unregister_code(0x15);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 55:
        //ぶ
if(record->event.pressed){
            register_code(0x1f);

unregister_code(0x1f);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    

    case 54:
        //べ
if(record->event.pressed){
            register_code(0x2e);

unregister_code(0x2e);

register_code(0x2f);

unregister_code(0x2f);

        }
        break;
    


    case 53:
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
    

    case 52:
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
    

    case 51:
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
    

    case 50:
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
    

    case 49:
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
    

    case 48:
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
    

    case 47:
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
    

    case 46:
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
    

    case 45:
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
    

    case 44:
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
    

    case 43:
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
    

    case 42:
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
    

    case 41:
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
    

    case 40:
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
    

    case 39:
        //¥
if(record->event.pressed){
            register_code(0x89);

unregister_code(0x89);

        }
        break;
    

    case 38:
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
    

    case 37:
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
    

    case 36:
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
    

    case 35:
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
    

    case 34:
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
    

    case 33:
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
    

    case 32:
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
    

    case 31:
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
    

    case 30:
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
    

    case 29:
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
    

    case 28:
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
    

    case 27:
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
    

    case 26:
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

