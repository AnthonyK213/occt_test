#include "IFSelect_PrintCount.hxx"
#include "OcctTestConfig.h"
#include "occt.h"
#include <fstream>
#include <iostream>
#include <pybind11/embed.h>
#include <pybind11/pybind11.h>
#include <vector>

#define SPLIT split();

namespace py = pybind11;

void split() { std::cout << "----------" << std::endl; }

void intersection_test()
{
  std::ofstream f;
  f.open("a.json");

  const gp_Pnt pt0{0, 0, 0};
  const gp_Pnt pt1{1, 1, 0};
  const TopoDS_Edge edge0 = BRepBuilderAPI_MakeEdge(pt0, pt1).Edge();

  const gp_Pnt pt2{1, 0, 0};
  const gp_Pnt pt3{0, 1, 0};
  const TopoDS_Edge edge1 = BRepBuilderAPI_MakeEdge(pt2, pt3).Edge();

  IntTools_EdgeEdge intersection(edge0, edge1);
  intersection.Perform();

  if (intersection.IsDone())
  {
    IntTools_SequenceOfCommonPrts commonParts = intersection.CommonParts();
    for (auto &part : commonParts)
    {
      Standard_Real t = part.VertexParameter1();
      std::cout << t << std::endl;
      Standard_Real u0, u1;
      auto curve = BRep_Tool::Curve(edge0, u0, u1);
      gp_Pnt pt = curve->Value(t);
      pt.DumpJson(std::cout);
    }
  }

  edge0.DumpJson(f);

  f.close();
}

void python_test()
{
  py::scoped_interpreter guard{};
  auto pyOCCT = py::module_::import("pyRpOCCT");
  py::module_::import("sys").attr("path").attr("append")("..");
  auto pyModule = py::module_::import("demo");
  auto pyFunction = pyModule.attr("test");
  auto pyResult = pyFunction();
}

void std_import_test()
{
  std::ofstream f;
  f.open("result.json");

  STEPControl_Reader reader;
  IFSelect_ReturnStatus stat = reader.ReadFile("../occt_stp_test.stp");

  // reader.PrintCheckLoad(false, IFSelect_ItemsByEntity);

  // Standard_Integer ic = Interface_Static::IVal("read.precision.mode");

  // Standard_Real rp = Interface_Static::RVal("read.precision.val");

  // Standard_Real rp = Interface_Static::RVal("read.maxprecision.val");

  // Standard_Integer ic = Interface_Static::IVal("read.maxprecision.mode");

  // Standard_Integer mv = Interface_Static::IVal("read.stdsameparameter.mode");

  // Standard_Integer rp = Interface_Static::IVal("read.surfacecurve.mode");

  // Standard_Real era = Interface_Static::RVal("read.encoderegularity.angle");

  // Standard_Integer ic = Interface_Static::IVal("read.step.product.mode");

  // Standard_Integer ic =  Interface_Static::IVal("read.step.product.context");

  // Standard_Integer ic = Interface_Static::IVal("read.step.shape.repr");

  // Standard_Integer ic = Interface_Static::IVal("read.step.assembly.level");

  // Standard_Integer ic = Interface_Static::IVal("read.step.shape.relationship");

  // Standard_Integer ic = Interface_Static::IVal("read.step.shape.aspect");

  // Standard_Integer ic = Interface_Static::IVal("read.step.tessellated");

  reader.ClearShapes();

  // reader.PrintCheckTransfer(false, IFSelect_ItemsByEntity);

  Standard_Integer NbRoots = reader.NbRootsForTransfer();
  Standard_Integer num = reader.TransferRoots();

  Handle(TColStd_HSequenceOfTransient) list = reader.GiveList();

  // std::cout << list->Size() << std::endl;

  Standard_Integer nbtrans = reader.TransferList(list);

  Standard_Integer nb = list->Length();
  for (Standard_Integer i = 1; i < nb; ++i)
  {
    Handle(Standard_Transient) ent = list->Value(i);
    Standard_Boolean Ok = reader.TransferEntity(ent);
  }

  TopoDS_Shape result = reader.OneShape();

  TopExp_Explorer myExplorer(result, TopAbs_EDGE);

  while (myExplorer.More())
  {
    auto obj = TopoDS::Edge(myExplorer.Current());
    obj.DumpJson(f);
    myExplorer.Next();
  }

  // std::cout
  //     << result.NbChildren() << std::endl;
}

int main(int argc, char *argv[])
{
  SPLIT;

  // intersection_test();
  // python_test();
  std_import_test();

  SPLIT;

  return 0;
}
