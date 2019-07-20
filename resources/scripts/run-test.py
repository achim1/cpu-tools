import numpy as np
import time
import pylab as p
import numpy as np

from hepbasestack import visual as v

import matplotlib
v.set_style_default()

import pycputools as cpu      

start_time = time.monotonic()

temps, clocks = [], []

iteration = 0 
plot_number = 0
while True:                                      
    temp = cpu.get_cpu_temp()
    speed = np.array(cpu.get_cpu_clock_speed()) 
    temps.append(temp)
    clocks.append(speed.mean())
    time.sleep(5)
    iteration += 1
    if iteration == 12:
        p.scatter(temps, clocks)
        p.savefig("avcpu" + str(plot_number))
        plot_number += 1
        iteration = 0
