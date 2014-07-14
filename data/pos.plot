reset
set term png
set output "pos.png"

set xlabel "x"
set ylabel "y"

set size square

SCALE = 100
set xrange [-SCALE:SCALE]
set yrange [-SCALE:SCALE]

plot "pos.dat" u 2:3:1 w l lc palette t ""
#l lc palette t ""
#pt 7 ps 0.2 t ""
set output
