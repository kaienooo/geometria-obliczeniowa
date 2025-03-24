set xrange [-7:8]
set yrange [-6:8]
set grid
plot 'data/plot_data.txt' using 1:2:3:4 with vectors nohead notitle, \
