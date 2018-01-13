from collections import defaultdict

class MacroIDPool:
    """
    This is not an ideal place but moved from keymap_to_code_transforemer
    due to dependency issue;python does not like circular dependencies.
    """
    pool = [ n for n in range(10,128)]
    @staticmethod
    def get_id():
        return MacroIDPool.pool.pop(len(MacroIDPool.pool)-1)

    @staticmethod
    def reset():
        """
        Not a good design but when Keymap object
        attempt to generate KEYMAP and macro code
        more than once, this method needs to be called.
        So ids no that are no longer used become available.

        todo come up with a better design.
        :return:
        """
        MacroIDPool.pool =[ n for n in range(10,128)]

class KeyConfDictParser:
    """
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
        self.keyname = d['keyname']
        self.macro_code = d['macro']
        self.macro_name = d['macro_name']

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
        if self.macro_code != "":
            self.macro_id = MacroIDPool.get_id()

    def is_macro(self):
        if self.macro_code != "":
            return True
        return False

    def to_macro_code(self):
        if self.macro_code == "":
            raise ValueError(
                "dict contained Non or null for "
                "macro has not been provided")

        code = """
    case %s:
        %s
        break;
    """% (self.macro_id,self.macro_code.strip())
        return code

    def to_keymap_element(self):
        if self.macro_code != "":
            return "M(%d)" % self.macro_id

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


if "__main__" == __name__:
    macro = \
    """if(record->event.pressed){
            return MACRO(T(H),T(I),END);
        }
    """
    p = KeyConfDictParser({'macro':macro})
    print(p.is_macro())
    print(p.to_keymap_element())
    print(p.to_macro_code())


    p = KeyConfDictParser({'hid_usage_id':"0x10"})
    print(p.is_macro())
    print(p.to_keymap_element())
    # print(p.to_macro_code())
