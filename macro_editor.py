import sys

from PyQt5.QtGui import QFont
from PyQt5.QtWidgets import QWidget, QTextEdit, QVBoxLayout, QApplication, QHBoxLayout, QLabel, QPushButton


class Base(QWidget):
    def getFontHeight(self) -> int:
        return self.fontMetrics().height()

    def getFontWidth(self) -> int:
        # boundingRect does not include margins
        return self.fontMetrics().boundingRect("_").width()


class Main(Base):
    def __init__(self):
        super(Main,self).__init__()
        self.__init_gui()

    def __init_gui(self):
        self.main_v_layout = ml = QVBoxLayout()
        # display message to the user
        hl = QHBoxLayout()
        self.message_label = l = QLabel()
        self.start_recording_button = b = QPushButton()
        hl.addWidget(b)
        hl.addWidget(l)
        hl = QHBoxLayout()


        self.input_capture_text_edit = e = QTextEdit()
        self.generated_code_text_edit = e2 = QTextEdit()
        hl.addWidget(e)
        hl.addWidget(e2)
        ml.addLayout(hl)
        self.setLayout(ml)

    def __init_listener(self):
        self.start_recording_button.clicked.connect(
            self.on_recording_start_requested )


    def on_recording_start_requested(self):
        pass
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
        d ={}
        return d


if __name__ == "__main__":
    app = QApplication(sys.argv)
    geo = app.desktop().screenGeometry()
    w = geo.width()
    h = geo.height()

    m = Main()
    m.setMinimumWidth((3*w)/4)
    m.setMinimumHeight((3*h)/4)
    m.init_font()
    m.move(0,0)
    m.show()
    sys.exit(app.exec_())
