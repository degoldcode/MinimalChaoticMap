reset
set term png
set output "histogram.png"

T = 20000
BINS = 100

set xlabel "State"
set ylabel "Probability"

plot "histo.dat" u ($0/BINS):($1/T) w l t "Histogram"
set output
