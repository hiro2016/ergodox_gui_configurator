# Build Environment Setup

This page describes setting up the build environment for QMK. These instructions cover AVR processors (such as the atmega32u4.)

<!-- FIXME: We should have ARM instructions somewhere. -->

# Windows 10

## Creators Update
If you have Windows 10 with Creators Update or later, you can build and flash the firmware directly. Before the Creators Update, only building was possible. If you don't have it yet or if are unsure, follow [these instructions](https://support.microsoft.com/en-us/instantanswers/d4efb316-79f0-1aa1-9ef3-dcada78f3fa0/get-the-windows-10-creators-update).

## Windows Subsystem for Linux
In addition to the Creators Update, you need Windows 10 Subystem for Linux, so install it following [these instructions](http://www.howtogeek.com/249966/how-to-install-and-use-the-linux-bash-shell-on-windows-10/). If you already have the Windows 10 Subsystem for Linux from the Anniversary update it's recommended that you [upgrade](https://betanews.com/2017/04/14/upgrade-windows-subsystem-for-linux/) it to 16.04LTS, because some keyboards don't compile with the toolchains included in 14.04LTS. Note that you need to know what your are doing if you chose the `sudo do-release-upgrade` method.

## Git
If you already have cloned the repository on your Windows file system you can ignore this section.

You will need to clone the repository to your Windows file system using the normal Git for Windows and **not** the WSL Git. So if you haven't installed Git before, [download](https://git-scm.com/download/win) and install it. Then [set it up](https://git-scm.com/book/en/v2/Getting-Started-First-Time-Git-Setup), it's important that you setup the e-mail and user name, especially if you are planning to contribute. 

Once Git is installed, open the Git bash command and change the directory to where you want to clone QMK, note that you have to use forward slashes, and that your c drive is accessed like this `/c/path/to/where/you/want/to/go`. Then run `git clone --recurse-submodules https://github.com/qmk/qmk_firmware`, this will create a new folder `qmk_firmware` as a subfolder of the current one.

## Toolchain setup
The Toolchain setup is done through the Windows Subsystem for Linux, and the process is fully automated. If you want to do everything manually, there are no other instructions than the scripts themselves, but you can always open issues and ask for more information.

1. Open "Bash On Ubuntu On Windows" from the start menu. 
2. Go to the directory where you cloned `qmk_firmware`. Note that the paths start with `/mnt/` in the WSL, so you have to write for example `cd /mnt/c/path/to/qmk_firmware`. 
3. Run `util/wsl_install.sh` and follow the on-screen instructions.
4. Close the Bash command window, and re-open it.
5. You are ready to compile and flash the firmware!

## Some important things to keep in mind
* You can run `util/wsl_install.sh` again to get all the newest updates.
* Your QMK repository need to be on a Windows file system path, since WSL can't run executables outside it.
* The WSL Git is **not** compatible with the Windows Git, so use the Windows Git Bash or a windows Git GUI for all Git operations
* You can edit files either inside WSL or normally using Windows, but note that if you edit makefiles or shell scripts, make sure you are using an editor that saves the files with Unix line endings. Otherwise the compilation might not work.

# Windows (Vista and later)
1. If you have ever installed WinAVR, uninstall it.
2. Install [MHV AVR Tools](https://infernoembedded.com/sites/default/files/project/MHV_AVR_Tools_20131101.exe). Disable smatch, but **be sure to leave the option to add the tools to the PATH checked**.
3. If you are going to flash Infinity based keyboards you will need to install dfu-util, refer to the instructions by [Input Club](https://github.com/kiibohd/controller/wiki/Loading-DFU-Firmware).
4. Install [MinGW](https://sourceforge.net/projects/mingw/files/Installer/mingw-get-setup.exe/download). During installation, uncheck the option to install a graphical user interface. **DO NOT change the default installation folder.** The scripts depend on the default location.
5. Clone this repository. [This link will download it as a zip file, which you'll need to extract.](https://github.com/qmk/qmk_firmware/archive/master.zip) Open the extracted folder in Windows Explorer.
6. Open the `\util` folder.
7. Double-click on the `1-setup-path-win` batch script to run it. You'll need to accept a User Account Control prompt. Press the spacebar to dismiss the success message in the command prompt that pops up.
8. Right-click on the `2-setup-environment-win` batch script, select "Run as administrator", and accept the User Account Control prompt. This part may take a couple of minutes, and you'll need to approve a driver installation, but once it finishes, your environment is complete!

If you have trouble and want to ask for help, it is useful to generate a *Win_Check_Output.txt* file by running `Win_Check.bat` in the `\util` folder.

# Mac
If you're using [homebrew,](http://brew.sh/) you can use the following commands:

    brew tap osx-cross/avr
    brew install avr-libc
    brew install dfu-programmer

This is the recommended method. If you don't have homebrew, [install it!](http://brew.sh/) It's very much worth it for anyone who works in the command line. Note that the `make` and `make install` portion during the homebrew installation of avr-libc can take over 20 minutes and exhibit high CPU usage.

You can also try these instructions:

1. Install Xcode from the App Store.
2. Install the Command Line Tools from `Xcode->Preferences->Downloads`.
3. Install [DFU-Programmer](https://dfu-programmer.github.io/).

If you are going to flash Infinity based keyboards you will also need dfu-util

    brew install dfu-util

# Linux

To ensure you are always up to date, you can just run `sudo util/install_dependencies.sh`. That should always install all the dependencies needed. **This will run `apt-get upgrade`.**

You can also install things manually, but this documentation might not be always up to date with all requirements.

The current requirements are the following, but not all might be needed depending on what you do. Also note that some systems might not have all the dependencies available as packages, or they might be named differently.

```
build-essential
gcc
unzip
wget
zip
gcc-avr
binutils-avr
avr-libc
dfu-programmer
dfu-util
gcc-arm-none-eabi
binutils-arm-none-eabi
libnewlib-arm-none-eabi
git
```

Install the dependencies with your favorite package manager.

Debian/Ubuntu example:

    sudo apt-get update
    sudo apt-get install gcc unzip wget zip gcc-avr binutils-avr avr-libc dfu-programmer dfu-util gcc-arm-none-eabi binutils-arm-none-eabi libnewlib-arm-none-eabi

# Docker

If this is a bit complex for you, Docker might be the turn-key solution you need. After installing [Docker](https://www.docker.com/products/docker), run the following command at the root of the QMK folder to build a keyboard/keymap:

```bash
# You'll run this every time you want to build a keymap
# modify the keymap and keyboard assigment to compile what you want
# defaults are ergodox/default

docker run -e keymap=gwen -e subproject=ez -e keyboard=ergodox --rm -v $('pwd'):/qmk:rw edasque/qmk_firmware

# On windows docker seems to have issue with VOLUME tag in Dockerfile, and $('pwd') won't print a windows compliant path, use full path instead like this
docker run -e keymap=default -e subproject=ez -e keyboard=ergobox --rm -v D:/Users/Sacapuces/Documents/Repositories/qmk:/qmk:rw edasque/qmk_firmware

```

This will compile the targeted keyboard/keymap and leave it in your QMK directory for you to flash.

# Vagrant
If you have any problems building the firmware, you can try using a tool called Vagrant. It will set up a virtual computer with a known configuration that's ready-to-go for firmware building. OLKB does NOT host the files for this virtual computer. Details on how to set up Vagrant are in the [vagrant guide](vagrant_guide.md).

# Verify Your Installation
1. If you haven't already, obtain this repository ([https://github.com/qmk/qmk_firmware](https://github.com/qmk/qmk_firmware)). You can either download it as a zip file and extract it, or clone it using the command line tool git or the Github Desktop application.
2. Open up a terminal or command prompt and navigate to the `qmk_firmware` folder using the `cd` command. The command prompt will typically open to your home directory. If, for example, you cloned the repository to your Documents folder, then you would type `cd Documents/qmk_firmware`. If you extracted the file from a zip, then it may be named `qmk_firmware-master` instead.
3. To confirm that you're in the correct location, you can display the contents of your current folder using the `dir` command on Windows, or the `ls` command on Linux or Mac. You should see several files, including `readme.md` and a `quantum` folder. From here, you need to navigate to the appropriate folder under `keyboards/`. For example, if you're building for a Planck, run `cd keyboards/planck`.
4. Once you're in the correct keyboard-specific folder, run the `make` command. This should output a lot of information about the build process. More information about the `make` command can be found below.
