import time

import pickle

from NoneGUIComponents.keymap import Keymap
from NoneGUIComponents.key_conf_dict_parser import KeyConfDictParser
from NoneGUIComponents.dict_keys import *
from NoneGUIComponents.macro_composer import MacroComposer
from NoneGUIComponents.macro_id_pool import MacroIDPool


class KeymapsToCodeTransformer:
    """
    Converts a list of Keymap class objects to strings that
    can be inserted into the content of
    keymap_source.c
    """
    def __init__(self, keymap_array:[Keymap]):
        self.keymap_array = keymap_array
        self.keymap_expression_string = ""
        self.macro_code = []

        # macro timer definitions
        self.field_members_to_add = []


    def _handle_key_dict(self, d:dict) -> str:
        """
        :param d: dictionary
        :return:
        Takes an configuration for a single key.
        Generates a keycode to to be inserted into KEYMAP macro in keymap.c file.
        As a side effect, prepare macro code and field variables used for insertion.
        """
        p = KeyConfDictParser(d)
        p.assign_id_if_no_id_bound()
        p = self._prepare_macro_code_to_be_inserted(p)
        return p.to_keymap_element()

    def _prepare_macro_code_to_be_inserted(self, p:KeyConfDictParser):
        if not p.is_macro():
            return p
        # CTL receptor use two macro ids; the first should be inserted into KEYMAP.
        # somescript still does not assign macro id; to be removed
        code = p.macro_code
        m = MacroComposer()
        # KeyConfDictParser already have assigned an unique id to macro
        if m.is_contain_macro_gui_timer(code):
            m, d = m.make_macro_timer_name_unique(
                code,str(time.time()).replace('.','_'))
            self.field_members_to_add.append(d)
            self.macro_code.append(m)
        else:
            self.macro_code.append(code)
        return p

    def _dict_to_name_string(self, d):
        k = KeyConfDictParser(d)
        return k.to_descriptive_string()

    def _keymap_to_string(self, keymap_2d_array):
        keycodes = []
        m = keymap_2d_array

        # m is currently a dict
        def format_and_add(d):
            if d is None:
                d = {}
            keycode = self._handle_key_dict(d)
            keycode += ","
            keycodes.append(keycode)

        for c in range(0,7):
            format_and_add(m[0][c])
        keycodes.append("\n")
        for c in range(0,7):
            format_and_add(m[1][c])
        keycodes.append("\n")
        for c in range(0,6):
            format_and_add(m[2][c])
        keycodes.append("\n")
        for c in range(0,7):
            format_and_add(m[3][c])
        keycodes.append("\n")
        for c in range(0,5):
            format_and_add(m[4][c])
        keycodes.append("\n")
        for c in range(0,2):
            format_and_add(m[5][c])
        keycodes.append("\n")
        format_and_add(m[6][c])
        keycodes.append("\n")
        for c in range(0,3):
            format_and_add(m[7][c])
        keycodes.append("\n")
        keycodes = "".join(keycodes)
        return keycodes

    def generate_code(self)->dict:
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
        # todo remove this
        # every key configuration dict should have at least
        # one id bound to it. But since old scripts that
        # expects ids to be assigned to each key at this stage
        # still exist, the line below store the MacroIDPool state
        # so as to avoid exhausting ids in MacroIDPool when compile
        # is requested multiple times.
        macro_id_pool_state = MacroIDPool._pool.copy()
        keymaps = []
        macro = []
        member_definitions = []
        for i, k in enumerate(self.keymap_array):
            # k contains a single layer
            k, m, d = self._generate_code_from_keymap(k)
            keymaps.append('[%s] = %s' % (i ,k) )
            macro.append(m)
            member_definitions.append(d)

        keymaps = '\n'.join(keymaps)
        macro = '\n'.join(macro)
        member_definitions = '\n'.join(member_definitions)
        MacroIDPool._pool = macro_id_pool_state
        return {key_keymaps:keymaps, 'macro':macro,'members': member_definitions}



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
    file_in = "/home/d/PycharmProjects/GUIConfigurator/ctd_jis_kana_nichola_with_qwerty_layouts_for_jis_and_us_layouts.ekm"
    file_out = "/home/d/PycharmProjects/GUIConfigurator/test_out.c"

    # The outer most is the 9 layers of keymap.
    layers = []
    with open(file_in,"rb") as f:
        layers = pickle.load(f)

    # for i, layer in enumerate(layers):
    #     print('------------ left-----------')
    #     print(left)
    #     print('------------ right-----------')
    #     print(right)

    keymaps=[]
    for l in layers:
        k = Keymap()
        k.set_data(l)
        keymaps.append(k)

    t =KeymapsToCodeTransformer(keymaps)
    d = t.generate_code()
    for k in d.keys():
        print(k)
        print(d[k])





    # d = {'a':'a'}
    # t =KeymapsToCodeTransformer([])
    # data = t._handle_key_dict(d)
    # print(data)
