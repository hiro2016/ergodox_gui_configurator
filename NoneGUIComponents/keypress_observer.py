import platform
import time
from PyQt5.QtWidgets import QApplication
import sys

if platform.system() == "Windows":
    import pyHook
    from NoneGUIComponents.windows_scancode_to_hid_id_map import *
else:
    #from NoneGUIComponents import pyxhook
    from NoneGUIComponents import pyxqhook
    from NoneGUIComponents.x11_to_hid_usage_id_map import *

class KeyPressObserver:
    """""
    Scanner script for x11 keycode and key name.
    
    Translates captured scancode to hid usage id via a
    static map;not very reliable.
     
    Wraps pyxhook for linux.
    This may also wrap pyhook in future for windows support.
    
    The call back takes two arguments.
    The first is hid_usage_id.
    The second is keyName which may not be always available. 
    
    WARNING!!
    Not calling destroy when this object is no longer needed
    may result in memory leak.
    WARNING2!!
    destroy sometimes fails.
    """""


    """""
    These keys are to be consumed, so this script's 
    gui does not become de-focused;e.g. windows key 
    press should not open windows menu while GUIConfigurator 
    is in focus. Currently this works for ubuntu only.
    """""
    keys_to_consume = [
        'Super_L', # windows key name in linux
        'Alt_L', #left alt
        'Menu',
        'Escape'
    ]

    def __init__(self, keydown_callback, keyup_callback=None):
        """
        :param keydown_callback: takes hid_usage_id:str, keyname:str
        """
        pl = platform.system()
        self.is_linux = pl == "Linux"

        if self.is_linux:
            # Create hookmanager
            self.hookman = pyxqhook.HookManager()
            # Define our callback to fire when a key is pressed down
            self.hookman.KeyDown = self.linuxKeyPressEvent
            self.hookman.KeyUp= self.linuxKeyReleaseEvent
        else:
            self.hookman = pyHook.HookManager()
            self.hookman.KeyDown = self.windowsKeyPressEvent
            self.hookman.KeyUp= self.windowsKeyReleaseEvent

        # Hook the keyboard
        # self.hookman.HookKeyboard()
        # Start our listener
        if self.is_linux:
            self.hookman.start()
        self.keydown_callback = keydown_callback
        self.keyup_callback = None
        if keyup_callback is not None:
            self.keyup_callback = keyup_callback

    def linuxKeyReleaseEvent(self, event):
        # This method may be called after destroy mothed call.
        # e.g. user press windows key, this object's destroy method called,
        # then sometimes this KeyPressEvent method is called.
        if self.keyup_callback is None:
            return True #do not block
        try:
            hid_usage_id = x11_to_hid_usage_id_map[str(event.X11KeyCode)]
        except KeyError as e:
            raise KeyError(
                "There is no conversion rule for the given X11 keycode:" +
                str(event.X11KeyCode) +
                ". Edit `x11_to_hid_usage_id_map.py` "
                "and add translation rule for the keycode.\n"
                "You can use `xev` command to see x11 key code\n"
                "For hid usage ids, refer to: "
                "http://www.usb.org/developers/hidpage/Hut1_12v2.pdf ")

        self.keyup_callback(hid_usage_id, event.Key)
        # block windows keypress and so on
        for name in self.keys_to_consume:
            if name == event.Key:
                print('blocking:' + event.Key)
                return False # prevent os from receiving keypress
        return True

    def linuxKeyPressEvent(self, event):
        # This method may be called after destroy mothed call.
        # e.g. user press windows key, this object's destroy method called,
        # then sometimes this KeyPressEvent method is called.
        if self.keydown_callback is None:
            return True #do not block
        try:
            hid_usage_id = x11_to_hid_usage_id_map[str(event.X11KeyCode)]
        except KeyError as e:
            raise KeyError(
                "There is no conversion rule for the given X11 keycode:" +
                str(event.X11KeyCode) +
                ". Edit `x11_to_hid_usage_id_map.py` "
                "and add translation rule for the keycode.\n"
                "You can use `xev` command to see x11 key code\n"
                "For hid usage ids, refer to: "
                "http://www.usb.org/developers/hidpage/Hut1_12v2.pdf ")

        self.keydown_callback(hid_usage_id, event.Key)
        # block windows keypress and so on
        for name in self.keys_to_consume:
            if name == event.Key:
                print('blocking:' + event.Key)
                return False # prevent os from receiving keypress
        return True


    def windowsKeyPressEvent(self,event):
        """
        Not tested
        :param event:
        :return:
        """
        if self.keyup_callback is None:
            return True

        try:
            hid_usage_id = window_scancode_to_hid_id_map[str(event.ScanCode)]
        except KeyError as e:
            msg = "There is no conversion rule for the given X11 keycode:"
            str(event.X11KeyCode)
            ". \nEdit `scancode_to_hid_usage_id_map.py`\n"
            "and add translation rule for the scancode.\n"
            "For hid usage ids, refer to:\n"
            "http://www.usb.org/developers/hidpage/Hut1_12v2.pdf "
            raise KeyError(msg)
        keyname = "" if event.Key is None else event.Key
        self.keyup_callback(hid_usage_id, keyname)
        for name in self.keys_to_consume:
            if name == event.Key:
                print('blocking:' + event.Key)
                return False # prevent os from receiving keypress
        return True

    def windowsKeyPressEvent(self,event):
        if self.keydown_callback is None:
            return True

        try:
            hid_usage_id = window_scancode_to_hid_id_map[str(event.ScanCode)]
        except KeyError as e:
            msg = "There is no conversion rule for the given X11 keycode:"
            str(event.X11KeyCode)
            ". \nEdit `scancode_to_hid_usage_id_map.py`\n"
            "and add translation rule for the scancode.\n"
            "For hid usage ids, refer to:\n"
            "http://www.usb.org/developers/hidpage/Hut1_12v2.pdf "
            raise KeyError(msg)
        keyname = "" if event.Key is None else event.Key 
        self.keydown_callback(hid_usage_id, keyname)
        for name in self.keys_to_consume:
            if name == event.Key:
                print('blocking:' + event.Key)
                return False # prevent os from receiving keypress
        return True



    def destroy(self):
        if not self.is_linux:
            self.hookman.UnhookKeyboard()
        # Close the listener when we are done
        self.keydown_callback = None
        # Horror of asynchronous programing,
        # cancel does not immediately kills hookman.
        # self.hookman.KeyDown = None
        if self.is_linux:
            self.hookman.cancel()


if __name__ == "__main__":
    # import  pythoncom, platform

    app = QApplication(sys.argv)

    def print_scancode_keyname(scancode, keyname):
        print('hid  id:' + scancode)
        print('keyname:' + keyname)

    def print_up(scancode, keyname):
        print('up:' + scancode)
        print('up:' + keyname)
    o = KeyPressObserver(print_scancode_keyname,print_up)
    # if platform.system() == "linux":
    #     time.sleep(60)
    # else:
    #     pythoncom.PumpMessages()

    r = app.exec_()
    sys.exit(r)
    o.destroy()

