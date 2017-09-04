from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QHBoxLayout, QComboBox, QLabel, QVBoxLayout

class SelectModifierMaskComponent(QVBoxLayout):
    options = {
        "None":None,
        "RSFT":"RSFT",
        "LSFT":"LSFT",
        "MEH_T":"MEH_T",
        "LCTL":"LCTL",
        "RCTL":"RCTL",
        "LALT":"LALT",
        "RALT":"RALT",
        "LGUI":"GUI",
        'RGUI':"RGUI",
        'HYPR':'HYPR',
        'MEH':'MEH',
        'LCAG':'LCAG'

    }
    qmk_options_params = [ str(v) for v in range(0,10) ]

    def __init__(self):
        super(SelectModifierMaskComponent, self).__init__()
        self.__init_gui()

    def __init_gui(self):
        hbl = QHBoxLayout()
        l = QLabel("Modifier mask")
        cb = self.modifier_selection_combobox = QComboBox()
        for o in self.options.keys():
            cb.addItem(QIcon(),o)
        cb.setCurrentText("None")

        hbl2 = QHBoxLayout()
        l2 = QLabel("Modifier mask 2")
        cb2 = self.modifier_selection_combobox2 = QComboBox()
        for o in self.options.keys():
            cb2.addItem(QIcon(),o)
        cb2.setCurrentText("None")

        hbl.addWidget(l)
        hbl.addWidget(cb)
        hbl2.addWidget(l2)
        hbl2.addWidget(cb2)
        self.addLayout(hbl)
        self.addLayout(hbl2)



    def getData(self) -> dict:
        # prevents key error later
        data = {'modifier_mask':None}
        ct = self.modifier_selection_combobox.currentText()
        ct2 = self.modifier_selection_combobox2.currentText()
        if ct is None or str(ct) == "None":
            return data
        data["modifier_mask"] = self.options[ct]
        if ct2 is None or str(ct) == 'None':
            return data
        data['modifier_mask2'] = self.options[ct2]
        return data


    def setEnabled(self,state:bool):
        self.modifier_selection_combobox.setEnabled(state)


