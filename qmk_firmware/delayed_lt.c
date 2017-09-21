//#define DLT_DEBUG_PRINT
// For controlling threshold and other variables for individual 
// keys, use macro.
//
//e.g.
//  
      /*case 3:*/
        /*if(record->event.pressed){*/
          /*uint16_t kc = DLT(6,0x08);*/
          /*dlt_threshold = 200;*/
          /*dlt_threshold_key_not_up = 200;*/
          /*dlt_pre_keypress_idling =90;*/
          /*dlt_hold_decreased_by =60;*/
          /*dlt_hold_increased_by =25;*/
          /*dlt_restrict_same_hand_dlt_action = true;*/
          /*dlt_no_layer_toggle_while_modifier_on = true;*/
          /*process_action_delayed_lt_from_macro(kc,record);*/
        /*}else{*/
          /*uint16_t kc = DLT(6,0x08);*/
          /*process_action_delayed_lt_from_macro(kc,record);*/
          /*dlt_reset();*/
        /*}*/
        /*break;*/
//
// The duration of time DLT key must be held down to trigger 
// DLT action;layer toggle while the key is down.
//
// Different keyboard has a different tapping term, you
// must set this to what your mechanical switch requires.
// Tapping term for my board is 130ms.
//
#define DLT_THRESHOLD 180 

// Same as above except the value below is applied when another key is 
// pressed while DLT key is still down and that another key is not 
// released before DLT key.
#define DLT_THRESHOLD_KEY_NOT_UP 180

// Typically, there is some idling time before switching keyboard layers.
// The value below controls the threshold of that indling time. 
//
// (idling time < DLT_PRE_KEYPRESS_IDLING) -> 
//    reduce the length of time key was held down.
//
// (indling time >= DLT_PRE_KEYPRESS_IDLING )
//    increase the length of time key was held down.
//
// What is compared against DLT_PRE_KEYPRESS_IDLING is 
// interval between non-dlt key press and dlt key press 
// and not tapping term.
//
// My case, the intermal between typing k and j fast is about 60 to 80ms.
#define DLT_PRE_KEYPRESS_IDLING 85

// Increase of decrease the duration of time dlt key was held down depending
// on idling before dlt key press.
#define DLT_HOLD_INCREASED_BY 25
#define DLT_HOLD_DECREASED_BY 25

#define DLT_OFF_WHILE_MODIFIER_ON true
//Given K is a dlt key, prevent K to change the current layer 
//when user press keys such as `KJ` or `KL` in sequence;when
//J or L key is tapped while K is pressed down, DLT layer switch 
//still happens.
#define DLT_RESTRICT_SAME_HAND_DLT_ACTION true



uint8_t dlt_threshold =DLT_THRESHOLD;
uint8_t dlt_threshold_key_not_up = DLT_THRESHOLD_KEY_NOT_UP;
uint8_t dlt_pre_keypress_idling = DLT_PRE_KEYPRESS_IDLING;
uint8_t dlt_hold_increased_by = DLT_HOLD_INCREASED_BY;
uint8_t dlt_hold_decreased_by = DLT_HOLD_DECREASED_BY;
//Make pressing the keys of the same keyboard half less
//likely to trigger DLT action.
//e.g.
//Given K is a DLT key, pressing fast `jkjk` might cause j to be
//pressed while k is still down. Setting this option true decrease
//the holding time of k prior to deciding whether DLT actian is
//requested.
//I needed this as I use dvorak and typing `kjd` to input `the`.
bool dlt_restrict_same_hand_dlt_action = DLT_RESTRICT_SAME_HAND_DLT_ACTION;

//disables DLt action while shift is pressed down.
bool dlt_no_layer_toggle_while_modifier_on= DLT_OFF_WHILE_MODIFIER_ON;
//These numbers are for ergodox
//left hand range row 0 to 6 and col 0 to 5
//right hand range row 7 to 13 and col 0 to 5
#define IS_LEFT_HAND_KEY(keypos) (keypos.row < 7)
#define IS_SAME_HAND_KEY(key1, key2) (IS_LEFT_HAND_KEY(key1)==IS_LEFT_HAND_KEY(key2))


