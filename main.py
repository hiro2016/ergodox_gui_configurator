import shutil
from PyQt5 import QtCore, Qt, QtGui

from PyQt5.QtCore import QRect, QProcess, QDir
from PyQt5.QtGui import QFont, QIcon, QKeySequence
from PyQt5.QtWidgets import QApplication, QMainWindow, QLabel, QWidget, QAction, QHBoxLayout, QSizePolicy, QPushButton, \
    QToolBar, QPlainTextEdit

import central_widget
from configWidget import *

__author__ = 'Hiro'
import sys
import platform
import logging
import os

def get_exe_path():
    if hasattr(sys, "frozen"):
        full_script_path = os.path.dirname(sys.executable)
        return os.path.realpath(full_script_path)
    else:
        # return os.path.dirname(os.path.realpath(sys.argv[0]))
        return os.path.dirname(os.path.abspath(__file__))
# set default behaviour

logging.basicConfig(
    level=logging.DEBUG,
    stream=sys.stdout,
    format="%(asctime)s - %(name)s - %(levelname)s - %(message)s")
logger = logging.getLogger("GUIConfig")

# logger.setLevel(logging.WARNING)
# to stderror logginer.StreamHandler()
# logger.addHandler(logging.StreamHandler())


class MainWindow(QMainWindow):
    def __init__(self):
        super(MainWindow,self).__init__()
        ConfigurationManager.load_settings()
        self.__init_ui()
        self.show()

    def setFixedHeight(self, p_int):
        c = self.centralWidget()
        height = p_int
        if c is not None:
            c.setFixedHeight(height)
        super().setFixedHeight(p_int)

    def setFixedWidth(self, p_int):
        c = self.centralWidget()
        if c is not None:
            c.setFixedWidth(p_int)
        super().setFixedWidth(p_int)


    def __init_ui(self):
        # self.setCentralWidget(self.center_w)
        self.setWindowTitle("Ergodox gui configurator")
        #Actions
        open_file = QAction(QIcon(), "Open File", self)
        open_file.setShortcut("Ctrl+O")
        open_file.triggered.connect(self.on_open_keymap)

        save_file = QAction(QIcon(), "Save As", self)
        save_file.setShortcut("Ctrl+O")
        save_file.triggered.connect(self.on_save_keymap)

        if platform.system() == "Windows":
            compile_file = QAction(QIcon(),'Generate keymap.c',self)
            compile_file.triggered.connect(self.generate_keymap_c)
        else:
            compile_file = QAction(QIcon(),"Compile", self)
            compile_file.triggered.connect(self.on_compile_requested)
        compile_file.setShortcut("Ctrl+Alt+x")

        quit_this = QAction(QIcon(),"Quit", self)
        quit_this.setShortcut("Ctrl+q")
        quit_this.triggered.connect(self.close)

        configure = QAction(QIcon(),"Configure", self)
        configure.triggered.connect(self.open_config_window)

        # menubar
        # menubar = self.menuBar()
        # menubar.setFont(QFont().setPointSize(12))
        # file = menubar.addMenu("&File")
        # file.addAction(open_file)
        # file.addAction(save_file)

        self.toolbar = tb = QToolBar()
        tb.setFloatable(False)
        tb.addAction(open_file)
        tb.addAction(save_file)
        tb.addAction(configure)
        tb.addAction(compile_file)
        tb.addAction(quit_this)
        self.addToolBar(QtCore.Qt.TopToolBarArea, tb)


    def open_config_window(self):
        self.config_widget = w = ConfigWidget()
        w.show()

    def generate_keymap_c(self):
        self.w = w= QWidget()
        geo = self.geometry()
        w.setFixedWidth(geo.width()/2)
        w.setFixedHeight(geo.height()/2)
        l = QHBoxLayout(w)
        self.font = QFont("monospace", 18)
        self.font.setStyleHint(QFont.TypeWriter)

        self.console_out = e = QPlainTextEdit()
        e.setFont(self.font)
        e.setPlainText("Generating keymap.c")
        e.setSizePolicy(
            QSizePolicy.Expanding,
            QSizePolicy.Expanding
        )
        l.addWidget(e)
        w.show()
        QtGui.QGuiApplication.processEvents()

        # compiling
        self._generate_keymap_c_file()
        keymap_c_file_path = os.path.join(os.getcwd(),"keymap.c")
        msg = "keymap.c file generated at:" +keymap_c_file_path
        e.appendPlainText('\n')
        e.appendPlainText(msg)
        e.appendPlainText('\n')
        msg = "Compile via this script is not available" \
              " for windows os.\n\n" \
              "Place keymap.c in your qmk's eargodox dir\n" \
              "e.g.\n" \
              r" qmk_firmware\keyboards\ergodox\keymaps\custom_keymap\keymap.c" \
              "\n\nand make via msys2\n\n " \
              "How to set up msys for qmk: https://docs.qmk.fm/getting_started_build_tools.html"
        e.appendPlainText(msg)


    def on_compile_requested(self):
        # preparing output console
        self.w = w= QWidget()
        geo = self.geometry()
        w.setFixedWidth(geo.width()/2)
        w.setFixedHeight(geo.height()/2)
        l = QHBoxLayout(w)
        self.font = QFont("monospace", 18)
        self.font.setStyleHint(QFont.TypeWriter)

        self.console_out = e = QPlainTextEdit()
        e.setFont(self.font)
        e.setPlainText("Compiling keymap\n")
        e.setSizePolicy(
            QSizePolicy.Expanding,
            QSizePolicy.Expanding
        )
        l.addWidget(e)
        w.show()
        QtGui.QGuiApplication.processEvents()

        # compiling
        self.compile(e)


    def on_save_keymap(self):
        if self.centralWidget() is None:
            return
        path, type = QFileDialog.getSaveFileName(
            self,
            "save file as",
            get_exe_path(),
            "Ergodox Keymap files (*.ekm)"
        )
        if path[-4:] != ".ekm":
            path += ".ekm"
        self.centralWidget().save_keymap(path)


    def on_open_keymap(self, pressed):
        if self.centralWidget() is None:
            return
        path, type = QFileDialog.getOpenFileName(
            self, "select a file",get_exe_path(),"Ergodox Keymap files (*.ekm)")
        print(path)
        self._setContralWidget()
        self.centralWidget().load_keymap(path)

    def _generate_keymap_c_file(self):
        print('_generate_keymap_c called')
        new_map = self.centralWidget()\
            .get_keymap_as_string()
        j = os.path.join
        source = j(get_exe_path(), "keymap_source.c")
        with open(source,'r') as f:
            data = f.read()
        data = data.replace("place_holder",new_map)
        out_path = j(get_exe_path(),'keymap.c')
        with open(out_path, "w") as f:
            f.write(data)

    def compile(self, console:QPlainTextEdit):
        self._generate_keymap_c_file()
        keymap_c_file_path = os.path.join(os.getcwd(),"keymap.c")
        copy_to_dest = os.path.join(
            ConfigurationManager.ergodox_root_path,"keymaps/custom_keymap/")

        # mkdir
        if not os.path.exists(copy_to_dest):
            os.mkdir(copy_to_dest)
        shutil.copy2(keymap_c_file_path, copy_to_dest)

        # run make command
        make_dir = ConfigurationManager.ergodox_root_path
        p = QProcess(self)
        p.setWorkingDirectory(make_dir)

        cd = QDir.currentPath()
        QDir.setCurrent(make_dir)
        try:
            p.start("make", ['custom_keymap'])
            if not p.waitForStarted():
                raise ChildProcessError("could not run make command")
            if not p.waitForReadyRead():
                raise ChildProcessError("could not read stdout")

            while True:
                p.waitForReadyRead()
                line = str(bytes(p.readLine()).decode('utf-8'))
                print(line)
                console.appendPlainText(line)
                QApplication.processEvents()
                if p.atEnd():
                    break

            qmk_dir = os.path.dirname(
                os.path.dirname(ConfigurationManager.ergodox_root_path))
            console.appendPlainText("Finished! See console for a prettier output.\n\n")
            console.appendPlainText("You should find the generated"
                                    " hex file at: %s/custom_keymap.hex"
                                    % (qmk_dir))

        except Exception as e:
            raise e
        finally:
            QDir.setCurrent(cd)

        QDir.setCurrent(cd)

    def _setContralWidget(self):
        cw = central_widget.CentralWidget()
        self.setCentralWidget(cw)
        cw.setFixedHeight(self.height())
        cw.setFixedWidth(self.width())

    # Not used in favour of pyxhook,
    # could not block alt_l search bar pop etc this way.
    # def keyPressEvent(self, key_event):
    #     keycode = key_event.key()
    #     if QtCore.Qt.Key_Super_L == keycode:
    #         print("Super_L pressed")
    #         return
    #
    #     if QtCore.Qt.Key_Meta == keycode:
    #         print("Windows or meta key pressed")
    #         return
    #
    #     if QtCore.Qt.Key_Alt == keycode:
    #         print("Alt key pressed")
    #         return
    #
    #     # always works.
    #     print("keycode:" + str(keycode))
    #     print("Super_L in qt:"+str(QtCore.Qt.Key_Super_L))
    #     super().keyPressEvent(key_event)
    #


if __name__ == "__main__":
    app = QApplication(sys.argv)
    t = MainWindow()
    geo = app.desktop().screenGeometry()

    width = geo.width()
    height = geo.height()
    width -= width/30
    height -= height/10


    # sv = key_configurator.KeyConfigurator()
    t.move(0,0)
    t.setFixedHeight(height)
    t.setFixedWidth(width)
    t._setContralWidget()

    sys.exit(app.exec_())
