#include "OcctTestConfig.h"
#include "occt.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <pybind11/pybind11.h>
#include <pybind11/embed.h>

namespace py = pybind11;

int main(int argc, char *argv[]) {

#ifdef DEBUG
  std::cout << "Hello, OCCT!" << std::endl;
#endif

  std::ofstream f;
  f.open("a.json");

  const gp_Pnt pt0{0, 0, 0};
  const gp_Pnt pt1{1, 0, 0};
  const TopoDS_Edge edge0 = BRepBuilderAPI_MakeEdge(pt0, pt1).Edge();

  edge0.DumpJson(f);

  f.close();

  py::scoped_interpreter guard{};
  auto pyOCCT = py::module_::import("pyRpOCCT");
  py::module_::import("sys").attr("path").attr("append")("..");
  auto pyModule = py::module_::import("demo");
  auto pyFunction = pyModule.attr("test");
  auto pyResult = pyFunction();

  return 0;
}
