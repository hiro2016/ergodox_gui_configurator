from NoneGUIComponents.keypress_observer import KeyPressObserver
import time
from PyQt5.QtCore import pyqtSignal, QObject

class MacroRecorder(QObject):
    #hid id, keyname, code
    keypressed = pyqtSignal(str,str,str)
    #hid id, keyname, code
    keyreleased = pyqtSignal(str,str,str)

    def __init__(self):
        super(MacroRecorder,self).__init__()
        self.keypress_observer = None
        # used for filtering keypress events generated multiple times.
        # Keyboard send keypress once and OS periodically generates keypress
        # events until keyboard sends keyrelease event.
        self.last_key_press = None
        # Used for recording keypress time
        self.keypress_time = 0

    def onKeyPress(self, hid_id:str, keyname:str):
        """
        Callback passed to keypress_observer
        :param hid_id:
        :param keyname:
        :return:
        """
        # Directly updating qt widget from QThread
        # causes the thread to freeze.
        if self.last_key_press != hid_id:
            code = "register_code(%s);"%hid_id
            self.last_key_press = hid_id
            self.keypress_time = time.time()
            self.keypressed.emit(hid_id,keyname,code)

    def onKeyRelease(self, hid_id:str, keyname:str):
        """
        Callback passed to keypress_observer
        :param hid_id:
        :param keyname:
        :return:
        """
        hold_duration_is_ms =time.time() - self.keypress_time
        hold_duration_is_ms = hold_duration_is_ms*1000
        hold_duration_is_ms = int(hold_duration_is_ms)

        code = []
        no_interval_keys = ["Control", "Shift", "Super","Alt"]
        if all(not e in keyname for e in no_interval_keys):
            #equivalent of MACRO I(interval in ms)
            keypress_interval_code = "{ uint8_t ms = %s; while (ms--) wait_ms(1); }" \
                                     % hold_duration_is_ms
            code.append(keypress_interval_code)

        code.append("unregister_code(%s);\n"%hid_id)
        # Directly updating qt widget from QThread
        # causes the thread to freeze.
        self.keyreleased.emit(hid_id,keyname,"\n".join(code))
        # as last_key_press is for filtering key holding
        self.last_key_press = None

    def start(self):
        if self.keypress_observer is None:
            self.keypress_observer = KeyPressObserver(
                self.onKeyPress,
                self.onKeyRelease )

    def stop(self):
        if self.keypress_observer is not None:
            self.keypress_observer.destroy()
            self.keypress_observer = None

    def isRecording(self):
        return True if self.keypress_observer is not None else False
