# generate random numbers
```bash
python3 -c 'import random; print("\n".join([str(random.random() * 100) for x in range(1000)]))' > data.dat
```


```bash
docker run --rm -v $(pwd):/work gnuplot -e 'set term png;
set output "output.png";
set xlabel "Value"; set ylabel "Number of Occurances";
n=25;max=100;min=0;width=(max-min)/n;
hist(x,width)=width*floor(x/width)+width/2.0;
set style fill solid 0.5;
plot "data.dat" u (hist($1,width)):(1.0) smooth freq w boxes notitle
'
```
