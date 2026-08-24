#include <pybind11/pybind11.h>  // Main header pybind11 library.
#include <pybind11/stl.h>       // Header for STL containers (e.g., std::vector, std::map, etc.).

#include <sstream>
#include <vector>

#include "orion/matrix.hpp"

namespace py = pybind11;

PYBIND11_MODULE(orion,
                m) {  // Create a Python module named "orion" and bind it to the variable "m".
  m.doc() = "Orion is a C++ algebra linear library.";  // Module docstring.

  py::class_<orion::Matrix>(
      m, "Matrix",
      py::dynamic_attr())  // Bind the C++ class "orion::Matrix" to a Python class named "Matrix"
                           // with dynamic attributes. py::dynamic_attr() allows the Python class to
                           // have dynamic attributes, meaning you can add new attributes to
                           // instances of the class at runtime.
      .def(py::init<std::size_t, std::size_t, double>(), py::arg("rows"), py::arg("cols"),
           py::arg("initial_value") = 0.0)  // Bind the Matrix(i, j, v) constructor and
                                            // defines v = 0.0 as standart fill.
      .def(py::init<std::vector<std::vector<double>>>())  // Bind the Matrix((...)) constructor to a
                                                          // Matrix[[...]] in Python. Thanks to
                                                          // <pybind11/stl.h> Allows instantiating
                                                          // the class in Python using nested lists.
      .def("rows", &orion::Matrix::rows)
      .def("cols", &orion::Matrix::cols)
      .def("__add__", &orion::Matrix::operator+)
      .def("__sub__", &orion::Matrix::operator-)
      .def(
          "__matmul__",
          static_cast<orion::Matrix (orion::Matrix::*)(const orion::Matrix&) const>(
              &orion::Matrix::operator*))  // The use of static_cast happen because the operator* is
                                           // overloaded, it indicates which exaclty version to use.
      .def("__mul__", &orion::Matrix::hadamard)
      .def("__truediv__", &orion::Matrix::operator/)
      .def("transpose", &orion::Matrix::transpose)
      .def("mean", &orion::Matrix::mean)
      .def("sum", static_cast<double (orion::Matrix::*)() const>(&orion::Matrix::sum))  // sum().
      .def("sum", static_cast<orion::Matrix (orion::Matrix::*)(int) const>(
                      &orion::Matrix::sum))  // sum(axis).
      .def("__getitem__",
           [](const orion::Matrix& matrix, std::tuple<std::size_t, std::size_t> idx) {
             auto [row, col] = idx;
             return matrix(row, col);
           })  // Lambda function to translate getter method Matrix(i, j) to Matrix[i, j].
      .def("__setitem__",
           [](orion::Matrix& matrix, std::tuple<std::size_t, std::size_t> idx, double value) {
             auto [row, col] = idx;
             matrix(row, col) = value;
           })  // Allows Matrix[i, j] = x.
      .def("__str__", [](const orion::Matrix& matrix) {
        std::ostringstream oss;  // ostringstream accumulates text inside a memory buffer.
        oss << matrix;           // Inserts the matrix inside the oss flow.
        return oss.str();        // str() converts all the content inside the oss in a text.
      });
}