from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QHBoxLayout, QComboBox, QLabel, QVBoxLayout
from NoneGUIComponents.dict_keys import *

class SelectSpecialActionComponent(QVBoxLayout):
    # For adding hid usag ids, look at:
    # http://www.usb.org/developers/hidpage/Hut1_12v2.pdf
    qmk_options = {
        "None":None,
        "TT":"TT",
        "MO":"MO",
        'OSM':'OSM',
        'OSL':"OSL",
        "TO":"TO",
        "TG":"TG",
        "RESET":"RESET",
        "- and _(us only)":'0x2d',
        "Mute":'0x7f',
        "= and +(us only)":'0x2e',
        '\' and \"(us only)':'0x34',
        'Pause': '0x48',
        'Keyboard Scroll Lock': '0x47',
        'PrintScreen': '0x46',
        'Volume Up':  '0x80',
        'Volume Down':  '0x81',
        'Henkan':'0x8a',
        'Muhenkan':'0x8b',
        'comma/,':'0x8c',
        'power':'0x00',
        'PgDown':'00x4e',
        'PgUp':'00x61',
        'Hiragana':'00x93',
        'Katakana':'00x92',
        'RGUI/RWIN': '0xe7'
    }
    osm_options = [
            'KC_LCTRL',
            'KC_LSHIFT',
            'KC_LALT',
            'KC_LGUI',
            'KC_RCTRL',
            'KC_RSHIFT',
            'KC_RALT',
            'KC_RGUI' ]

    qmk_options_params = [ str(v) for v in range(0,10) ]

    def __init__(self):
        super(SelectSpecialActionComponent, self).__init__()
        self.__init_gui()
        self.__init_listener()

    def __init_special_actions_combo_box(self):
        for o in self.qmk_options.keys():
            self.special_action_combo_box.addItem(QIcon(),o)
        self.special_action_combo_box.setCurrentText("None")

    def __init_special_actions_param_combo_box(self):
        self.special_actions_param_combo_box.clear()
        if self.special_action_combo_box.currentText() == 'OSM':
            for o in self.osm_options:
                self.special_actions_param_combo_box.addItem(QIcon(),o)
        else:
            for o in self.qmk_options_params:
                self.special_actions_param_combo_box.addItem(QIcon(),o)

    def __init_gui(self):
        hbl = QHBoxLayout()
        l = QLabel("sends")
        cb = self.special_action_combo_box = QComboBox()
        self.__init_special_actions_combo_box()

        hbl.addWidget(l)
        hbl.addWidget(cb)
        self.addLayout(hbl)


        # let user choose a parameter
        # e.g. 1 in TL(1, KC_T)
        hbl = QHBoxLayout()
        l = QLabel("Layer")
        hbl.addWidget(l)
        cb = self.special_actions_param_combo_box = QComboBox()
        self.__init_special_actions_param_combo_box()
        self.special_actions_param_combo_box.setEnabled(False)

        hbl.addWidget(cb)
        self.addItem(hbl)

    def __init_listener(self):
        self.special_action_combo_box.currentTextChanged.connect(self.onCurrentTextChanged)


    def getData(self) -> dict:
        # prevents key error later
        data = {
            'special_action':None,
            'special_action_param':None
        }
        ct = self.special_action_combo_box.currentText()
        if ct is None or str(ct) == "None":
            return data

        data["special_action"] = v = self.qmk_options[ct]
        param = None
        if self.special_actions_param_combo_box.isEnabled():
            data["special_action_param"] = param= self.special_actions_param_combo_box.currentText()
        if (ct is not None) and (str(ct) != "None"):
            data[key_key_name] = ct
            if param is not None:
                data[key_key_name] += "("+param+")"

        return data

    def onCurrentTextChanged(self, txt):
        self.__init_special_actions_param_combo_box()
        enable = False
        txt = str(txt)
        for selection in  [ 'OSM','OSL',"MO", "TO", "TG", "TL","TT"]:
            if txt == selection:
                enable = True
                break
        if enable:
            self.special_actions_param_combo_box.setEnabled(True)
        else:
            self.special_actions_param_combo_box.setEnabled(False)

    def setEnabled(self,state:bool):
        self.special_actions_param_combo_box.setEnabled(state)
        self.special_action_combo_box.setEnabled(state)



