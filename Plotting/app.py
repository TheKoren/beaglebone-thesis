import PyGnuplot as gp
from datetime import datetime

now = datetime.now()
current_time = now.strftime("%y-%m-%d %H:%M:%S")

macs = [("14:B4:57:6D:A5:6D","SL_TB_0"), ("00:0B:57:64:8F:DD","SL_TB_1"), ("58:8E:81:72:F6:52","SL_TB_2"), ("58:8E:81:72:F6:11","SL_TB_3"), ("08:6B:D7:FE:13:F7","SL_TB_4")]
plot_type = [("Air","TVOC (ppd)","eCO2 (ppm)","3","4"),("Light","Amb light (Lux)","UV Index","6","5"), ("Temperature","Temperature (°C)","Relative Humidity (%RH)","7","8"), ("Sound","Sound level [dbA]","","9","1/0")]

def tempFile(address):
    temp = open('temp.txt', 'w')
    temp.truncate(0)
    data = open('data.txt', 'r')
    Lines = data.readlines()
    for line in Lines:
        x = line.split(",")
        if(x[0] == address):
            temp.write(line)
    temp.close()


for mac in macs:
    gp.c("set datafile separator \",\"")
    gp.c("set term png size 800,600")
    gp.c("set size 1,1")
    gp.c("set style data fsteps")
    gp.c("set xlabel \"Date\"")
    gp.c("set timefmt \"%s\"")
    gp.c("set xdata time")
    gp.c("set format x \"%m/%d\\n%H:%M:%S\"")
    gp.c("set xlabel \"Time (UTC)\"")
    gp.c("set xtics 7200")
    gp.c("set grid")
    gp.c("set key right")
    gp.c("set label \"Koren Zoltan MIT " +  str(current_time) + "\" at screen 0.99, screen 0.02 right textcolor rgb \"#888888\"")
    tempFile(mac[0])
    for plot in plot_type:
        gp.c("set title \"IoT Measurement: " + plot[0] + "\"")
        gp.c("set ylabel \"" + plot[1] + "\"")
        string = plot[0] + "_" + mac[1] + ".png"
        gp.c("set output \"" + string + "\"")
        if(plot[2] == "UV Index"):
            gp.c("set y2range [0:5]")
        else:
            gp.c("set autoscale y2")
        if (plot[0] == "Sound"):
            gp.c("plot \"< tail -n 202 'temp.txt'\" using 2:" + plot[3] + " axes x1y1 t \"" + plot[1] + "\" w lines lt rgb \"red\"")
            gp.c("set y2label \" \"")
        else:
            gp.c("set y2tics")
            gp.c("set y2label \"" + plot[2] + "\"")
            gp.c("plot \"< tail -n 202 'temp.txt'\" using 2:" + plot[3] + " axes x1y1 t \"" + plot[1] + "\" w lines lt rgb \"red\", \"< tail -n 144 'temp.txt'\" using 2:" + plot[4] + " axes x1y2 t \"" + plot[2] + "\" with lines")
