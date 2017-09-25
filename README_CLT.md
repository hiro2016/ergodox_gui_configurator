# CLT macro function - emulating delayed shift  
##### Pressing two keys together rather than hold shift/layer-key then press another key


### Background and what CLT macro function does  
Inputting an non-latin literal often requires multiple key strokes to input a single 
literal.  
Some input systems use multiple keys as OSL keys and make those OSL keys themselves 
subject to the effect of other OSL keys.  

e.g.  

 - press y then a inputs `や`  
 - press g then y and then a inputs `ぎゃ` 
 
`y` is an OSL key and at the same time its role changes when preceded by another OSL 
key press.
 
 
Some other systems use constant dedicated OSL keys that have a constant role in all layers.  

e.g. 
 _ press a inputs `た`
 - press right shift with a inputs `ぬ`  
 
   
Methods involve constant dedicated OSL keys generally accepts OSL key presses to be delayed 
to some extend meaning:  
  
e.g. 
    
    press A and then press right shift inputs `ぬ`
    press right shift and then a inputs `ぬ`
    
Delaying OSL key press does not change the result.

 
CLT macro function is written to mimic the above mentioned behaviour.
  

# How to use  
Include the following files in your `keymap.c`  

    #include "delayed_lt.c"
    #include "delayed_lt_macro_support.c"
    #include "combo_lt.c"
    
And hand code!  

###Or Use GUI configuration tool

#### Configure layer emitter key
Run the configuration tool and click a key that represents a Right thumb button.   
You will see the below.
Select Assign macro radio button and click 'Start macro wizard button'.   
![Alt text](key_configurator.png?raw=false "Key configurator")    
  
When the below appears, click `Create a combo emitter macro` button.   
![Alt text](macro_wizard.png?raw=false "Key configurator")    
  
  
Click `select a key` button and once pop up appears press enter.  
Also select the layer to temporarily switch to when another key is 
pressed with this key.
![Alt text](clt_emitter_config.png?raw=false "Key configurator")     
    
Save your macro by clicking numerous save buttons and name your macro and then 
again save.    
![Alt text](key_configurator.png?raw=false "Key configurator")    


Now Layer key has been taken care of.


#### Configure receiver key
At configurator's main window, click a key.   
When the pop up window appears, click `Start macro wizard` button.  
Then click `create a combo receiver macro` button from the list below. 
![Alt text](macro_wizard.png?raw=false "Key configurator")    

Click `record macro` to record your tapped alone time macro.    
![Alt text](clt_receiver_config.png?raw=false "Key configurator")      
  
Click `Start recording` button and perform key strokes the macro should copy.
    
![Alt text](macro_recorder.png?raw=false "Key configurator")    
  
Save your macro by clicking numerous save buttons and name your macro and then 
again save.    
![Alt text](key_configurator.png?raw=true "Key configurator")    


### Configure a key in another layer 
At this point, there is nothing assigned to the keys in other layers.  
  
At the configurator's top, select the tab for the layer to which 
the thumb key switches the layer to and configure the button found 
in the same position as the receiver key you have just configured.  
  
Configure it to send a different key sequence; if last time you have 
configured the receiver key to register `t@`, then this time maybe 
configure the key to register `t` alone.  
  
   
### Done  
Compile and flash and test.  
When the thumb key and the receiver key is pressed down together, `t` should be sent.   
When thumb key alone is topped enter should be sent.  
When receiver key alone is tapped, `t@` should be sent.   
And the order of key presses should not matter.  



## Why CLT macro function is a function to be used in macro and not an action code  
Many non-latin literals are not bound to a single scancode/virtual-keycode
but to a sequence of scancodes;inputting them requires macro.  
Since in QMK or in TMK a macro cannot be used with another action code, creating 
CLT action code for latin alphabets is possible, but doing so for non-latin 
alphabets is not practical.


## A macro code example for people would rather hand code    

        case 6:
          //Constant dedicated OSL key
          clt_layer = 1;//layer to switch to when pressed
          uint16_t kc = KC_SPACE;//keycode to send when tapped alone
          process_combo_lt(kc, record);
          break;
        case 7:
          // A macro for non-OSL key.
          // When tapped alone registers A.
          // When tapped with a key to which M(6) is bound, 
          // registers either a macro or keycode found in
          // clt_layer in the same position.
          if(!record->event.pressed){
            if( (!clt_pressed) ){
              //simple tap
                register_code(KC_A);
                unregister_code(KC_A);
            }else{
                //clt key pressed after this macro key was pressed, 
                //send keycode in another layer
                _send_key(clt_layer, record->event.key);
                clt_pressed = false;
            }
          
          }
          break;
      }


