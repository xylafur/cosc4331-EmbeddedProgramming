###############################################################################
##  This is a file just to help me install the tools I need to compile arm code
##  and also run that code in QEMU and debug with gdb
##
##  Since I run different distros on my laptop and desktop I wanted to make
##  sure that I have an easy install script for both
##
##  I accidentally wiped all of my files more often than I'm proud of.. so its
##  good to have things like this on git
###############################################################################
OS=""

if [ -f /etc/fedora-release ]; then
    OS="FEDORA"
    INSTALL=dnf install
elif [ -f /etc/arch-release ]; then
    OS="ARCH"
    INSTALL="pacman -S"
else
    echo "Don't know how to install stuff for this os.. sorry"
    exit 1
fi

OPER="$1"
if [ "$OPER" = "" ]; then
    echo "Specify an operation!"
    exit 1
fi

case $OPER in
qemu)
    if [ $OS = "FEDORA" ]; then
        PACKAGE=qemu-user
    elif [ $OS = "ARCH" ]; then
        PACKAGE=qemu-headless-arch-extra
    fi
    ;;
arm-cc)
    if [ $OS = "FEDORA" ]; then
        PACKAGE=arm-none-eabi-gcc-cs
    elif [ $OS = "ARCH" ]; then
        PACKAGE=arm-none-eabi-binutils
    fi
    ;;
arm-gdb)
    #luckly this is the same for both arch and fedora
    PACKAGE=arm-none-eabi-gdb
    ;;
all)
    bash $0 qemu
    bash $0 arm-cc
    bash $0 arm-gdb
    exit 0
    ;;
*)
    echo "Don't know how to install: $OPER"
    echo "Valid operations are: qemu, arm-cc, arm-gdb, all"
    exit 1
    ;;
esac

sudo $INSTALL $PACKAGE
