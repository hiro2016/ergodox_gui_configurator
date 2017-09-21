from NoneGUIComponents.keymap import Keymap
from NoneGUIComponents.key_conf_dict_parser import KeyConfDictParser, MacroIDPool
from NoneGUIComponents.macro_composer import MacroComposer


class KeymapsToCodeTransformer:
    def __init__(self, keymap_array:[Keymap]):
        MacroIDPool.reset()
        self.keymap_array = keymap_array
        self.keymap_expression_string = ""
        self.macro_code = []

        # macro timer definitions
        self.field_members_to_add = []


    def _dict_to_string(self, d:dict) -> str:
        p = KeyConfDictParser(d)
        if p.is_macro():
            code = p.to_macro_code()
            m =MacroComposer()
            # KeyConfDictParser already have assigned unique id to macro
            m, d = m.make_macro_timer_name_unique(code,p.macro_id)
            self.macro_code.append(m)
            self.field_members_to_add.append(d)
        return p.to_keymap_element()

    def dict_to_name_string(self, d):
        k = KeyConfDictParser(d)
        return k.to_descriptive_string()

    def _keymap_to_string(self, keymap_2d_array):
        out = []
        m = keymap_2d_array

        # m is currently dict
        def format_and_add(d):
            if d is None:
                d = {}
            data = self._dict_to_string(d)
            data += ","
            out.append(data)

        for c in range(0,7):
            format_and_add(m[0][c])
        out.append("\n")
        for c in range(0,7):
            format_and_add(m[1][c])
        out.append("\n")
        for c in range(0,6):
            format_and_add(m[2][c])
        out.append("\n")
        for c in range(0,7):
            format_and_add(m[3][c])
        out.append("\n")
        for c in range(0,5):
            format_and_add(m[4][c])
        out.append("\n")
        for c in range(0,2):
            format_and_add(m[5][c])
        out.append("\n")
        format_and_add(m[6][c])
        out.append("\n")
        for c in range(0,3):
            format_and_add(m[7][c])
        out.append("\n")
        out = "".join(out)
        return out

    def generate_code(self, sourc_keymapc:str, dest: str)->dict:
        """
        :return: dict

        'keymap': `[0] = KEYMAP(...),[1]=KEYMAP(...),[n]=...` macro expressions.

        'macro': macro code to be placed in `action_get_macro`'s switch statements.

        'members':field member definitions to be added to keymap.c.

        An example of where macro code goes into
              switch(id) {
                case 0:
                    if (record->event.pressed) {
                        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
                    }
                    break;
                // macro is inserted here
                .
                .
                .
                }

        An example of members
            uint16_t gui_macro_editor_timer_65 = 0;
        """
        keymap = []
        macro = []
        member_definitions = []
        for i, k in enumerate(self.keymap_array):
            k, m, d = self._generate_code_from_keymap(k)
            keymap.append('[%s] = %s' % (i ,k) )
            macro.append(m)
            member_definitions.append(d)

        keymap = '\n'.join(keymap)
        macro = '\n'.join(macro)
        member_definitions = '\n'.join(member_definitions)
        return {'keymap':keymap, 'macro':macro,'members': member_definitions}



    def _generate_code_from_keymap(self, keymap: Keymap):
        rm = keymap.right_hand_keymap
        lm = keymap.left_hand_keymap
        rm = self._keymap_to_string(rm)
        lm = self._keymap_to_string(lm)
        rm = rm.rstrip("\n")
        rm = rm.rstrip(",")
        new_map = "KEYMAP(  \n %s \n %s )," % (lm,rm)
        macro_code = '\n'.join(self.macro_code)
        field_members_to_add = "\n".join(self.field_members_to_add)
        self.field_members_to_add = []
        self.macro_code = []
        return new_map, macro_code, field_members_to_add

if __name__ == '__main__':
    d = {'a':'a'}
    t =KeymapsToCodeTransformer([])
    data = t._dict_to_string(d)
    print(data)
