## CPU-tools

Read out temperature and clock speed of a modern multicore cpu on linux. Tested with a Ryzen 2700X.
This requires the [it87 driver](https://github.com/rpavlik/it87.git) to be installed in case you 
are on the X470 plattform.

If the pybindings shall be used, this requires pybind11 > 2.2. pybind11 can be installed on any Ubuntu system with 
`sudo apt install pybind11-dev`

### How to install

Run `make`

### Gotchas

There is an example script `watercool.py`, which can run as service and will set the led color
as well as the fan speed of a Kraken cooler depending on the temperature read out with pycputools.

