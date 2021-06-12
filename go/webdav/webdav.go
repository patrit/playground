package main

import (
	"flag"
	"fmt"
	"log"
	"net/http"

	"golang.org/x/net/webdav"
)

var dir string

func main() {

	dirFlag := flag.String("d", "/media", "Directory to serve from. Default is CWD")
	httpPort := flag.Int("p", 8080, "Port to serve on (Plain HTTP)")

	flag.Parse()

	dir = *dirFlag

	srv := &webdav.Handler{
		FileSystem: webdav.Dir(dir),
		LockSystem: webdav.NewMemLS(),
		Logger: func(r *http.Request, err error) {
			if err != nil {
				log.Printf("WEBDAV [%s]: %s, ERROR: %s\n", r.Method, r.URL, err)
			} else {
				log.Printf("WEBDAV [%s]: %s \n", r.Method, r.URL)
			}
		},
	}
	http.Handle("/", srv)
	if err := http.ListenAndServe(fmt.Sprintf(":%d", *httpPort), nil); err != nil {
		log.Fatalf("Error with WebDAV server: %v", err)
	}

}
