# Homework2

<p style="text-align: right">--计科153、谢志彬、6103115112</p>



## Q1.1: Go Programming



####step.1 编写源码

```go
package main

import (
    "fmt"
    "os"
    "strconv"
    "log"
    "math"
)

func main() {
    args_len := len(os.Args)
    if args_len == 2 {  // is circle
        r, err := strconv.ParseFloat(os.Args[1], 64)  // get radius

        if err != nil {
            fmt.Println("Args value ERROR")
            log.Fatal(err)
        } else {
            fmt.Println("This is a circle")
            perimeter := 2 * math.Pi * r
            area := math.Pi * math.Pow(r, 2)
            fmt.Printf("r = %.3f\nperimeter = %.3f\narea = %.3f\n", r, perimeter, area)
        }
    } else if args_len == 3 {  // is rectangle
        a, err := strconv.ParseFloat(os.Args[1], 64)
        b, err := strconv.ParseFloat(os.Args[2], 64)

        if err != nil {
            fmt.Println("Args value ERROR")
            log.Fatal(err)
        } else {
            fmt.Println("This is a rectangle")
            perimeter := 2 * (a + b)
            area := a * b
            fmt.Printf("a = %.3f\nb = %.3f\nperimeter = %.3f\narea = %.3f\n", a, b, perimeter, area)
        }
    } else {
        fmt.Println("Args ERROR")
    }
}
```



#### step2. 编译

```bash
go build
```



#### step3.运行

![](/home/siliconx/Pictures/Screenshot-from-2018-04-24-02-21-34.png)





## Q1.2将上述go程序部署成http服务

#### step1.修改代码

```go
package main

import (
    "fmt"
    "os"
    "strconv"
    "log"
    "math"
    "net/http"
)

var msg string
func main() {
    args_len := len(os.Args)
    if args_len == 2 {  // is circle
        r, err := strconv.ParseFloat(os.Args[1], 64)  // get radius

        if err != nil {
            msg = fmt.Sprintf("Args value ERROR")
            log.Fatal(err)
        } else {
            perimeter := 2 * math.Pi * r
            area := math.Pi * math.Pow(r, 2)
            msg = fmt.Sprintf("This is a circle\nr = %.3f\nperimeter = %.3f\narea = %.3f", r, perimeter, area)
        }
    } else if args_len == 3 {  // is rectangle
        a, err := strconv.ParseFloat(os.Args[1], 64)
        b, err := strconv.ParseFloat(os.Args[2], 64)

        if err != nil {
            msg = fmt.Sprintln("Args value ERROR")
            log.Fatal(err)
        } else {
            perimeter := 2 * (a + b)
            area := a * b
            msg = fmt.Sprintf("This is a rectangle\na = %.3f\nb = %.3f\nperimeter = %.3f\narea = %.3f", a, b, perimeter, area)
        }
    } else {
        msg = fmt.Sprintf("Args ERROR")
    }

    fmt.Println(msg)
    http.HandleFunc("/", http_server)
    http.ListenAndServe(":8080", nil)
}

func http_server(response http.ResponseWriter, request *http.Request) {
    fmt.Fprintf(response, msg)
}
```



#### step2.运行结果

![](/home/siliconx/Pictures/Screenshot-from-2018-04-24-02-22-51.png)

![](/home/siliconx/Pictures/Screenshot-from-2018-04-24-02-23-27.png)

![](/home/siliconx/Pictures/Screenshot-from-2018-04-24-02-24-02.png)





***



## Q2 (Bash, and Bash Hard)



#### step1.编写代码

```bash
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

```



#### step2.运行

![](/home/siliconx/code/linux/imgs/Screenshot-from-2018-04-22-22-33-37.png)

![](/home/siliconx/code/linux/imgs/Screenshot-from-2018-04-22-22-34-02.png)

![](/home/siliconx/code/linux/imgs/Screenshot-from-2018-04-22-22-35-54.png)