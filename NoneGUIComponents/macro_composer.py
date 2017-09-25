"""
Generates qmk macro from given param values.


Moving all tap code execution to release time simplifies everithyng.
Use cases:
    - Sending modifier like shift when long held -> Need action_code macro can't
    - Simple macro execution on key tap
        if(!record->event.pressed){
            register(KC_H);
            unregister(KC_H);
            register(KC_I);
            unregister(KC_I);
        }


    - A macro triggered on long holding a key
        if(!record->event.pressed){
            gui_macro_editor_timer = record->event.time;
        }else{
            if(200<timer_elapsed(record->event.time)){
                register(KC_H);
                unregister(KC_H);
                register(KC_I);
                unregister(KC_I);
            }else{
                register(KC_B);
                unregister(KC_B);
                register(KC_Y);
                unregister(KC_Y);
            }
        }
"""

class MacroComposer:
    #keymap_source.c must contain the strings below
    keymap_place_holder = "//keymap_place_holder"
    macro_place_holder = "//macro_place_holder"
    field_member_place_holder = '//field_member_place_holder'
    gui_macro_editor_timer_name = 'gui_macro_editor_timer'
    timer_init_code = "%s = record->event.time;" % \
                           gui_macro_editor_timer_name
    timer_init_code_place_holder = "//timer_place_holder"
    code_place_holder = "//place_holder"
    def __init__(self):
        self._tap_code = ""
        self._hold_code = ""
        self._hold_threshold = ""
        self._default_code = """
        if(record->event.pressed){
            //timer_place_holder
        }else{
            //place_holder
        }
        """

    def set_tap_code(self, on_tap):
        self._tap_code = on_tap

    def get_timer_name(self)->str:
        return self.timer_init_code.split('=')[0].strip()

    def get_if_timer_elapsed_conditional(self):
        return "if(%s<timer_elapsed(%s))" % (
            self._hold_threshold, self.get_timer_name())

    def set_hold_code(self, on_hold:str):
        self._hold_code = on_hold

    def set_hold_threshold_in_ms(self, time_in_ms:str)->str:
        # throws error if not valid integer
        print("key hold threshold set to:"+ str(int(time_in_ms)))
        self._hold_threshold = time_in_ms

    def generate(self):
        lc = self._hold_code
        dc = self._default_code
        if dc is None:
            dc = ""
        if lc is None:
            hc = ""

        code = ''
        if(lc == ""):
            # Triggerd on tap only
            return self._generate_code_for_tap_only()
        else:
            # Triggered on hold and another macro executed on tap
            return self._generate_code_for_hold_and_tag()

    def _generate_code_for_hold_and_tag(self):
        # these are copy
        tc = self._tap_code
        dc = self._default_code
        lc = self._hold_code

        # Generate code
        lc = self.get_if_timer_elapsed_conditional() \
             + "{\n                " + lc + "\n            }"
        tc = "else{\n                "+tc+"\n            }"
        c = lc + tc

        # insert timer init
        # later the variable that holds the key press time
        # timer value should be renamed for each macro.
        dc = dc.replace(
            self.timer_init_code_place_holder,
            self.timer_init_code)

        return dc.replace( self.code_place_holder, c)

    def _generate_code_for_tap_only(self):
        tc = self._tap_code
        dc = self._default_code

        # always executed on release
        code = """
        if(!record->event.pressed){
            %s
        }
        """%tc
        return dc.replace(self.code_place_holder,code)

    @staticmethod
    def is_contain_macro_gui_timer(macro_code):
        if MacroComposer.gui_macro_editor_timer_name in macro_code:
            return True

    def make_macro_timer_name_unique(self, macro_code, macro_id):
        """
        Takes macro code and macro id.
        Append macro id to gui_macro_editor_timer.
        :param macro_code:
        :param macro_id:
        :return:
        Refactored macro_code, Unique macro timer definition

        Definition example:
                uint16_t gui_macro_editor_timer_56 = 0;
        """

        new_timer_name = self.gui_macro_editor_timer_name + "_%s" % str(macro_id)
        macro_code = macro_code.replace(
            self.gui_macro_editor_timer_name,
            new_timer_name )
        definition = 'uint16_t ' + new_timer_name + ' = 0;'
        return macro_code, definition

    @staticmethod
    def generate_combo_lt_emitter_macro(hid_id, layer):
        c = [
            'clt_layer = %s;' % layer,
            'process_combo_lt(%s, record);'%hid_id,
            'break;'
            ]
        return '\n'.join(c)

if __name__ == "__main__":
    o = MacroComposer()
    o.set_hold_code("hi")
    o.set_hold_threshold_in_ms("200")
    o.set_tap_code("bye")
    print(o.generate())

    o = MacroComposer()
    o.set_tap_code("bye")
    print(o.generate())
