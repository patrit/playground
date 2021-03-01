# TEX example

# build container with dependencies
```
sudo docker build -t tex 
```

# run latex
```
sudo docker run -v $(pwd):/data tex example.tex
```
