import sys
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QHBoxLayout, QComboBox, QLabel, QVBoxLayout, QApplication, QWidget

from NoneGUIComponents.key_conf_dict_parser import KeyConfDictParser


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

    def __init__(self, previous_conf):
        super(SelectModifierMaskComponent, self).__init__()
        self.__init_gui(previous_conf)

    def __init_gui(self,d):
        p = KeyConfDictParser(d)
        hbl = QHBoxLayout()
        l = QLabel("Modifier mask")
        cb = self.modifier_selection_combobox = QComboBox()
        for o in self.options.keys():
            cb.addItem(QIcon(),o)
        pv = p.modifier_mask
        pv = pv if pv != '' else 'None'
        cb.setCurrentText(pv)

        hbl2 = QHBoxLayout()
        l2 = QLabel("Modifier mask 2")
        cb2 = self.modifier_selection_combobox2 = QComboBox()
        for o in self.options.keys():
            cb2.addItem(QIcon(),o)
        pv = p.modifier_mask2
        pv = pv if pv != '' else 'None'
        cb2.setCurrentText(pv)

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
        self.modifier_selection_combobox2.setEnabled(state)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = QWidget()
    # t = ScancodeViewer()
    # t = KeyCodeViewer()
    t = SelectModifierMaskComponent()
    w.setLayout(t)
    w.show()
    r = app.exec_()
    print(t.getData())
    print("calling exit")
    sys.exit(r)
