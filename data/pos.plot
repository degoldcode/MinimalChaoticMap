reset
set term postscript enhanced color eps "Helvetica,12"
set output "walker.eps"

set xlabel "x"
set ylabel "y"

set size square

SCALE = 500
set xrange [-SCALE:SCALE]
set yrange [-SCALE:SCALE]

plot "goals.dat" u 1:2 w p pt 7 ps 0.2 lc rgb "black" t "Goal", "walker.dat" u 1:2:0 w p pt 7 ps 0.1 lc palette t "", "goals.dat" u 1:(($3 > 0)?$2:1/0) w p pt 7 ps 0.2 lc rgb "green" t "Hit" 
#l lc palette t ""
#pt 7 ps 0.2 t ""
set output
