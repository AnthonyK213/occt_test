import sys
sys.path.append("build/")
import pyRpOCCT as occt

pln = occt.gp_Pln(occt.gp_Ax3(occt.gp_Pnt(1, 2, 3), occt.gp_Dir(0, 0, 1), occt.gp_Dir(1, 0, 0)))
circle = occt.Geom_Circle(occt.gp_Ax2(occt.gp_Pnt(1, 2, 3), occt.gp_Dir(0, 0, 1), occt.gp_Dir(1, 0, 0)), 30)

def test():
    print(circle)
    pass

# test()
