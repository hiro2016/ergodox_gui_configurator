#include "ergodox.h"
/*#include "debug.h"*/
//#include "debug.h"
////#include "action_layer.h"
//#include "version.h"
#include "delayed_lt.c"
#include "delayed_lt_macro_support.c"
#include "combo_lt.c"


#define BASE 0 // default layer
#define SYMB 1 // symbols #define MDIA 2 // media keys

// macro and custom function definitions for Japanese Language input
//muzunara base layer left top row
#define JP_MO M(243)
#define JP_NI M(231)
#define JP_HA F(1)
#define JP_TE M(237)
#define JP_DE M(235)

//muzunara base layer right top row

#define JP_RE M(195)
#define JP_XTU M(193)
#define JP_SI F(2)
#define JP_TO M(189)
#define JP_E M(187)


//muzunara base layer left home row
#define JP_KA M(229)
#define JP_LEFT_RING_MIZUNARA M(180)
#define JP_LEFT_MIDDLE_MIZUNARA M(179)
#define JP_NA M(223)
#define JP_RU M(225)

//muzunara base layer right home row

#define JP_KI M(197)
#define JP_NN M(199)
#define JP_RIGHT_MIDDLE_MIZUNARA M(240)
#define JP_RIGHT_RING_MIZUNARA M(239)
#define JP_I M(201)

//muzunara base layer left bottum row

#define JP_KO M(213)
#define JP_GA M(215)
#define JP_DA M(217)
#define JP_TA F(0)
#define JP_XYO M(221)

//muzunara base layer right bottum row
#define JP_KU M(211)
#define JP_U M(209)
#define JP_COMMA M(207) 
#define JP_PERIOD M(205)
#define JP_NO M(203)

// muzunara right thumb layer left top row
// びね?
#define JP_BI M(113)
#define JP_NE 0x36
#define JP_QUESTION M(112)

// muzunara right thumb layer right top row
//-ぷぶゃ゛
#define JP_PU M(144)
#define JP_BU M(143)
#define JP_XYA LSFT(0x24)
#define JP_DATEN 0x2f

// muzunara right thumb layer left home row
// やげふよゆ

#define JP_YA 0x24
#define JP_GE M(111)
#define JP_FU 0x1f
#define JP_YO 0x26
#define JP_YU 0x25

// muzunara right thumb layer right home row
// ひつすわま
// 0x19,0x1d,0x15,0x27,0x0d,KC_TRNS,
#define JP_HI 0x19
#define JP_TU 0x1d
#define JP_SU 0x15
#define JP_WA 0x27
#define JP_MA 0x0d

// muzunara right thumb layer left bottom row
// もでょ already defined on base layer


// muzunara right thumb layer rigt bottom row
// -ぉぺゅぴ
#define JP_XO M(142)
#define JP_PE M(141)
#define JP_XYU RSFT(0x25)
#define JP_PI M(140)



// muzunara left thumb layer(7) left top row
// -づぼほ-
#define JP_DU M(138)
#define JP_BO M(137)
#define JP_HO 0x2d

// muzunara left thumb layer(7) right top row
// むちめ

#define JP_MU 0x31
#define JP_TI 0x04
#define JP_ME 0x38

// muzunara left thumb layer(7) left home row
// あけすおさ
// KC_TRNS,0x20,0x34,0x15,0x23,0x1b,
#define JP_A 0x20
#define JP_KE 0x34
#define JP_SU 0x15
#define JP_O 0x23
#define JP_SA 0x1b


// muzunara left thumb layer(7) right home row
// ぬみじりぐ
#define JP_NU 0x1e
#define JP_MI 0x11
#define JP_ZI M(115)
#define JP_RI 0x0f
#define JP_GU M(114)

// muzunara left thumb layer(7) left bottom row
// ごぜへ
#define JP_GO M(136)
#define JP_ZE M(135)
#define JP_HE 0x2e


// muzunara left thumb layer(7) right bottom row
// くれえ already defined


