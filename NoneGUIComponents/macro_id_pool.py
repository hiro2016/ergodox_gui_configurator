import inspect
import logging
import sys

logging.basicConfig(
    level=logging.INFO,# logging.DEBUG,
    stream=sys.stdout,
    format="%(asctime)s - %(name)s - %(levelname)s - %(message)s")
logger = logging.getLogger("MacroIDPool")

class MacroIDPool:
    """
    This is not an ideal place but moved from keymap_to_code_transforemer
    due to dependency issue;python does not like circular dependencies.
    """
    _pool = [n for n in range(0, 254)]

    @staticmethod
    def get_id():
        id = MacroIDPool._pool.pop(len(MacroIDPool._pool) - 1)
        MacroIDPool.log("id %s is fetched:now removed from the pool"%id)
        return id

    @staticmethod
    def is_id_in_use(id:int):
        # MacroIDPool.log("id %s checked if in use"%id)
        return id not in MacroIDPool._pool

    @staticmethod
    def detect_id_conflict(ids: list):
        """
        :param ids:
        :return: ids that is already in use as a list
        """
        conflict = []
        for id in ids:
            if MacroIDPool.is_id_in_use(id):
                conflict.append(id)
        return conflict

    @staticmethod
    def mark_as_in_use(ids:list):
        for id in ids:
            MacroIDPool._pool.remove(id)
            MacroIDPool.log("id %s marked as in use"%id)


    @staticmethod
    def log(message):
        do_log = logger.getEffectiveLevel() == logging.DEBUG
        if not do_log:
            return
        stacks = inspect.stack()
        stack_trace = []
        for stack in stacks:
            stack_trace.append(stack[3])
        stack_trace = "\n\t".join(stack_trace)
        logger.log(logging.DEBUG, message + ":" + stack_trace)


    @staticmethod
    def mark_as_not_in_use(ids: list):
        for id in ids:
            if MacroIDPool.is_id_in_use(id):
                MacroIDPool.log("id %s is returned to the pool"%id)
                MacroIDPool._pool.append(id)


    @staticmethod
    def reset():
        """
        Not a good design but when Keymap object
        attempt to generate KEYMAP and macro code
        more than once, this method needs to be called.
        So ids no that are no longer used become available.

        todo come up with a better design.
        :return:
        """
        MacroIDPool._pool =[n for n in range(0, 254)]
        MacroIDPool.log("macro id pool is reseted")


if __name__ == "__main__":
    import sys
    logging.basicConfig(
        level=logging.DEBUG,
        stream=sys.stdout,
        format="%(asctime)s - %(name)s - %(levelname)s - %(message)s")
    MacroIDPool.mark_as_in_use([53])
