#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include "GBMSimulation.h"

namespace py = pybind11;

static py::array paths_view_no_copy(const Eigen::MatrixXd& M, py::handle base_owner) {
    using py::ssize_t;
    const ssize_t rows = static_cast<ssize_t>(M.rows());
    const ssize_t cols = static_cast<ssize_t>(M.cols());

    std::array<ssize_t, 2> shape   { rows, cols };
    std::array<ssize_t, 2> strides {
        static_cast<ssize_t>(sizeof(double)),
        static_cast<ssize_t>(sizeof(double) * rows)
    };

    return py::array(py::dtype::of<double>(), shape, strides, M.data(), base_owner);
}

PYBIND11_MODULE(_core, m) {
    py::class_<GBMSimulation>(m, "GBMSimulation")
        .def(py::init<>())
        .def(py::init<real, real, real, real, int, int, uint64_t>(),
             py::arg("S0"), py::arg("mu"), py::arg("sigma"), py::arg("T"),
             py::arg("n_steps"), py::arg("n_paths"), py::arg("seed") = 0ULL)

        .def("simulate", &GBMSimulation::simulate,
             "Run the simulation and fill the internal path matrix.")

        // Option 1: return a **copy** as a NumPy array (simplest)
        .def("paths", [](const GBMSimulation& self) {
                return self.paths_ref();   // pybind11/eigen copies to NumPy
            },
            "Return paths as a NumPy array (copy).")

        // Option 2: return a **zero-copy** NumPy view onto internal Eigen data
        .def("paths_view", [](py::object self_obj, GBMSimulation& self) {
                return paths_view_no_copy(self.paths_ref(), self_obj);
            },
            "Return a zero-copy NumPy view of the internal paths "
            "(invalidated if the object is destroyed or resized)."
        )
        ;
}