// muzunara left ring finger layer(8) left top row
// べぃぁど-
/*KC_TRNS,M(123),M(122),M(121),M(120),0x56,KC_TRNS,*/
#define JP_XI M(122)
#define JP_XA M(121)
#define JP_DO M(120)

// muzunara left ring finger layer(8) right top row
// ぽばず
#define JP_PO M(133)
#define JP_BA M(132)
#define JP_ZU M(131)
#define JP_MARU 0x30


// muzunara left ring finger layer(8) left home row
// らせわろそ
// KC_TRNS,0x12,0x13,0x27,0x87,0x06,
#define JP_RA 0x12
#define JP_SE 0x13
#define JP_WA 0x27
#define JP_RO 0x87
#define JP_SO 0x06

// muzunara left ring finger layer(8) right home row
// ぎーけせを  
#define JP_GI M(130)
#define JP_YOKOBOU M(129)
#define JP_KE 0x34 
#define JP_SE 0x13 
#define JP_WO M(128) 

// muzunara left ring finger layer(8) left bottom row
// べぇぞざ-
#define JP_BE M(119)
#define JP_XE RSFT(0x22)
#define JP_ZO M(118)
#define JP_ZA M(117)

// muzunara left ring finger layer(8) right bottom row
// ぱヴぅぢ
#define JP_PA M(127)
#define JP_VU M(126)
#define JP_XU LSFT(0x21)
#define JP_DI M(125)

// JIS KANA symbols(layer6)
// top most
#define JP_CURLY_BRACKET_OPEN M(172)
#define JP_CURLY_BRACKET_CLOSE M(171)
//top row
#define JP_YEN M(158)
#define JP_LESS M(157)
#define JP_PLUS 0x57
// already definede #define JP_QUESTION M(156)
#define JP_AT M(155)
#define JP_BACKTICK M(170)
#define JP_SHARP M(169)
#define JP_KAGIKAKKO_OPEN LSFT(0x30)
#define JP_KAGIKAKKO_CLOSE LSFT(0x31)
#define JP_SINGLE_QUOTE M(168)

//home row
#define JP_UNDERLINE M(154)
#define JP_PERCENTAGE M(153)
#define JP_PIPE M(152)
#define JP_EQUAL M(151)
#define JP_EXCLAMATION M(150)
#define JP_TILD M(149)

#define JP_BACKSLASH M(167)
#define JP_ASTERISK 0x55
#define JP_PARENTHESE_OPEN M(166)
#define JP_PARENTHESE_CLOSE M(165)
#define JP_SLASH 0x54
#define JP_DOUBLEQUOTE M(164)

//bottom  
// #define JP_UNDERLINE M(154) already defined
#define JP_GREATER M(147)
#define JP_MINUS 0x56
#define JP_AND M(146)
#define JP_COLON M(148) // does not work, 145 is for none japanese kana

//^$[].
#define JP_CARET M(163)
#define JP_DOLLAR M(162)
#define JP_SQUARE_BRACKET_OPEN M(161)
#define JP_SQUARE_BRACKET_CLOSE M(160)
#define JP_DOT M(159)


// JIS symbols(layer3)  
// top row
#define JIS_YEN 0x89
#define JIS_LESS RSFT(0x36) 
#define JIS_PLUS 0x57 
#define JIS_QUESTION LSFT(0x38) 
#define JIS_AT 0x2f 

#define JIS_BACKTICK RSFT(0x2f)
#define JIS_SHARP RSFT(0x20) 
#define JIS_CURLY_BRACE_OPEN RSFT(0x30) 
#define JIS_CURLY_BRACE_CLOSE RSFT(0x31) 
#define JIS_QUOTE LSFT(0x24)

//home row
//_%|=!~\*()/"
#define JIS_UNDERLINE RSFT(0x87)
#define JIS_PERCENTAGE LSFT(0x22)
#define JIS_PIPE RSFT(0x89)
#define JIS_EQUAL LSFT(0x2d)
#define JIS_EXCLAMATION RSFT(0x1e)
#define JIS_TILD RSFT(0x2e)

