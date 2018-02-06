import sys
from NoneGUIComponents.macro_recorder import MacroRecorder
from GUIComponents.GUIBase import GUIBase
from PyQt5.QtGui import QFont, QIcon
from PyQt5.QtWidgets import QTextEdit, QVBoxLayout, QApplication, QHBoxLayout, QLabel, QPushButton, QLineEdit, \
    QDialog, QCheckBox


class MacroRecorderGUI(GUIBase):
    """
    Generate C code for qmk macro.
    Unless user canceled or did nothing, the generated code is
    available via getData method
    """
    key_macro = 'macro'
    macro_type = "simple_macro"
    def __init__(self):
        super(MacroRecorderGUI, self).__init__()
        self.__init_gui()
        self.macro_recorder = MacroRecorder()
        self.__init_listener()

    def close(self):
        if self.macro_recorder.isRecording():
            self.macro_recorder.stop()
        super().close()


    def _update_text_edit_for_keypress(self, hid_id, keyname, code):
        self.keyname_list_text_edit.append("pressed: "+keyname)
        self.generated_code_text_edit.append(code);

    def _update_text_edit_for_keyrelease(self, hid_id, keyname, code):
        self.keyname_list_text_edit.append( "released: "+keyname)
        filter_up_to = None
        if self.filter_sleep_time_cb.isChecked():
            try:
                filter_up_to = code.index('}')
            except ValueError:
                pass
            if filter_up_to is not None and filter_up_to > 0:
                code = code[filter_up_to + 1:]
        self.generated_code_text_edit.append(code)

    def onRecordingStartClicked(self):
        if self.macro_recorder.isRecording():
            self.macro_recorder.stop()
            self.start_recording_button.setText("Start recording")
            self.user_message_display_label.clear()
        else:
            self.macro_recorder.start()
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

        # Filter sleeps
        hl = QHBoxLayout()
        l = QLabel("filter sleep interval between key press and release")
        hl.addWidget(l)
        self.filter_sleep_time_cb = b = QCheckBox()
        b.setChecked(True)
        hl.addWidget(b)
        ml.addLayout(hl)


        # Save and cancel buttons
        hl = QHBoxLayout()
        self.cancel_button = b = QPushButton(QIcon(),"Cancel")
        hl.addWidget(b)
        self.save_button = b = QPushButton(QIcon(),"Save")
        hl.addWidget(b)
        ml.addLayout(hl)

        self.setLayout(ml)



        #small fonts are paint to look at. Resize
        geo =QApplication.desktop().screenGeometry()
        w =geo.width()
        h =(3*geo.height())/4
        self.setFixedWidth(w)
        self.setFixedHeight(h)
        self.move(0,0)


    def __init_listener(self):
        self.start_recording_button.clicked.connect(
            self.onRecordingStartClicked)
        self.macro_recorder.keypressed.connect(
            self._update_text_edit_for_keypress)
        self.macro_recorder.keyreleased.connect(
            self._update_text_edit_for_keyrelease)


        self.clear_recorded_macro_button.clicked.connect(
            self._clear_recorded_macro_clicked)

        def save():
            self.close()

        def cancel():
            self.generated_code_text_edit.clear()
            self.close()

        self.save_button.clicked.connect(save)
        self.cancel_button.clicked.connect(cancel)

    def _clear_recorded_macro_clicked(self):
        self.keyname_list_text_edit.clear()
        self.user_message_display_label.clear()
        self.recording_input_field.clear()
        self.generated_code_text_edit.clear()


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
        code = self.generated_code_text_edit.toPlainText()
        if code is None or code == '':
            return { self.key_macro: ''}
        return { self.key_macro: code }







if __name__ == "__main__":
    app = QApplication(sys.argv)
    geo = app.desktop().screenGeometry()
    w = geo.width()
    h = geo.height()

    m = MacroRecorderGUI()
    m.setMinimumWidth((3*w)/4)
    m.setMinimumHeight((3*h)/4)
    m.init_font()
    m.move(0,0)
    m.show()
    r = app.exec_()
    print(m.getData())
    sys.exit(r)
