#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <stdio.h>
#include <stdlib.h>
#include "serial.h"
#define TYPE float
namespace py = pybind11;

void test()
{
    //This function will be used to compare runs inside python and C++
    test_all();
}
py::array_t<TYPE, py::array::c_style | py::array::forcecast> bonsai_pybind(py::size_t num_points,
 py::array_t<TYPE, py::array::c_style | py::array::forcecast> locations,
 py::array_t<TYPE, py::array::c_style | py::array::forcecast> weights, float theta, bool dodebug)
{
    py::buffer_info loc = locations.request();
    TYPE *points = (TYPE *) loc.ptr;
    py::buffer_info wt_buffer = weights.request();
    TYPE *wt = (TYPE *) wt_buffer.ptr;
    // Output Array
    py::array_t<TYPE, py::array::c_style | py::array::forcecast> output({num_points});
    py::buffer_info out = output.request();
    TYPE *ptrOut = (TYPE *) out.ptr;
    int flag = get_pots(num_points, theta, ptrOut, points, wt, 1);
    return output;
}

PYBIND11_MODULE(fmm_gpu, m)
{
    m.doc() = "Test Run for comparision with C++ run";
    m.def("test", &test, py::return_value_policy::take_ownership);

    m.doc() = "Actual run";
    m.def("bonsai", &bonsai_pybind, py::return_value_policy::take_ownership);
}