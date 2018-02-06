typedef struct {
  uint16_t id;
  uint16_t default_keycode;
  keypos_t keypos;
  uint16_t time;
} quantum_state_input;

quantum_state_input quantum_state_input_que[4] = {
  {0,0,{126,126},0},
  {0,0,{126,126},0},
  {0,0,{126,126},0},
  {0,0,{126,126},0}
};

quantum_state_input shift_input_que(quantum_state_input* que){
  /*
   * push the elements in quantum_state_input_que to the right.  
   * So as to allow insertion of a new element at the position 0.
   *
   * Only four elements are kept and if anything is spilt from the tail,
   * this function returns that element, 
   * else returns zero initialized quantum_state_input. 
   *
   */

  //recording the default_keycode of the element at position 3.
  quantum_state_input clt = que[3];
  /*print("timer for previous keypress at position 0:");*/
  /*print_val_dec(que[0].time);*/

  que[3] = que[2];
  que[2] = que[1];
  que[1] = que[0];
  que[0] = (quantum_state_input){0,0,{126,126},0};

  /*print("timer for previous keypress now shifted to position 1:");*/
  /*print_val_dec(quantum_state_input_que[1].time);*/

  return clt ;
}

void enque_input(
    const uint16_t id,  
    const uint16_t default_keycode,  
    const keypos_t keypos, 
    const uint16_t time){
  quantum_state_input r = shift_input_que(quantum_state_input_que);
  if(r.id != 0){
    // do nothing as only keypress up to 3 are supported as of now.
    print("queued item removed as quantum_state_input_que was already full.\n");
  }
  quantum_state_input_que[0].id =  id;
  quantum_state_input_que[0].default_keycode =  default_keycode;
  quantum_state_input_que[0].keypos=  keypos;
  quantum_state_input_que[0].time =  time;
  return;
}

//alias for shift_input_que 
inline quantum_state_input shift_input(void){
    return shift_input_que(quantum_state_input_que);
}

bool is_in_input_que(uint16_t id){
  for(uint8_t i=0;i<4;++i){
    if(quantum_state_input_que[i].id==id) return true;
  }
  return false;
}

