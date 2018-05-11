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
    http.ListenAndServe("0.0.0.0:8080", nil)
}

func http_server(response http.ResponseWriter, request *http.Request) {
    // fmt.Println(msg)
    fmt.Fprintf(response, msg)
}
