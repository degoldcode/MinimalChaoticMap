reset
set term png
set output "histogram.png"

T = 1000000
BINS = 2

set xlabel "Average Output"
set ylabel "Probability"

plot "histo.dat" u ($0/BINS):($1/T) w l t "Histogram"
set output
