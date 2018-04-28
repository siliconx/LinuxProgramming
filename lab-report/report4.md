#南昌大学实验报告4

姓名：<u>___谢志彬____</u>
	
学号：<u>__6103115112_</u>

邮箱地址：_________siliconx@163.com_____

专业班级：_________<u>计算机科学与技术153</u>_____

实验日期：<u>___2018/04/22   ___</u>

课程名称：________<u>Linux程序设计实验</u>____



##实验项目名称

## Multi-processing in Linux



##实验目的

#####	1.理解多进程机制

##### 	2.理解进程调度

##### 3.理解多线程编程



##实验基础

####	C语言、多进程、多线程



##实验步骤



### Q1: The Fork Question

#### I.编写Makefile

```makefile
#Makefile

all: fork_problem.out multi-fork.out

fork_problem.out: fork_problem.c
	gcc fork_problem.c -o fork_problem.out

multi-fork.out: multi-fork.c
	gcc multi-fork.c -o multi-fork.out
```



#### II.编译

![](/home/siliconx/Pictures/Screenshot-from-2018-04-22-23-21-02.png)



#### III.答

#####a -- fork_problem.c

```
LINE X将输出: I am the child - value = 20
LINE Y将输出: I am the parent - value = 5
因为pid == 0时表示子进程，pid > 0时表示父进程
```



```
运行程序验证结论正确
```

![](/home/siliconx/Pictures/Screenshot-from-2018-04-22-23-33-31.png)



##### b -- multi-fork.c

```
将产生8个进程，推导如下
```

![](/home/siliconx/Pictures/P80423-115355_recompress.jpg)



```
运行代码，验证结论
共有8个不同的pid
```

![](/home/siliconx/Pictures/Screenshot-from-2018-04-22-23-58-23.png)



***



### Q2 Fork and fork more

#### step1.补全代码

fork1.c

```c
#include <stdio.h>

void fork2();

int main() {
    fork2();
    return 0;
}

void fork2() {
    printf("L0");
    fork();
    printf("L1\n");
    fork();
    printf("Bye\n");
}
```



fork2.c

```c
#include <stdio.h>

void fork2();

int main() {
    fork2();
    return 0;
}

void fork2() {
    printf("L0\n");
    fork();
    printf("L1\n");
    fork();
    printf("Bye\n");
}
```



#### step2.运行

![](/home/siliconx/Pictures/Screenshot-from-2018-04-24-02-47-24.png)



#### step3.解释

```
fork1和fork2之间的差别仅仅在于fork()函数的第一行的printf的内容有没有`\n`
却导致了不一样的输出顺序。
主要原因是在Linux下，\n会刷新缓冲区

```



***



### Q3.Processes

#### step1 -- collatz.c

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {
    if (argc != 2) {  // arguments error
        printf("ARG ERROR\n");
        exit(0);
    }

    long n =  atoi(argv[1]);
    if (n < 1) {  // convert failed
        printf("ARG ERROR\n");
        exit(0);
    }

    while (n > 1) {  // gen the collatz sequence
        printf("%ld ", n);
        if (n % 2 == 1) {
            n = 3 * n + 1;
        } else {
            n /= 2;
        }
    }
    printf("1\n");
    return 0;
}
```



#### step2 -- run collatz.out

![](/home/siliconx/Pictures/Screenshot-from-2018-04-27-23-20-56.png)



#### step3 -- collatz2.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
    if (argc != 2) {  // arguments error
        printf("ARG ERROR\n");
        exit(0);
    }

    execlp("./collatz.out", "./collatz.out", argv[1], NULL);  // call collatz.out

    return 0;
}

```



####step4 -- run collatz2.out

![](/home/siliconx/Pictures/Screenshot-from-2018-04-27-23-33-47.png)



***



## Q4.Threads

#### step1 -- collatz-thrd.c

```c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// linkedlist
struct node {
    int e;
    struct node *next;
};

struct node *head = NULL;  // header of list
struct node *r = NULL;  // pointer of current positoin

void *gen_collatz(void *param);  // thread to generate collatz

int main(int argc, char *argv[]) {
    pthread_t tid;  // the thread identifier
    pthread_attr_t attr;  // set of attributes for the thread

    if (argc != 2) {
        fprintf(stderr, "usage: %s <integer value>\n", argv[0]);
        return -1;
    }

    // get the default attributes
    pthread_attr_init(&attr);

    // create the thread
    pthread_create(&tid, &attr, gen_collatz, argv[1]);

    // now wait for the thread to exit
    pthread_join(tid, NULL);

    //  traversing the list
    r = head;
    while (r != NULL) {
        printf("%d ", r->e);
        r = r->next;
    }
    printf("\n");
}

/**
 * The thread will begin control in this function
 */
void *gen_collatz(void *param) {
    int n = atoi(param);  // convert string to int

    if (n > 1) {
        struct node *temp;

        while (n > 1) {  // gen the collatz sequence

            // create a node by malloc
            temp = (struct node *) malloc(sizeof(struct node));
            temp->e = n;
            temp->next = NULL;

            if (head == NULL) {
                head = temp;  // first node
                r = temp;
            } else {  // latter node
                r->next = temp;
                r = r->next;
            }

            if (n % 2 == 1) {
                n = 3 * n + 1;
            } else {
                n /= 2;
            }
        }

        // lastest node -- value: 1
        temp = (struct node *) malloc(sizeof(struct node));
        temp->e = 1;
        temp->next = NULL;

        r->next = temp;
    }

    pthread_exit(0);
}

```



#### step2 -- complie && run

![](/home/siliconx/Pictures/Screenshot-from-2018-04-28-00-18-38.png)

##

##实验思考

 * 理解多进程机制
 * 理解进程调度、进程间的关系
 * 理解多线程编程、使用pthread库



##参考资料

 * 《Linux程序设计》
 * [GNU Hurd](http://www.gnu.org/software/hurd/index.html)/ POSIX Threading Library


