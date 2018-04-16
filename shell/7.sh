#!/bin/bash

# `seq` gen expression, `bc` calculating
seq -s "*" $1 | bc
