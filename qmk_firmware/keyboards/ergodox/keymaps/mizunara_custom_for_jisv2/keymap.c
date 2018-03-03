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
 M(252),0x3a,0x3b,0x3c,0x3d,0x3e,KC_TRNS,
0x2b,M(251),0x36,LT(9, 0x37),0x13,0x1c,0x39,
LSFT(0x87),0x04,0x12, F(4), /*SFT_T(0x08),*/ DLT(4, 0x18),0x0c,
0xe1,F(3), 0x14,0x0d,M(249),0x1b,TO(3),
0xe4,0xe3,0xe6,TO(9),TO(5),
TO(5),TO(3),
KC_TRNS,
M(248),0x4c,0x29,
 
 0x2d,KC_TRNS,KC_TRNS,0x57,KC_TRNS,LALT(LSFT(0x1b)),0x87,
TO(3),0x09,0x0a,LT(9, 0x06),0x15,0x0f,0x38,
0x07,DLT(4, 0x0b),F(5), /*SFT_T(0x17),*/ 0x11,0x16,0x2d,
TO(1),0x05,0x10,0x1a,0x19,CTL_T(0x1d),0xe5,
TO(0),0x50,0x4f,0x51,0x52,
0x4b,KC_TRNS,
0x4e,
0x2b,0x2a,M(253) ),


[1] = KEYMAP(  
 M(227),M(226),M(185),M(184),M(183),M(182),M(181),
0x2b,M(243),M(231),F(1),M(237),M(235),KC_TRNS,
OSL(6),M(229),M(180),M(179),M(223),M(225),
0xe1,M(213),M(215),M(217),F(0),M(221),0x56,
0xe4,0xe3,0xe6,TO(9),TO(5),
KC_TRNS,KC_TRNS,
KC_TRNS,
M(178),0x4c,0x29,
 
 M(247),M(246),M(245),M(244),M(241),0x56,0x57,
TO(6),M(195),M(193), F(2), M(189),M(187),0x38,
M(197),M(199),M(240),M(239),M(201),OSL(6),
KC_TRNS,M(211),M(209),M(207),M(205),M(203),0xe5,
TO(0),0x50,0x4f,0x51,0x52,
0x4b,0x93,
0x4e,
0x2b,0x2a,M(238) ),
[2] = 
  KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,M(113),0x36,M(112),KC_TRNS,KC_TRNS,
KC_TRNS,0x24,M(111),0x1f,0x26,0x25,
//nokey,nokey,も,で,ょ,nokey,nokey
KC_TRNS, KC_TRNS, M(242), M(234),M(220),KC_TRNS,KC_TRNS, 
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
0x2c,0x4c,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,0x56,M(144),M(143),LSFT(0x24),0x2f,KC_TRNS,
0x19,0x1d,0x15,0x27,0x0d,KC_TRNS,
KC_TRNS,0x56,M(142),M(141),RSFT(0x25),M(140),KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,M(139) ),

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
KC_TRNS,KC_TRNS,M(177),0x54,M(176),KC_TRNS,KC_TRNS,
0x4c,M(175),0x87,M(174),0x39,KC_TRNS,
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
0x62,0x5c,0x5d,0x5e,0x57,M(173),
TO(1),0x56,0x59,0x5a,0x5b,0x58,0xe5,
TO(0),0x62,0x63,0x58,0x58,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,0x58 ),
[6] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
0x2b,M(158),M(157),0x57,M(156),M(155),TO(1),
M(154),M(153),M(152),M(151),M(150),M(149),
OSL(8),M(148),M(147),0x56,M(146),M(145),KC_TRNS,
0xe4,0xe3,0xe6,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,M(172),M(171),KC_TRNS,KC_TRNS,
KC_TRNS,M(170),M(169),LSFT(0x30),LSFT(0x31),M(168),KC_TRNS,
M(167),0x55,M(166),M(165),0x54,M(164),
TO(1),M(163),M(162),M(161),M(160),M(159),OSL(8),
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS ),
[7] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,0x56,M(138),M(137),0x2d,0x56,KC_TRNS,
KC_TRNS,0x20,0x34,0x15,0x23,0x1b,
KC_TRNS,0x56,M(136),M(135),0x2e,0x56,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
M(134),0x4c,KC_TRNS,
 

 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,0x31,0x04,0x38,KC_TRNS,KC_TRNS,
