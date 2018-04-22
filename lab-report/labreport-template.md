#南昌大学实验报告

姓名：<u>___谢志彬____</u>
	
学号：<u>__6103115112_</u>

邮箱地址：_________siliconx@163.com_____

专业班级：_________<u>计算机科学与技术153</u>_____

实验日期：<u>___2018/04/16   ___</u>

课程名称：________<u>Linux程序设计实验</u>____

##实验项目名称

## C Programming in Linux

##实验目的

#####	1.在Linux下进行C语言程序设计

##### 	2.使用Makefile

##### 3.使用GDB



##实验基础

####	C语言、Makefile、GDB

##实验步骤

##### T1

step1.摘抄源代码: Linux Poem: The American C

```c
long long time, ago,
i, can, still, remember, how;
typedef struct s{} was,
all, we, had;

s o,  I, knew, If=I; had my, chance =
I, could, code, a, perfect, prance;

s ee; was ruling;
we were, happy
,good ,ole, times;

all that, changed, when; class es{} came;
we got, spoiled, And, thats = a, shame;

all is, broken, noting;s same
,c_plus_plus, has, killed, the, flame;

had We, believed, iin, rocknroll=
could,ve, coding, cured, our, mortal, souls;

we met=a, girl, who, sang= the, blues;
we asked, her, For, some= happy, news;

s he, said, to, me, with, pretty, smile
=If, you, are; main(){
    return
        the,
        time;
}

```

step2:

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



