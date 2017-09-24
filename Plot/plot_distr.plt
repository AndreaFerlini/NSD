#!/usr/bin/gnuplot -persist
set term postscript eps enhanced color "Helvetica" 18 dl 3

set xlabel "Degree"
set ylabel "Nodes"

set xtics 1
set ytics 1

#set xrange [1:50] 
#set yrange [0:2]
 
set key bmargin center horizontal nobox
set style line 2 lc rgb 'red' pt 15   # circle

set grid y
 
set output "with_zdn.distr.eps"
 
plot "../graphs/with_zdn.distr" with points ls 2 notitle
