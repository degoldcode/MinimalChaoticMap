reset
set term png
set output "bifurcation.png"

set xlabel "self-connection strength"
set ylabel "x"
set grid
set ytics 0.5

plot "pscan.dat" u 1:2 w p pt 7 ps 0.2 t "", "" u 1:3 w l lt 1 lc rgb "#0080FF" t "Mean", "" u 1:5 w l lt 1 lc rgb "#00CC66" t "Turning rate", "" u 1:6 w l lt 1 lc rgb "#CC0066" t "Absolute turning rate"
set output
