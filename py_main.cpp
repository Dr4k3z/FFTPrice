#include <pybind11/pybind11.h>
#include <Eigen/Dense>

namespace py = pybind11;

double dot_example() {
    Eigen::Vector2d a(1.0, 2.0), b(3.0, 4.0);
    return a.dot(b); // 11.0
}

double dot_prod() {
    Eigen::Vector2d a(1.0, 2.0), b(3.0, 4.0);
    return a.dot(b); // 11.0
}

PYBIND11_MODULE(fftprice, m) {
    m.def("dot_example", &dot_example);
    m.def("dot_prod", &dot_prod);
}
