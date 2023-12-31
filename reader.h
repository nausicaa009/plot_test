#ifndef READER_H
#define READER_H

#include <istream>
#include <string>
#include <deque>
#include "plot.h"

class Reader {
private:
  Reader(const Reader &);
  Reader &operator=(const Reader &);

  std::deque<std::string> tokens;

public:
  Reader();
  ~Reader();

  void read_input(std::istream &in, Plot &plot);
};

#endif