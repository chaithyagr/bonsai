#include "serial.h"
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <stdio.h>
#include <stdlib.h>
#define TYPE float
namespace py = pybind11;

void test()
{
    //This function will be used to compare runs inside python and C++
    test_all();
}
py::array_t<TYPE, py::array::c_style | py::array::forcecast> bonsai_pybind(py::size_t num_points,
 py::array_t<TYPE, py::array::c_style | py::array::forcecast> locations,
 py::array_t<TYPE, py::array::c_style | py::array::forcecast> weights, bool dodebug)
{
    py::buffer_info loc = locations.request();
    TYPE *points = (TYPE *) loc.ptr;
    py::buffer_info wt_buffer = weights.request();
    TYPE *wt = (TYPE *) wt_buffer.ptr;
    // Output Array
    float *pots;
    int flag = get_pots(num_points, pots, points, wt, 1);

    py::array_t<TYPE, py::array::c_style | py::array::forcecast> output({num_points});
    py::buffer_info out = output.request();
    TYPE *ptrOut = (TYPE *) out.ptr;
    for(int l = 0 ; l < num_points ; l++)
    {
        ptrOut[l] = 0;
        //TODO
    }
    return output;
}

PYBIND11_MODULE(fmm, m)
{
    m.doc() = "Test Run for comparision with C++ run";
    m.def("test", &test, py::return_value_policy::take_ownership);

    m.doc() = "Actual run";
    m.def("bonsai", &bonsai_pybind, py::return_value_policy::take_ownership);
}