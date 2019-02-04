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

# Only tested this for Ubuntu 14.04 (since this is the only Ubuntu I run and
# normally I woudln't touch Ubuntu with a 10 foot pole)
elif [ -f /etc/lsb-release ] && grep -q Ubuntu /etc/lsb-release ; then
    OS="UBUNTU"
    INSTALL="apt-get install"
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
    if [ $OS = "FEDORA" ] || [ $OS = "UBUNTU" ]; then
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
    elif [ $OS = "UBUNTU" ]; then
        PACKAGE=gcc-arm-none-eabi
    fi
    ;;
arm-gdb)
    if [ $OS = "FEDORA" ] || [ $OS = "ARCH" ]; then
        PACKAGE=arm-none-eabi-gdb
    else
        # On my Ubuntu Install I was having problems installing the
        # Specifically arm gdb... SO I installed the multiarch gdb
        # To invoke gdb on Ubuntu you need to type `gdb-multiarch`
        PACKAGE=gdb-multiarch
        #PACKAGE=gdb-arm-none-eabi
    fi
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
