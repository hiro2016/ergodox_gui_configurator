import time

from NoneGUIComponents import pyxhook
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

    def __init__(self, callback: "method(str,str)"):
        # Create hookmanager
        self.hookman = pyxhook.HookManager()
        # Define our callback to fire when a key is pressed down
        self.hookman.KeyDown = self.keyPressEvent
        # Hook the keyboard
        self.hookman.HookKeyboard()
        # Start our listener
        self.hookman.start()
        self.callback = callback

    def keyPressEvent(self, event: pyxhook.pyxhookkeyevent):
        # This method may be called after destroy mothed call.
        # e.g. user press windows key, this object's destroy method called,
        # then sometimes this KeyPressEvent method is called.
        if self.callback is None:
            return True #do not block
        try:
            hid_usage_id = x11_to_hid_usage_id_map[str(event.X11KeyCode)]
        except KeyError as e:
            raise KeyError(
                "There is no conversion rule for the given X11 keycode:" +
                str(event.X11KeyCode) +
                ". Edit `scancode_to_hid_usage_id_map.py` "
                "and add translation rule for the scancode.")

        self.callback(hid_usage_id, event.Key)
        # block windows keypress and so on
        for name in self.keys_to_consume:
            if name == event.Key:
                print('blocking:' + event.Key)
                return False # prevent os from receiving keypress
        return True


    def destroy(self):
        # Close the listener when we are done
        self.callback = None
        # Horror of asynchronous programing,
        # cancel does not immediately kills hookman.
        # self.hookman.KeyDown = None
        self.hookman.cancel()


if __name__ == "__main__":
    def print_scancode_keyname(scancode, keyname):
        print('hid usage id:' + scancode)
        print('keyname:' + keyname)
    o = KeyPressObserver(print_scancode_keyname)
    time.sleep(60)
    o.destroy()

