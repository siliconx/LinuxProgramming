#!/bin/sh

if [ $# != 3 ]; then
    echo "USAGE: $0 FILENAME FROM(int) TO(int)"
    exit 1
fi

echo "FILENAE: $1"
echo "FROM: $2"
echo "TO: $3"

echo "================ target text ================"
cat $1 | head -n $3 | tail -n +$2
echo "\n==================== done ===================="