#define JIS_BACSLASH 0x87
#define JIS_ASTERISK 0x55
#define JIS_PARENTHES_OPEN RSFT(0x25)
#define JIS_PARENTHES_CLOSE RSFT(0x26)
#define JIS_SLASH 0x38
#define JIS_DOUBLE_QUOTE LSFT(0x1f)

// bottom row
#define JIS_SEMI_COLON 0x33
//#define JIS_UNDERLINE
#define JIS_GREATER LSFT(0x37)
#define JIS_MINUS 0x56
#define JIS_AND RSFT(0x23)
#define JIS_COLON 0x34

//^$[].
#define JIS_CARET 0x2e
#define JIS_DOLLAR LSFT(0x21)
#define JIS_SQUARE_BRACKET_OPEN 0x30
#define JIS_SQUARE_BRACKET_CLOSE 0x31
#define JIS_PERIOD 0x37

// extra
#define JIS_COMMA KC_COMM
#define JIS_SINGLE_OR_DOUBLE_QUOTE_OR_CTRL F(3)
#define ECLIPSE_EXECUTE LALT(LSFT(0x1b))
#define DLT4_U M(247)
#define DLT4_H M(246)

// layer 5
#define JIS_DLT_K M(249) 
#define JIS_E_OR_SHIFT F(4) 
#define JIS_T_OR_SHIFT F(5) 
#define JIS_SEMI_COLON_AND_COLON M(251) 


 

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = KEYMAP(  
 M(252),KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,KC_TRNS,
KC_TAB,JIS_SEMI_COLON_AND_COLON,JIS_COMMA,LT(10, JIS_PERIOD),KC_P,KC_Y,KC_CAPSLOCK,
JIS_UNDERLINE,KC_A,KC_O, JIS_E_OR_SHIFT, DLT4_U,KC_I,
KC_LSHIFT,JIS_SINGLE_OR_DOUBLE_QUOTE_OR_CTRL, KC_Q,KC_J,JIS_DLT_K,KC_X,TO(3),
KC_LCTRL,KC_LGUI,KC_LALT,TO(10),TO(5),
TO(5),TO(3),
KC_TRNS,
M(248),0x4c,0x29,
 
 JIS_MINUS,KC_TRNS,KC_TRNS,JIS_PLUS,KC_TRNS,ECLIPSE_EXECUTE,JIS_BACSLASH,
TO(3),KC_F,KC_G,LT(10, KC_C),KC_R,KC_L,JIS_SLASH,
KC_D,DLT4_H,JIS_T_OR_SHIFT, KC_N,KC_S,JIS_MINUS,
TO(1),KC_B,KC_M,KC_W,KC_V,CTL_T(KC_Z),KC_RSHIFT,
TO(0),KC_LEFT,KC_RIGHT,KC_DOWN,KC_UP,
0x4b,KC_TRNS,
0x4e,
KC_TAB,0x2a,M(253) ),


[1] = KEYMAP(  
 M(227),M(226),M(185),M(184),M(183),M(182),M(181),
KC_TAB,JP_MO,JP_NI,JP_HA,JP_TE,JP_DE,KC_TRNS,
OSL(6),JP_KA,JP_LEFT_RING_MIZUNARA,JP_LEFT_MIDDLE_MIZUNARA,JP_NA,JP_RU,
KC_LEFT,JP_KO,JP_GA,JP_DA,JP_TA,JP_XYO,JIS_MINUS,
KC_LCTRL,KC_LGUI,KC_LALT,TO(10),TO(5),
KC_TRNS,KC_TRNS,
KC_TRNS,
M(178),0x4c,0x29,
 
JP_BACKTICK,JP_SQUARE_BRACKET_OPEN,JP_SQUARE_BRACKET_CLOSE,JP_PARENTHESE_OPEN,JP_PARENTHESE_CLOSE,JP_MINUS,JP_PLUS,
TO(6), JP_RE,JP_XTU,JP_SI,JP_TO,JP_E,JP_BACKSLASH,
JP_KI,JP_NN,JP_RIGHT_MIDDLE_MIZUNARA,JP_RIGHT_RING_MIZUNARA,JP_I,OSL(6),
KC_TRNS, JP_KU,JP_U,JP_COMMA,JP_PERIOD,JP_NO,0xe5,
TO(0),KC_LEFT,KC_RIGHT,KC_DOWN,KC_UP,
0x4b,0x93,
0x4e,
KC_TAB,0x2a,M(238) ),

