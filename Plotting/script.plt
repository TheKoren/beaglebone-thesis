# Not used for the project, just for sample
set datafile separator ","
set term png size 800,600
set output "output.png"
set size 1,1
set title "HTTP payload size and response time"
set style data fsteps
set xlabel "Date"
set timefmt "%s"
set xdata time
set format x "%m/%d\n%H:%M:%S"
set xlabel "Time (UTC)"
set y2tics
set grid
set key right
set label "Copyright: Koren 2021" at screen 0.99, screen 0.02 right textcolor rgb "#888888"
set ylabel "Temperature (°C)"
set y2label "Relative Humidity (%)"
plot "< tail -n 144 'data.txt'" using 1:2 axes x1y1 t "Temperature (C)" w lines lt rgb "red", "< tail -n 144 'data.txt'" using 1:3 axes x1y2 t "Relative Humidity (%)" with lines
