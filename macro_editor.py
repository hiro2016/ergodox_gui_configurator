import re
import sys

from GUIComponents.DLTConfigComponent import DLTConfigComponent
from GUIComponents.combo_emitter_macro_gw import ComboEmitterMacroGW
from GUIComponents.combo_receptor_macro_gw import ComboReceptorMacroGW
from GUIComponents.macro_recorder_gui import MacroRecorderGUI
from GUIComponents.GUIBase import *
from GUIComponents.dual_function_macro_generation_wizard import DualFunctionMacroGW

from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QWidget, QSizePolicy, QVBoxLayout, QApplication, QLabel, QHBoxLayout, QPushButton, \
    QTextEdit, QLineEdit

from NoneGUIComponents.key_conf_dict_generator import KeyConfDictGenerator
from NoneGUIComponents.key_conf_dict_parser import KeyConfDictParser
from NoneGUIComponents.macro_id_pool import MacroIDPool
from NoneGUIComponents.macro_composer import MacroComposer
from NoneGUIComponents.dict_keys import *

class MacroEditor(GUIBase):
    """
    Takes a dict object containing configuration for a single key.
    """
    def __init__(self, macro_dict=''):
        super(MacroEditor, self).__init__()
        # here for backward compatibility
        # it's defaultdict and not dict
        if type(macro_dict) is str:
            macro_dict = {key_macro_code : macro_dict}
        self.macro_data = macro_dict

        p = KeyConfDictParser(self.macro_data)
        self.code = p.macro_code
        self.macro_type = p.macro_type
        self.macro_ids = p.macro_ids
        self.macro_name = p.macro_name


        self.setSizePolicy(
            QSizePolicy.Expanding,
            QSizePolicy.Expanding )
        self.__init_gui()
        self.__init_listeners()

    def __init_gui(self):
        self.top_layout = tl = QVBoxLayout(self)
        l = QLabel("Available actions")
        tl.addWidget(l)
        tl.addWidget(self.create_horizontal_separator())

        # Simple macro
        hl = QHBoxLayout()
        hl.setSpacing(10)
        L = QLabel("Create a simple macro that sends \n"
                   "your keystrokes" )
        hl.addWidget(L)
        self.single_tap_only_macro_button = b = QPushButton(
            QIcon(),"Record your keystrokes as macro")
        hl.addWidget(b)
        tl.addLayout(hl)
        self.setLayout(tl)
        tl.addWidget(self.create_horizontal_separator())

        # Dual function macro
        hl = QHBoxLayout()
        hl.setSpacing(10)
        L = QLabel("Create a macro that is triggered \n"
                   "when the key is held down for X\n"
                   "milliseconds ")
        hl.addWidget(L)
        self.create_dfm_button = b = QPushButton(
            QIcon(),"Create a dual function macro")
        hl.addWidget(b)
        tl.addLayout(hl)
        tl.addWidget(self.create_horizontal_separator())

        # Create combo lt receiver macro
        hl = QHBoxLayout()
        hl.setSpacing(10)
        L = QLabel("Create a macro: combo receiver.\n"
                   "Switches to a different layer\n"
                   "and register keycode/macro found\n"
                   "there when pressed with emitter\n"
                   "macro key.")
        hl.addWidget(L)
        self.create_combo_receiver_button= b = QPushButton(
            QIcon(),"Create a combo receiver macro")
        hl.addWidget(b)
        tl.addLayout(hl)
        tl.addWidget(self.create_horizontal_separator())

        # Create combo lt emitter macro
        hl = QHBoxLayout()
        hl.setSpacing(10)
        L = QLabel("Create a macro: combo emitter.\n"
                   "Causes combo receiver macro\n"
                   "to act as described in the above.")
        hl.addWidget(L)
        self.create_combo_emitter_button = b = QPushButton(
            QIcon(),"Create a combo emitter macro")
        hl.addWidget(b)
        tl.addLayout(hl)
        tl.addWidget(self.create_horizontal_separator())


        #DLT configuration button
        hl = QHBoxLayout()
        hl.setSpacing(10)
        self.open_dlt_config_widget = b = QPushButton(
            "Set this key as DLT key")
        b.clicked.connect(self.configure_as_dlt_key)
        hl.addWidget(b)
        tl.addLayout(hl)
        tl.addWidget(self.create_horizontal_separator())

        # Let user assign marco key name
        hl = QHBoxLayout()
        hl.setSpacing(10)
        l = QLabel('Name of your macro')
        hl.addWidget(l)
        self.macro_name_line_edit = e = QLineEdit()
        e.setText(self.macro_name)
        # e.setEnabled(False)
        hl.addWidget(e)
        tl.addLayout(hl)
        tl.addWidget(self.create_horizontal_separator())


        # generated code view
        l = QLabel("Generated macro code(Editable)")
        tl.addWidget(l)
        self.code_view_text_edit = e =QTextEdit()
        tl.addWidget(e)
        e.setText(self.code)



        def cancel():
            self.code_view_text_edit.clear()
            self.close()

        hl = QHBoxLayout()
        hl.setSpacing(10)
        b = QPushButton(QIcon(),"Cancel")
        b.clicked.connect(cancel)
        hl.addWidget(b)
        b = QPushButton(QIcon(),"Save")
        b.clicked.connect(self.save)
        hl.addWidget(b)
        tl.addLayout(hl)


    def configure_as_dlt_key(self):
        c = DLTConfigComponent()
        c.show()
        c.exec_()
        d = c.getData()
        code = d[key_macro]
        self.macro_type = DLTConfigComponent.macro_type
        # name = d[key_macro_name]
        if code is not None and code != '':
            self.set_code([code])
            self.code_view_text_edit.setPlainText(self.code)

    def set_code(self,codes:list):
        self.code = ""
        while len(self.macro_ids) < len(codes):
            self.macro_ids.append(MacroIDPool.get_id())

        for i, code in enumerate(codes):
            macro_id = self.macro_ids[i]
            # add macro name as comment to macro code
            macro_comment = "// " +self.macro_name_line_edit.text()+ " \n"

            self.code += """
        case %s:
            %s
            %s
            break\n;
        """ % (macro_id, macro_comment,code.strip())

    def __init_listeners(self):
        self.single_tap_only_macro_button.clicked.connect(
            self.show_single_tap_only_macro_recorder_gui)
        self.create_dfm_button.clicked.connect(self.show_dfm_generator_wizard)

        self.create_combo_emitter_button.clicked.connect(
            self.show_combo_emitter_generator)
        self.create_combo_receiver_button.clicked.connect(
            self.show_combo_receptor_generator_wizard)

    def show_combo_emitter_generator(self):
        w = ComboEmitterMacroGW()
        w.show()
        w.exec_()
        d = w.getData()
        self.set_code([d[ComboEmitterMacroGW.key_macro]])
        self.macro_type = ComboEmitterMacroGW.macro_type
        self.code_view_text_edit.setPlainText(self.code)

    def show_combo_receptor_generator_wizard(self):
        """
        This method generates two macros.
        Combo receiver sends different key sequences depending on
        whether emitter key is pressed.

        One for sending keycodes.
        One for queueing a request.

        Cannot use set_code for the reason explained above: two macros.
        :return:
        """
        w = ComboReceptorMacroGW()
        w.show()
        w.exec_()
        d = w.getData()
        self.set_code_for_clt_receptor(d[key_macro])
        self.code_view_text_edit.setPlainText(self.code)
        self.macro_type = ComboReceptorMacroGW.macro_type

    def set_code_for_clt_receptor(self, code):
        while len(self.macro_ids) < 2:
            self.macro_ids.append(MacroIDPool.get_id())

        self.code = ""
        macro_id = self.macro_ids[1]
        macro_id2 = self.macro_ids[0]

        # macro_id is at 1 position of self.macro_ids
        self.code += "\n case %s:\n %s" % (macro_id,code.strip())

        # macro_id2 is at 0 position of self.macro_ids
        self.code += "\n case %s:\n process_combo_lt_receptor(record,%s,M(%s)); break;" \
                     % (macro_id2,macro_id2,macro_id)

    def show_dfm_generator_wizard(self):
        w = DualFunctionMacroGW()
        w.show()
        w.exec_()
        d = w.getData()
        self.set_code([d["macro"]])
        self.macro_type = DualFunctionMacroGW.macro_type
        self.code_view_text_edit.setPlainText(self.code)

    def show_single_tap_only_macro_recorder_gui(self):
        mr = MacroRecorderGUI()
        mr.show()
        mr.exec_()
        d = mr.getData()
        self.set_code([MacroComposer.generate_simple_tap_macro(d["macro"])])
        self.macro_type = MacroRecorderGUI.macro_type
        if self.code is not None and self.code != "":
            self.code_view_text_edit.setPlainText(self.code.strip())


    def getData(self):
        # User might have edited the content manually
        self.code = self.code_view_text_edit.toPlainText()
        name = self.macro_name_line_edit.text()
        g = KeyConfDictGenerator()
        g.set_code(self.code)
        g.set_macro_ids(self.macro_ids)
        g.set_macro_name(name)
        g.set_macro_type(self.macro_type)
        return g.to_macro_dict()

    def save(self):
        self.close()


if __name__ == "__main__":
    app = QApplication(sys.argv)
    w = MacroEditor()
    w.show()
    r = app.exec_()
    d = w.getData()
    for k in d.keys():
        print(k + ":" + str(d[k]))
        print('____________\n')

    sys.exit(r)
