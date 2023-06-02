#include "OcctTestConfig.h"
#include "occt.h"
#include <iostream>
#include <vector>
#include <fstream>

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

  return 0;
}
