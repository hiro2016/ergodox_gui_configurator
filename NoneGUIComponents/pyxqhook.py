#!/usr/bin/python
#
import signal
import sys
import re
import time
import threading
# need the latest Xlib https://github.com/python-xlib/python-xlib
from PyQt5.QtCore import QThread, QObject, pyqtSignal
from PyQt5.QtWidgets import QApplication

import Xlib
import atexit
from Xlib import X, XK, display
from Xlib.ext import record
from Xlib.protocol import rq




class HookManager(QObject):
    finished = pyqtSignal()
    pipe = pyqtSignal(str)
    def __init__(self):
        super(HookManager,self).__init__()
        self.pipe.connect(self.pipe_signaled)



        self.ison = {"shift":False, "caps":False}

        # Compile our regex statements.
        self.isshift = re.compile('^Shift')
        self.iscaps = re.compile('^Caps_Lock')
        self.shiftablechar = re.compile('^[a-z0-9]$|^minus$|^equal$|^bracketleft$|^bracketright$|^semicolon$|^backslash$|^apostrophe$|^comma$|^period$|^slash$|^grave$')
        self.logrelease = re.compile('.*')
        self.isspace = re.compile('^space$')

        # Assign default function actions (do nothing).
        self.KeyDown = lambda x: True
        self.KeyUp = lambda x: True

        self.contextEventMask = [X.KeyPress, X.MotionNotify]
        # self.contextEventMask = [X.KeyPress,X.MotionNotify, xinput.RawKeyPress]

        # Hook to our display.
        self.local_dpy = display.Display()
        self.record_dpy = display.Display()


        # default display used for grab_keyboard
        self.dpy = display.Display()

        self.start_grabbing_keyboard()
        signal.signal(signal.SIGTERM, self.cancel)
        atexit.register(self.cancel)

        self.count = 0
        self.ctx = None

    @staticmethod
    def pipe_signaled(msg):
        print(msg)

    def print(self, *msg):
        self.pip.emit("".join(msg))

    def start(self):
        self.run()

    def run(self):
        self.qtherad = QThread()
        self.moveToThread(self.qtherad)
        self.qtherad.start()

    def process(self):
        # since this is all async, displays could be closed before run completes.
        # this try block is less than ideal but does the trick for time being.
        try:
            # Check if the extension is present
            if not self.record_dpy.has_extension("RECORD"):
                print("RECORD extension not found")
                sys.exit(1)
            r = self.record_dpy.record_get_version(0, 0)
            # print("RECORD extension version %d.%d" % (r.major_version, r.minor_version))


            # Create a recording context; we only want key and mouse events
            self.ctx = self.record_dpy.record_create_context(
                0,
                [record.AllClients],
                [{
                    'core_requests': (0, 0),
                    'core_replies': (0, 0),
                    'ext_requests': (0, 0, 0, 0),
                    'ext_replies': (0, 0, 0, 0),
                    'delivered_events': (0, 0),
                    'device_events': tuple(self.contextEventMask), #(X.KeyPress, X.ButtonPress),
                    'errors': (0, 0),
                    'client_started': False,
                    'client_died': False,
                }])

            # Enable the context; this only returns after a call to record_disable_context,
            # while calling the callback function in the meantime
            self.record_dpy.record_enable_context(self.ctx, self.processevents)
            self.local_dpy.flush()
        except Exception as e:
            pass

    def close_displays(self):
        if self.local_dpy is not None:
            self.local_dpy.close()
        if self.dpy is not None:
            self.dpy.close()
        if self.record_dpy is not None:
            self.record_dpy.close()

        # run might just be startig when these are called
        self.record_dpy = None
        self.dpy = None
        self.local_dpy = None
        # self.local_dpy.record_disable_context(self.ctx)
        self.finished.emit()



    def cancel(self):
        # could be called before run
        # WARING!!!
        # The order of execution matters
        self.stop_grabbing_keyboard()
        if self.ctx is not None and self.record_dpy is not None:
            self.record_dpy.record_disable_context(self.ctx)
            self.record_dpy.record_free_context(self.ctx)
        self.close_displays()
        # fineshed.set is dangerous because it really stops
        # the thread, if clean up code is in run, fineshed.set
        # won't let it run.
        self.finished.set()


    def printevent(self, event):
        print(event)

    def processevents(self, reply):
        if reply.category != record.FromServer:
            return True # no blocking
        if reply.client_swapped:
            print("* received swapped protocol data, cowardly ignored")
            return True
        if not len(reply.data) or ord(str(reply.data[0])) < 2:
            print("not an event")
            # not an event
            return True

        data = reply.data
        while len(data):
            event, data = rq.EventField(None).parse_binary_value(data, self.record_dpy.display, None, None)
            if event.type == X.KeyPress:
                # print("data:"+ str(data))
                hookevent = self.keypressevent(event)
                consume = not self.KeyDown(hookevent)
                if not consume:
                    self.post_key_tap(event)
            elif event.type == X.KeyRelease:
                hookevent = self.keyreleaseevent(event)
                self.KeyUp(hookevent)
            elif event.type == X.ButtonPress:
                hookevent = self.buttonpressevent(event)
                self.MouseAllButtonsDown(hookevent)
            elif event.type == X.ButtonRelease:
                hookevent = self.buttonreleaseevent(event)
                self.MouseAllButtonsUp(hookevent)
            elif event.type == X.MotionNotify:
                # use mouse moves to record mouse position, since press and release events
                # do not give mouse position info (event.root_x and event.root_y have
                # bogus info).
                self.mousemoveevent(event)

    def start_grabbing_keyboard(self):
        # screen root window
        # root = self.record_dpy.screen().root
        # http://python-xlib.sourceforge.net/doc/html/python-xlib_16.html
        self.window_in_focus = wif = self.dpy.get_input_focus().focus
        # specify what to capture
        wif.change_attributes(event_mask = X.KeyPressMask|X.KeyReleaseMask)
        # own_event, pointer_mode, keyboard_mode, current_time
        wif.grab_keyboard(True,X.GrabModeAsync,X.GrabModeAsync,X.CurrentTime)

    def stop_grabbing_keyboard(self):
        """
        """
        if self.dpy is None:
            return
        try:
            self.dpy.ungrab_keyboard(
                onerror=None,
                time=X.CurrentTime)
            self.dpy.flush()
            self.dpy.sync()
        except Xlib.error.ConnectionClosedError as e:
            pass


    def post_key_tap(self, event):
        """
        Take a KeyPressEvent
        Called by precessevents
        Post KeyPress and KeyRelease events.

        focus window needs to be called prior to each send_event call!
        getfocus, keypress, keyrelease does not work
        getfocus, keypress, getfocus, keyrelease work.


        Introduced as grab_keyboard seems to consume keypressevents.

        Note: grab_keyboard is not supposed to consume key taps,
        and at one point, I cannot remember what causes it, I saw
        all grabbed key related events released at the end of script
        execution.
        """
        self.window_in_focus = self.dpy.get_input_focus().focus
        new_event = Xlib.protocol.event.KeyPress(
            window=self.window_in_focus,
            time=int(time.time()), #server x time
            root=event.root,
            same_screen=event.same_screen,
            root_y = event.root_y,
            root_x = event.root_x,
            detail = event.detail,
            type = X.KeyPressMask,
            state = event.state,
            event_y = event.event_y,
            event_x = event.event_x,
            child = event.child

        )
        self.dpy.send_event(
            self.window_in_focus,
            event=new_event,
            event_mask=X.KeyPressMask,
            propagate=True,
            onerror=self.cancel
        )
        self.dpy.flush()
        self.dpy.sync()

        self.window_in_focus = self.dpy.get_input_focus().focus
        new_event = Xlib.protocol.event.KeyRelease(
            window=self.window_in_focus,
            time=int(time.time()),
            root=event.root,
            same_screen=event.same_screen,
            root_y = event.root_y,
            root_x = event.root_x,
            # scancode
            detail = event.detail,
            # key press and key release structs are same, difference is here.
            type = X.KeyRelease,
            # inclusive or of modifier keys and buttons.
            # https://tronche.com/gui/x/xlib/events/keyboard-pointer/keyboard-pointer.html
            state = event.state,
            event_y = event.event_y,
            event_x = event.event_x,
            child = event.child
        )
        self.dpy.send_event(
            self.window_in_focus,
            event=new_event,
            event_mask=X.KeyReleaseMask,
            propagate=True,
            onerror=self.cancel
        )
        #allow_events is irrelevant for grab_keyboard
        # self.record_dpy.allow_events(X.ReplayKeyboard,int(time.time()))
        self.dpy.flush()
        self.dpy.sync()



    def keypressevent(self, event):
        matchto = self.lookup_keysym(self.local_dpy.keycode_to_keysym(event.detail, 0))
        if self.shiftablechar.match(self.lookup_keysym(self.local_dpy.keycode_to_keysym(event.detail, 0))): ## This is a character that can be typed.
            if self.ison["shift"] == False:
                keysym = self.local_dpy.keycode_to_keysym(event.detail, 0)
                return self.makekeyhookevent(keysym, event)
            else:
                keysym = self.local_dpy.keycode_to_keysym(event.detail, 1)
                return self.makekeyhookevent(keysym, event)
        else: ## Not a typable character.
            keysym = self.local_dpy.keycode_to_keysym(event.detail, 0)
            if self.isshift.match(matchto):
                self.ison["shift"] = self.ison["shift"] + 1
            elif self.iscaps.match(matchto):
                if self.ison["caps"] == False:
                    self.ison["shift"] = self.ison["shift"] + 1
                    self.ison["caps"] = True
                if self.ison["caps"] == True:
                    self.ison["shift"] = self.ison["shift"] - 1
                    self.ison["caps"] = False
            return self.makekeyhookevent(keysym, event)

    def keyreleaseevent(self, event):
        if self.shiftablechar.match(self.lookup_keysym(self.local_dpy.keycode_to_keysym(event.detail, 0))):
            if self.ison["shift"] == False:
                keysym = self.local_dpy.keycode_to_keysym(event.detail, 0)
            else:
                keysym = self.local_dpy.keycode_to_keysym(event.detail, 1)
        else:
            keysym = self.local_dpy.keycode_to_keysym(event.detail, 0)
        matchto = self.lookup_keysym(keysym)
        if self.isshift.match(matchto):
            self.ison["shift"] = self.ison["shift"] - 1
        return self.makekeyhookevent(keysym, event)

    # need the following because XK.keysym_to_string() only does printable chars
    # rather than being the correct inverse of XK.string_to_keysym()
    def lookup_keysym(self, keysym: int) -> str:
        """"
         Looks like returning the common name for the key pressed by
         the user. The source of names seems some linux directory.
         Read xlib doc for details?
         Since [0] is given for ome jis keyboard key press, keysym is
         probably an int.
        """

        for name in dir(XK):
            if name.startswith("XK_") and getattr(XK, name) == keysym:
                return name.lstrip("XK_")
        return "[%d]" % keysym

    def asciivalue(self, keysym: int):
        # lookup_keysym finds the keys' common name
        # based on the given x11 keycode and generates a string such
        # as "KX_A", which has nothing to do with the actual input.
        # print("keysym:"+chr(keysym))
        num = XK.string_to_keysym(self.lookup_keysym(keysym))
        # print("after keysym to string:"+chr(num))
        if num == X.NoSymbol:
            return 0

        if num < 256:
            return num
        else:
            return 0

    def makekeyhookevent(self, keysym, event):
        storewm = self.xwindowinfo()
        if event.type == X.KeyPress:
            MessageName = "key down"
        elif event.type == X.KeyRelease:
            MessageName = "key up"
        return pyxhookkeyevent(storewm["handle"], storewm["name"], storewm["class"], self.lookup_keysym(keysym), self.asciivalue(keysym), False, event.detail, MessageName)


    def xwindowinfo(self):
        try:
            windowvar = self.local_dpy.get_input_focus().focus
            wmname = windowvar.get_wm_name()
            wmclass = windowvar.get_wm_class()
            wmhandle = str(windowvar)[20:30]
        except:
            ## This is to keep things running smoothly. It almost never happens, but still...
            return {"name":None, "class":None, "handle":None}
        if (wmname == None) and (wmclass == None):
            try:
                windowvar = windowvar.query_tree().parent
                wmname = windowvar.get_wm_name()
                wmclass = windowvar.get_wm_class()
                wmhandle = str(windowvar)[20:30]
            except:
                ## This is to keep things running smoothly. It almost never happens, but still...
                return {"name":None, "class":None, "handle":None}
        if wmclass == None:
            return {"name":wmname, "class":wmclass, "handle":wmhandle}
        else:
            return {"name":wmname, "class":wmclass[0], "handle":wmhandle}

