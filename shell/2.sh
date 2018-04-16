#!/bin/sh

if [ $# != 2 ]; then
    echo "ARGS ERROR"
    echo "USAGE: $0 FILENAME TARGET_WORD"
    exit 1
fi

echo "FILENAME: $1"
echo "TARGET WORD: $2"

echo "================ original text ================"
more $1

echo "================ new text ================"
sed -e "/$2/d" $1 > $1.witout-$2
more $1.witout-$2

