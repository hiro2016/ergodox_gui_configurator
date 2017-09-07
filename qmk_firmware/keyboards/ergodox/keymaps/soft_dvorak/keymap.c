#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "version.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD
};



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |6/dov=  |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |9/dov+|  8   |   0  | \      |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | tab    |   Q  |   W  |LT2 E |   R  |   T  |  CAP |           |6/dov=|   Y  |   U  |   I  |   O  |   P  |[/dov/  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |'/dov_  |   A  |LT5 S |Sft  D|LT4 F |   G  |------|           |------|   H  |LT4 J |Sft K |LT5 L |;     | '/dov- |
 * |--------+------+------+------+------+------|6/dov=|           | Meh  |------+------+------+------+------+--------|
 * | LShift |Z/Ctrl|   X  |LT2/C |LT1/V |   B  |      |           |      |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 * |Grv/CTl |  CMD |Alt   | TT(2)| ESC  |                                       |  L0  |left  |right |down  |up    |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | L1   | L3   |       |PgUp  |Ctrl/End|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |LT(3) |      | L4   |       |PgDown|        |LT(3) |
 *                                 |Space |Space |------|       |------|backsp  |Enter |
 *                                 |      |      | ESC  |       |TAB   |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
// layer 0 : default
// 
[BASE] = KEYMAP(  
         /*left hand*/
        KC_6,         KC_1,         KC_F2,   KC_F3,   KC_4,   KC_5,   KC_LEFT,
        KC_TAB,        KC_Q,         KC_W,   LT(2,KC_E),   KC_R,   KC_T,   KC_CAPS,
        RSFT(KC_QUOT),        KC_A,         LT(5,KC_S),   SFT_T(KC_D),   LT(4,KC_F),   KC_G,
        KC_LSFT,        CTL_T(KC_Z),  KC_X,   KC_C,   LT(1,KC_V),   KC_B,   M(10),
        CTL_T(KC_GRV), KC_LGUI,      KC_LALT,  TT(2), KC_ESC,
                                              TG(1),  TG(3),
                                                              TG(4),
                                               LT(3,KC_SPC), KC_DELT, KC_ESC, 
        // right hand
             KC_RGHT,     KC_6,   KC_7,  KC_9,   KC_8,   KC_0, KC_BSLS,
             KC_6,    KC_Y,   KC_U,  KC_I,   KC_O,   KC_P,     KC_LBRC,                                  
             KC_H,   LT(4,KC_J),  SFT_T(KC_K),   LT(5,KC_L),   KC_SCLN, KC_QUOT,
             MEH_T(KC_NO),KC_N,   KC_M,  KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
                                  TO(0), KC_LEFT, KC_RIGHT, KC_DOWN, KC_UP,
             KC_PGUP,        CTL_T(KC_END),
             KC_PGDOWN,
             KC_TAB, KC_BSPC, LT(3,KC_ENT)
),     
/* Keymap 1: Symbol Layer
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |Version  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      | PGUp |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |------|           |------| Down |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |      |      |      |      |      |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | EPRM  |      |      |      |      |                                       |      |    . |   0  |   =  |      |
 *   `-----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBLS
//
[1] = KEYMAP(
       // left hand
       VRSN,   KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,  KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
          EPRM,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       KC_TRNS,KC_TRNS,
                                               KC_TRNS,
                               KC_TRNS,KC_TRNS,KC_TRNS,
       // right hand
       KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS, KC_PGUP,   KC_KP_7,   KC_KP_8,    KC_KP_9,    KC_ASTR, KC_F12,
                KC_PGDOWN, KC_KP_4,   KC_KP_5,    KC_KP_6,    KC_PLUS, KC_TRNS,
       KC_TRNS, KC_AMPR, KC_KP_1,   KC_KP_2,    KC_KP_3,    KC_BSLS, KC_TRNS,
                         KC_TRNS, KC_DOT,  KC_KP_0,    KC_EQL,  KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS 
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           | RESET|      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |9/dov+|      |      |      |           |      |      |PGUP  |up    |[/dov/|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|6/dov=|MsRght|      |------|           |------|      |left  |down  |right |      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |PGDOWN|      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[2] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_UP, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_NO, KC_PGUP, KC_UP, LCTL(KC_LBRC), KC_NO, KC_NO,
       KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO,
       KC_NO, KC_NO, KC_PGDOWN, KC_NO, KC_NO, KC_NO, KC_NO, 
       KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Keymap 3: Media and mouse keys
 * 
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |       |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |,/dov<|9/dov+|{/dov?|      |      |           |      |+/dov`|=/dov# |3/dov{|4/dov}|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |!/dov%|  dov||6/dov=|-/dov!|~/dov~|------|           |------|      |7/dov*|5/dov(|8/dov)|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |E/dov>|'/dov-|1/&   |      |      |           |      |{/dov^|`/dov/$|2/dov[|0/dov]|      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |       |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[3] = KEYMAP(
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_NO, RSFT(KC_W), KC_9, KC_LCBR, KC_NO, KC_NO,
       KC_NO, KC_EXLM, KC_PIPE, KC_6, KC_MINS, KC_TILD, 
       KC_NO, KC_NO, RSFT(KC_E), KC_QUOT, KC_1, KC_NO, KC_NO,
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, LSFT(KC_PLUS), KC_EQL, KC_3, KC_4, KC_NO, KC_NO,
       KC_NO, KC_7, KC_5, KC_8, KC_7, KC_NO,
       KC_NO, KC_RCBR, KC_GRV, KC_2, KC_0, KC_NO, KC_NO,
       KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/*
 *  
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |]/dov@|Q/dov:|backsp|      |      |           |      |      |z/'   |[/dov/|o/dovl|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |Enter |Space | ESC  |q/dov;|      |------|           |------|del   |Z/dov"|\/dov\|k/dovs|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |Tab   |t/dovy|b/dovx|      |      |           |      |      |n/dovb|y/dovf|./dovz|      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
[4] = KEYMAP(
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_RBRC,  LSFT(KC_Q), KC_BSPC, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_ENT, KC_SPC, KC_ESC, KC_Q, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TAB, KC_T, KC_B, KC_TRNS, KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                           KC_TRNS, KC_TRNS,
                                                    KC_TRNS,
                                  KC_TRNS, KC_TRNS, KC_TRNS,
    // right hand
       RESET, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_NO, KC_TRNS, KC_Z, KC_LBRC, KC_P, KC_TRNS, KC_NO,
       KC_DELT, RSFT(KC_Z), KC_BSLS, KC_SCLN, KC_NO, KC_NO,
       KC_NO, KC_NO, KC_N, KC_Y, KC_SLSH, KC_NO, KC_NO,
       KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),

/* Radical hand movement reduction layer.
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |          |      |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |q/dov;|/dovy |      |      |      |           |      |      |      |y/dovf|o/dovl|      |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |a/dova|/dovi |      |      |------|           |------|      |      |h/dovd|;/dovs|      |          - |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |z/dov'|dovx  |      |      |      |           |      |      |      |n/dovb|//dovz|      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 * |        |      |      |      |      |                                       |      |      |          |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------        ,------------- 
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------ 
 *                                 |      |      |      |       |      |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 |      |      |      |       |      |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
// layer 0 : default
// 
[5] = KEYMAP(  
         /*left hand*/
        KC_TRNS,         KC_TRNS,         KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
        KC_TRNS,  KC_TRNS,        KC_TRNS,         KC_Q,   KC_T,   KC_TRNS,   KC_TRNS,   
        KC_TRNS, KC_TRNS,  KC_TRNS,        KC_A,         KC_G,   KC_TRNS,     
        KC_TRNS, KC_TRNS,        KC_TRNS,  KC_Z,   KC_B,   KC_TRNS,   KC_TRNS,   
        KC_TRNS, KC_TRNS,      KC_TRNS,  KC_TRNS, KC_TRNS,
        KC_TRNS,  KC_TRNS,
        KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, 
        // right hand
        KC_TRNS,     KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,             KC_TRNS,
        KC_TRNS,    KC_TRNS,   KC_Y,  KC_P,   KC_TRNS,   KC_TRNS,             KC_TRNS,
                    KC_TRNS,   KC_H,  KC_SCLN,  KC_TRNS,   KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,   KC_N,  KC_SLSH, KC_TRNS, KC_TRNS,   KC_TRNS,
                            KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,          KC_TRNS,
        KC_TRNS,        KC_TRNS,
        KC_TRNS,
        KC_TRNS, KC_TRNS,KC_TRNS 
),     
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
        }
        break;
        case 1:
        if (record->event.pressed) { // For resetting EEPROM
          eeconfig_init();
        }
        break;
        case 10:
          if(record->event.pressed) 
            return MACRO( D(LALT), T(LBRC),  U(LALT), END) ;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
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
