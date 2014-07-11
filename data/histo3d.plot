reset
set term png
set output "histogram3d.png"

set xlabel "x"
set ylabel "Self-connection strength"
set cblabel "Probability"
set xtics 25
set xrange [0:100]
set yrange [0:150]
set palette grey

plot "histo3d.dat" matrix with image
set output
