# CLT macro function - emulating delayed shift  
##### Pressing two keys together rather than hold shift/layer-key then press another key


### What CLT macro function does  
Basically same as combo, but done with layer_toggle and macro. 

    Press K key and D key sends D key press in another layer
    Press D key and K key sends D key press in another layer as the above  
    # two key presses must occure within 200ms
    
Code:  
    
        case 6:
          // macro for K key
          // CLT emitter
          clt_layer = 1;//layer to switch to when pressed
          uint16_t kc = KC_K;//keycode to send when not combo 
          process_combo_lt(kc, record);
          break;
        case 7:
          // A macro for D key.
          if(!record->event.pressed){
            if( (!clt_pressed) ){
              // excuted when not combo
                register_code(KC_A);
                unregister_code(KC_A);
            }else{
                // sending a D key tap in layer 1
                _send_key(clt_layer, record->event.key);
                clt_pressed = false;
            }
          }
          break;
      }
    
  

# How to use  
Include the following files in your `keymap.c`  

    #include "delayed_lt.c"
    #include "delayed_lt_macro_support.c"
    #include "combo_lt.c"
    
Insert ` if(!process_action_delayed_lt(keycode,record)) return false;` to your process_record_user.  
    
And hand code!  

### Or Use GUI configuration tool

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
  
Configure it to send a different key sequence; if you have 
configured the receiver key to register `t@`, then this time maybe 
configure the key to register `t`.  
  
   
### Done  
Compile, flash and test.  
When the thumb key and the receiver key is pressed down together, `t` should be sent.   
When the thumb key alone is tapped enter should be sent.  
When the receiver key alone is tapped, `t@` should be sent.   
And the order of key presses should not matter.  


### A more Advanced example

CLT emitter that is also a receiver.
    
    if(record->event.pressed){
        clt_layer = 7;
    }
    // When not combo, set one shot layer.
    if(!process_combo_lt(OSL(7), record)){
        //Called only when clt_inerrupted is set to true.
        _send_key(clt_layer, record->event.key);
    }
    break;
    
    
CLT emitter that interacts with the above:  

    // CLT emitter that interrupts another CLT emitter  
    if(clt_pressed){
        //handle case where another clt key is already pressed down.
        if(record->event.pressed){
            clt_interrupted = true;
            clt_layer2 = clt_layer;
            // The other CLt key should send a corresponding key in layer9 when up.
            clt_layer = 9;
        }
    }else{
        if(record->event.pressed) {clt_layer = 9;}
    }

    if(!process_combo_lt(0x2c, record)){
    //this key is released before another CLT key
        clt_interrupted = true;
    }
    break;


CLT was not written with the above behaviour in mind, so the code is a little 
forced to say the least but works.