#!/bin/sh

if [ $# = 0 ]; then
    echo "usage: $0 [-a -n N] directory"
    exit 1
fi

A=""  # 参数-a
N=10  # 参数-n的值

while getopts ":an:" opt; do  # 通过getopts获取参数 
  case $opt in
    a)
        A="-a"
        ;;
    n)
        N=$OPTARG
        ;;
    \?)
        echo "Invalid args"
        ;;
  esac
done

# shift参数以便获取路径值
shift $((OPTIND - 1))

# 遍历路径
for var in "$@"
do
    echo "$var"
    du -h $A $var | head -n $N
done

