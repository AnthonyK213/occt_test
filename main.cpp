#include <iostream>
#include <vector>
#include "build/OcctTestConfig.h"

int main(int argc, char *argv[]) {
#ifdef DEBUG
  std::cout << "Hello, OCCT!" << std::endl;
#endif

  return 0;
}
