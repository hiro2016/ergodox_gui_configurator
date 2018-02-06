from NoneGUIComponents.key_conf_dict_parser import KeyConfDictParser
class Keymap:
    """
    Data container.
    Holds user defininions for what should happen when a key is pressed
    for each ergodox keys.

    definitions are stored in a 2d array s a dict object and the rows and columns
    for the locations of the user defined actions are as following.

    KeyConfDictParser class object is used to parse the dict object.



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

    def update_key_data(self, old_data, new_data):
        """
        Find key to update by providing old key configuration.
        :param old_data:
        :param new_data:
        :return:
        """
        if old_data is None:
            return
        if new_data is None:
            return
        for r, row in enumerate(self.left_hand_keymap):
            for c,item in enumerate(row):
                if item is not None:
                    if set(old_data)==set(item):
                        self.left_hand_keymap[r][c] = new_data
        for r, row in enumerate(self.right_hand_keymap):
            for c,item in enumerate(row):
                if item is not None:
                    if set(old_data)==set(item):
                        self.right_hand_keymap[r][c] = new_data


    def get_all_keys_data(self):
        r = []
        for row in self.left_hand_keymap:
            for e in row:
                r.append(e)
        for row in self.right_hand_keymap:
            for e in row:
                r.append(e)
        return r

    def get_all_macro_ids_in_use(self):
        ids = []
        for d in self.get_all_keys_data:
            if d is None:
                continue
            p = KeyConfDictParser(d)
            for id in p.ids:
                ids.append(id)
        return ids


    def get_key(self, hand: "0 for left, 1 for right", row: int, col: int):
        if hand == 0:
            return self.left_hand_keymap[row][col]
        else:
            return self.right_hand_keymap[row][col]

    def get_data(self)->[]:
        """
        :return: list to be pickled.
        """
        return [self.right_hand_keymap, self.left_hand_keymap]

    def set_data(self, data:[]):
        """
        :data: what is returned by get_data is
        passed to here when un-pickled.

        The outer layer of pickled data structure represents layers, so:

            keymaps = []
            with open("file.emk","rb") as f:
                layers = pickle.load(f)
                for l in layers:
                    keymaps.append(Keymap(l))

        :return:
        """
        self.right_hand_keymap = data[0]
        self.left_hand_keymap = data[1]

