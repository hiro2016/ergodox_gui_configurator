import sys

import pickle
from PyQt5 import QtCore

from PyQt5.QtCore import QRect
from PyQt5.QtWidgets import QWidget, QVBoxLayout, QPushButton, QHBoxLayout, QApplication, QSizePolicy, QBoxLayout, \
    QGridLayout, QLabel, QSpacerItem, QTabWidget

import key_configurator
from NoneGUIComponents.key_conf_dict_parser import KeyConfDictParser
from NoneGUIComponents.keymap_to_code_transformer import KeymapsToCodeTransformer
from NoneGUIComponents.keymap import Keymap
from NoneGUIComponents.macro_composer import MacroComposer


class Tab(QWidget):
    """
    Contains main keys and thumb cluster keys.
    given a Keymap object, loads the predefined configuration.
    keymap.c generation is handled by main.
    """
    right = Keymap.right
    left = Keymap.left
    def __init__(self):
        super(Tab, self).__init__()
        # keymap object holds data.
        self.keymap = Keymap()

        # QPushButtons represent keys
        self.buttons_left = [[ None for _ in range(7) ] for _ in range(8)]
        self.buttons_right = [[ None for _ in range(7) ] for _ in range(8)]

        self.__init_gui()

    def __init_gui(self):
        # Adding buttons that represent keys
        self.__init_keyboard_widgets()
        self.__init_main_key_clusters()
        self.__init_thumb_clusters()


    def __init_keyboard_widgets(self):
        """
        Creates and add widgets that represent right and left halves of
        the keyboard.

        add field members:
        self.left_kb
        self.right_kb

        #the below should hold layouts that contain QPushButtons
        that represent keys gui way.
        self.left_v_box_layout = left_vl = QVBoxLayout()
        self.right_v_box_layout = right_vl = QVBoxLayout()
        :return:
        """
        outer_most_layout = QHBoxLayout(self)
        self.left_kb = QWidget()
        self.right_kb = QWidget()

        outer_most_layout.addWidget(self.left_kb,True)
        outer_most_layout.addWidget(self.right_kb,True)
        self.setLayout(outer_most_layout)

        # buttons representing keys goes into these layout
        self.left_grid_layout = QGridLayout()
        self.right_grid_layout = QGridLayout()

        # enforce all elements within stretched equally.
        for c in range(0,9):
            self.right_grid_layout.setRowStretch(c,1)
            self.left_grid_layout.setRowStretch(c,1)

        self.left_kb.setLayout(self.left_grid_layout)
        self.right_kb.setLayout(self.right_grid_layout)


    def get_keymap_data(self):
        """
        returns pickle-able Keymap data.
        :return:
        """
        return self.keymap.get_data()

    def _set_button_label(self,d:dict, b:QPushButton):
        p = KeyConfDictParser(d)
        if p.is_macro():
            t = 'Macro:\n' + p.macro_name
        else:
            t = p.to_keymap_element()
            t = t.replace(p.hid_usage_id,p.keyname)
        b.setText(t)

    def set_keymap_data(self,data):
        """
        sets unpickled data to Keymap.
        :param data:what was generated by get_keymap_data
        :return:
        """
        self.keymap.set_data(data)
        keymap = self.keymap
        for row, l in enumerate(keymap.right_hand_keymap):
            for col, data in enumerate(l):
                if data is None:
                    continue
                b = self.buttons_right[row][col]
                self._set_button_label(data,b)

        for row, l in enumerate(keymap.left_hand_keymap):
            for col, data in enumerate(l):
                if data is None:
                    continue
                b = self.buttons_left[row][col]
                self._set_button_label(data,b)



    def __init_main_key_clusters(self):
        left_vl = self.left_grid_layout
        right_vl = self.right_grid_layout
        # Note: A QPushButton position and the key data indices
        # in 2d array differ.

        # row one left hand
        for ic in range(0, 7):
            b = QPushButton("button")
            self.__assign_handler_to_button_and_store(b, self.left, 0, ic)
            left_vl.addWidget(b,0,ic)

        # row one right hand
        for ic in range(0, 7):
            b = QPushButton("button")
            self.__assign_handler_to_button_and_store(b, self.right, 0, ic)
            right_vl.addWidget( b,0,ic)

        # row two
        # right most key for left keyboard and left most for right keyboard
        # is handled later.
        for ic in range(0, 6):
            b = QPushButton("button")
            self.__assign_handler_to_button_and_store(b, self.left, 1, ic)
            left_vl.addWidget(b,1,ic)
        for ic in range(1, 7):
            b = QPushButton("button")
            self.__assign_handler_to_button_and_store(b, self.right, 1, ic)
            right_vl.addWidget(b,1,ic)

        # row three
        for ic in range(0, 6):
            b = QPushButton("button")
            self.__assign_handler_to_button_and_store(b, self.left, 2, ic)
            left_vl.addWidget(b,2,ic)

        for ic in range(1, 7):
            b = QPushButton("button")
            self.__assign_handler_to_button_and_store(b, self.right, 2, ic - 1)
            right_vl.addWidget(b,2,ic)


        # row four
        # right most key for left keyboard and left most for right keyboard
        # is handled later.
        for ic in range(0, 6):
            b = QPushButton("button")
            self.__assign_handler_to_button_and_store(b, self.left, 3, ic)
            left_vl.addWidget(b,3,ic)
        for ic in range(1, 7):
            b = QPushButton("button")
            self.__assign_handler_to_button_and_store(b, self.right, 3, ic)
            right_vl.addWidget(b,3,ic)


        # row five
        for ic in range(1, 6):
            b = QPushButton("button")
            self.__assign_handler_to_button_and_store(b, self.left, 4, ic - 1)
            left_vl.addWidget(b,4,ic)
        for ic in range(1, 6):
            b = QPushButton("button")
            self.__assign_handler_to_button_and_store(b, self.right, 4, ic - 1)
            right_vl.addWidget(b,4,ic)

        # The odd two keys on the row two and four
        # that occupy three rows together.
        # lef hand
        lvbl = QVBoxLayout()
        rvbl = QVBoxLayout()
        b = QPushButton("button")
        self.__assign_handler_to_button_and_store(b, self.left, 1, 6)
        lvbl.addWidget(b,False)
        b = QPushButton("button")
        self.__assign_handler_to_button_and_store(b, self.left, 3, 6)

        lvbl.addWidget(b,False)

        # right hand keyboard
        b = QPushButton("button")
        self.__assign_handler_to_button_and_store(b, self.right, 1, 0)
        rvbl.addWidget(b,False)
        b = QPushButton("button")
        self.__assign_handler_to_button_and_store(b, self.right, 3, 0)
        b.heightForWidth(False)
        rvbl.addWidget(b,False)

        right_vl.addLayout(rvbl,1,0,3,1)
        left_vl.addLayout(lvbl,1,6,3,1)

    def __init_thumb_clusters(self):
        # Thumb cluster keys goes into these
        self.right_thumb_cluster = QGridLayout()
        self.left_thumb_cluster = QGridLayout()

        #Adding layout to the sub-widget's root grid layout.
        # CentralWidget-> layout->subwidget->layout->left_thumb_cluster
        self.left_grid_layout.addLayout(self.left_thumb_cluster,6,4,4,3)
        self.right_grid_layout.addLayout(self.right_thumb_cluster,6,0,4,3)


        # row six left thumb cluster
        for ic in range(1, 3):
            b = QPushButton("button")
            self.__assign_handler_to_button_and_store(b, self.left, 5, ic - 1)
            self.left_thumb_cluster.addWidget(
                b,0,ic)

        # right
        for ic in range(0, 2):
            b = QPushButton("button")
            self.__assign_handler_to_button_and_store(b, self.right, 5, ic)
            self.right_thumb_cluster.addWidget(
                b,0,ic)

        # row seven left
        b = QPushButton("button")
        self.__assign_handler_to_button_and_store(b, self.left, 6, 0)
        self.left_thumb_cluster.addWidget(b,1,2)
        #right
        b = QPushButton("button")
        self.__assign_handler_to_button_and_store(b, self.right, 6, 0)
        self.right_thumb_cluster.addWidget( b,1,0)

        # row eight left
        for c in range(0,3):
            b = QPushButton("button")
            self.__assign_handler_to_button_and_store(b, self.left, 7, c)
            if(c<2):
                self.left_thumb_cluster.addWidget(
                    b,1,c,2,1)
            else:
                self.left_thumb_cluster.addWidget(
                    b,2,c)


        #right
        for c in range(0,3):
            b = QPushButton("button")
            self.__assign_handler_to_button_and_store(b, self.right, 7, c)
            if(c>0):
                self.right_thumb_cluster.addWidget(
                    b,1,c,2,1)
            else:
                self.right_thumb_cluster.addWidget(
                    b,2,c)




    def setFixedHeight(self, p_int):
        super().setFixedHeight(p_int)

    def setFixedWidth(self, p_int):
        super().setFixedWidth(p_int)

    def __assign_handler_to_button_and_store(self,
                                             button: QPushButton,
                                             hand: "0 for left 1 for right",
                                             row: int,
                                             col: int):
        """
        Assigns onClicked handler to QPushButton representing a keyboard key.
        Stores the button object in a 2d array.
        :param button:
        :param hand: whether the button represents a key in the right or left keyboard.
        :param row: the row position of the button; refer to keymap
        :param col: the column position of the button;refer to keymap
        :return: void
        """
        # onButtonPressed is here to keep reference to param values.
        def onButtonPressed(pressed, hand=hand, button = button,row=row,col=col):
            prv_config = self.keymap.get_key(hand, row, col)
            sv = key_configurator.KeyConfigurator(prv_config)
            sv.show()
            sv.exec_()
            data =  sv.getData()
            self._process_user_input(button, data,hand, row,col)

        sizePolicy = QSizePolicy(
            QSizePolicy.Fixed,
            QSizePolicy.Expanding)

        # adding to 2d array so the button will be accessible by their coordinates.
        if hand is Keymap.left:
            self.buttons_left[row] [col] = button
        else:
            self.buttons_right[row][col] = button


        button.setSizePolicy(sizePolicy)
        button.clicked.connect(onButtonPressed)

    def _process_user_input(self, button:QPushButton, data:dict,hand:int, row:int, col:int):
        """
        Called when user configured a key.
        Reflects changes to the GUI and update the data in keymap.

        :param data:
        :param hand: whether the button represents a key in the right or left keyboard.
        :param row:
        :param col:
        :return:
        """
        self._set_button_label(data,button)
        self.keymap.set_key(hand, row, col, data)

    def _compute_key_width(self):
        r = QRect(self.geometry())
        return r.width() / 20
    def _resize_button(self, b:QPushButton):
        b.setFixedWidth(self._compute_key_width())
        b.setFixedHeight(self._compute_key_width())

    def get_keymap_as_string(self):
        return self.keymap.to_KEYMAP()