inline void dlt_reset(void){
  dlt_threshold =DLT_THRESHOLD;
  dlt_threshold_key_not_up = DLT_THRESHOLD_KEY_NOT_UP;
  dlt_pre_keypress_idling = DLT_PRE_KEYPRESS_IDLING;
  dlt_hold_increased_by = DLT_HOLD_INCREASED_BY;
  dlt_hold_decreased_by = DLT_HOLD_DECREASED_BY;
  dlt_restrict_same_hand_dlt_action = DLT_RESTRICT_SAME_HAND_DLT_ACTION;
  dlt_no_layer_toggle_while_modifier_on= DLT_OFF_WHILE_MODIFIER_ON;
}

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

//State where a DLT key was pressed down, then another key 
//was pressed but that key was not released before the DLT 
//key release.
//The duration of the DLT key hold, however, was greater than
//DLT_THRESHOLD_KEY_NOT_UP.
#define DLT_MODE_LONGPRESS_AND_KEYPRESS_DETECTED 2

//DLT key down, anothere key tapped, DLT key released.
//Full LT cycle completed.
#define DLT_MODE_LT 3

//A DLT key tapped and no other key was pressed while 
//the DLT key was down.
//A requeset for sending a key.
#define DLT_MODE_SINGLE_TAP 4

//DLT captures key events.
//DLT sends a keypress and keyrelease events for keys pressed 
//while DLT key is held and have not yet been released when DLT 
//key is released.
//The above behaviour causes two keyrelase events to be registered 
//if key release events are not filtered after DLT key release.
//The line below controls that filtering behaviour.
#define DLT_DISABLE_KEYRELEASE_FILTER(keypos) (keypos.col=128)
#define DLT_IS_KEYRELASE_FILTER_ENABLED(keypos) (keypos.col!=128)

//The variable below:
//  1. store DLT key pressed time while dlt_on.
//  So the timers are available for next DLT key press.
//  2. needed by process_action_delayed_lt_from_macro.
//  As process_action_delayed_lt sets pre_dlt_idling_time before
//  action_get_macro is called, getting the last key pressed time 
//  in macro is not possible without below.
//
uint16_t pre_pre_dlt_idling_time = 0;

// Holds a key's state. 
// Changed only if another key was pressed while DLT key was
// held.
// If that non-DLT key was released before DLT key release, 
// then set back to true.
// Needed to differentiate a key tap(keydown and keyrelease) 
// and keydown event that occured during DLT key hold.
bool prv_key_up = true;

//Holds the MPU timer time at which a DLT key press occured. 
int16_t dlt_timer = 0;

// Time interval between a keypress and a DLT key press.
// Before a DLT key is pressed, pre_dlt_idling_time 
// holds the time at which the last key was pressed. 
int16_t pre_dlt_idling_time = 0;

// Holds the last pressed key position.
// Used to check whether a keypress occured while DLT 
// key was pressed down.
keypos_t prv_keypos ={128,128};//8col, 8row, set it to 128 to disable filtering

