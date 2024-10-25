#include <pybind11/pybind11.h>

namespace py = pybind11;

// function declaration
void bind_camera(py::module_ &);
void bind_triangulation(py::module_ &);

PYBIND11_MODULE(triangulation_module, m) {
    m.doc() = "Pybind11 bindings for triangulation project"; // Optional module docstring
    bind_camera(m);              // Bind Camera class
    bind_triangulation(m);       // Bind TriangulationIRMP class
}