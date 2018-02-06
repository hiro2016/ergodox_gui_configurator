import sys
from PyQt5 import QtCore

from GUIComponents.GUIBase import GUIBase
from PyQt5.QtGui import QFont, QIcon
from PyQt5.QtWidgets import QVBoxLayout, QApplication, QHBoxLayout, QLabel, QPushButton, QLineEdit, \
    QComboBox, QWidget, QCheckBox, QTextEdit

from GUIComponents.macro_recorder_gui import MacroRecorderGUI
from NoneGUIComponents.dict_keys import *


class ComboReceptorMacroGW(GUIBase):
    """
    """
    macro_type = "clt_receptor"
    def __init__(self):
        super(ComboReceptorMacroGW, self).__init__()
        self.__init_gui()
        self.__init_listener()
        self.generated_macro_code = ''


    def __init_gui(self):
        self.main_v_layout = ml = QVBoxLayout()

        # keycode
        hl = QHBoxLayout()
        l = QLabel("Macro to run when this key alone is tapped")
        self._set_width_to_50(l)
        hl.addWidget(l)
        self.tapped_alone_macro_text_edit = e = QTextEdit()

        #open KeySelector botton
        self.record_tapped_alone_macro_button = b = QPushButton("Record macro")
        hl.addWidget(e)
        hl.addWidget(b)
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
        tapped_alone_time_macro = self.tapped_alone_macro_text_edit.toPlainText()
        c = [
            'if(!record->event.pressed){',
                tapped_alone_time_macro,
            '}',
            'break;'
        ]
        return '\n'.join(c)

    def __init_listener(self):
        self.save_button.clicked.connect(
            self.save )
        self.cancel_button.clicked.connect(
            self.cancel )
        self.record_tapped_alone_macro_button.clicked.connect(self.record_tapped_alone_macro)

    def record_tapped_alone_macro(self):
        s = MacroRecorderGUI()
        s.show()
        s.exec_()
        self.tapped_alone_macro_text_edit.setText(
            s.getData()[key_macro])

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
            key_macro: self.generated_macro_code,
        }

if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = ComboReceptorMacroGW()
    w.show()
    r = app.exec_()
    print(w.getData())
    print(w.getData()[key_macro])
    sys.exit(r)
