DSLite=/opt/ccstudio/ccsv8/ccs_base/DebugServer/bin/DSLite
CONFIG=MSP432P401R.ccxml

if [ $# -eq 2 ]; then
    START=$1
    LENGTH=$2
    OUTPUT=""
elif [ $# -eq 3 ]; then
    START=$1
    LENGTH=$2   
    OUTPUT="--output=$3"
else
    echo "$0 <start address> <length> [output filename] "
fi

$DSLite --config=$CONFIG --range=$START,$LENGH $OUTPUT
