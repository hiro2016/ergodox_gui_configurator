import sys

from PyQt5.QtCore import pyqtSignal
from PyQt5.QtGui import QFont, QIcon
from PyQt5.QtWidgets import QWidget, QTextEdit, QVBoxLayout, QApplication, QHBoxLayout, QLabel, QPushButton, QLineEdit
from NoneGUIComponents.keypress_observer import KeyPressObserver


class Base(QWidget):
    def getFontHeight(self) -> int:
        return self.fontMetrics().height()

    def getFontWidth(self) -> int:
        # boundingRect does not include margins
        return self.fontMetrics().boundingRect("_").width()




class Main(Base):
    keypressed = pyqtSignal(str,str)
    keyreleased = pyqtSignal(str,str)
    def __init__(self):
        super(Main,self).__init__()
        self.__init_gui()
        self.keypress_observer = None
        self.__init_listener()
        # used for filtering keypress events generated multiple times
        # keyboard send keypress once and OS periodically generates keypress
        # events until keyboard sends keyrelease event. 
        self.last_key_press = None

    def close(self):
        if self.keypress_observer is not None:
            self.keypress_observer.destroy()
        super().close()

    def onKeyPress(self, hid_id:str, keyname:str):
        """
        Callback passed to keypress_observer
        :param hid_id:
        :param keyname:
        :return:
        """
        # Directly updating qt widget from QThread
        # causes the thread to freeze.
        self.keypressed.emit(hid_id,keyname)

    def onKeyRelease(self, hid_id:str, keyname:str):
        """
        Callback passed to keypress_observer
        :param hid_id:
        :param keyname:
        :return:
        """
        # Directly updating qt widget from QThread
        # causes the thread to freeze.
        self.keyreleased.emit(hid_id,keyname)

    def _update_text_edit_for_keypress(self, hid_id, keyname):
        self.keyname_list_text_edit.append("pressed: "+keyname)

    def _update_text_edit_for_keyrelease(self, hid_id, keyname):
        self.keyname_list_text_edit.append("released: "+keyname)

    def onRecordingStartClicked(self):
        if self.keypress_observer is not None:
            self.start_recording_button.setText("Start recording")
            self.keypress_observer.destroy()
            self.keypress_observer = None
        else:
            self.keypress_observer = KeyPressObserver(
                self.onKeyPress,
                self.onKeyRelease )
            self.start_recording_button.setText("Stop recording")
            self.user_message_display_label.setText("Start typing")
            self.recording_input_field.setFocus(True)


    def __init_gui(self):
        self.main_v_layout = ml = QVBoxLayout()
        # display message to the user
        hl = QHBoxLayout()
        self.start_recording_button = b = QPushButton(
            QIcon(),"Start recording" )

        hl.addWidget(b)
        self.clear_recorded_macro_button = b = QPushButton(
            QIcon(),"Clear" )
        hl.addWidget(b)

        ml.addLayout(hl)
        hl = QHBoxLayout()

        self.recording_input_field = QLineEdit()
        ml.addWidget(self.recording_input_field)
        self.user_message_display_label = l = QLabel()
        ml.addWidget(l)


        self.keyname_list_text_edit = e = QTextEdit()
        self.generated_code_text_edit = e2 = QTextEdit()
        hl.addWidget(e)
        hl.addWidget(e2)
        ml.addLayout(hl)
        self.setLayout(ml)

    def __init_listener(self):
        self.start_recording_button.clicked.connect(
            self.onRecordingStartClicked)
        self.keypressed.connect(self._update_text_edit_for_keypress)
        self.keyreleased.connect(self._update_text_edit_for_keyrelease)


        self.clear_recorded_macro_button.clicked.connect(
            self._clear_recorded_macro_clicked)

    def _clear_recorded_macro_clicked(self):
        self.keyname_list_text_edit.clear()
        self.user_message_display_label.clear()
        self.recording_input_field.clear()


    def init_font(self):
        """
        Must be called after width, height set.
        :return:
        """
        font_size = 12
        while self.getFontHeight() < (self.height()/20):
            self.font = f =QFont()
            f.setPointSize(font_size)
            self.setFont(f)
            font_size += 1

    def getData(self):
        d ={}
        return d


if __name__ == "__main__":
    app = QApplication(sys.argv)
    geo = app.desktop().screenGeometry()
    w = geo.width()
    h = geo.height()

    m = Main()
    m.setMinimumWidth((3*w)/4)
    m.setMinimumHeight((3*h)/4)
    m.init_font()
    m.move(0,0)
    m.show()
    sys.exit(app.exec_())
