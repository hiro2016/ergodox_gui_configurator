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
        :return:
        """
        self.right_hand_keymap = data[0]
        self.left_hand_keymap = data[1]

