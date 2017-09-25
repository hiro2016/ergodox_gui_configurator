import sys
from PyQt5 import QtCore

from GUIComponents.macro_recorder_gui import MacroRecorderGUI
from GUIComponents.GUIBase import GUIBase
from PyQt5.QtGui import QFont, QIcon
from PyQt5.QtWidgets import QTextEdit, QVBoxLayout, QApplication, QHBoxLayout, QLabel, QPushButton, QLineEdit, \
    QDialog, QMessageBox

from NoneGUIComponents.macro_composer import MacroComposer


class DualFunctionMacroGW(GUIBase):
    """
    Generate C code for qmk macro.
    Unless user canceled or did nothing, the generated code is
    available via getData method
    todo macro generation code needs to be separated from gui.
    """
    def __init__(self):
        super(DualFunctionMacroGW, self).__init__()
        self.__init_gui()
        self.__init_listener()
        self.generated_macro_code = None
        self.key_tap = ""
        self.key_hold = ""
        self.key_tap_code = ""
        self.key_hold_code = ""


    def close(self):
        super().close()

    def __init_gui(self):
        self.main_v_layout = ml = QVBoxLayout()
        #timer for detecting a long hold
        hl = QHBoxLayout()
        l = QLabel("Length in milliseconds to\n"
                   "hold the key to trigger\n"
                   "the main macro")
        self.keypress_threshold = e = QLineEdit()
        e.setText("200")
        e.setAlignment(QtCore.Qt.AlignRight)

        hl.addWidget(l)
        hl.addWidget(e)
        hl.addWidget(QLabel("ms"))
        hl.setSpacing(10)
        ml.addLayout(hl)


        # long hold macro
        hl = QHBoxLayout()
        self.generate_code_for_holding_button = b = QPushButton(
            QIcon(),"Start recording macro for when key is held down" )
        hl.addWidget(b)
        ml.addLayout(hl)

        # macro code for short tap
        hl = QHBoxLayout()
        self.generate_code_for_key_tap_button = b = QPushButton(
            QIcon(),"Start recording macro for when key is tapped" )
        hl.addWidget(b)
        ml.addLayout(hl)

        hl = QHBoxLayout()
        self.generated_code_text_edit = e2 = QTextEdit()
        hl.addWidget(e2)
        ml.addLayout(hl)

        # Save and cancel buttons
        hl = QHBoxLayout()
        self.cancel_button = b = QPushButton(QIcon(),"Cancel")
        hl.addWidget(b)
        self.save_button = b = QPushButton(QIcon(),"Save")
        hl.addWidget(b)
        ml.addLayout(hl)

        self.setLayout(ml)

    def get_hold_threshold(self):
        hold_time = self.keypress_threshold.text()
        try:
            hold_time = int(hold_time)
        except Exception as e :
            m = QMessageBox()
            m.setWindowTitle("Something is wrong")
            m.setText("Trouble processing the key holding duration of:%s"%str(e))
            m.show()
            m.exec_()
        return str(hold_time)


    def start_macro_recorder_for_tap(self):
        r = MacroRecorderGUI()
        r.init_font()
        r.show()
        r.exec_()
        self.key_tap_code = r.getData()["macro"]
        #let user edit.
        # getData must fetches data from
        # generated_code_text_edit
        self.generated_code_text_edit.setText(self.generate_code())


    def start_macro_recorder_for_hold(self):
        """
        Generate code that is run once when key is released.
        :return:
        """
        r = MacroRecorderGUI()
        r.init_font()
        r.show()
        r.exec_()
        self.key_hold_code = r.getData()["macro"]
        #let user edit.
        # getData must fetches data from
        # generated_code_text_edit
        self.generated_code_text_edit.setText(self.generate_code())

    def generate_code(self):
        c = MacroComposer()
        c.set_tap_code(self.key_tap_code)
        if self.key_hold_code != "" and self.key_hold_code is not None:
            c.set_hold_code(self.key_hold_code)
            c.set_hold_threshold_in_ms(self.get_hold_threshold())
        return c.generate()

    def __init_listener(self):
        self.generate_code_for_holding_button.clicked.connect(
            self.start_macro_recorder_for_hold )
        self.generate_code_for_key_tap_button.clicked.connect(
            self.start_macro_recorder_for_tap )

        self.save_button.clicked.connect(
            self.save )
        self.cancel_button.clicked.connect(
            self.cancel )

    def save(self):
        self.close()

    def cancel(self):
        self.generated_code_text_edit.clear()
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
        return { "macro": self.generated_code_text_edit.toPlainText()}




if __name__ == "__main__":
    app = QApplication(sys.argv)
    geo = app.desktop().screenGeometry()
    w = geo.width()
    h = geo.height()

    m = DualFunctionMacroGW()
    m.setMinimumWidth((3*w)/4)
    m.setMinimumHeight((3*h)/4)
    m.init_font()
    m.move(0,0)
    m.show()
    r = app.exec_()
    print(m.getData())
    sys.exit(r)