// The position of the key that has triggered the DLT action. 
// Until this key is released, futher DLT key presses result in 
// sending keys and not layer changes.
keypos_t dlt_toggler;
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
  //detect shift.
  //For the time being supporting shift only.
  
  
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
 /*
    QK_TMK                = 0x0000,
    QK_TMK_MAX            = 0x00FF,
    QK_MODS               = 0x0100,
    QK_LCTL               = 0x0100,
    QK_LSFT               = 0x0200,
    QK_LALT               = 0x0400,
    QK_LGUI               = 0x0800,
    QK_RMODS_MIN          = 0x1000,
    QK_RCTL               = 0x1100,
    QK_RSFT               = 0x1200,
    QK_RALT               = 0x1400,
    QK_RGUI               = 0x1800,
    QK_MODS_MAX           = 0x1FFF,*/
  if(QK_MACRO <= keycode && keycode <QK_MACRO_MAX){
      action_t action;
      keyrecord_t record;
      action.code = keycode;
      record.event.key = prv_keypos;
      record.event.pressed = true;
      record.event.time = timer_read();
      //id contain opt alh opt contain id!
      action_get_macro(&record,action.func.id, action.func.id);
      record.event.pressed = false;
      action_get_macro(&record,action.func.id, action.func.id);
      return;
  }
  switch(keycode>>8){
    case(0x2):
      register_code(KC_LSHIFT);
      register_code(keycode & 0xff);
      unregister_code(keycode & 0xff);
      unregister_code(KC_LSHIFT);
      break;
    case(0x12):
      register_code(KC_LSHIFT);
      register_code(keycode & 0xff);
      unregister_code(keycode & 0xff);
      unregister_code(KC_LSHIFT);
      break;
    default:
      register_code(keycode & 0xff);
      unregister_code(keycode & 0xff);
  }
}

uint8_t inline _get_action_for_delayed_lt_released(uint16_t keycode, keyrecord_t *record){
  // A flag for controlling the input handling downstream.
  uint8_t mode = 0;

#define IS_KEYPOS_SAME(keyone,keytwo)  ((keyone.col==keytwo.col)&&(keyone.row==keytwo.row))
#define ANOTHER_KEY_PRESSED (!IS_KEYPOS_SAME(prv_keypos, record->event.key))
  /*bool anotherKeyPressed = !(prv_keypos.col == record->event.key.col &&\
                           prv_keypos.row == record->event.key.row);*/
    
  int16_t held_down_time = timer_elapsed(dlt_timer);

  if(pre_dlt_idling_time > dlt_pre_keypress_idling){
    held_down_time += dlt_hold_increased_by;
#ifdef DLT_DEBUG_PRINT
    print("DLT held down time added\n");
    print_val_dec(held_down_time);
    print("before addition\n");
    print_val_dec(held_down_time-dlt_hold_increased_by);
    print("timers\n");
    print_val_dec(timer_read());
    print_val_dec(pre_dlt_idling_time);
#endif
  }else{
    held_down_time -= dlt_hold_decreased_by;
#ifdef DLT_DEBUG_PRINT
    print("DLT held down time reduced\n");
    print_val_dec(held_down_time);
    print("before reduction\n");
    print_val_dec(held_down_time+dlt_hold_decreased_by);
    print("timers\n");
    print_val_dec(timer_read());
    print_val_dec(pre_dlt_idling_time);
#endif
  }


  //IS_KEYPOS_SAME(record->event.key,prv_keypos);
  //print_val_bin8(anotherKeyPressed);
  if (ANOTHER_KEY_PRESSED){
    //layer switching and input not allowed with the same keyboard half.
    if(dlt_restrict_same_hand_dlt_action && \
        (!prv_key_up) && \
        IS_SAME_HAND_KEY(prv_keypos, dlt_toggler)){
      held_down_time = 0;
#ifdef DLT_DEBUG_PRINT
      print("key pressed and dlt key belongs to the same keyboard half. holding time set to zero\n");
#endif
    }
    //DLT key was held down long enough? 
    //non DLT key pressed during DLT key press, is that non DLT key released yet?
    if ((held_down_time > dlt_threshold_key_not_up) && !prv_key_up){ 
      //longer than thresh hold, LT request
      mode = DLT_MODE_LONGPRESS_AND_KEYPRESS_DETECTED;
#ifdef DLT_DEBUG_PRINT
      print("dlt long press and keypres not tap\n");
#endif
    }else if(held_down_time > dlt_threshold && prv_key_up){
      //  full LT input cycle completed
      mode = DLT_MODE_LT;
#ifdef DLT_DEBUG_PRINT
      print("lt mode\n");
#endif
    }else{
      // A key pressed detected while DLT key was down, 
      // but DLT keypress as whole was too short.
      // Must be an unintentionl simultaneous key press.
      // set a flag to send the key in the default layer.
      mode = DLT_MODE_SHORTPRESS_AND_KEYPRESS_DETECTED; 
#ifdef DLT_DEBUG_PRINT
      print("dlt keypress too short, do normal input \n");
#endif
    }
  }else if(held_down_time > 200){
    mode = DLT_MODE_LT;
#ifdef DLT_DEBUG_PRINT
    print("lt mode\n");
#endif
  }else{
  // A single key tap 
    mode = DLT_MODE_SINGLE_TAP;
#ifdef DLT_DEBUG_PRINT
    print("single tap\n");
#endif
  }
  return mode;
}

