 set title 'waveform'
 set ylabel 'voltage'
 set xlabel 'time'
 set grid ytics mytics
 set mytics 2
 set grid xtics mxtics
 set mxtics 5
 set term png size 1280,720
 set output 'out.png'
 plot 'log.dat' using 1:2 w l
