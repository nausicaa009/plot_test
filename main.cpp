#include <iostream>
#include <fstream>
#include <string>
#include "reader.h"


int main(int argc, char** argv) {
  int rc = 0;

  if (argc < 2) {
    std::cerr << "Usage: plot <input file>";
    return 1;
  }

  std::ifstream in(argv[1]);
  if (!in.is_open()) {
    std::cerr << "Error: couldn't open input file " << argv[1] << "\n";
    return 1;
  }

  Reader reader;
  reader.read_input(in);
  
  return rc;
}