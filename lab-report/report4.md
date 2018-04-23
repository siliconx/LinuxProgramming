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





##实验数据或结果



##实验思考



##参考资料



