from collections import defaultdict

from NoneGUIComponents.macro_id_pool import MacroIDPool
from NoneGUIComponents.dict_keys import *


class KeyConfDictParser:
    """
    ***!!!WARNING!!!**
    Currently fetches macro id from MacroIDPool if given dict contains a macro
    and if it does not have an id assigned yet.
    If you are just using this class to peek what's inside of a dict, you must
    release the id.
    *******

    An individual key's configuration is
    stored in dict object;this is to
    make pickling easier.

    This class parses that dict object containing
    a key's configuration and converting it to a
    string representations that can be inserted into
    `keymap.c` or into an appropriate section of
    `action_get_macro` function.

    Also handles macro.
    """
    def __init__(self,d:dict):
        # return empty string by dafault rather than KeyError
        dd = defaultdict(lambda :'')
        if d is None:
            d = {}

        for k in d.keys():
            dd[k] = d[k]
        d = dd

        self.hid_usage_id = d['hid_usage_id']
        self.long_press = d["on_long_press"]
        self.long_press_param = d["on_long_press_param"]
        self.special_action_param = d["special_action_param"]
        self.special_action = d["special_action"]
        self.modifier_mask = d["modifier_mask"]
        self.modifier_mask2 = d["modifier_mask2"]
        self.keyname = d[key_key_name]

        self.macro_code = d[key_macro]
        # now macro_code should be dict
        if type(self.macro_code) is dict:
            t = self.macro_code
            self.macro_ids = t[key_macro_ids]
            self.macro_name = t[key_macro_name]
            self.macro_type = t[key_macro_type]
            self.macro_code = t[key_macro_code]
        else:
            self.macro_ids = []
            self.macro_name = d[key_macro_name]
            self.macro_type = ""


        for atr in self.__dict__.keys():
            if getattr(self,atr) is None:
                setattr(self,atr,'')

        # Making sure nothing is set to None
        # It can happen when set explicitly.
        # if self.hid_usage_id is None:
        #     self.hid_usage_id = ''
        # if self.keyname is None:
        #     self.keyname = ''
        # if self.long_press is None:
        #     self.long_press = ''
        # if self.long_press_param is None:
        #     self.long_press_param = ''
        # if self.special_action is None:
        #     self.special_action = ''
        # if self.special_action_param is None:
        #     self.special_action_param = ''
        # if self.modifier_mask is None:
        #     self.modifier_mask = ''
        # if self.modifier_mask2 is None:
        #     self.modifier_mask2 = ''
        # if self.macro_code is None:
        #     self.macro_code = ''
        # if self.macro_name is None:
        #     self.macro_name = ''
        #
        # self.macro_id = None

    def is_macro(self):
        if self.macro_code.strip() != "":
            return True
        return False

    def assign_id_if_no_id_bound(self):
        # to be removed, handle old macro code generation script that
        # do not assign a macro id.
        if self.is_macro() and self.macro_type == "" and len(self.macro_ids) == 0:
            id = MacroIDPool.get_id()
            self.macro_ids.append(id)
            case_statement  = "case %s:\n" % (id)
            self.macro_code = case_statement + self.macro_code + "\n break;"


    def to_keymap_element(self):
        if self.is_macro():
            self.assign_id_if_no_id_bound()
            return "M(%s)"%(self.macro_ids[0])
        data = self.hid_usage_id

        # TT, TG, RESET, etc
        if self.special_action != "":
            data = self.special_action
            if self.special_action_param != '':
                data = data + '(' + self.special_action_param + ')'
            return data

        if data == '':
            # can happen
            return "KC_TRNS"

        if self.modifier_mask != "":
            data = self.modifier_mask + '(' + data + ')'
        if self.modifier_mask2 != "":
            data = self.modifier_mask2 + '(' + data + ')'

        if self.long_press_param != '':
            data = self.long_press + "(" + self.long_press_param + ", " + data + ")"
        elif self.long_press != '':
            data = self.long_press + "(" + data + ")"
        return data

    def to_descriptive_string(self):
        s = self.keyname
        if s == '':
            s = self.special_action
            if self.special_action_param != '':
                s = s + '(' + self.special_action_param + ')'
        s += "\n"
        if self.modifier_mask != '':
            s += "m:" + self.modifier_mask
        s += "\n"
        if self.long_press != '':
            s += 'lp:' + self.long_press
        if self.long_press_param != '':
            s += '(' + self.long_press_param + '...'
        s += "\n"
        return s

    def get_macro_id_count(self):
        return len(self.macro_ids)

    def release_macro_ids(self):
        if len(self.macro_ids) == 0:
            return
        MacroIDPool.mark_as_not_in_use(self.macro_ids)


if "__main__" == __name__:
    macro = \
    """if(record->event.pressed){
            return MACRO(T(H),T(I),END);
        }
    """
    p = KeyConfDictParser({'macro':macro})
    print(p.is_macro())
    print(p.to_keymap_element())


    p = KeyConfDictParser({'hid_usage_id':"0x10"})
    print(p.is_macro())
    print(p.to_keymap_element())
