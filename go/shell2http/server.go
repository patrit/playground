package main

import (
    "net/http"
    "os/exec"
)

func execShellCommand(w http.ResponseWriter, ctype string, cmdString string) {

    cmd := exec.Command("sh", "-c", cmdString)
    stdoutStderr, err := cmd.CombinedOutput()
    if err != nil {
        w.Write(stdoutStderr)
        return
    }
    w.Header().Set("Content-Type", ctype)
    w.Write(stdoutStderr)
}

func index(w http.ResponseWriter, r *http.Request) {
    execShellCommand(w, "text/html", "cat /app/index.html")
}

func env(w http.ResponseWriter, r *http.Request) {
    execShellCommand(w, "application/json", "/app/env.sh")
}

func cpuinfo(w http.ResponseWriter, r *http.Request) {
    execShellCommand(w, "application/json", "/app/cpuinfo.sh")
}

func main() {
    http.HandleFunc("/", index)
    http.HandleFunc("/index.html", index)
    http.HandleFunc("/env.json", env)
    http.HandleFunc("/cpuinfo.json", cpuinfo)
    http.ListenAndServe(":80", nil)
}
