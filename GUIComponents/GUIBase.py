from PyQt5.QtWidgets import QDialog, QFileDialog, QFrame


class GUIBase(QDialog):
    def __init__(self):
        super(GUIBase, self).__init__()
        self.data = []

    def getFontHeight(self) -> int:
        return self.fontMetrics().height()

    def getFontWidth(self) -> int:
        # boundingRect does not include margins
        return self.fontMetrics().boundingRect("_").width()

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

