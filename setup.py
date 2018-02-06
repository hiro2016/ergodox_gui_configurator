# import sys
from distutils.sysconfig import get_python_lib
import os
from cx_Freeze import *


build_exe_options = {
    "packages": ["os",'pyHook']
    ,"excludes": ["tkinter"],
    'includes':['pyHook'],
    'include_files': ['keymap_source.c']
}

# GUI applications require a different base on Windows (the default is for a
# console application).
base = None
if sys.platform == "win32":
    base = "Win32GUI"
executable = [ Executable(
    "main.py",
    base=base
)]

setup(  name = "ergodox_gui_configurator",
        version = "0.1",
        description = "Ergodox gui configurator",
        options = {"build_exe": build_exe_options},
        executables = executable )