// Mizunara right thumb layer
[2] = 
  KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,JP_BI,JP_NE,JP_QUESTION,KC_TRNS,KC_TRNS,
KC_TRNS,JP_YA,JP_GE,JP_FU,JP_YO,JP_YU,
KC_TRNS, KC_TRNS, JP_MO, JP_DE,JP_XYO,KC_TRNS,KC_TRNS, 
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
0x2c,0x4c,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,JP_PU,JP_BU,JP_XYU,JP_DATEN,KC_TRNS,
JP_HI,JP_TU,JP_SU,JP_WA,JP_MA,KC_TRNS,
KC_TRNS,KC_TRNS,JP_XO,JP_PE,JP_XYU,JP_PI,KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,M(139) ),

[3] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,JIS_YEN,JIS_LESS,JIS_PLUS,JIS_QUESTION,JIS_AT,KC_TRNS,
JIS_UNDERLINE ,JIS_PERCENTAGE ,JIS_PIPE ,JIS_EQUAL ,JIS_EXCLAMATION ,JIS_TILD,
JIS_SEMI_COLON,JIS_UNDERLINE,JIS_GREATER,JIS_MINUS,JIS_AND,JIS_COLON,TO(3),
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
0x2c,0x4c,KC_TRNS,
 
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,JIS_BACKTICK ,JIS_SHARP ,JIS_CURLY_BRACE_OPEN ,JIS_CURLY_BRACE_CLOSE ,JIS_QUOTE,KC_TRNS,
JIS_BACSLASH ,JIS_ASTERISK ,JIS_PARENTHES_OPEN ,JIS_PARENTHES_CLOSE ,JIS_SLASH ,JIS_DOUBLE_QUOTE,
TO(1), JIS_CARET,JIS_DOLLAR, JIS_SQUARE_BRACKET_OPEN,JIS_SQUARE_BRACKET_CLOSE, JIS_PERIOD,KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,0x58 ),

//vim & IDE shortcut layer
[4] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,0x2f,0x34,0x2a,KC_TRNS,KC_TRNS,
KC_TRNS,0x58,0x2c,0x29,0x33,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TAB,0x1c,0x1b,KC_TRNS,KC_TRNS,
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

// numpad layer
[5] = KEYMAP(  
 JIS_MINUS,0x1e,JIS_MINUS,JIS_MINUS,JIS_MINUS,JIS_MINUS,JIS_MINUS,
KC_TAB,JIS_PIPE,KC_A,KC_B,KC_C,LSFT(JIS_COMMA),JIS_LESS,
0x39,JIS_TILD,JIS_COMMA,JIS_PERIOD,KC_X,JIS_TILD,
JIS_SEMI_COLON,JIS_AND,KC_D,KC_E,KC_F,JIS_GREATER,TO(3),
KC_LCTRL,KC_LGUI,KC_LALT,TO(10),TO(5),
KC_TRNS,KC_TRNS,
KC_TRNS,
0x2c,0x4c,0x29,
 
 JIS_MINUS,JIS_MINUS,KC_LNUM,KC_PSLS,KC_PAST,KC_KP_MINUS,JIS_QUESTION,
TO(1),KC_PAST,KC_P7,KC_P8,KC_P9,KC_PEQL,JIS_BACSLASH,
KC_P0,KC_P4,KC_P5,KC_P6,JIS_PLUS,JIS_DOUBLE_QUOTE,
TO(3),JIS_MINUS,KC_P1,KC_P2,KC_P3,KC_PENT,JIS_COLON,
TO(0),KC_P0,KC_PDOT,KC_PENT,KC_PENT,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,0x58),

