import pickle
from collections import defaultdict



class Key:
    def __init__(self,d:dict):
        # return empty string by dafault rather than KeyError
        dd = defaultdict(lambda :'')
        if d is None:
            d = {}

        for k in d.keys():
            dd[k] = d[k]
        d = dd

        self.hid_usage_id = d['hid_usage_id']
        self.long_press = d["on_long_press"]
        self.long_press_param = d["on_long_press_param"]
        self.special_action_param = d["special_action_param"]
        self.special_action = d["special_action"]
        self.modifier_mask = d["modifier_mask"]
        self.modifier_mask2 = d["modifier_mask2"]
        self.keyname = d['keyname']

        # making sure nothing is set to None
        if self.hid_usage_id is None:
            self.hid_usage_id = ''
        if self.keyname is None:
            self.keyname = ''
        if self.long_press is None:
            self.long_press = ''
        if self.long_press_param is None:
            self.long_press_param = ''
        if self.special_action is None:
            self.special_action = ''
        if self.special_action_param is None:
            self.special_action_param = ''
        if self.modifier_mask is None:
            self.modifier_mask = ''
        if self.modifier_mask2 is None:
            self.modifier_mask2 = ''

    def to_string(self):
        data = self.hid_usage_id
        # TT, TG, RESET, etc
        if self.special_action != "":
            data = self.special_action
            if self.special_action_param != '':
                data = data + '(' + self.special_action_param + ')'
            return data

        if data == '':
            # can happen
            return "KC_TRNS"

        if self.modifier_mask != "":
            data = self.modifier_mask + '(' + data + ')'
        if self.modifier_mask2 != "":
            data = self.modifier_mask2 + '(' + data + ')'

        if self.long_press_param != '':
            data = self.long_press + "(" + self.long_press_param + ", " + data + ")"
        elif self.long_press != '':
            data = self.long_press + "(" + data + ")"
        return data

    def to_descriptive_string(self):
        s = self.keyname
        if s == '':
            s = self.special_action
            if self.special_action_param != '':
                s = s + '(' + self.special_action_param + ')'
        s += "\n"
        if self.modifier_mask != '':
            s += "m:" + self.modifier_mask
        s += "\n"
        if self.long_press != '':
            s += 'lp:' + self.long_press
        if self.long_press_param != '':
            s += '(' + self.long_press_param + '...'
        s += "\n"
        return s




class Keymap:
    """
    Data container.
    Holds user defininions for what should happen when a key is pressed
    for each ergodox keys.

    definitions are stored in a 2d array s a dict object and the rows and columns
    for the locations of the user defined actions are as following.

    Key class object is used to parse the dict object.



/*
 * left_hand_keymap,                                              right_hand_keymap
 * row, col
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |0,0     |0,1   |0,2   |0,3   | 0,4  | 0,5  | 0,6  |           |0,0     |0,1   |0,2   |0,3   | 0,4  | 0,5  | 0,6  |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |1,0     |1,1   |1,2   |1,3   |1,4   |1,5   |1,6   |           | 1,0  |1,1   |1,2   |1,3   |1,4   |1,5   |  1,6   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |2,0     | 2,1  |2,2   |2,3   |2,4   | 2,5  |------|           |------| 2,0  | 2,1  |2,2   |2,3   |2,4   | 2,5    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | 3,0    |3,1   |3,2   |3,3   |3,4   |3,5   |3,6   |           | 3,0  |3,1   |3,2   |3,3   |3,4   |3,5   |3,6     |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 * |4,0     |  4,1 |4,2   |4,3   |4,4   |                                       |4,0     |  4,1 |4,2 |4,3   |4,4   |
 * `------------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        | 5,0 |5,1    |       | 5,0 |5,1    |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      | 6,0  |       |6,0   |        |      |
 *                                 |      |      |------|       |------|        |      |
 *                                 | 7,0  | 7,1  | 7,2  |       | 7,0  | 7,1    | 7,2  |        |      |
 *                                 `--------------------'       `----------------------'
 */
    """
    right = 1
    left = 0

    def __init__(self):
        self.right_hand_keymap = [[None for _ in range(7)] for c in range(8)]
        self.left_hand_keymap = [[None for _ in range(7)] for c in range(8)]

    def set_key(self, hand: "0 for left, 1 for right", row: int, col: int, data):
        if hand == 0:
            self.left_hand_keymap[row][col] = data
        else:
            self.right_hand_keymap[row][col] = data

    def get_data(self)->[]:
        """
        :return: list to be pickled.
        """
        return [self.right_hand_keymap, self.left_hand_keymap]

    def set_data(self, data:[]):
        """
        :data: what is returned by get_data.
        :return:
        """
        self.right_hand_keymap = data[0]
        self.left_hand_keymap = data[1]


    def _dict_to_string(d:dict) -> str:
        return Key(d).to_string()

    def dict_to_name_string(d):
        k = Key(d)
        return k.to_descriptive_string()


    def _keymap_to_string(keymap_2d_array):
        out = []
        m = keymap_2d_array

        # m is currently dict
        def format_and_add(d):
            if d is None:
                d = {}
            data = Keymap._dict_to_string(d)
            data += ","
            out.append(data)

        for c in range(0,7):
            format_and_add(m[0][c])
        out.append("\n")
        for c in range(0,7):
            format_and_add(m[1][c])
        out.append("\n")
        for c in range(0,6):
            format_and_add(m[2][c])
        out.append("\n")
        for c in range(0,7):
            format_and_add(m[3][c])
        out.append("\n")
        for c in range(0,5):
            format_and_add(m[4][c])
        out.append("\n")

        for c in range(0,2):
            format_and_add(m[5][c])
        out.append("\n")
        format_and_add(m[6][c])
        out.append("\n")
        for c in range(0,3):
            format_and_add(m[7][c])
        out.append("\n")
        out = "".join(out)
        return out

    def to_string(self):
        rm = self.right_hand_keymap
        lm = self.left_hand_keymap
        rm = Keymap._keymap_to_string(rm)
        lm = Keymap._keymap_to_string(lm)
        rm = rm.rstrip("\n")
        rm = rm.rstrip(",")
        new_map = "KEYMAP(  \n %s \n %s )," % (lm,rm)
        return new_map








