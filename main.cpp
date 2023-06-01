#include "OcctTestConfig.h"
#include "occt.h"
#include <iostream>
#include <vector>

int main(int argc, char *argv[]) {

#ifdef DEBUG
  std::cout << "Hello, OCCT!" << std::endl;
#endif

  gp_Pnt pt0{0, 0, 0};
  gp_Pnt pt1{1, 0, 0};
  TopoDS_Edge edge0 = BRepBuilderAPI_MakeEdge(pt0, pt1).Edge();

  std::cout << pt0.X() << " " << &pt0 << std::endl;
  std::cout << &edge0 << std::endl;

  return 0;
}
