## CPU-tools

Read out temperature and clock speed of a modern multicore cpu on linux. Tested with a Ryzen 2700X.
This requires the [it87 driver](https://github.com/rpavlik/it87.git) to be installed.

If the pybindings shall be used, this requires pybind11 > 2.2. pybind11 can be installed on any Ubuntu system with 
`sudo apt install pybind11-dev`

### How to install

Run `make`