// Kana symbols layer
[6] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TAB,JP_YEN,JP_LESS,JP_PLUS,JP_QUESTION,JP_AT,TO(1),
JP_UNDERLINE,JP_PERCENTAGE,JP_PIPE,JP_EQUAL,JP_EXCLAMATION,JP_TILD,
OSL(8),JP_UNDERLINE,JP_GREATER,JP_MINUS,JP_AND,JP_COLON,KC_TRNS,
KC_LCTRL,KC_LGUI,KC_LALT,TO(10),KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,JP_CURLY_BRACKET_OPEN,JP_CURLY_BRACKET_CLOSE,KC_TRNS,KC_TRNS,
KC_TRNS,JP_BACKTICK,JP_SHARP,JP_KAGIKAKKO_OPEN,JP_KAGIKAKKO_CLOSE,JP_SINGLE_QUOTE,KC_TRNS,
JP_BACKSLASH,JP_ASTERISK,JP_PARENTHESE_OPEN,JP_PARENTHESE_CLOSE,JP_SLASH,JP_DOUBLEQUOTE,
TO(1),JP_CARET,JP_DOLLAR,JP_SQUARE_BRACKET_OPEN,JP_SQUARE_BRACKET_CLOSE,JP_DOT,OSL(8),
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS ),

// Mizunara  left thumb layer
[7] = KEYMAP(  
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,JP_DU,JP_BO,JP_HO,KC_TRNS,KC_TRNS,
KC_TRNS,JP_A,JP_KE,JP_SU,JP_O,JP_SA,
KC_TRNS,KC_TRNS,JP_GO,JP_ZE,JP_HE,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
M(134),0x4c,KC_TRNS,
 

 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,JP_MU,JP_TI,JP_ME,KC_TRNS,KC_TRNS,
JP_NU,JP_MI,JP_ZI,JP_RI,JP_GU,KC_TRNS,
KC_TRNS,KC_TRNS,JP_KU,JP_RE,JP_E,KC_TRNS,KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,0x58 ),

// For mizunara right ring finger  
[8] = KEYMAP(
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,JP_BE,JP_XI,JP_XA,JP_DO,KC_TRNS,KC_TRNS,
KC_TRNS,JP_RA,JP_SE,JP_WA,JP_RO,JP_SO,
KC_TRNS,JP_BE,JP_XE,JP_ZO,JP_ZA,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
M(116),0x4c,KC_TRNS,
 
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
JP_PI,JP_KU,JP_RE,JP_E,JP_NO,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,M(124) ),
// For mizunara left ring finger  

[9] = KEYMAP( 
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS, JP_KO,JP_MO,JP_DE,JP_XYO,JP_BE,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
M(116),0x4c,KC_TRNS,
 
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,JP_PO,JP_BA,JP_ZU,JP_MARU,KC_TRNS,
JP_GI,JP_YOKOBOU,JP_KE,JP_SE,JP_WO,KC_TRNS,
KC_TRNS,KC_TRNS,JP_PA,JP_VU,JP_XU,JP_DI,KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,M(124) ),

[10] = KEYMAP(  
 KC_F1,KC_F2,KC_F3,KC_F4,KC_F5,0x3f,0x40,
KC_TRNS,KC_TRNS,0x8b,0x35,0x8a,0x93,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,TO(0),
KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
0x2c,0x4c,KC_TRNS,
 
 RESET,0x41,0x42,0x43,0x44,0x45,KC_TRNS,
KC_TRNS,KC_TRNS,0x4b,KC_UP,LCTL(0x54),KC_TRNS,KC_TRNS,
KC_TRNS,KC_LEFT,KC_DOWN,KC_RIGHT,KC_TRNS,KC_TRNS,
TO(1),KC_TRNS,0x4e,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
TO(0),KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
KC_TRNS,KC_TRNS,
KC_TRNS,
KC_TRNS,0x2a,0x58 ),
  
  
  
};


