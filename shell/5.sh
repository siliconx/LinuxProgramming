#!/bin/bash

# present the result in a form of matrix
# ROW: each file
# COL: occurrence of each word

printf "WORD \ FILE"
for i in $@; do
    printf "%11s" $i
done
echo

for word in $(<$1); do  # read words_file word by word
    printf "%11s" $word

    for i in $@; do  # counting
      printf "%11s" `grep -w "$word" $i | wc -l`
    done
    echo
done
