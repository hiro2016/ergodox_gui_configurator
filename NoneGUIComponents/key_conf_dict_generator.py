import re

from NoneGUIComponents.dict_keys import *
from collections import defaultdict

from NoneGUIComponents.key_conf_dict_parser import KeyConfDictParser


class KeyConfDictGenerator:
    def __init__(self):
        self.code = ""
        self.macro_name = ""
        self.macro_ids = []
        self.macro_type = ""

        #leave these for now
        self.main_keypress_interceptor = {}
        self.select_long_key_press_option_component = {}
        self.select_special_action = {}
        self.select_modifier_mask_component = {}

    def set_code(self,code):
        self.code = code

    def set_macro_name(self,name):
        self.macro_name = name

    def set_macro_ids(self, ids:list):
        self.macro_ids = ids

    def set_macro_type(self,macro_type):
        self.macro_type = macro_type

    def _clean_code_comment(self):
        # add name as comment
        self.code = re.sub("//.*?\n","",self.code)

    def _prepend_comment_to_code(self):
        if self.macro_name != "":
            self.code = "// "+self.macro_name + "\n" + self.code

    def to_macro_dict(self):
        """
        Used by macro Editor
        :return:
        """
        self._clean_code_comment()
        self._prepend_comment_to_code()
        macro = {
            key_macro_code:self.code,
            key_macro_name: self.macro_name,
            key_macro_ids:self.macro_ids,
            key_macro_type: self.macro_type
        }
        return macro
    def set_macro_dict(self,d:dict):
        """
        Used by key configurator
        :return:
        """
        dd = defaultdict(lambda : "")
        dd.update(d)
        d = dd
        self._clean_code_comment()
        self._prepend_comment_to_code()

        self.code = d[key_macro_code]
        self.macro_name = d[key_macro_name]
        self.macro_ids = d[key_macro_ids]
        if self.macro_ids == "":
            self.macro_ids = []
        self.macro_type =d[key_macro_type]

    def to_dict(self):
        d = self.main_keypress_interceptor
        d.update(self.select_long_key_press_option_component)
        d.update(self.select_special_action)
        d.update(self.select_modifier_mask_component)
        d[key_macro] = self.to_macro_dict()
        d[key_key_name] = self.get_keyname(d)
        return d

    @staticmethod
    def get_keyname(key_conf_dict:dict):
        d = key_conf_dict
        p = KeyConfDictParser(d)
        if p.is_macro():
            return '' # Macro should use macro_name
        t = p.to_keymap_element()
        # check if keymap_element contains hid_usage_id that
        # needs to be translated.
        #
        if p.special_action != "":
            return KeyConfDictGenerator._line_break_label(p.keyname)

        # Note: when user chooses the keycode to assign to a key from
        # drop down menu, p.hid_usage_id is empty;bad design.
        # todo fix this.
        if p.hid_usage_id != "" and t.index(str(p.hid_usage_id)) > -1:
            t = t.replace(str(p.hid_usage_id), p.keyname)
        else:
            # when user selects input from drop down menu
            t = p.keyname
        return KeyConfDictGenerator._line_break_label(t)

    @staticmethod
    def _line_break_label(button_label):
        """
        :param button_label:
        :return:
        """
        nl = []
        if len(button_label)<= 10:
            return button_label

        while len(button_label)>10:
            l = button_label[0:10]
            button_label = button_label[10:]
            nl.append(l)
        nl.append(button_label)

        return "\n".join(nl)
