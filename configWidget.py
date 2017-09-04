import pickle

import os
from collections import defaultdict

import sys
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QWidget, QSizePolicy, QVBoxLayout, QHBoxLayout, QLineEdit, QLabel, QFileDialog, QPushButton, \
    QApplication

"""
Responsible for: 
    providing gui ergodox root path setter
    Loading the default ergodox_root_path
    
Has very strong dependency to main.
"""

def get_exe_path():
    if hasattr(sys, "frozen"):
        full_script_path = os.path.dirname(sys.executable)
        return os.path.realpath(full_script_path)
    else:
        return os.path.dirname(os.path.realpath(sys.argv[0]))
conf_filename = "config"


class ConfigurationManager:
    qmk_path = "" # load settings sets this
    ergodox_root_path = "" # load settings sets this
    def __init__(self):
        self.load_settings()

    @staticmethod
    def load_settings():
        # default
        c = ConfigurationManager
        c.qmk_path = os.path.join(get_exe_path() + "/qmk_firmware")
        c.ergodox_root_path = os.path.join(c.qmk_path,"/keyboards/ergodox")

        # loads last saved values
        # creates if the file does not exist.
        if not os.path.exists(conf_filename):
            with open(conf_filename,"w") as f:
                f.write("")

        dd = defaultdict(lambda :"")
        d = dict()
        with open(conf_filename,"rb") as f:
            try:
                d = pickle.load(f)
            except EOFError:
                # empty config
                pass

        if d is not None:
            for k in d.keys():
                dd[k] = d[k]

        for k in dd.keys():
            v = dd[k]
            if k == "qmk_path" and v == "":
                # use default
                continue
            setattr(ConfigurationManager,k,v)
            if k == "ergodox_root_path" and v == "":
                # use default
                continue

    @staticmethod
    def _save_settings():
        d = {"qmk_path": ConfigurationManager.qmk_path,
             "ergodox_root_path": ConfigurationManager.ergodox_root_path}
        with open(conf_filename,"wb") as f:
            pickle.dump(d,f)

    @staticmethod
    def set_ergodox_root_path(path:str):
        ConfigurationManager.qmk_path = os.path.dirname(
            os.path.dirname(path))
        ConfigurationManager.ergodox_root_path = path



class ConfigWidget(QWidget):
    def __init__(self):
        super(ConfigWidget, self).__init__()
        ConfigurationManager.load_settings()
        self.setSizePolicy(
            QSizePolicy.Expanding,
            QSizePolicy.Expanding )
        self.__init_gui()

    def __init_gui(self):
        vbl = QVBoxLayout(self)
        l = QHBoxLayout()
        label = QLabel("Ergodox root path in qmk_firmware")
        label.setToolTip( "e.g.qmk_firmware_root_dir/keyboards/ergodox ")
        self.line_edit = le = QLineEdit()
        print(ConfigurationManager.ergodox_root_path)
        le.setText(ConfigurationManager.ergodox_root_path)
        l.addWidget(label)
        l.addWidget(le)

        o_dialog_button = QPushButton(QIcon(),"...")
        o_dialog_button.clicked.connect(self.open_file_dialg)
        l.addWidget(o_dialog_button)
        vbl.addLayout(l)
        # Ok or cancel buttons
        hl = QHBoxLayout()

        o = QPushButton("ok")
        o.clicked.connect(self.save_and_close)
        c = QPushButton("cancel")
        c.clicked.connect(self.close)
        hl.addWidget(c)
        hl.addWidget(o)
        vbl.addLayout(hl)


    def open_file_dialg(self):
        path = QFileDialog.getExistingDirectory(
            self, caption="select ergodox folder path in qmk firmware" )
        ConfigurationManager.set_ergodox_root_path(path)
        self.line_edit.setText(path)
        ConfigurationManager._save_settings()


    def save_and_close(self):
        self.qmk_path = self.line_edit.text()
        ConfigurationManager._save_settings()
        self.close()

if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = ConfigWidget()
    w.show()
    sys.exit(app.exec_())