class pyxhookkeyevent:
    """This is the class that is returned with each key event.f
    It simply creates the variables below in the class.

    Window = The handle of the window.
    WindowName = The name of the window.
    WindowProcName = The backend process for the window.
    Key = The key pressed, shifted to the correct caps value.
    Ascii = An ascii representation of the key. It returns 0 if the ascii value is not between 31 and 256.
    KeyID = This is just False for now. Under windows, it is the Virtual Key Code, but that's a windows-only thing.
    ScanCode = Please don't use this. It differs for pretty much every type of keyboard. X11 abstracts this information anyway.
    MessageName = "key down", "key up".
    """

    def __init__(self, Window, WindowName, WindowProcName, Key, Ascii, KeyID, X11KeyCode, MessageName):
        self.Window = Window
        self.WindowName = WindowName
        self.WindowProcName = WindowProcName
        self.Key = Key
        self.Ascii = Ascii
        self.KeyID = KeyID
        self.X11KeyCode = X11KeyCode
        self.MessageName = MessageName

    def __str__(self):
        return "Window Handle: " + str(self.Window) + "\nWindow Name: " + str(self.WindowName) + "\nWindow's Process Name: " + str(self.WindowProcName) + "\nKey Pressed: " + str(self.Key) + "\nAscii Value: " + str(self.Ascii) + "\nKeyID: " + str(self.KeyID) + "\nScanCode: " + str(self.X11KeyCode) + "\nMessageName: " + str(self.MessageName) + "\n"


if __name__ == '__main__':
    app = QApplication(sys.argv)
    hm = HookManager()
    def filter_winwods_button_pres(e:pyxhookkeyevent):
        print(e)
        if e.Key is "Super_L":
            return False # block input
        else:
            return True
    hm.KeyDown = filter_winwods_button_pres
    hm.start()
    sys.exit(app.exec_())
    hm.cancel()

    # A simple test for the error below.
    # Xlib.error.DisplayConnectionError: Can't connect to display ":0": b'Maximum number of clients reached'
    # for c in range(0,500):
    #     hm = HookManager()
    #     hm.HookKeyboard()
    #     hm.KeyDown = filter_winwods_button_pres
    #     hm.start()
    #     hm.cancel()
    # print('done')
