#pragma once

#include "occt.h"
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_DECLARE_HOLDER_TYPE(T, Handle(T), true);

PYBIND11_MODULE(pyRpOCCT, m) {
  py::class_<gp_Pnt>(m, "gp_Pnt")
      .def(py::init<>())
      .def(py::init<double, double, double>())
      .def("X", &gp_Pnt::X)
      .def("Y", &gp_Pnt::Y)
      .def("Z", &gp_Pnt::Z);

  py::class_<gp_Dir>(m, "gp_Dir")
      .def(py::init<>())
      .def(py::init<double, double, double>())
      .def("X", &gp_Dir::X)
      .def("Y", &gp_Dir::Y)
      .def("Z", &gp_Dir::Z);

  py::class_<gp_Ax1>(m, "gp_Ax1")
      .def(py::init<>())
      .def(py::init<const gp_Pnt &, const gp_Dir &>())
      .def("Direction", &gp_Ax1::Direction)
      .def("Location", &gp_Ax1::Location);

  py::class_<gp_Ax2>(m, "gp_Ax2")
      .def(py::init<>())
      .def(py::init<const gp_Pnt &, const gp_Dir &, const gp_Dir &>());

  py::class_<gp_Ax3>(m, "gp_Ax3")
      .def(py::init<>())
      .def(py::init<const gp_Pnt &, const gp_Dir &, const gp_Dir &>());

  py::class_<gp_Pln>(m, "gp_Pln")
      .def(py::init<>())
      .def(py::init<const gp_Ax3 &>())
      .def("YAxis", &gp_Pln::YAxis);

  py::class_<Geom_Curve, Handle(Geom_Curve)>(m, "Geom_Curve");

  py::class_<Geom_Line, Handle(Geom_Line), Geom_Curve>(m, "Geom_Line")
      .def(py::init<const gp_Pnt &, const gp_Dir &>());

  py::class_<Geom_Conic, Handle(Geom_Conic), Geom_Curve>(m, "Geom_Conic");

  py::class_<Geom_Circle, Handle(Geom_Circle), Geom_Conic>(m, "Geom_Circle")
      .def(py::init<const gp_Ax2 &, double>())
      .def("Radius", &Geom_Circle::Radius);
}
