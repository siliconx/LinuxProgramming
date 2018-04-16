#!/bin/bash

# `seq` gen expression, `bc` calculating
printf "%d! = %s \n" $1 `seq -s "*" $1 | bc`
