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
0x56,0x1c,0x18,LT(9, 0x0c),0x12,0x13,M(190),
0x0b,0x0d,0x0e,0x0f,M(189),M(188),
TO(7),0x11,0x10,0x36,0x37,CTL_T(0x38),0xe5,
TO(0),0x50,0x4f,0x51,0x52,
0x4b,0x65,
KC_TRNS,
0x45,0x2a,LT(7, 0x58) ),
[1] = KEYMAP(  
 0x35,M(181),M(180),M(179),M(178),M(177),KC_TRNS,
0x2b,M(253),M(251),M(249),M(247),M(245),TO(1),
OSL(3),M(215),M(217),M(219),M(221),M(223),
OSL(8),M(213),M(211),M(209),M(207),M(205),0x56,
0xe4,0xe3,0xe6,TO(9),TO(3),
0x48,0x4d,
KC_TRNS,
M(176),0x4c,0x29,
 
 0x56,M(187),M(186),M(185),M(184),0x56,0x57,
0x56,M(243),M(241),M(239),M(237),M(235),M(183),
M(225),M(227),M(229),M(231),M(233),OSL(9),
TO(8),M(203),M(201),M(199),M(197),M(195),LT(8, 0x89),
TO(0),0x50,0x4f,0x51,0x52,
0x4b,0x58,
KC_TRNS,
0x8b,0x2a,M(182) ),
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
KC_TRNS,M(162),0x22,0x0f,RSFT(0x24),0x33,KC_TRNS,
KC_TRNS,RSFT(0x27),0x20,0x18,M(161),0x10,
KC_TRNS,RSFT(0x21),LSFT(0x89),0x87,0x24,RSFT(0x08),KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 KC_TRNS,0x3f,0x40,0x41,0x42,0x43,0x44,
KC_TRNS,M(175),M(174),M(173),M(172),M(171),KC_TRNS,
M(170),M(169),M(168),M(167),KC_TRNS,KC_TRNS,
KC_TRNS,M(166),M(165),M(164),M(163),0x2f,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
0x45,KC_TRNS,KC_TRNS ),
[6] = KEYMAP(  
 KC_TRNS,0x3a,0x3b,0x3c,0x3d,0x3e,KC_TRNS,
KC_TRNS,0x30,M(159),M(158),M(157),M(156),KC_TRNS,
KC_TRNS,M(155),M(154),M(153),M(152),M(151),
KC_TRNS,KC_TRNS,M(150),M(149),M(148),M(147),KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 KC_TRNS,0x3f,0x40,0x41,0x42,0x43,0x44,
KC_TRNS,0x26,0x0c,0x37,0x0d,RSFT(0x22),KC_TRNS,
0x11,0x23,0x0e,RSFT(0x26),RSFT(0x1d),KC_TRNS,
KC_TRNS,0x1e,0x25,0x31,0x27,M(160),KC_TRNS,
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
0x2b,M(133),M(132),0x57,M(131),M(130),TO(1),
M(129),M(128),M(127),M(126),M(125),M(124),
OSL(8),M(123),M(122),0x56,M(121),M(120),KC_TRNS,
0xe4,0xe3,0xe6,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,M(146),M(145),KC_TRNS,KC_TRNS,
KC_TRNS,M(144),M(143),LSFT(0x30),LSFT(0x31),M(142),KC_TRNS,
M(191),0x55,M(141),M(140),M(193),M(139),
TO(8),M(138),M(137),M(136),M(135),M(134),OSL(8),
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
        case 190:
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
case 189:
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
case 188:
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
case 187:
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
case 186:
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
case 185:
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
case 184:
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
// ら

 case 242:
 if(!record->event.pressed){
register_code(0x12);

unregister_code(0x12);

}
break;
 case 243:
 process_combo_lt_receptor(record,243,M(242)); break;
// ち

 case 240:
 if(!record->event.pressed){
register_code(0x04);

unregister_code(0x04);

}
break;
 case 241:
 process_combo_lt_receptor(record,241,M(240)); break;
// く

 case 238:
 if(!record->event.pressed){
register_code(0x0b);

unregister_code(0x0b);

}
break;
 case 239:
 process_combo_lt_receptor(record,239,M(238)); break;
// つ

 case 236:
 if(!record->event.pressed){
register_code(0x1d);

unregister_code(0x1d);

}
break;
 case 237:
 process_combo_lt_receptor(record,237,M(236)); break;
// 、

 case 234:
 if(!record->event.pressed){
register_code(0xe1);
register_code(0x36);

unregister_code(0x36);

unregister_code(0xe1);

}
break;
 case 235:
 process_combo_lt_receptor(record,235,M(234)); break;
case 183:
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
// は

 case 224:
 if(!record->event.pressed){
register_code(0x09);

unregister_code(0x09);

}
break;
 case 225:
 process_combo_lt_receptor(record,225,M(224)); break;
// と

 case 226:
 if(!record->event.pressed){
register_code(0x16);

unregister_code(0x16);

}
break;
 case 227:
 process_combo_lt_receptor(record,227,M(226)); break;
// き

 case 228:
 if(!record->event.pressed){
register_code(0x0a);

unregister_code(0x0a);

}
break;
 case 229:
 process_combo_lt_receptor(record,229,M(228)); break;
// い

 case 230:
 if(!record->event.pressed){
register_code(0x08);

unregister_code(0x08);

}
break;
 case 231:
 process_combo_lt_receptor(record,231,M(230)); break;
// ん

 case 232:
 if(!record->event.pressed){
register_code(0x1c);

unregister_code(0x1c);

}
break;
 case 233:
 process_combo_lt_receptor(record,233,M(232)); break;
// め

 case 202:
 if(!record->event.pressed){
register_code(0x38);

unregister_code(0x38);

}
break;
 case 203:
 process_combo_lt_receptor(record,203,M(202)); break;
// そ

 case 200:
 if(!record->event.pressed){
register_code(0x06);

unregister_code(0x06);

}
break;
 case 201:
 process_combo_lt_receptor(record,201,M(200)); break;
// ね

 case 198:
 if(!record->event.pressed){
register_code(0x36);

unregister_code(0x36);

}
break;
 case 199:
 process_combo_lt_receptor(record,199,M(198)); break;
// ほ

 case 196:
 if(!record->event.pressed){
register_code(0x2d);

unregister_code(0x2d);

}
break;
 case 197:
 process_combo_lt_receptor(record,197,M(196)); break;
// ・

 case 194:
 if(!record->event.pressed){
register_code(0xe1);
register_code(0x38);

unregister_code(0x38);

unregister_code(0xe1);

}
break;
 case 195:
 process_combo_lt_receptor(record,195,M(194)); break;
case 182:
//clt(5,ret)
clt_layer = 5;
process_combo_lt(0x58, record);
break;
 break;
case 181:
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
case 180:
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
case 179:
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
case 178:
//「
if(record->event.pressed){
            register_code(0xe1);
register_code(0x30);

unregister_code(0x30);

unregister_code(0xe1);

        }
 break;
case 177:
//」
if(record->event.pressed){
            register_code(0xe1);
register_code(0x31);

unregister_code(0x31);

unregister_code(0xe1);

        }
 break;
// 。

 case 252:
 if(!record->event.pressed){
register_code(0xe1);
register_code(0x37);

unregister_code(0x37);

unregister_code(0xe1);

}
break;
 case 253:
 process_combo_lt_receptor(record,253,M(252)); break;
// か

 case 250:
 if(!record->event.pressed){
register_code(0x17);

unregister_code(0x17);

}
break;
 case 251:
 process_combo_lt_receptor(record,251,M(250)); break;
// た

 case 248:
 if(!record->event.pressed){
register_code(0x14);

unregister_code(0x14);

}
break;
 case 249:
 process_combo_lt_receptor(record,249,M(248)); break;
// こ

 case 246:
 if(!record->event.pressed){
register_code(0x05);

unregister_code(0x05);

}
break;
 case 247:
 process_combo_lt_receptor(record,247,M(246)); break;
// さ

 case 244:
 if(!record->event.pressed){
register_code(0x1b);

unregister_code(0x1b);

}
break;
 case 245:
 process_combo_lt_receptor(record,245,M(244)); break;
// う

 case 214:
 if(!record->event.pressed){
register_code(0x21);

unregister_code(0x21);

}
break;
 case 215:
 process_combo_lt_receptor(record,215,M(214)); break;
// し

 case 216:
 if(!record->event.pressed){
register_code(0x07);

unregister_code(0x07);

}
break;
 case 217:
 process_combo_lt_receptor(record,217,M(216)); break;
// て

 case 218:
 if(!record->event.pressed){
register_code(0x1a);

unregister_code(0x1a);

}
break;
 case 219:
 process_combo_lt_receptor(record,219,M(218)); break;
// け

 case 220:
 if(!record->event.pressed){
register_code(0x34);

unregister_code(0x34);

}
break;
 case 221:
 process_combo_lt_receptor(record,221,M(220)); break;
// せ

 case 222:
 if(!record->event.pressed){
register_code(0x13);

unregister_code(0x13);

}
break;
 case 223:
 process_combo_lt_receptor(record,223,M(222)); break;
// .

 case 212:
 if(!record->event.pressed){
register_code(0x39);

unregister_code(0x39);

register_code(0x37);

unregister_code(0x37);

register_code(0x39);

unregister_code(0x39);

}
break;
 case 213:
 process_combo_lt_receptor(record,213,M(212)); break;
// ひ

 case 210:
 if(!record->event.pressed){
register_code(0x19);

unregister_code(0x19);

}
break;
 case 211:
 process_combo_lt_receptor(record,211,M(210)); break;
// す

 case 208:
 if(!record->event.pressed){
register_code(0x15);

unregister_code(0x15);

}
break;
 case 209:
 process_combo_lt_receptor(record,209,M(208)); break;
// ふ

 case 206:
 if(!record->event.pressed){
register_code(0x1f);

unregister_code(0x1f);

}
break;
 case 207:
 process_combo_lt_receptor(record,207,M(206)); break;
// へ

 case 204:
 if(!record->event.pressed){
register_code(0x2e);

unregister_code(0x2e);

}
break;
 case 205:
 process_combo_lt_receptor(record,205,M(204)); break;
case 176:
//clt(6,space)
clt_layer = 6;
process_combo_lt(0x2c, record);
break;
 break;



case 175:
//ぱ
if(record->event.pressed){
            register_code(0x09);

unregister_code(0x09);

register_code(0x30);

unregister_code(0x30);

        }
 break;
case 174:
//ぢ
if(record->event.pressed){
            register_code(0x04);

unregister_code(0x04);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 173:
//ぐ
if(record->event.pressed){
            register_code(0x0b);

unregister_code(0x0b);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 172:
//づ
if(record->event.pressed){
            register_code(0x1d);

unregister_code(0x1d);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 171:
//ぴ
if(record->event.pressed){
            register_code(0x19);

unregister_code(0x19);

register_code(0x30);

unregister_code(0x30);

        }
 break;
case 170:
//ば
if(record->event.pressed){
            register_code(0x09);

unregister_code(0x09);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 169:
//ど
if(record->event.pressed){
            register_code(0x16);

unregister_code(0x16);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 168:
//ぎ
if(record->event.pressed){
            register_code(0x0a);

unregister_code(0x0a);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 167:
//ぽ
if(record->event.pressed){
            register_code(0x2d);

unregister_code(0x2d);

register_code(0x30);

unregister_code(0x30);

        }
 break;
case 166:
//ぷ
if(record->event.pressed){
            register_code(0x1f);

unregister_code(0x1f);

register_code(0x30);

unregister_code(0x30);

        }
 break;
case 165:
//ぞ
if(record->event.pressed){
            register_code(0x06);

unregister_code(0x06);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 164:
//ぺ
if(record->event.pressed){
            register_code(0x2e);

unregister_code(0x2e);

register_code(0x30);

unregister_code(0x30);

        }
 break;
case 163:
//ぼ
if(record->event.pressed){
            register_code(0x2d);

unregister_code(0x2d);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 162:
//ぁ
if(record->event.pressed){
            register_code(0xe5);
register_code(0x20);

unregister_code(0x20);

unregister_code(0xe5);

        }
 break;
case 161:
//ゅ
if(record->event.pressed){
            register_code(0xe1);
register_code(0x25);

unregister_code(0x25);

unregister_code(0xe1);

        }
 break;
case 160:
//ぉ
if(record->event.pressed){
            register_code(0xe5);
register_code(0x23);

unregister_code(0x23);

unregister_code(0xe5);

        }
 break;
case 159:
//が
if(record->event.pressed){
            register_code(0x17);

unregister_code(0x17);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 158:
//だ
if(record->event.pressed){
            register_code(0x14);

unregister_code(0x14);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 157:
//ご
if(record->event.pressed){
            register_code(0x05);

unregister_code(0x05);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 156:
//ざ
if(record->event.pressed){
            register_code(0x1b);

unregister_code(0x1b);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 155:
//ヴ
if(record->event.pressed){
            register_code(0x21);

unregister_code(0x21);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 154:
//じ
if(record->event.pressed){
            register_code(0x07);

unregister_code(0x07);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 153:
//で
if(record->event.pressed){
            register_code(0x1a);

unregister_code(0x1a);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 152:
//げ
if(record->event.pressed){
            register_code(0x34);

unregister_code(0x34);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 151:
//ぜ
if(record->event.pressed){
            register_code(0x13);

unregister_code(0x13);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 150:
//び
if(record->event.pressed){
            register_code(0x19);

unregister_code(0x19);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 149:
//ず
if(record->event.pressed){
            register_code(0x15);

unregister_code(0x15);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 148:
//ぶ
if(record->event.pressed){
            register_code(0x1f);

unregister_code(0x1f);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 147:
//べ
if(record->event.pressed){
            register_code(0x2e);

unregister_code(0x2e);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;

case 146:
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
case 145:
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
case 144:
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
case 143:
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
case 142:
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
// backslash
case 191:
            
            if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0x87);

unregister_code(0x87);

register_code(0x39);

unregister_code(0x39);

        }
            break
;
case 141:
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
case 140:
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
// /
case 193:
            
            if(record->event.pressed){
            register_code(0x39);

unregister_code(0x39);

register_code(0x38);

unregister_code(0x38);

register_code(0x39);

unregister_code(0x39);

        }
            break
;
case 139:
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
case 138:
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
case 137:
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
case 136:
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
case 135:
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
case 134:
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
case 133:
//¥
if(record->event.pressed){
            register_code(0x89);

unregister_code(0x89);

        }
 break;
case 132:
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
case 131:
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
case 130:
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
case 129:
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
case 128:
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
case 127:
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
case 126:
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
case 125:
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
case 124:
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
case 123:
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
case 122:
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
case 121:
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
case 120:
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