const uint16_t PROGMEM fn_actions[] = {
[0] = ACTION_FUNCTION_TAP(219),
[1] = ACTION_FUNCTION_TAP(233),
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

  // equivalent of LT(10,は) for CLT receptor
  case 233:
  if(record->tap.count>0){
   process_combo_lt_receptor(record,233,M(232)); 
  }else{
    if(record->event.pressed){
      layer_on(10);// cursor arrows layer
    }else{
      layer_off(10);
    }
   }
  return;
  // equivalent of LT(10,し) for CLT receptor
  case 191:
  if(record->tap.count>0){
   process_combo_lt_receptor(record,191,M(190)); 
  }else{
    if(record->event.pressed){
      layer_on(10);// cursor arrows layer
    }else{
      layer_off(10);
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
    if(record->tap.count>=1){
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
    }else if (record->tap.count == 0){
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
// DLT(4,KC_U)
if(record->event.pressed){
  dlt_threshold = 180;
  dlt_threshold_key_not_up = 180;
  dlt_hold_decreased_by = 25;
  dlt_hold_increased_by = 25;
  dlt_pre_keypress_idling = 85;
  process_action_delayed_lt_from_macro(DLT(4,KC_U),record);
}else{
  process_action_delayed_lt_from_macro(DLT(4,KC_U),record);
  dlt_reset();
}
break;
case 246:  
// DLT(4,KC_H)
if(record->event.pressed){
  dlt_threshold = 180;
  dlt_threshold_key_not_up = 180;
  dlt_hold_decreased_by = 25;
  dlt_hold_increased_by = 25;
  dlt_pre_keypress_idling = 85;
  process_action_delayed_lt_from_macro(DLT(4,KC_H),record);
}else{
  process_action_delayed_lt_from_macro(DLT(4,KC_H),record);
  dlt_reset();
}
break;

/*case 245:*/
/*//]*/
/*if(record->event.pressed){*/
            /*register_code(0x39);*/

/*unregister_code(0x39);*/

/*register_code(0x31);*/

/*unregister_code(0x31);*/

/*register_code(0x39);*/

/*unregister_code(0x39);*/

        /*}*/
 /*break;*/
/*case 244:*/
/*//(*/
/*if(record->event.pressed){*/
            /*register_code(0x39);*/

/*unregister_code(0x39);*/

/*register_code(0xe1);*/
/*register_code(0x25);*/

/*unregister_code(0x25);*/

/*unregister_code(0xe1);*/

/*register_code(0x39);*/

/*unregister_code(0x39);*/

        /*}*/
 /*break;*/
/*case 241:*/
/*//)*/
/*if(record->event.pressed){*/
            /*register_code(0x39);*/

/*unregister_code(0x39);*/

/*register_code(0xe1);*/
/*register_code(0x26);*/

/*unregister_code(0x26);*/

/*unregister_code(0xe1);*/

/*register_code(0x39);*/

/*unregister_code(0x39);*/

        /*}*/
 /*break;*/
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
//CLT6 or ret

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
//CLT9
if(record->event.pressed){
clt_layer = 9;
}

if(!process_combo_lt(OSL(9), record)){
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
//CLT(6) or space

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
/*case 173:*/
/*//' "*/
/*//' "*/
/*if(record->event.pressed){*/

/*if(keyboard_report->mods & (2|32)){*/
/*register_mods(2);*/
/*register_code(0x1f);*/
/*unregister_code(0x1f);*/
/*unregister_mods(2);*/
/*}else{*/
/*register_mods(2);*/
/*register_code(0x24);*/
/*unregister_code(0x24);*/
/*unregister_mods(2);*/
/*}*/
/*}*/
 /*break;*/
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
// _
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
//_
/*case 148:*/
/*if(record->event.pressed){*/
            /*register_code(0x39);*/

/*unregister_code(0x39);*/

/*register_code(0xe1);*/
/*register_code(0x87);*/

/*unregister_code(0x87);*/

/*unregister_code(0xe1);*/

/*register_code(0x39);*/

/*unregister_code(0x39);*/

        /*}*/
 /*break;*/

case 148:
//colon for japanese kana
  if(record->event.pressed){
    register_code(0x39);
    unregister_code(0x39);
    register_code(0x34);
    unregister_code(0x34);
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
//CLT6 or return
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
//CLT6 or space
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
//CLT6 or  return
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
//CLT6 or  space
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


