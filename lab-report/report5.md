#南昌大学实验报告

姓名：<u>___谢志彬____</u>

学号：<u>__6103115112_</u>

邮箱地址：_________siliconx@163.com_____

专业班级：_________<u>计算机科学与技术153</u>_____

实验日期：<u>___2018/05/7   ___</u>

课程名称：________<u>Linux程序设计实验</u>____



##实验项目名称

## Lab 5 -- Build it and Share it

<h3 style="color: red">!!!注 由于openstack过于庞大，在我的笔记本电脑上无法成功部署服务，所以我把openstack换成了更加轻量级的服务 -- Docker</h3>

<h5 style="color: blue">构建环境为我个人的腾讯云服务器学生机(ip: 119.29.148.227)</h>



##实验目的

#####	1.理解laaS架构的机制

##### 2.尝试部署一个工程服务

##### 3.理解构建一个可视化web服务的过程



##实验基础

##### 1. Docker

##### 2. Linux



##实验步骤



##### 1.安装docker

> 使用Docker官方提供的脚本进行安装
>
> ```bash
> $ curl -fsSL get.docker.com -o get-docker.sh
> ```
>
> ```bash
> $ sudo sh get-docker.sh --mirror Aliyun
> ```
>
> ![](/home/siliconx/Pictures/Screenshot-from-2018-05-11-04-17-39.png)



##### 2.启动Docker CE

> ```bash
> $ sudo systemctl enable docker
> ```
>
> ```bash 
> $ sudo systemctl start docker
> ```
>
> ![](/home/siliconx/Pictures/Screenshot-from-2018-05-11-04-20-07.png)



##### 3.在go工程目录下编写dockerfile

> ```dockerfile
> FROM golang:latest
> 
> MAINTAINER siliconx "siliconx@163.com"
> 
> WORKDIR $HOME/go/src/calculate
> ADD . $HOME/go/src/calculate
> RUN go build .
> 
> EXPOSE 8080  # 容器的暴露端口
> 
> ENTRYPOINT ["./calculate", "3", "9"]  # 命令行参数为 3 和 9
> ```



##### 4.构建镜像

> ```bash
> $ docker build -t calculate .
> ```
>
> ![](/home/siliconx/Pictures/Screenshot-from-2018-05-11-04-58-24.png)



##### 5.列出镜像

> ```bash
> $ docker images
> ```
>
> ![](/home/siliconx/Pictures/Screenshot-from-2018-05-11-05-01-55.png)



##### 6.启动镜像

>```bash
>$ docker run -p 8080:8080 calculate  # 将宿主机的8080端口映射到容器的8080端口
>```
>
>![](/home/siliconx/Pictures/Screenshot-from-2018-05-11-05-19-28.png)



#####7.在浏览器中访问

>![](/home/siliconx/Pictures/Screenshot-from-2018-05-11-05-22-14.png)



##### 至此实验完成！



##实验思考

#####1.openstack实在过于庞大，Docker相比之下就显得十分轻量级了

##### 2.使用Docker部署web服务比使用openstack方便快捷得多



##参考资料

##### 1.Golang

##### 2.Docker