bool inline _handle_action_delayed_lt_released(uint16_t keycode, uint8_t mode){
  ////higher 8bits are all set to zero when action_for_key is used.
  //custom_action_t action;
  //action.code = keycode;
  switch(mode){
    case DLT_MODE_SHORTPRESS_AND_KEYPRESS_DETECTED:
      //An unintentional simultaneous key press
      //Treat this as an normal input request.
      register_code(keycode & 0xff);
      unregister_code(keycode & 0xff);
      _send_key(dlt_start_layer,prv_keypos);
      return false;
    case DLT_MODE_LONGPRESS_AND_KEYPRESS_DETECTED:
      //Premature lt key release
      _send_key(dlt_layer_to_toggle, prv_keypos);
      return false;
    case DLT_MODE_LT:
      //full lt cycle completed
      //There is no key release event that needs to be capured.
      DLT_DISABLE_KEYRELEASE_FILTER(prv_keypos);
      return false;
    case DLT_MODE_SINGLE_TAP:
      //single tap
      /*print_val_bin8(prv_keypos.col);*/
      /*print_val_bin8(prv_keypos.row);*/
      /*print_val_bin8(record->event.key.col);*/
      /*print_val_bin8(record->event.key.row);*/
      /*print_val_dec(keycode);*/
      register_code(keycode & 0xff);
      unregister_code(keycode & 0xff);
      //There is no key release event that needs to be capured.
      DLT_DISABLE_KEYRELEASE_FILTER(prv_keypos);
      return false;
    }
  return true;
}


bool inline _action_delayed_lt_pressed(uint16_t keycode,keyrecord_t *record){
  //record the layer to move back to.
  dlt_start_layer = biton32(layer_state);
  //get the layer to move to
  dlt_layer_to_toggle = GET_DLT_LAYER(keycode);
  //prv_key_up tracks whether a key was pressed while
  //DLT key was pressed down and not yet released at 
  //the time DLT key is released. 
  prv_key_up=true;

  //The key that is bound to DLT action.
  //Only when the key bound O dlt_toggler 
  //is released DLT action ends.
  dlt_toggler = record->event.key;

  //Holds the key that was pressed down while DLT key
  //was held down. 
  //Used to fetch the keycode to send when the key 
  //assigned to prv_keypos is released.
  //Used to detect the keypress that occured while DLT 
  //key was down in _action_delayed_lt_released.
  prv_keypos = record->event.key;
  //Time at which DLT keypress occured.
  //Used to compute the duration of DLT key hold.
  dlt_timer = record->event.time;

  //Keep the time DLT key is pressed, so it's available for next
  //DLT key press.
  pre_pre_dlt_idling_time = pre_dlt_idling_time;
  //record the interval between the last key press and DLT key press.
  pre_dlt_idling_time = TIMER_DIFF_16(dlt_timer, pre_dlt_idling_time);
  //don't call downstream code as what must be done has already been done.
  return false;
}

