#南昌大学实验报告
---
> Fill-in the following sections with either English or Chinese.
>
> In your submission email, you may deliver (1) your source code (packed in one file or shared in a netdisk link) (2) PDF version of this report
> 
> **Remove** these comments when writing your report


姓名：<u>______谢志彬_______</u>
	
学号：<u>_________6103115112__________</u>

邮箱地址：_________siliconx@163.com_____

专业班级：_________<u>计算机科学与技术153</u>_____

实验日期：<u>_________2018/04/09   ___</u>
 
课程名称：________<u>Linux程序设计实验</u>____

##实验项目名称

####	Bash Programming

##实验目的

#####	1.编写shell脚本解决实际问题

##### 	2.通过系统调用实现一些Liunx的实用工具

##实验基础

####	shell脚本的使用

##实验步骤

##### T1

```bash
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
```



##### T2

```bash
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
```



##### T3

```
#!/bin/sh

# reference https://blog.csdn.net/beyondlpf/article/details/46426513
find -type f -perm -700
```



##### T4

```bash
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
```



##### T5

```bash
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
```



##### T6

```bash
#!/bin/bash

ls -d */  # list dir only
```



##### T7

```bash
#!/bin/bash

# `seq` gen expression, `bc` calculating
seq -s "*" $1 | bc
```




##实验数据或结果



##实验思考



##参考资料



