import re

from NoneGUIComponents.dict_keys import *
from collections import defaultdict

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
        return d

