import sys
from PyQt5 import QtCore

from GUIComponents.KeySelector import KeySelector
from GUIComponents.GUIBase import GUIBase
from PyQt5.QtGui import QFont, QIcon
from PyQt5.QtWidgets import  QVBoxLayout, QApplication, QHBoxLayout, QLabel, QPushButton, QLineEdit, \
    QComboBox, QWidget, QCheckBox

from NoneGUIComponents.macro_composer import MacroComposer
from NoneGUIComponents.dict_keys import *




class DLTConfigComponent(GUIBase):
    """
    """
    macro_type = 'dlt'
    def __init__(self):
        super(DLTConfigComponent, self).__init__()
        self.__init_gui()
        self.__init_listener()
        self.generated_macro_code = ''



    def __init_gui(self):
        self.main_v_layout = ml = QVBoxLayout()


        # keycode
        hl = QHBoxLayout()
        l = QLabel("keycode to send")
        self._set_width_to_50(l)
        hl.addWidget(l)
        self.keycode_line_edit = e = QLineEdit()
        #open KeySelector botton
        self.open_key_selector_button = b = QPushButton("Select a key")
        hl.addWidget(e)
        hl.addWidget(b)
        ml.addLayout(hl)
        ml.addWidget(self.create_horizontal_separator())

        # Layer
        hl = QHBoxLayout()
        l = QLabel("Layer to temporarily toggle")
        self._set_width_to_50(l)
        hl.addWidget(l)
        self.layer_combobox = e = QComboBox()
        items = [str(n) for n in range(0,8)]
        e.addItems(items)
        hl.addWidget(e)
        ml.addLayout(hl)
        ml.addWidget(self.create_horizontal_separator())

        # Length of time to hold the key to trigger layer switching
        hl = QHBoxLayout()
        l = QLabel("Hold length for DLT press & key tap")
        self._set_width_to_50(l)
        hl.addWidget(l)
        self.hold_length_for_tap = e = QLineEdit()
        e.setText('200')
        hl.addWidget(e)
        l = QLabel('ms')
        hl.addWidget(l)
        ml.addLayout(hl)
        ml.addWidget(self.create_horizontal_separator())

        # Length of time hold key to send keycode in the toggled layer

        #descriptive label

        hl = QHBoxLayout()
        l = QLabel('Hold length for DLT & key press\n(hover over this for more detail)')
        l.setWindowIconText("hover for info")
        l.setToolTip("DLT allows you to choose whether to register a \n"
                     "keycode in the toggled layer or in the un-toggled layer\n"
                     "when another key is pressed while DLT key is down\n"
                     "but not released before DLT key is released.\n")
        l.setToolTipDuration(90000)
        self._set_width_to_50(l)
        hl.addWidget(l)
        self.hold_length_for_press = e = QLineEdit()
        e.setText('200')
        hl.addWidget(e)
        l = QLabel('ms')
        hl.addWidget(l)
        ml.addLayout(hl)
        ml.addWidget(self.create_horizontal_separator())

        # idling time definition

        hl = QHBoxLayout()
        l = QLabel("Idling time threshold\n(hover over this for more detail)")
        l.setToolTip(
            "Idling time before switching a layer \n"
            "is about 60ms more than keypress intervals\n"
            "while typing an English word.\n"
            "Here you can configure to add to or\n"
            "subtract from your DLT key holding\n"
            "duration based on the interval between\n"
            "the keypress one before DLT and the DLT\n"
            "key press")
        l.setToolTipDuration(90000)
        self._set_width_to_50(l)
        hl.addWidget(l)
        self.idling_time_threashold= e = QLineEdit()
        e.setText('90')
        hl.addWidget(e)
        ml.addLayout(hl)


        # reduce by
        hl = QHBoxLayout()
        l = QLabel( "reduce hold duration by:")
        l.setToolTip("If idling before DLT key press is\n"
                     "less than threshold")
        self._set_width_to_50(l)
        hl.addWidget(l)
        self.reduce_by= e = QLineEdit()
        e.setText('40')
        hl.addWidget(e)
        ml.addLayout(hl)

        # increase by
        hl = QHBoxLayout()
        l = QLabel( "increase hold duration by:")
        l.setToolTip("If idling before DLT key press is\n"
                     "greater than threshold")
        self._set_width_to_50(l)
        hl.addWidget(l)
        self.increase_by = e = QLineEdit()
        e.setText('25')
        hl.addWidget(e)
        ml.addLayout(hl)
        ml.addWidget(self.create_horizontal_separator())

        ohl = QHBoxLayout()
        hl = QHBoxLayout()
        l = QLabel("Disable layer toggle while modifier is on")
        hl.addWidget(l)
        self.no_layer_toggle_while_modifier_on = c = QCheckBox()
        c.setChecked(True)
        hl.addWidget(c)
        ohl.addLayout(hl)


        hl = QHBoxLayout()
        l = QLabel("Reduced chance of layer toggle for the same hand keys")
        hl.addWidget(l)
        self.no_restrict_same_hand_dlt = c = QCheckBox()
        c.setChecked(True)
        hl.addWidget(c)
        ohl.addLayout(hl)
        ml.addLayout(ohl)

        # Save and cancel buttons
        hl = QHBoxLayout()
        self.cancel_button = b = QPushButton(QIcon(),"Cancel")
        hl.addWidget(b)
        self.save_button = b = QPushButton(QIcon(),"Save")
        hl.addWidget(b)
        ml.addLayout(hl)

        self.setLayout(ml)

    def _create_descriptive_label(self, description):
        l = QLabel(description)
        l.setWordWrap(True)
        l.setAlignment(QtCore.Qt.AlignTop)
        l.setMaximumHeight(self.getFontHeight()*6)
        return l

    def _set_width_to_50(self,w:QWidget):
        g = self.geometry()
        w.setMaximumWidth(g.width()/2)
        w.setMinimumWidth(g.width()/2)
        w.setWordWrap(True)


    def generate_code(self)->str:
        layer = self.layer_combobox.currentText()
        keycode = self.keycode_line_edit.text()
        threshold_tap = self.hold_length_for_tap.text()
        threshold_press = self.hold_length_for_press.text()
        increase_by = self.increase_by.text()
        reduce_by = self.reduce_by.text()
        idling = self.idling_time_threashold.text()
        c = [
        'if(record->event.pressed){',
        'uint16_t kc = DLT(%s,%s);'%(layer, keycode),
        'dlt_threshold = %s;' % threshold_tap ,
        'dlt_threshold_key_not_up = %s;' % threshold_press,
        'dlt_hold_decreased_by = %s;' % increase_by,
        'dlt_hold_increased_by = %s;' % reduce_by,
        'dlt_pre_keypress_idling = %s;' % idling,
        'process_action_delayed_lt_from_macro(kc,record);',
        '}else{',
        'uint16_t kc = DLT(%s,%s);' % (layer,keycode),
        'process_action_delayed_lt_from_macro(kc,record);',
        'dlt_reset();'
        '}']
        return '\n'.join(c)

    def __init_listener(self):
        self.save_button.clicked.connect(
            self.save )
        self.cancel_button.clicked.connect(
            self.cancel )
        self.open_key_selector_button.clicked.connect(self.select_key)

    def select_key(self):
        s = KeySelector()
        s.show()
        s.exec_()
        self.keycode_line_edit.setText(s.getData()[KeySelector.key_hid_usage_id])

    def save(self):
        self.generated_macro_code = self.generate_code()
        self.close()

    def cancel(self):
        self.generated_macro_code = ''
        self.close()

    def init_font(self):
        """
        Must be called after width, height set.
        :return:
        """
        font_size = 12
        while self.getFontHeight() < (self.height()/30):
            self.font = f =QFont()
            f.setPointSize(font_size)
            self.setFont(f)
            font_size += 1

    def getData(self):
        return {
            key_macro: self.generated_macro_code
        }




if __name__ == "__main__":
    app = QApplication(sys.argv)
    geo = app.desktop().screenGeometry()
    w = geo.width()
    h = geo.height()

    m = DLTConfigComponent()
    m.setMinimumWidth((3*w)/4)
    m.setMinimumHeight((3*h)/4)
    m.init_font()
    m.move(0,0)
    m.show()
    r = app.exec_()
    print(m.getData())
    sys.exit(r)
