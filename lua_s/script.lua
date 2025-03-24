function drawData(x1,x2,y1,y2,plotData,labelsData)
    file = io.open("plot_script.plt","w")
    io.output(file)
    io.write(string.format("set xrange [%d:%d]\n",x1-2,x2+2))
    io.write(string.format("set yrange [%d:%d]\n",y1-2,y2+2))
    io.write("set grid\n")
    io.write(string.format("plot '%s' using 1:2:3:4 with vectors nohead notitle, \\\n",plotData))
    --io.write(string.format("\t'%s' using 2:3:(sprintf(\"%s\",$1)) with labels point pt 7 offset char 0,0.5 notitle\n",labelsData,"%d"))
    
    io.close(file)
    os.execute("gnuplot -persist plot_script.plt")
end