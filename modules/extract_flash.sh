DSLite=/opt/ccstudio/ccsv8/ccs_base/DebugServer/bin/DSLite
CONFIG=MSP432P401R.ccxml

usage(){
    echo "$0 <start address> <length> [output filename] "
    exit 1
}

if [ $# -eq 1 ]; then
    if [ $1 = "READ_FLASH" ]; then
        START="0x00020000"
        LENGTH="16383"
        OUTPUT="--output=FLASH.data"
    else
        usage
    fi
elif [ $# -eq 2 ]; then
    START=$1
    LENGTH=$2
    OUTPUT=""
elif [ $# -eq 3 ]; then
    START=$1
    LENGTH=$2   
    OUTPUT="--output=$3"
else
    usage
fi

$DSLite memory --config=$CONFIG --range=$START,$LENGTH $OUTPUT
