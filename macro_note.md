### Be aware of inline functions  
Use of biggish inline functions in macro causes 
hex file bloating. Ones that declare 
a variable within are particularly dangerous.  

### Use core TMK functions as much as possible  
QMK is a thick layer placed on top of TMK 
and the real jobs are done by tmk core. Reducing
dependencies is always a good idea.  
  
### Useful functions  

#### Layer related  
tmk_keyboard/tmk_core/common/action_layer.c

 - layer_move  
 `layer_state = 2;` etc sometimes does not work.  
 `layer_state = 1UL << 2` or use shortcut like layer_move.  
 - layer_on  
 Used to temporarily turn on a higher layer.  
 Due to how layer toggling works, you cannot 
 `layer_on(1)` while you are on layer 2 or on 
 a higher layer. 
 
 - layer_off  
 Undo the effect of layer_on  
 - biton32  
 biton32(layer_state) returns the current layer.
 
 
 Note: 
 layer_state records the current layer 
 as a bit positions.  
 e.g.  
     
     # layer 5 is on  
     layer state value = 1000
     
     # layer 0 is on  
     layer state value = 0000
     
     # layer 1 is on  
     layer state value = 0001
     
     # layer_on(5) has been called while on layer 1.
     # layer_off(5) will move back the layer to 1.
     layer state value = 1001

#### Key events  
 - register_code  
 sends event key pressed
 - unregister_code  
 sends event key released  
 