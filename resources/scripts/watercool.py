#! /usr/bin/env python3

"""
System service to have a more controlled fan curve for a Kraken cooler on LINUX
This utilizes liquidctl. At the moment, just an example script to toy around, but
it illustrates what the cputools can be used for. This specific example sets the
color of the Kraken from blue to red, depending on the temperature.
"""

import liquidctl.cli as cli
from liquidctl.util import color_from_str
import sys
import os
from datetime import datetime
sys.path.append('/home/achim/config-new/cpu-tools-build')

import pycputools as cpu
import time

dev = cli.find_liquidctl_devices()
for d in dev:
    print (d)
d.connect()
print (d.get_status())

# adjust this every 2 seconds
bracket = [(40,50), (50,60), (60,200)]
#def in_which_bracket

#d.set_color('logo', 'super-fixed', [color_from_str('FFFFFF')])
#d.set_color('logo', 'super-fixed', [color_from_str('000000')])

##cmap = cm.get_cmap('seismic', 5)    # PiYG
##
##levels = []
##for i in range(cmap.N):
##    rgb = cmap(i)[:3] # will return rgba, we take only first 3 so we get rgb
##    print(matplotlib.colors.rgb2hex(rgb))
##    levels.append(color_from_str(matplotlib.colors.rgb2hex(rgb)[1:]))
##    print (rgb)
##
##print (levels)
# intializing
d.set_color('logo', 'super-fixed', [color_from_str('000000')])
d.set_color('ring', 'loading', [color_from_str('FFFFFF')])
d.set_fixed_speed('fan', 50)
try:
    os.remove('/var/log/watercool.log')
except Exception as e:
    pass

logfile = open('/var/log/watercool.log', 'w')
logfile.write(f'# CPU temperature log {datetime.now().ctime()}\n')
lasttemp = 0
while True:
    time.sleep(2)
    temp = cpu.get_cpu_temp()
    logfile.write(f'{datetime.now()} -- {temp}\n')
    logfile.flush()
    if abs(lasttemp - temp) < 8:
        continue
    if temp <= 40:
        if lasttemp > 40:
            d.set_fixed_speed('fan', 50)
            d.set_color('ring', 'loading', [color_from_str('0000FF')])
            d.set_color('logo', 'super-fixed', [color_from_str('000000')])
            lasttemp = temp
            continue
    elif temp <= 50:
        if (lasttemp < 40) or (lasttemp > 50):
            d.set_fixed_speed('fan', 50)
            d.set_color('ring', 'loading', [color_from_str('FFFFFF')])
            d.set_color('logo', 'super-fixed', [color_from_str('000000')])
            lasttemp = temp
            continue
    elif temp <= 60:
        if (lasttemp <= 50) or (lasttemp > 60):
            d.set_fixed_speed('fan', 80)
            d.set_color('ring', 'loading', [color_from_str('FF0000')])
            d.set_color('logo', 'super-fixed', [color_from_str('000000')])
            lasttemp = temp
            continue
    else:
        d.set_fixed_speed('fan', 100)
        d.set_color('ring', 'loading', [color_from_str('FF0000')])
        lasttemp = temp
        continue
    
#d.set_speed_profile??
#d.set_fixed_speed?
d.set_fixed_speed('fan',100)
#d.set_fixed_speed('fan',10)
#d.set_fixed_speed('fan',50)
#d.set_fixed_speed('fan',60)
#d.set_fixed_speed('fan',70)
#d.set_fixed_speed('fan',80)
#d.set_fixed_speed('fan',90)
#d.set_fixed_speed('fan',100)
#d.set_fixed_speed('fan',200)
#d.set_fixed_speed('fan',100)
#d.get_status()
#d.get_status()
#profile = [(35, 50), (40,60)]
#d.set_speed_profile??
#d.description
#d.device_type
#d.supports_cooling
#d.supports_lighting
#%history

