from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QHBoxLayout, QComboBox, QLabel, QVBoxLayout

class SelectSpecialActionComponent(QVBoxLayout):
    # For adding hid usag ids, look at:
    # http://www.usb.org/developers/hidpage/Hut1_12v2.pdf
    qmk_options = {
        "None":None,
        "TT":"TT",
        "MO":"MO",
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
        'RGUI/RWIN': '0xe7'
    }
    qmk_options_params = [ str(v) for v in range(0,10) ]

    def __init__(self):
        super(SelectSpecialActionComponent, self).__init__()
        self.__init_gui()
        self.__init_listener()

    def __init_gui(self):
        hbl = QHBoxLayout()
        l = QLabel("sends")
        cb = self.special_action_combo_box = QComboBox()
        for o in self.qmk_options.keys():
            cb.addItem(QIcon(),o)
        cb.setCurrentText("None")

        hbl.addWidget(l)
        hbl.addWidget(cb)
        self.addLayout(hbl)


        # let user choose a parameter
        # e.g. 1 in TL(1, KC_T)
        hbl = QHBoxLayout()
        l = QLabel("Layer")
        hbl.addWidget(l)
        cb = self.long_press_arg_combo_box = QComboBox()
        cb.setEnabled(False)
        for o in self.qmk_options_params:
            cb.addItem(QIcon(),o)

        hbl.addWidget(cb)
        self.addItem(hbl)

    def __init_listener(self):
        self.special_action_combo_box.currentTextChanged.connect(self.onCurrentTextChanged)


    def getData(self) -> dict:
        # prevents key error later
        data = {'special_action':None,'special_action_param':None}
        ct = self.special_action_combo_box.currentText()
        if ct is None or str(ct) == "None":
            return data

        data["special_action"] = v = self.qmk_options[ct]
        if self.long_press_arg_combo_box.isEnabled():
            data["special_action_param"] = self.long_press_arg_combo_box.currentText()
        return data

    def onCurrentTextChanged(self, txt):
        enable = False
        txt = str(txt)
        for selection in  [ "MO", "TO", "TG", "TL","TT"]:
            if txt == selection:
                enable = True
                break
        if enable:
            self.long_press_arg_combo_box.setEnabled(True)
        else:
            self.long_press_arg_combo_box.setEnabled(False)

    def setEnabled(self,state:bool):
        self.long_press_arg_combo_box.setEnabled(state)
        self.special_action_combo_box.setEnabled(state)



