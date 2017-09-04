from PyQt5.QtWidgets import QDialog, QFileDialog


class GUIBase(QDialog):
    def __init__(self):
        super(GUIBase, self).__init__()
        self.data = []

    def getFontHeight(self) -> int:
        return self.fontMetrics().height()

    def getFontWidth(self) -> int:
        # boundingRect does not include margins
        return self.fontMetrics().boundingRect("_").width()

