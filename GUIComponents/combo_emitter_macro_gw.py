import sys
from PyQt5 import QtCore

from GUIComponents.KeySelector import KeySelector
from GUIComponents.GUIBase import GUIBase
from PyQt5.QtGui import QFont, QIcon
from PyQt5.QtWidgets import  QVBoxLayout, QApplication, QHBoxLayout, QLabel, QPushButton, QLineEdit, \
    QComboBox, QWidget, QCheckBox

from NoneGUIComponents.macro_composer import MacroComposer




class ComboEmitterMacroGW(GUIBase):
    key_macro = 'macro'
    macro_type = "clt_emitter"
    def __init__(self):
        super(ComboEmitterMacroGW, self).__init__()
        self.__init_gui()
        self.__init_listener()
        self.generated_macro_code = ''



    def __init_gui(self):
        self.main_v_layout = ml = QVBoxLayout()

        # keycode
        hl = QHBoxLayout()
        l = QLabel("keycode to send")
        self._set_width_to_50(l)
        hl.addWidget(l)
        self.keycode_line_edit = e = QLineEdit()
        #open KeySelector botton
        self.open_key_selector_button = b = QPushButton("Select a key")
        hl.addWidget(e)
        hl.addWidget(b)
        ml.addLayout(hl)
        ml.addWidget(self.create_horizontal_separator())

        # Layer
        hl = QHBoxLayout()
        l = QLabel("Layer to temporarily toggle")
        self._set_width_to_50(l)
        hl.addWidget(l)
        self.layer_combobox = e = QComboBox()
        items = [str(n) for n in range(0,8)]
        e.addItems(items)
        hl.addWidget(e)
        ml.addLayout(hl)
        ml.addWidget(self.create_horizontal_separator())

        # Save and cancel buttons
        hl = QHBoxLayout()
        self.cancel_button = b = QPushButton(QIcon(),"Cancel")
        hl.addWidget(b)
        self.save_button = b = QPushButton(QIcon(),"Save")
        hl.addWidget(b)
        ml.addLayout(hl)

        self.setLayout(ml)

    def _create_descriptive_label(self, description):
        l = QLabel(description)
        l.setWordWrap(True)
        l.setAlignment(QtCore.Qt.AlignTop)
        l.setMaximumHeight(self.getFontHeight()*6)
        return l

    def _set_width_to_50(self,w:QWidget):
        g = self.geometry()
        w.setMaximumWidth(g.width()/2)
        w.setMinimumWidth(g.width()/2)
        w.setWordWrap(True)


    def generate_code(self)->str:
        layer = self.layer_combobox.currentText()
        keycode = self.keycode_line_edit.text()
        return MacroComposer.generate_combo_lt_emitter_macro(keycode,layer)

    def __init_listener(self):
        self.save_button.clicked.connect(
            self.save )
        self.cancel_button.clicked.connect(
            self.cancel )
        self.open_key_selector_button.clicked.connect(self.select_key)

    def select_key(self):
        s = KeySelector()
        s.show()
        s.exec_()
        self.keycode_line_edit.setText(s.getData()[KeySelector.key_hid_usage_id])

    def save(self):
        self.generated_macro_code = self.generate_code()
        self.close()

    def cancel(self):
        self.generated_macro_code = ''
        self.close()

    def init_font(self):
        """
        Must be called after width, height set.
        :return:
        """
        font_size = 12
        while self.getFontHeight() < (self.height()/30):
            self.font = f =QFont()
            f.setPointSize(font_size)
            self.setFont(f)
            font_size += 1

    def getData(self):
        return {
            self.key_macro: self.generated_macro_code,
        }




if __name__ == "__main__":
    app = QApplication(sys.argv)
    geo = app.desktop().screenGeometry()
    w = geo.width()
    h = geo.height()

    m = ComboEmitterMacroGW()
    m.setMinimumWidth((3*w)/4)
    m.setMinimumHeight((3*h)/4)
    m.init_font()
    m.move(0,0)
    m.show()
    r = app.exec_()
    print(m.getData())
    sys.exit(r)