class CentralWidget(QWidget):
    """
    Provides the central gui for configurator.
    Given a Keymap object, loads the predefined configuration.
    keymap.c generation is handled by main.
    """
    def __init__(self):
        super(CentralWidget, self).__init__()
        self.tabs = []
        self.__init_gui()

    def __init_gui(self):
        self.tab_w = QTabWidget(self)
        for c in range(0,10):
            t = Tab()
            self.tab_w.addTab(t, 'layer ' + str(c))
            self.tabs.append(t)

    def setFixedHeight(self, p_int):
        super().setFixedHeight(p_int)
        self.tab_w.setFixedHeight(p_int)

    def setFixedWidth(self, p_int):
        super().setFixedWidth(p_int)
        self.tab_w.setFixedWidth(p_int)

    def save_keymap(self,path):
        """
        Pickles Keymap object's data.
        GUI should be provided by main.
        :return:
        """
        layers = []
        for m in self.tabs:
            layers.append(m.get_keymap_data())

        with open(path,"wb") as f:
            pickle.dump(layers,f)


    def load_keymap(self, path):
        """
        Loads pickled keymap data.
        :param path:
        :return:
        """
        with open(path,"rb") as f:
            layers = pickle.load(f)
            for i, l in enumerate(layers):
                self.tabs[i].set_keymap_data(l)

    def load_keymapc_from_and_write_to(self, source, dest)->dict:
        """
        source: the default keymap.c file to modify.
        dest: path to the file to write into
        :return: what should be inserted into keymap_source.c
        """
        t = KeymapsToCodeTransformer([t.keymap for t in self.tabs])
        d = t.generate_code(source,dest)
        keymap = d['keymap']
        macro = d['macro']
        members = d['members']
        with open(source,'r') as f:
            data = f.read()
        data = data.replace(MacroComposer.keymap_place_holder, keymap)
        data = data.replace(MacroComposer.macro_place_holder, macro)
        data = data.replace(MacroComposer.field_member_place_holder, members)
        with open(dest, "w") as f:
            f.write(data)

    def move_current_tab_to_layer(self, layer):
        self.tabs
        current_index = self.tab_w.currentIndex()
        current_tab = self.tabs[current_index]
        swap_target = self.tabs[layer]
        self.tab_w.removeTab(current_index)
        self.tab_w.removeTab(layer)
        self.tab_w.insertTab(layer, current_tab, "layer%s"%layer)
        self.tab_w.insertTab(current_index, swap_target, 'layer%s'%current_index)
        self.tabs[current_index] = swap_target
        self.tabs[layer] = current_tab





if __name__ == "__main__":
    app = QApplication(sys.argv)
    c = CentralWidget()
    c.show()
    sys.exit(app.exec_())
