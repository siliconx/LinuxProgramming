#!/bin/sh

for i in $@; do
    if [ -f $i ]; then
    	# wc -- get the number of lines of a file
    	echo $i 'is a FILE, LINES:' `wc -l < $i`

    elif [ -d $i ]; then
    	echo $i 'is a DIR'

    else
    	echo $i 'NOTFOUND'
    fi
done