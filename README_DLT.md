# DLT - an extended TL 
##### Like LT but with more control  
  
### What is Layer
##### Keyboards without layers always send the same signal.    
e.g.

        Press A key -> Signal for A key reaches your system
        
##### Keyboards with layers can send different signals for the same key press
e.g.  

        Hold a function key and press A key -> Signal for LEFT
        press A key -> Signal for A key

Also  

 - There can be multiple function keys or layer keys.  
 - Function keys or layer keys can be like a Caps lock key 


### What is LT  
LT is a qmk action code. 
It allows you to use a single key for input purpose and as a layer key. 

##### How does it work?
LT key looks at how long you are holding the key and decide whether to act as a layer key
 or as a normal key.  
e.g.  

        Hold J key, tap D, Release J -> Signal for ESC
        J key tap -> Signal for J
        
        
## What is DLT and why it's needed?  
#### LT does not tolerate premature LT key release 
e.g.  
     
        Hold LT(layer6,J) key, D key press, Release J key, Release D key -> Signals for J and D 
        
No matter how long you were holding J key, premature TL key release send signals 
in your current layer.

#### DLT limitations 
Unlike LT, DLT evaluates the hold duration at DLT key release time and makes the 
decision when premature DLT key release occurs.   
Nevertheless, people hold down some keys longer that 200ms with some fingers 
while typing a English word.  
  
Spending 250ms for holding one key and then pressing 
another key is bearable but not enjoyable. 
#### Solution and yet another issue
If some fingers like to hold keys longer than others, then setting tapping term
for each finger should solve the problem. Since encoding more than two arguments
in a keycode is not possible, macro must be used.

    case 2:
          if(record->event.pressed){
            uint16_t kc = DLT(6,KC_J);
            //DLT key press & tap threashold
            dlt_threshold = 200;
            
            //DLT key press & key press threashold
            dlt_threshold_key_not_up = 200;
            
            //Key press interval between DLT key and the key before
            dlt_pre_keypress_idling =90;
            
            //If the interval is less than dlt_pre_keypress_idling, 
            //your dlt key hold duration is increased by the 
            //dlt_pre_keypress_idling value.
            dlt_hold_decreased_by = 60;
            
            //If the interval is greater than dlt_pre_keypress_idling, 
            //you dlt key hold duration is increased by the 
            //dlt_pre_keypress_idling value.
            dlt_hold_increased_by =25;
            
            //Makes DLT not tolerate premature DLT key release for 
            //Keys pressed with the same hand. 
            dlt_restrict_same_hand_dlt_action = true;
            
            // While shift, ctrl, alt, gui keys are pressed, 
            //do not switch layer
            dlt_no_layer_toggle_while_modifier_on = true;
            
            process_action_delayed_lt_from_macro(kc,record);
          }else{
            uint16_t kc = DLT(6,KC_J);
            process_action_delayed_lt_from_macro(kc,record);
            dlt_reset();
          }
          break;


Too many configuration options and each parameters require fairly 
delicate treatment. But once it is configured properly, DLT macro
works like a charm. 

### How to use 
Download these two files:  
https://github.com/hiro2016/ergodox_gui_configurator/blob/master/qmk_firmware/delayed_lt.c  
https://github.com/hiro2016/ergodox_gui_configurator/blob/master/qmk_firmware/delayed_lt_macro_support.c  
  
Include them in your keymap.c

        #include "delayed_lt.c"
        #include "delayed_lt_macro_support.c"

Insert ` if(!process_action_delayed_lt(keycode,record)) return false;` to your process_record_user.  

### GUI configuration option for ergodox  
Run the configurator and click any button and you will see the below.  
  
![Alt text](key_configurator.png?raw=true "Key configurator")    

Click set this key as DLT key and you will see the below.  


![Alt text](dlt_config_screen.png?raw=true "Title")    

Currently to view the generated code, you must save your macro first and 
click the key you have configured and then select the radio button 
and click start macro wizard button.  There you can see the macro from your
previous configuration and you may hand edit the code.  

## Using the dlt_restrict_same_hand_dlt_action option with other than ergodox keyboard.
Edit the following section in `delayed_lt.c` for your keyboard.

    //These numbers are for ergodox
    //left hand keys range row 0 to 6 and col 0 to 5
    //right hand keys range row 7 to 13 and col 0 to 5
    #define IS_LEFT_HAND_KEY(keypos) (keypos.row < 7)
    #define IS_SAME_HAND_KEY(key1, key2) (IS_LEFT_HAND_KEY(key1)==IS_LEFT_HAND_KEY(key2))
    
  






 
 
 
        
   
        