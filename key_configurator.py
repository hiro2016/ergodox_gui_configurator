import sys

from GUIComponents.DLTConfigComponent import DLTConfigComponent
from GUIComponents.KeyPresstInterceptorComponent import  *
from GUIComponents.GUIBase import  *
from GUIComponents.SelectLongKeyPressOptionComponent import  *
from GUIComponents.SelectSpecialActionComponent import  *
from GUIComponents.SelectModifierMaskComponent import  *
from PyQt5 import QtCore

from PyQt5.QtGui import QFont, QTextCursor, QFontMetrics, QIcon
from PyQt5.QtWidgets import QWidget, QDialog, QHBoxLayout, QPlainTextEdit, QSizePolicy, QFileDialog, QVBoxLayout, \
    QLabel, QTextEdit, QApplication, QComboBox, QBoxLayout, QRadioButton, QFrame, QPushButton

from NoneGUIComponents.key_conf_dict_parser import KeyConfDictParser, MacroIDPool
from macro_editor import MacroEditor


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

    def __init__(self, previous=None):
        super(KeyConfigurator,self).__init__()
        self.previous_config = {} if previous is None else previous
        self.__init_gui()
        self.macro_data = {}
        self.data_to_return_on_getData = None

    def __init_gui(self):
        # todo fix this, calling KeyConfParser fetches ID here needlessly
        MacroIDPool.reset()
        p = KeyConfDictParser(self.previous_config)
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
        self.main_keypress_interceptor = c = KeyPressInterceptorComponent(
            self.previous_config )
        rb.toggled.connect(self.first_radio_button_toggled)
        hl.addLayout(c)
        self.main_v_layout.addItem(hl)
        self.setLayout(self.main_v_layout)

        # modifier such as shift, alt, ctl to be send with the above
        hl = QHBoxLayout()
        hl.setSpacing(10)
        self.select_modifier_mask_component = SelectModifierMaskComponent(
            self.previous_config )
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
        self.addItem(self.create_horizontal_separator())

        # Assign macro
        hl = QHBoxLayout()
        hl.setSpacing(10)
        # label
        ihl = QHBoxLayout()
        rb = QRadioButton()
        rb.toggled.connect(self.third_radio_button_toggled)
        top_label = QLabel("Assign macro")
        top_label.setAlignment(QtCore.Qt.AlignLeft|QtCore.Qt.AlignVCenter)
        ihl.addWidget(top_label)
        ihl.addWidget(rb)
        hl.addLayout(ihl)
        hl.addWidget(self.create_vertical_separator())

        # buttons - too messy
        iivl =QVBoxLayout() # to the right of radio button
        hl.addLayout(iivl)
        self.addItem(hl)

        iihl = QHBoxLayout() #top row of iivl
        self.assign_macro_button = b =QPushButton(QIcon(),"Start macro wizard")
        b.clicked.connect(self.start_macro_wizard)
        b.setEnabled(False)
        iihl.addWidget(b)
        iivl.addLayout(iihl)

        iihl = QHBoxLayout() #bottom row of iivl
        # Let user assign marco key name
        hl = QHBoxLayout()
        hl.setSpacing(10)
        l = QLabel('Name of your macro')
        hl.addWidget(l)
        self.macro_name_line_edit = e = QLineEdit()
        e.setText(p.macro_name)
        e.setEnabled(False)
        hl.addWidget(e)
        iivl.addLayout(iihl)
        iihl.addLayout(hl)
        hl.addWidget(self.create_horizontal_separator())

        #DLT configuration button
        self.open_dlt_config_widget = b = QPushButton(
            "Set this key as DLT key")
        b.clicked.connect(self.configure_as_dlt_key)
        self.addItem(b)
        hl.addWidget(self.create_horizontal_separator())



        # save or cancel button
        hl = QHBoxLayout()
        hl.setSpacing(10)
        b = QPushButton("Cancel")
        b.clicked.connect(self.cancel)
        hl.addWidget(b)
        b = QPushButton("Save")
        b.clicked.connect(self.save)
        hl.addWidget(b)
        self.addItem(hl)

    def configure_as_dlt_key(self):
        c = DLTConfigComponent()
        c.show()
        c.exec_()
        m = c.getData()
        if m is not None or m != '':
            self.macro_data = m
            self.macro_name_line_edit.setText(m[DLTConfigComponent.key_macro_name])
            self.save()

    def save(self):
        d = self.main_keypress_interceptor.getData()
        d2 = self.select_long_key_press_option_componont.getData()
        d3 = self.select_special_action.getData()
        d4 = self.select_modifier_mask_component.getData()
        d5 = self.macro_data
        macro_name = self.macro_name_line_edit.text()
        if macro_name:
            d5['macro_name'] = macro_name
        else:
            d5['macro_name'] = 'undefined'

        d.update(d2)
        d.update(d3)
        d.update(d4)
        d.update(d5)
        self.data_to_return_on_getData = d
        self.close()

    def cancel(self):
        self.data_to_return_on_getData = self.previous_config
        self.close()

    def first_radio_button_toggled(self, state):
        self.main_keypress_interceptor.setEnabled(state)
        self.select_modifier_mask_component.setEnabled(state)

    def second_radio_button_toggled(self,state):
        state = state == True
        self.select_special_action.setEnabled(state)
        self.main_keypress_interceptor.setEnabled(not state)
        self.select_modifier_mask_component.setEnabled(not state)

    def third_radio_button_toggled(self,state:bool):
        state = state == True
        self.main_keypress_interceptor.setEnabled(not state)
        self.select_modifier_mask_component.setEnabled(not state)
        self.select_special_action.setEnabled(not state)
        self.select_long_key_press_option_componont.setEnabled(not state)
        self.assign_macro_button.setEnabled(state)
        self.macro_name_line_edit.setEnabled(state)

    def start_macro_wizard(self):
        macro = None
        if self.macro_data is not None and self.macro_data != "":
            for k in self.macro_data.keys():
                macro = self.macro_data[k]

        if macro is not None and macro != "":
            e = MacroEditor(self.macro_data[MacroEditor.key_macro])
        else:
            p = KeyConfDictParser(self.previous_config)
            e = MacroEditor(p.macro_code)
        e.show()
        e.exec_()
        self.macro_data = e.getData()

    def getData(self) -> dict:
        if self.data_to_return_on_getData is not None:
            return self.data_to_return_on_getData
        else:
            return self.previous_config

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

