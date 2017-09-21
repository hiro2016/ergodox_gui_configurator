import sys
from GUIComponents.macro_recorder_gui import MacroRecorderGUI
from GUIComponents.GUIBase import *
from GUIComponents.dual_function_macro_generation_wizzard import DualFunctionMacroGW

from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QWidget, QSizePolicy, QVBoxLayout, QApplication, QLabel, QHBoxLayout, QPushButton, QTextEdit

from NoneGUIComponents.macro_composer import MacroComposer


class MacroEditor(GUIBase):
    def __init__(self,prv_macro):
        super(MacroEditor, self).__init__()
        self.code = ""
        self.setSizePolicy(
            QSizePolicy.Expanding,
            QSizePolicy.Expanding )
        self.__init_gui(prv_macro)
        self.__init_listeners()

    def __init_gui(self,prv_macro):
        self.top_layout = tl = QVBoxLayout(self)
        l = QLabel("Available actions")
        tl.addWidget(l)
        tl.addWidget(self.create_horizontal_separator())

        # Simple macro
        hl = QHBoxLayout()
        hl.setSpacing(10)
        L = QLabel("Create a simple macro that sends \n"
                   "your keystrokes" )
        hl.addWidget(L)
        self.recorder_button = b = QPushButton(
            QIcon(),"Record your keystrokes as macro")
        hl.addWidget(b)
        tl.addLayout(hl)
        self.setLayout(tl)
        tl.addWidget(self.create_horizontal_separator())

        # Dual function macro
        hl = QHBoxLayout()
        hl.setSpacing(10)
        L = QLabel("Create a macro that is triggered \n"
                   "when the key is held down for X\n"
                   "milliseconds ")
        hl.addWidget(L)
        self.create_dfm_button = b = QPushButton(
            QIcon(),"Create a dual function macro")
        hl.addWidget(b)
        tl.addLayout(hl)
        tl.addWidget(self.create_horizontal_separator())

        # generated code view
        l = QLabel("Generated macro code(Editable)")
        tl.addWidget(l)
        self.code_view_text_edit = e =QTextEdit()
        tl.addWidget(e)
        e.setText(prv_macro)

        def save():
            self.close()
        def cancel():
            self.code_view_text_edit.clear()
            self.close()

        hl = QHBoxLayout()
        hl.setSpacing(10)
        b = QPushButton(QIcon(),"Cancel")
        b.clicked.connect(cancel)
        hl.addWidget(b)
        b = QPushButton(QIcon(),"Save")
        b.clicked.connect(save)
        hl.addWidget(b)
        tl.addLayout(hl)



    def __init_listeners(self):
        self.recorder_button.clicked.connect(self.show_macro_recorder_gui)
        self.create_dfm_button.clicked.connect(self.show_dfm_generator_wizzard)

    def show_dfm_generator_wizzard(self):
        w = DualFunctionMacroGW()
        w.show()
        w.exec_()
        d = w.getData()
        self.code = d["macro"]
        self.code_view_text_edit.setPlainText(self.code)

    def show_macro_recorder_gui(self):
        mr = MacroRecorderGUI()
        mr.show()
        mr.exec_()
        d = mr.getData()
        c = MacroComposer()
        c.set_tap_code(d["macro"])
        self.code = c.generate()
        if self.code is not None and self.code != "":
            self.code_view_text_edit.setPlainText(self.code)


    def getData(self):
        # User might have edited the content manually
        self.code = self.code_view_text_edit.toPlainText()
        return {"macro":self.code}



if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = MacroEditor()
    w.show()
    r = app.exec_()
    print(w.getData())
    sys.exit(r)
