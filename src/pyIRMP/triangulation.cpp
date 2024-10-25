// bindings.cpp
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // For STL containers like std::vector
#include <pybind11/eigen.h>

#include "IRMP/triangulation.h"  // Include your class header


namespace py = pybind11;
using namespace tri;

// Trampoline class for handling virtual methods
class PyTriangulation : public Triangulation {
public:
    using Triangulation::Triangulation;  // Inherit constructors

    // Override pure virtual methods
    void init(const std::vector<Camera>& cams,
              const std::vector<Eigen::Vector3d>& b) override {
        PYBIND11_OVERRIDE_PURE(
            void,                // Return type
            Triangulation,       // Parent class
            init,                // Method name in C++
            cams, b              // Method arguments
        );
    }

    bool run(Eigen::Vector3d& res) override {
        PYBIND11_OVERRIDE_PURE(
            bool,                // Return type
            Triangulation,       // Parent class
            run,                 // Method name in C++
            res                  // Method argument
        );
    }
};


void bind_triangulationBase(py::module_ &m){
    // Bind the parent class Triangulation
    py::class_<Triangulation, PyTriangulation, std::shared_ptr<Triangulation>>(m, "Triangulation")
        //.def(py::init<>())  // Default constructor
        .def("init", &Triangulation::init, py::arg("cams"), py::arg("pts"),
             "Initialize the triangulation with cameras and points")
        .def("run", &Triangulation::run, py::arg("res"),
             "Run the triangulation and return the result as a boolean")
        .def_property_readonly("name", &Triangulation::name, "Get the name of the triangulation");
};


void bind_triangulationIRMP(py::module_ &m) {
    // Bind the child class TriangulationIRMP
    py::class_<TriangulationIRMP, Triangulation, std::shared_ptr<TriangulationIRMP>>(m, "TriangulationIRMP")
        .def(py::init<>())  // Default constructor
        .def("init", &TriangulationIRMP::init, 
             py::arg("cams"), 
             py::arg("pts"), 
             "Initialize the triangulation with cameras and points")
        .def("run", [](TriangulationIRMP &self) {
            Eigen::Vector3d result;  // Create a dummy vector
            self.run(result);         // Call the run function
            return result;           // Return the populated vector
        }, "Run the triangulation and return the result as an Eigen::Vector3d.");
        /*.def_property_readonly("max_iters_", [](const TriangulationIRMP &self) {
            return self.max_iters_(); // Use the public getter method
        }, "Maximum number of iterations");*/
};

void bind_triangulation(py::module_ &m){
    bind_triangulationBase(m);
    bind_triangulationIRMP(m);
}
