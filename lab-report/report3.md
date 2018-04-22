#南昌大学实验报告3

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



###实验一 -- Use C and Makefile for Coding



#### TASK1 -- 编译运行 Linux Poem: The American C

#####step1.摘抄源代码: Linux Poem: The American C

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



#####step2.编译运行

![](/home/siliconx/Pictures/Screenshot-from-2018-04-20-22-29-53.png)



#### TASK2 -- 分割代码

1.source.h

```c
#ifndef SOURCE_H
#define SOURCE_H


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
=If, you, are;

#endif

```



2.source.c

```c
// source.c 为空
```



3.main.c

```c
#include "source.h"

main(){
    return
        the,
        time;
}

```



####TASK3 -- 通过make编译上述代码

#####step1.编写Makefile

```makefile
#main/Makefile

all: executable

executable: source.o main.o
		g++ source.o main.o -o executable $(CXXFLAGS)

source.o: source.c source.h
		g++ -c source.c -o source.o $(CXXFLAGS)

main.o: main.c
		g++ -c main.c -o main.o $(CXXFLAGS)

```



#####step2.使用不同的flag进行编译

使用 -g, -ggdb, -O参数均可正常编译

![](/home/siliconx/Pictures/Screenshot-from-2018-04-20-23-04-08.png)



使用-Wall参数编译报错

![](/home/siliconx/Pictures/Screenshot-from-2018-04-20-23-07-12.png)



### 实验二 -- 使用sys/stat.h等库进行文件统计并使用Makefile编译 

##### step1.编写代码

main.c

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include "functions.h"

int main(int argc, char* argv[]) {
    char* path = argv[1];
    if (argc != 2) {
        printf("ARGS ERROR\n");
        return 1;
    }

    struct stat path_stat;
    if (stat(path, &path_stat) != 0) {
        printf("PATH INCORRECT!!!\n");
        return 1;
    }

    if (S_ISREG(path_stat.st_mode)) {
        printf("`%s` is a file\n", path);

        if (is_owner(path_stat.st_uid)) {
            printf("you are the owner of the file, and now changing the permissions to 777 of the file\n");
            chmod_to_777(path);
            printf("done!\n");
        } else {
            printf("you are NOT the owner of the file\n");
        }
    } else {
        printf("`%s` is a dir\n", path);
    }
}
```



functions.h

```
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int is_owner(int);
int chmod_to_777(char*);
```



functions.c

```
#include "functions.h"

int is_owner(int file_uid) {
    return getuid() == file_uid;
}


int chmod_to_777(char* path) {
    chmod(path, S_IRWXU | S_IRWXG | S_IRWXO);
    return 0;
}

```



makefile

```makefile
#main/Makefile

out: functions.o main.o
		g++ functions.o main.o -o out

functions.o: functions.c functions.h
		g++ -c functions.c -o functions.o

main.o: main.c
		g++ -c main.c -o main.o
```



##### step2.使用make编译

![](/home/siliconx/Pictures/Screenshot-from-2018-04-21-11-08-39.png)



##### step3.测试运行代码

![](/home/siliconx/Pictures/Screenshot-from-2018-04-21-11-11-04.png)



### 实验三 -- GDB

##### step1.编译可调试的可执行文件

![](/home/siliconx/Pictures/Screenshot-from-2018-04-20-23-46-41.png)

#####step2.打断点

![](/home/siliconx/Pictures/Screenshotfrom2018-04-21-10-47-25.png)



#####step3.运行并打印栈信息

![](/home/siliconx/Pictures/Screenshot-from-2018-04-21-10-48-41.png)



##实验思考

	###### 1.注意Makefile的编写规则

##### 2.GDB的各个参数

##### 3.sys/stat库的使用



##参考资料

《Linux程序设计》

《C语言程序设计》

