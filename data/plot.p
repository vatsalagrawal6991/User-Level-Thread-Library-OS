set xlabel "thread"
set ylabel "time"
set title "time at n=8"
plot "./data/time_8" using 2:3 title "thread vs original" w l
replot "./data/time_8" using 2:4 title "thread vs mythread" w l
replot "./data/time_8" using 2:6 title "thread vs pthread" w l
pause -1 "Hit" 
set title "time at n=128"
plot "./data/time_128" using 2:3 title "thread vs original" w l
replot "./data/time_128" using 2:4 title "thread vs mythread" w l
replot "./data/time_128" using 2:6 title "thread vs pthread" w l
pause -1 "Hit"
set title "time at n=64"
plot "./data/time_64" using 2:3 title "thread vs original" w l
replot "./data/time_64" using 2:4 title "thread vs mythread" w l
replot "./data/time_64" using 2:6 title "thread vs pthread" w l
pause -1 "Hit"
set title "time at n=256"
plot "./data/time_256" using 2:3 title "thread vs original" w l
replot "./data/time_256" using 2:4 title "thread vs mythread" w l
replot "./data/time_256" using 2:6 title "thread vs pthread" w l
pause -1 "Hit"
set title "time at n=512"
plot "./data/time_512" using 2:3 title "thread vs original" w l
replot "./data/time_512" using 2:4 title "thread vs mythread" w l
replot "./data/time_512" using 2:6 title "thread vs pthread" w l
pause -1 "Hit"
set title "CS time"
plot "./data/time_512" using 2:5 title "thread vs mythread n=512" w l
replot "./data/time_128" using 2:5 title "thread vs mythread n=128" w l
replot "./data/time_4" using 2:5 title "thread vs mythread n=4" w l
replot "./data/time_16" using 2:5 title "thread vs mythread n=16" w l
replot "./data/time_64" using 2:5 title "thread vs mythread n=64" w l
replot "./data/time_32" using 2:5 title "thread vs mythread n=32" w l
pause -1 "Hit"
plot "./data/time_128" using 2:7 title "thread vs pthread n=128" w l
replot "./data/time_4" using 2:7 title "thread vs pthread n=4" w l
replot "./data/time_16" using 2:7 title "thread vs pthread n=16" w l
replot "./data/time_64" using 2:7 title "thread vs pthread n=64" w l
replot "./data/time_32" using 2:7 title "thread vs pthread n=32" w l
pause -1 "Hit"
