reset
set term png
set output "bifurcation.png"

set xlabel "self-connection strength"
set ylabel "x"

plot "pscan.dat" u 1:2 w p pt 7 ps 0.2 t ""
set output
