import sys
from GUIComponents.KeyPresstInterceptorComponent import  *
from GUIComponents.GUIBase import  *
from GUIComponents.SelectLongKeyPressOptionComponent import  *
from GUIComponents.SelectSpecialActionComponent import  *
from GUIComponents.SelectModifierMaskComponent import  *
from PyQt5 import QtCore

from PyQt5.QtGui import QFont, QTextCursor, QFontMetrics, QIcon
from PyQt5.QtWidgets import QWidget, QDialog, QHBoxLayout, QPlainTextEdit, QSizePolicy, QFileDialog, QVBoxLayout, \
    QLabel, QTextEdit, QApplication, QComboBox, QBoxLayout, QRadioButton, QFrame



class KeyCodeViewer(GUIBase):
    #     """""
    #     More or less a note on how to use KeyPressInterceptorComponent
    #     Upon a key press this script finds:
    #         the key's common name if available
    #     Upon a key press this script guess:
    #         the keycode hid usage id the key sends
    #
    def __init__(self):
        super(KeyCodeViewer, self).__init__()
        self.main_v_layout = QVBoxLayout()
        self.main_keypress_interceptor = c = KeyPressInterceptorComponent()
        self.main_v_layout.addItem(c)
        self.setLayout(self.main_v_layout)

    def getData(self) -> dict:
        return self.main_keypress_interceptor.getData()

    def disconnect_keypress_observer(self):
        self.main_keypress_interceptor.disconnect_keypress_observer()

    def addItem(self, i):
        if issubclass(type(i),QBoxLayout):
            self.main_v_layout.addLayout(i)
        else:
            self.main_v_layout.addWidget(i)

    def close(self):
        self.main_keypress_interceptor.disconnect_keypress_observer()
        super().close()

class KeyConfigurator(GUIBase):
    """
    Let the user define an action to be taken when
    a keyboard key is pressed.
    A keypress can be configured to:
        send a hid usage id
        toggle a modifier

    Macro support planed.

    This script helps users define what should
    happen when a key is pressed.
    What key should perform that is not managed by this script.
    """

    def __init__(self):
        super(KeyConfigurator,self).__init__()
        self.__init_gui()

    def __init_gui(self):
        self.main_v_layout = QVBoxLayout()

        # fetches user input
        hl = QHBoxLayout()
        hl.setSpacing(10)
        # label
        ihl = QHBoxLayout()
        top_label = QLabel("Select input literal\n"
                             "field and press a key\n"
                             "to configure")
        top_label.setAlignment(QtCore.Qt.AlignLeft|QtCore.Qt.AlignVCenter)
        ihl.addWidget(top_label)
        rb = QRadioButton()
        rb.setChecked(True)

        ihl.addWidget(rb)
        hl.addLayout(ihl)
        hl.addWidget(self.create_vertical_separator())
        self.main_keypress_interceptor = c = KeyPressInterceptorComponent()
        rb.toggled.connect(self.first_radio_button_toggled)
        hl.addLayout(c)
        self.main_v_layout.addItem(hl)
        self.setLayout(self.main_v_layout)

        # modifier such as shift, alt, ctl to be send with the above
        hl = QHBoxLayout()
        hl.setSpacing(10)
        self.select_modifier_mask_component = SelectModifierMaskComponent()
        hl.addLayout(self.select_modifier_mask_component)
        self.main_v_layout.addLayout(hl)

        # separator
        self.addItem(self.create_horizontal_separator())

        # Let user assign TT, RESET to a key from a combobox list
        hl = QHBoxLayout()
        hl.setSpacing(10)
        # label
        ihl = QHBoxLayout()
        rb = QRadioButton()
        top_label = QLabel("Choose from list")
        top_label.setAlignment(QtCore.Qt.AlignLeft|QtCore.Qt.AlignVCenter)
        ihl.addWidget(top_label)
        ihl.addWidget(rb)
        hl.addLayout(ihl)
        hl.addWidget(self.create_vertical_separator())
        self.select_special_action = c = SelectSpecialActionComponent()
        c.setEnabled(False)
        hl.addLayout(c)
        rb.toggled.connect(self.second_radio_button_toggled)
        self.addItem(hl)

        # separator
        self.addItem(self.create_horizontal_separator())

        # Let users configure what the key should send for a long press
        hl = QHBoxLayout()
        self.select_long_key_press_option_componont = i = \
            SelectLongKeyPressOptionComponent()
        hl.addLayout(i)
        self.addItem(hl)
        self.main_keypress_interceptor.setFocus()

    @staticmethod
    def create_horizontal_separator():
        toto = QFrame()
        toto.setFrameShape(QFrame.HLine)
        toto.setFrameShadow(QFrame.Sunken)
        return toto
    @staticmethod
    def create_vertical_separator():
        toto = QFrame()
        toto.setFrameShape(QFrame.VLine)
        toto.setFrameShadow(QFrame.Sunken)
        return toto

    def first_radio_button_toggled(self, state):
        self.main_keypress_interceptor.setEnabled(state)
        self.select_modifier_mask_component.setEnabled(state)

    def second_radio_button_toggled(self,state):
        self.select_special_action.setEnabled(state)

    def getData(self) -> dict:
        d = self.main_keypress_interceptor.getData()
        d2 = self.select_long_key_press_option_componont.getData()
        d3 = self.select_special_action.getData()
        d4 = self.select_modifier_mask_component.getData()
        d.update(d2)
        d.update(d3)
        d.update(d4)
        # return {d, **d2, **d3, **d4 }
        return d
    def addItem(self, i):
        if issubclass(type(i),QBoxLayout):
            self.main_v_layout.addLayout(i)
        else:
            self.main_v_layout.addWidget(i)

    def close(self):
        self.main_keypress_interceptor.disconnect_keypress_observer()
        super().close()



if __name__ == "__main__":
    app = QApplication(sys.argv)
    # t = ScancodeViewer()
    # t = KeyCodeViewer()
    t = KeyConfigurator()
    t.show()
    r = t.exec_()
    print(t.getData())
    print("calling exit")
    sys.exit(r)

