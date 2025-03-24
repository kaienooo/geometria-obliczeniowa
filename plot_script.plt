set xrange [-12:12]
set yrange [-12:12]
set grid
plot 'data/plot_data.txt' using 1:2:3:4 with vectors nohead notitle, \
