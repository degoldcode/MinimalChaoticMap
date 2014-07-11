reset
set term png
set output "stspace.png"

set xlabel "x_n"
set ylabel "x_n+1"


#SCALE = 6
#set xrange [-SCALE:SCALE]
#set yrange [-SCALE:SCALE]

plot "stspace.dat" u 1:2 w p pt 7 ps 0.2 t ""
#l lc palette t ""
#pt 7 ps 0.2 t ""
set output

set output "tsignal.png"
set yrange [-0.05:1.05]
plot "stspace.dat" u 0:1 w l t ""
#l lc palette t ""
#pt 7 ps 0.2 t ""
set output
