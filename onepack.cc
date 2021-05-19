#include <iostream>
#include "include/elzip/elzip.hpp"

int main(int argc, char* argv[]) {
  std::cout << argv[0] << std::endl;
  elz::extractZip(argv[0]);

  return 0;
}