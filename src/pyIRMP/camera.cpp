#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include "IRMP/camera.h"

namespace py = pybind11;
using namespace tri;

void bind_camera(py::module_ &m) {
    py::class_<Camera>(m, "Camera")
        .def(py::init<const Eigen::Matrix3d&, const Eigen::Vector3d&, const Eigen::Matrix3d&, int, int>(),
             py::arg("attitude"), 
             py::arg("location"), 
             py::arg("K"), 
             py::arg("width"), 
             py::arg("height"), 
             "Create a Camera object with attitude, location, inner parameters, and dimensions")
        .def("project", [](const Camera& self, const Eigen::Vector3d& pt_w) {
            Eigen::Vector2d uv;
            if (self.project(pt_w, uv)) {
                return uv; // Return the projected 2D coordinates if successful
            } else {
                throw std::runtime_error("Projection failed.");
            }
        }, "Project a 3D point in world coordinates to 2D camera coordinates.")
        .def("w2c", &Camera::w2c, "Transform a point from world coordinates to camera coordinates.")
        .def("unproject", &Camera::unproject, "Unproject 2D camera coordinates back to 3D world coordinates.")
        .def_property_readonly("R", &Camera::R, "Get the rotation matrix of the camera.")
        .def_property_readonly("t", &Camera::t, "Get the translation vector of the camera.")
        .def_property_readonly("t_inv", &Camera::t_inv, "Get the inverse translation vector of the camera.");
}
