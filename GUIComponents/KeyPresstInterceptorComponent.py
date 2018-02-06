import platform
from threading import Timer

from PyQt5 import QtCore
from PyQt5.QtCore import QObject, pyqtSignal
from PyQt5.QtWidgets import QHBoxLayout, QVBoxLayout, QTextEdit, QLabel, QSizePolicy, QLineEdit, QApplication, QWidget
import sys

from NoneGUIComponents import keypress_observer
from NoneGUIComponents.dict_keys import *

from NoneGUIComponents.key_conf_dict_parser import KeyConfDictParser


class KeyPressInterceptorComponent(QVBoxLayout, QObject):
    """""
    A GUI component:
         label, QTextEdit(Captures the last user key stroke when selected).
         label, label(shows the guesstimate of the  hid usage id)
         label, QTextEdit(shows the keyname;editiable)
    The last item is editable because it's it's part of display string
    for QPushButtons in CentralWidget.
    
    Upon a key press this script finds: 
        the key's common name if available
    Upon a key press this script guess: 
        the keycode hid usage id the key sends
        
    To manage two information sources, pyxhook and QTextEdit,
    each running in its own thread and updating gui independently,
    using flag:
            boolean literalUpdated 
            and
            Timer to check if QTextEdit field needs to be cleared. 
        
        Ugly but truly solving the issue is not worth the effort as of now.
        
        Note:
            method call chains:
                QTextEdit event -> eventFilter -> connect_keypress_observer -> 
                pyxhook connection established.
                
                QTextEdit event -> eventFilter -> disconnect_keypress_observer ->
                disconnect pyxhook connection. 
                
                pyxhook keypress event -> inner function onKeyPress ->  
                signalKeyPressed-> on_key_pressed
                
                pyxhook keypress event -> inner function onKeyPress ->  
                fieldUpdateTimer -> inner function checkIfModifierKeyPressed
    """""

    # Here to call QTextEdit method from non-qt thread.
    # connected to on_key_pressed
    signalKeyPressed = pyqtSignal(str, str)

    # sets literal_input_te to "" from any thread.
    signalClearTextEdit = pyqtSignal()

    # referenced and set by by fieldUpdateTimer param function
    # checkIfModifierKeyPressed.
    # set by __init_gui::filter
    # Used to check if QLineEdit needs to be updated/cleared
    literalUpdated = False
    # Used Like PostDelayed or Future.
    # Decide whether to clear the literal_input_et after
    # both Qt and keypress_observer callback are completed.
    fieldUpdateTimer = None

    def __init__(self, prv_config:dict={}):
        super().__init__()
        self.__init_gui(prv_config)
        self.is_keypress_observer_connected = False

        # Enable user input scanning only when the top mont QTextEdit is
        # selected.
        self.literal_input_te.installEventFilter(self)

        # clears text edit where user select to capture scancode
        # this is necessary to make sure the te contains nothing
        # after the user presses a modifier key.
        te = self.literal_input_te
        self.signalClearTextEdit.connect(lambda f=te: f.clear())
        self.setFocus()
        # initializing attributes
        self.keypress_observer = None

    def setFocus(self, reason=QtCore.Qt.NoFocusReason):
        self.literal_input_te.setFocus(reason)

    # Only connected when QTextEdit is selected.
    def connect_keypress_observer(self):
        if self.is_keypress_observer_connected == True:
            return
        self.signalKeyPressed.connect(self.on_key_pressed)
        # qwidget cannot be accessed by an external thread, so doing it via signal.
        def onKeyPress(hid_usage_id:str, keyname:str, trigger = self.signalKeyPressed ):
            trigger.emit(hid_usage_id,keyname)

            # Check if the key pressed is a modifier. If so, clear literal_input_te.
            def checkIfModifierKeyPressed():
                if not self.literalUpdated:
                    self.signalClearTextEdit.emit()
                self.literalUpdated = False
                self.fieldUpdateTimer = None
            self.fieldUpdateTimer = Timer(0.05, checkIfModifierKeyPressed)
            self.fieldUpdateTimer.start()

        self.keypress_observer = keypress_observer.KeyPressObserver(onKeyPress)
        self.is_keypress_observer_connected = True

    def disconnect_keypress_observer(self):
        # this maybe called after closeEvent
        # OR before connect called
        try:
            self.signalKeyPressed.disconnect()
        except TypeError as e:
            print(e)
            msg = "disconnect() failed between 'signalKeyPressed' and all its connections"
            if msg not in str(e):
                raise e

        if self.keypress_observer is not None:
            if self.is_keypress_observer_connected:
                self.keypress_observer.destroy()
            self.keypress_observer = None

        self.is_keypress_observer_connected = False

    def __init_gui(self,d):
        p = KeyConfDictParser(d)
        # self.font = QFont()
        # self.font.setPointSize(13)

        bl = self
        # bl = self.vertical_box_layout = QVBoxLayout()
        hl1 = QHBoxLayout()
        hl1.setContentsMargins(0,5,5, 5)
        hl1.setSpacing(5)

        # literal row
        l_literal = QLabel("input literal")
        self.literal_input_te = input_literal = QLineEdit()

        # input_literal.setMaximumHeight(font_height)
        # input_literal.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        def filter():
            length = len(input_literal.text())
            self.literalUpdated = True
            if length == 2:
                c = input_literal.cursor()
                # c = input_literal.textCursor()
                # c.movePosition(QTextCursor.Left,QTextCursor.MoveAnchor)
                # c.deletePreviousChar()
                # c.movePosition(QTextCursor.Right,QTextCursor.MoveAnchor)
                ct = input_literal.text()
                input_literal.clear()
                input_literal.setText(ct[1])




        input_literal.textChanged.connect(filter
                                          # stackoverflow
                                          # lambda: te.setText(te.toPlainText()[-1])
                                          )
        hl1.addWidget(l_literal)
        hl1.addWidget(input_literal)

        # hid usage id row
        hl2 = QHBoxLayout()
        hl2.setContentsMargins(0,5,5, 5)
        hl2.setSpacing(5)
        l_hid_usage_id = QLabel("HID usage id:")
        hl2.addWidget(l_hid_usage_id)
        self.hid_usage_id_display = QLabel()# contents will be set upon user input
        self.hid_usage_id_display.setText(p.hid_usage_id)
        hl2.addWidget(self.hid_usage_id_display)


        # key name row
        hl3 = QHBoxLayout()
        hl3.setContentsMargins(0,5,5, 5)
        hl3.setSpacing(5)
        l_key_name = QLabel("Key's name")
        hl3.addWidget(l_key_name)
        self.key_name = QLineEdit()# contents will be set upon user input
        self.key_name.setText(p.keyname)
        # self.key_name.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        # self.key_name.setMaximumHeight(font_height)
        hl3.addWidget(self.key_name)


        bl.addLayout(hl1)
        bl.addLayout(hl2)
        bl.addLayout(hl3)
        # self.setSizePolicy(QSizePolicy.Expanding,QSizePolicy.Expanding)
        # self.setLayout(bl)
        bl.setAlignment(QtCore.Qt.AlignTop)

        # self.setGeometry(3,3,300,300)
        # print(self.geometry().height())
        # self.setStyleSheet("background-color:red;")


    def on_key_pressed(self, hid_usage_id:str, common_keyname:str):
        self.hid_usage_id_display.setText(hid_usage_id)
        self.key_name.setText(str(common_keyname))

    def closeEvent(self, QCloseEvent):
        self.disconnect_keypress_observer()
        super().closeEvent(QCloseEvent)

    def eventFilter(self, source, event):
        if(source is not self.literal_input_te):
            return super().eventFilter(source, event)
        # sometimes FocusIn is called twice.
        if event.type() == QtCore.QEvent.FocusOut:
            if self.is_keypress_observer_connected:
                self.disconnect_keypress_observer()
        elif event.type() == QtCore.QEvent.FocusIn:
            if not self.is_keypress_observer_connected:
                self.connect_keypress_observer()
        return super().eventFilter(source, event)

    def getData(self) -> dict:
        data = {
            key_hid_usage_id :self.hid_usage_id_display.text(),
            key_key_name:self.key_name.text()
        }
        return data

    def setEnabled(self,state):
        self.key_name.setEnabled(state)
        self.literal_input_te.setEnabled(state)
        if state:
            self.setFocus()
            self.connect_keypress_observer()
        else:
            self.disconnect_keypress_observer()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    # t = ScancodeViewer()
    # t = KeyCodeViewer()
    w = QWidget()
    t = KeyPressInterceptorComponent()
    w.setLayout(t)
    w.show ()
    r = app.exec_()
    sys.exit(r)
    print(t.getData())
