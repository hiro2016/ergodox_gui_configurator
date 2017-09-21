import sys
from PyQt5 import QtCore

from GUIComponents.macro_recorder_gui import MacroRecorderGUI
from GUIComponents.GUIBase import GUIBase
from PyQt5.QtGui import QFont, QIcon
from PyQt5.QtWidgets import QTextEdit, QVBoxLayout, QApplication, QHBoxLayout, QLabel, QPushButton, QLineEdit, \
    QDialog, QMessageBox
from NoneGUIComponents.macro_recorder import MacroRecorder


class KeySelector(GUIBase):
    key_hid_usage_id = 'hid_usage_id'
    def __init__(self):
        super(KeySelector,self).__init__()
        self.macro_recorder = r = MacroRecorder()
        r.keypressed.connect(self.onKeyPressed)


        ml = QVBoxLayout()
        ml.addWidget(QLabel("Press a key"))

        # hid usage id
        hl = QHBoxLayout()
        l =QLabel("hid usage id: ")
        hl.addWidget(l)
        self.hid_usage_id = l = QLabel("")
        hl.addWidget(l)
        ml.addLayout(hl)

        # keyname
        hl = QHBoxLayout()
        l = QLabel("keyname: ")
        hl.addWidget(l)
        self.keyname = l = QLabel("keyname: ")
        hl.addWidget(l)
        ml.addLayout(hl)

        #close button
        b = QPushButton(QIcon(),"Done")
        b.clicked.connect(self.close)
        ml.addWidget(b)
        self.setLayout(ml)


        self.macro_recorder.start()


    def onKeyPressed(self, hid_id, key_name, code):
        self.keyname.setText(key_name)
        self.hid_usage_id.setText(hid_id)

    def getData(self):
        """
        :return: {"hid_usage_id":hid_usage_id}
        """
        return {"hid_usage_id":self.hid_usage_id.text()}
    def close(self):
        self.macro_recorder.stop()
        super().close()