0x1e,0x11,M(115),0x0f,M(114),KC_TRNS,
//nokey,nokey,く,れ,え,nokey,nokey
KC_TRNS,KC_TRNS,M(210),M(194),M(186),KC_TRNS,KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,0x58 ),

[8] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,M(123),M(122),M(121),M(120),0x56,KC_TRNS,
KC_TRNS,0x12,0x13,0x27,0x87,0x06,
KC_TRNS,M(119),RSFT(0x22),M(118),M(117),0x56,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
M(116),0x4c,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,0x56,M(133),M(132),M(131),0x30,KC_TRNS,
M(130),M(129),0x34,0x13,M(128),KC_TRNS,
KC_TRNS,0x56,M(127),M(126),LSFT(0x21),M(125),KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,M(124) ),
[9] = KEYMAP(  
 0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,0x40,
KC_TRNS,KC_TRNS,0x8b,0x35,0x8a,0x93,KC_TRNS,
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
  
  
  
};


const uint16_t PROGMEM fn_actions[] = {
[1] = ACTION_FUNCTION_TAP(233),
[0] = ACTION_FUNCTION_TAP(219),
[2] = ACTION_FUNCTION_TAP(191),
[3] = ACTION_FUNCTION_TAP(250),// ' when tapped, ctrl when held
[4] = ACTION_FUNCTION_TAP(1), // e or OSM(KC_LSFT) on long press
[5] = ACTION_FUNCTION_TAP(2), // t or OSM(KC_RSFT) on long press
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
switch (id) {
  // e or OSM(MOD_LSFT)
  case 1:
    if(record->tap.count>0){
      if (record->event.pressed){
        register_code(0x08); //send e
        unregister_code(0x08);
      }
    }else{
      //send lshift 
      if(record->event.pressed){
        register_code(0xe1);
      }else{
        unregister_code(0xe1);
        if(IS_KEYPOS_SAME(last_keypressed,record->event.key)){
          set_oneshot_mods(MOD_LSFT);
        }
       }
     }
    return;
  // t or OSM(MOD_LSFT)
  case 2:
    if(record->tap.count>0){
      if (record->event.pressed){
        register_code(KC_T); //send t
        unregister_code(KC_T);
      }
    }else{
      //send lshift 
      if(record->event.pressed){
        register_code(0xe1);
      }else{
        unregister_code(0xe1);
        if(IS_KEYPOS_SAME(last_keypressed,record->event.key)){
          set_oneshot_mods(MOD_LSFT);
        }
       }
     }
    return;

  // equivalent of LT(9,は) for CLT receptor
  case 233:
  if(record->tap.count>0){
   process_combo_lt_receptor(record,233,M(232)); 
  }else{
    if(record->event.pressed){
      layer_on(9);// cursor arrows layer
    }else{
      layer_off(9);
    }
   }
  return;
  // equivalent of LT(9,し) for CLT receptor
  case 191:
  if(record->tap.count>0){
   process_combo_lt_receptor(record,191,M(190)); 
  }else{
    if(record->event.pressed){
      layer_on(9);// cursor arrows layer
    }else{
      layer_off(9);
    }
   }
  return;
// equivalent of LT(5,ょ) for CLT receptor
  case 219:
  /*print_val_dec(record->tap.count);*/
    if(record->tap.count>0){
     process_combo_lt_receptor(record,219,M(218)); 
    }else{
      if(record->event.pressed){
        layer_on(5);//numpad layer
      }else{
        layer_off(5);//numpadlayer
      }
    }
    return;
// equivalent of CTL_T(') 
  case 250:
    if(record->tap.count>0){
    //' "
      if(record->event.pressed){
        if((keyboard_report->mods & (2|32))|(get_oneshot_mods() & MOD_LSFT)){
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
    }else{
      // CTL_T
      if(record->event.pressed){
        register_code(KC_LCTRL);
      }else{
        unregister_code(KC_LCTRL);
      }
     }
    return;



  }
};













const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  // MACRODOWN only works in this function
      switch(id) {
        case 253:
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
case 252:
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
case 251:
// ; : 
// ; : 
if(record->event.pressed){

if(keyboard_report->mods & (2|32)){
uint8_t temp = keyboard_report->mods;
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
case 250:
// ' " 
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
case 249:
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
case 248:
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
case 247:
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
case 246:
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
case 245:
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
case 244:
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
case 241:
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
// れ

 case 194:
 if(record->event.pressed){
register_code(0x33);

unregister_code(0x33);

}
break;
 case 195:
 process_combo_lt_receptor(record,195,M(194)); break;
// っ

 case 192:
 if(!record->event.pressed){
register_code(0xe5);
register_code(0x1d);

unregister_code(0x1d);

unregister_code(0xe5);

}
break;
 case 193:
 process_combo_lt_receptor(record,193,M(192)); break;

// し
 case 190:
 if(!record->event.pressed){
register_code(0x07);
unregister_code(0x07);

}
break;
 case 191:
 process_combo_lt_receptor(record,191,M(190)); break;

// と
 case 188:
 if(!record->event.pressed){
register_code(0x16);

unregister_code(0x16);

}
break;
 case 189:
 process_combo_lt_receptor(record,189,M(188)); break;
// え

 case 186:
 if(record->event.pressed){
register_code(0x22);

unregister_code(0x22);

}
break;
 case 187:
 process_combo_lt_receptor(record,187,M(186)); break;
// き

 case 196:
 if(!record->event.pressed){
register_code(0x0a);

unregister_code(0x0a);

}
break;
 case 197:
 process_combo_lt_receptor(record,197,M(196)); break;
// ん

 case 198:
 if(!record->event.pressed){
register_code(0x1c);

unregister_code(0x1c);

}
break;
 case 199:
 process_combo_lt_receptor(record,199,M(198)); break;
case 240:
//CLT7

if(record->event.pressed){
clt_layer = 7;
}
if(!process_combo_lt(OSL(7), record)){
    _send_key(clt_layer, record->event.key);
}
break;
 break;
case 239:
//CLT8
if(record->event.pressed){
clt_layer = 8;
}
if(!process_combo_lt(OSL(8), record)){
    _send_key(clt_layer, record->event.key);
}
break;
 break;
// い

 case 200:
 if(!record->event.pressed){
register_code(0x08);

unregister_code(0x08);

}
break;
 case 201:
 process_combo_lt_receptor(record,201,M(200)); break;
// く

 case 210:
 if(record->event.pressed){
register_code(0x0b);

unregister_code(0x0b);

}
break;
 case 211:
 process_combo_lt_receptor(record,211,M(210)); break;
// う

 case 208:
 if(!record->event.pressed){
register_code(0x21);

unregister_code(0x21);

}
break;
 case 209:
 process_combo_lt_receptor(record,209,M(208)); break;
// 、

 case 206:
 if(!record->event.pressed){
register_code(0xe1);
register_code(0x36);

unregister_code(0x36);

unregister_code(0xe1);

}
break;
 case 207:
 process_combo_lt_receptor(record,207,M(206)); break;
// 。

 case 204:
 if(!record->event.pressed){
register_code(0xe1);
register_code(0x37);

unregister_code(0x37);

unregister_code(0xe1);

}
break;
 case 205:
 process_combo_lt_receptor(record,205,M(204)); break;
// の

 case 202:
 if(!record->event.pressed){
register_code(0x0e);

unregister_code(0x0e);

}
break;
 case 203:
 process_combo_lt_receptor(record,203,M(202)); break;
case 238:
//CLT9 ret

if(clt_pressed){
//handles a case where a midle finger key is pressed
//before thumb key.
    if(record->event.pressed){
        clt_interrupted = true;
        clt_layer2 = clt_layer;
        clt_layer = 2;
    }
}else{
    if(record->event.pressed) {clt_layer = 2;}
}
if(!process_combo_lt(0x58, record)){
//this key is released before the mindle finger key
if(clt_pressed) clt_interrupted = true;

}
break;
 break;
case 227:
//switch
//switch

//switch

        if(record->event.pressed){

            register_code(0x35);

unregister_code(0x35);
layer_move(0);

        }
        
 break;
case 226:
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
case 185:
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
case 184:
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
case 183:
//「
if(record->event.pressed){
            register_code(0xe1);
register_code(0x30);

unregister_code(0x30);

unregister_code(0xe1);

        }
 break;
case 182:
//」
if(record->event.pressed){
            register_code(0xe1);
register_code(0x31);

unregister_code(0x31);

unregister_code(0xe1);

        }
 break;
case 181:
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
// も

 case 242:
  if(record->event.pressed){
    register_code(0x10);
    unregister_code(0x10);
  }
  break;
 case 243:
 process_combo_lt_receptor(record,243,M(242)); break;
// に

 case 230:
 if(!record->event.pressed){
register_code(0x0c);

unregister_code(0x0c);

}
break;
 case 231:
 process_combo_lt_receptor(record,231,M(230)); break;
// は

 case 232:
 if(!record->event.pressed){
register_code(0x09);

unregister_code(0x09);

}
break;
 case 233:
 process_combo_lt_receptor(record,233,M(232)); break;
// て

 case 236:
 if(!record->event.pressed){
register_code(0x1a);

unregister_code(0x1a);

}
break;
 case 237:
 process_combo_lt_receptor(record,237,M(236)); break;

// で
 case 234:
  if(record->event.pressed){
    register_code(0x1a);
    unregister_code(0x1a);
    register_code(0x2f);
    unregister_code(0x2f);
  }
break;
 case 235:
 process_combo_lt_receptor(record,235,M(234)); break;
// か

 case 228:
 if(!record->event.pressed){
register_code(0x17);

unregister_code(0x17);

}
break;
 case 229:
 process_combo_lt_receptor(record,229,M(228)); break;
case 180:
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
case 179:
//CLT7
//CLT7
if(record->event.pressed){
clt_layer = 2;
}

if(!process_combo_lt(OSL(2), record)){
    //Called when thumb key is pressed after this key.
    _send_key(clt_layer, record->event.key);
}
break;
 break;

 case 222:
 if(!record->event.pressed){
register_code(0x18);

unregister_code(0x18);

}
break;
 case 223:
 process_combo_lt_receptor(record,223,M(222)); break;
// る

 case 224:
 if(!record->event.pressed){
register_code(0x37);

unregister_code(0x37);

}
break;
 case 225:
 process_combo_lt_receptor(record,225,M(224)); break;
// こ

 case 212:
 if(!record->event.pressed){
register_code(0x05);

unregister_code(0x05);

}
break;
 case 213:
 process_combo_lt_receptor(record,213,M(212)); break;
// が

 case 214:
 if(!record->event.pressed){
register_code(0x17);

unregister_code(0x17);

register_code(0x2f);

unregister_code(0x2f);

}
break;
 case 215:
 process_combo_lt_receptor(record,215,M(214)); break;
// だ

 case 216:
 if(!record->event.pressed){
register_code(0x14);

unregister_code(0x14);

register_code(0x2f);

unregister_code(0x2f);

}
break;
 case 217:
 process_combo_lt_receptor(record,217,M(216)); break;
// た

 case 218:
 if(!record->event.pressed){
register_code(0x14);

unregister_code(0x14);

}
break;
 case 219:
 process_combo_lt_receptor(record,219,M(218)); break;
// ょ

 case 220:
 if(record->event.pressed){
register_code(0xe1);
register_code(0x26);

unregister_code(0x26);

unregister_code(0xe1);

}
break;
 case 221:
 process_combo_lt_receptor(record,221,M(220)); break;
case 178:
//CLT9 space

if(clt_pressed){
//handle case where a midle finger key is pressed
//before thumb key.
    if(record->event.pressed){
        clt_interrupted = true;
        clt_layer2 = clt_layer;
        clt_layer = 7;
    }
}else{
    if(record->event.pressed) {clt_layer = 7;}
}

if(!process_combo_lt(0x2c, record)){
//this key is released before the mindle finger key
if(clt_pressed) clt_interrupted = true;
}
break;

 break;


case 177:
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
case 176:
//IDE aimp
if(record->event.pressed){
            register_code(0xe6);
register_code(0x58);

unregister_code(0x58);

unregister_code(0xe6);

        }
 break;
case 175:
//IDE acomp
if(record->event.pressed){
            register_code(0xe6);
register_code(0x38);

unregister_code(0x38);

unregister_code(0xe6);

        }
 break;
case 174:
//vim ac
if(record->event.pressed){
            register_code(0xe4);
register_code(0x11);

unregister_code(0x11);

unregister_code(0xe4);

        }
 break;
case 173:
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
case 172:
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
case 171:
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
case 170:
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
case 169:
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
case 168:
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
case 167:
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
case 166:
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
case 165:
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
case 164:
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
case 163:
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
case 162:
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
case 161:
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
case 160:
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
case 159:
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
case 158:
//¥
if(record->event.pressed){
            register_code(0x89);

unregister_code(0x89);

        }
 break;
case 157:
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
case 156:
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
case 155:
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
case 154:
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
case 153:
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
case 152:
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
case 151:
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
case 150:
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
case 149:
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
case 148:
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
case 147:
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
case 146:
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
case 145:
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
case 144:
//pu

        if(record->event.pressed){

            register_code(0x1f);

unregister_code(0x1f);

register_code(0x30);

unregister_code(0x30);

        
        
        }
        
 break;
case 143:
//bu

        if(record->event.pressed){

            register_code(0x1f);

unregister_code(0x1f);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        
 break;
case 142:
//xo
if(record->event.pressed){
            register_code(0xe1);
register_code(0x23);

unregister_code(0x23);

unregister_code(0xe1);

        }
 break;
case 141:
//pe

        if(record->event.pressed){

            register_code(0x2e);

unregister_code(0x2e);

register_code(0x30);

unregister_code(0x30);

        
        
        }
        
 break;
case 140:
//pi
if(record->event.pressed){
            register_code(0x19);

unregister_code(0x19);

register_code(0x30);

unregister_code(0x30);

        }
 break;
case 139:
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
case 138:
//du

        if(record->event.pressed){

            register_code(0x1d);

unregister_code(0x1d);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        
 break;
case 137:
//bo

        if(record->event.pressed){


            register_code(0x2d);

unregister_code(0x2d);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        
 break;
case 136:
//go
if(record->event.pressed){
            register_code(0x05);

unregister_code(0x05);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 135:
//ze
//ze

        if(record->event.pressed){

            register_code(0x13);

unregister_code(0x13);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        
 break;
case 134:
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
case 133:
//po

        if(record->event.pressed){

            register_code(0x2d);

unregister_code(0x2d);

register_code(0x30);

unregister_code(0x30);

        
        
        }
        
 break;
case 132:
//ba

        if(record->event.pressed){

            register_code(0x09);

unregister_code(0x09);

register_code(0x2f);

unregister_code(0x2f);

        }
        

 break;
case 131:
//zu

        if(record->event.pressed){

            register_code(0x15);

unregister_code(0x15);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        
 break;
case 130:
//gi

        if(record->event.pressed){

            register_code(0x0a);

unregister_code(0x0a);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        
 break;
case 129:
//-

        if(record->event.pressed){

            register_code(0xe1);
register_code(0x89);

unregister_code(0x89);

unregister_code(0xe1);

        
        
        }
        
 break;
case 128:
//wo

        if(record->event.pressed){

            register_code(0xe1);
register_code(0x27);

unregister_code(0x27);

unregister_code(0xe1);

        
        
        }
        
 break;
case 127:
//pa
if(record->event.pressed){
            register_code(0x09);

unregister_code(0x09);

register_code(0x30);

unregister_code(0x30);

        }
 break;
case 126:
//wu
if(record->event.pressed){
            register_code(0x21);

unregister_code(0x21);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 125:
//di

        if(record->event.pressed){
 
            register_code(0x04);

unregister_code(0x04);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        
 break;
case 124:
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
case 123:
//be

        if(record->event.pressed){

            register_code(0x2e);

unregister_code(0x2e);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        
 break;
case 122:
//xi

        if(record->event.pressed){

            register_code(0xe5);
register_code(0x08);

unregister_code(0x08);

unregister_code(0xe5);

        
        
        }
        
 break;
case 121:
//xa

        if(record->event.pressed){

            register_code(0xe5);
register_code(0x20);

unregister_code(0x20);

unregister_code(0xe5);

        
        
        }
        
 break;
case 120:
//do

        if(record->event.pressed){

            register_code(0x16);

unregister_code(0x16);

register_code(0x2f);

unregister_code(0x2f);

        
        
        }
        
 break;
case 119:
//be
if(record->event.pressed){
            register_code(0x2e);

unregister_code(0x2e);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 118:
//zo
if(record->event.pressed){
            register_code(0x06);

unregister_code(0x06);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 117:
//za
if(record->event.pressed){
            register_code(0x1b);

unregister_code(0x1b);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 116:
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
case 115:
//zi
if(record->event.pressed){
            register_code(0x07);

unregister_code(0x07);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 114:
//gu
if(record->event.pressed){
            register_code(0x0b);

unregister_code(0x0b);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 113:
//bi
if(record->event.pressed){
            register_code(0x19);

unregister_code(0x19);

register_code(0x2f);

unregister_code(0x2f);

        }
 break;
case 112:
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
case 111:
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


