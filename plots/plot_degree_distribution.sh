#!/bin/bash
#
#plot_degree_distribution.sh

cp "$1" "_temp_distr.toplot"

gnuplot "plot_distr.plt"

out="$1.distr.plot.eps"

mv "_out_distr.plot" "$out"

rm "_temp_distr.toplot"
