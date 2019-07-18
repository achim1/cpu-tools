#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>

//#include "cpu_tools.h"

namespace py = pybind11;

PYBIND11_MODULE(pycputools, m) {
    m.doc() = "Pybindings for cpu tools";

    m.def("test", &test);
    //m.def("get_cpu_temp", &get_cpu_temp, py::return_value_policy::reference);
    //m.def("get_cpu_clock_speed", &get_cpu_clock_speed, py::return_value_policy::reference);

}