bool inline process_action_delayed_lt(uint16_t keycode, keyrecord_t *record){
  if(dlt_on){
    //Ending DLT layer toggle.
    if(IS_KEYPOS_SAME(record->event.key, dlt_toggler)){    
      //keycode variable contains the hid usage id found in the toggled 
      //layer and not the value found in before-dlt-key-pressed-layer.
      keycode = keymap_key_to_keycode(dlt_start_layer, record->event.key);
      //let other function handle this if not DLT action, 
      //without this calling process_action_delayed_lt_from_macro 
      //in macro works only for key press.
      if(!((keycode&(~0xff))>=DLT_LAYER_TAP) && 
          ((keycode&(~0xff))<DLT_LAYER_MAX)){
        return true;
      }

      _handle_action_delayed_lt_released(\
          keycode, _get_action_for_delayed_lt_released(keycode,record));
      layer_off(dlt_layer_to_toggle);
      //dlt_timer = 0;//not needed
      dlt_on = false;
      //pre_pre_dlt_idling_time holds last pressed key time
      //so timer works for the nex round.
      pre_dlt_idling_time = pre_pre_dlt_idling_time;
      return false;
    }

    //upstream code sets higher 8bits of the keycode to all zero
    //for DLT key release. Re-fetcheng keycode.
    //action_for_key does not work, it returns action_t whose 
    //higher 8 bits all set to zeros.
    //print_val_bin16(keycode);
    //print(" - raw keycode printed\n");
  }else{
    //dlt_on is false
    if(record->event.pressed){
      //DLT action not request, let other functions handle this.
      if(!((keycode&(~0xff))>=DLT_LAYER_TAP && 
          (keycode&(~0xff))<DLT_LAYER_MAX)){
        //just record the keypress time.
        pre_pre_dlt_idling_time = pre_dlt_idling_time;
        pre_dlt_idling_time = record->event.time;
        return true;
      }

      //if shift key is being pressed down, do not start dlt action.
      if(dlt_no_layer_toggle_while_modifier_on && \
           keyboard_report->mods != 0){
        register_code(keycode & 0xff);
        //only sigle key press sent unlike in macro. 
        unregister_code(keycode & 0xff);
      }else{
        //DLT action request, turning it on.
        _action_delayed_lt_pressed(keycode, record);
        layer_on(dlt_layer_to_toggle);
        dlt_on = true;
      }
      return false;
    }else{
      //DLT captures key presses while it's on.
      //If there is non-DLT key pressed and not released
      //at the time DLT key release. DLT generates key 
      //release event for that key.
      //But the actual key is still pressed down and 
      //waiting to be released, so key release will 
      //be registered twice.
      //The line below prevents that.
      if(DLT_IS_KEYRELASE_FILTER_ENABLED(prv_keypos)){
#ifdef DLT_DEBUG_PRINT
        print("filtering keyrelease");
#endif
        DLT_DISABLE_KEYRELEASE_FILTER(prv_keypos);
        return false;
      }
      return true;
    }
  }


  // Only called while dlt_on is true.
  // Capturing and uncapture keypresses.
  if(record->event.pressed){
    prv_key_up = false;
    prv_keypos = record->event.key;
    //Since pre_dlt_idling_time is in use, use 
    //pre_pre_dlt_idling_time to record key press time.
    pre_pre_dlt_idling_time = record->event.time;
    // Do not send a keypress immidiately while dlt key is being 
    // held to allow later evaluation of non-dlt key press events  
    // when DLT key is released.
    //
    // But taps must be registered. 
    return false;
  }else{
    //key releases handled here.
    //Capturing a key release for a key that was pressed 
    //before DLT key was pressed causes extra keys to be 
    //registered. The line below prevents that.
    //prv_key_up is true when no key has been pressed since 
    //DLT key pressed 
    if(prv_key_up) return true;

    //LT cycle completed
    //SSLT is used as LT
    prv_key_up = true;
    //uint16_t kc = keymap_key_to_keycode(dlt_layer_to_toggle,prv_keypos);
    //print_val_bin16(kc);
    _send_key(dlt_layer_to_toggle,prv_keypos);
    return false;
  }
  return true;
};



