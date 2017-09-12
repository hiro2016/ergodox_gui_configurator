"""
Part of scancode_viewer.
Let user select action to perform when a key is long-pressed.
"""
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QHBoxLayout, QComboBox, QLabel, QVBoxLayout

class SelectLongKeyPressOptionComponent(QVBoxLayout):
    qmk_options = {
        "None":None,
        "LT": "LT",
        "DLT": "DLT",
        "Shift(SFT_T)":"SFT_T",
        "Control(CTL_T)":"CTL_T",
        "Alt":"ALT_T"
    }
    qmk_options_params = [ str(v) for v in range(0,10) ]

    def __init__(self):
        super(SelectLongKeyPressOptionComponent,self).__init__()
        self.__init_gui()
        self.__init_listener()

    def __init_gui(self):
        hbl = QHBoxLayout()
        # The selected key acts as on long press
        l = QLabel("Long press sends")
        cb = self.long_press_combo_box = QComboBox()
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
        self.long_press_combo_box.currentTextChanged.connect(self.onCurrentTextChanged)


    def getData(self) -> dict:
        data = {"on_long_press":None,"on_long_press_param":None}
        ct = self.long_press_combo_box.currentText()
        if ct is None or str(ct) == "None":
            return data

        data["on_long_press"] = v = self.qmk_options[ct]
        if self.long_press_arg_combo_box.isEnabled():
            data["on_long_press_param"] = self.long_press_arg_combo_box.currentText()
        return data

    def onCurrentTextChanged(self, txt):
        if str(txt) == "LT" or str(txt) == "DLT":
            self.long_press_arg_combo_box.setEnabled(True)
        else:
            self.long_press_arg_combo_box.setEnabled(False)

    def setEnabled(self,state:bool):
        self.long_press_arg_combo_box.setEnabled(state)
        self.long_press_combo_box.setEnabled(state)



