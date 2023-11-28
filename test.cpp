#include <iostream>
#include <deque>
#include <string>


void parse_function(std::deque<std::string> &q) {

  q.pop_front();


  for (std::deque<std::string>::const_iterator it = q.cbegin(); it != q.cend(); it++) {
    std::cout << *it << "\n";
  }

}

int main(int argc, char** argv) {

  float val = atof("1.2334");
  std::cout << val << "\n";

  val = atof("abc");
  std::cout << val << "\n";

  std::deque<std::string> q;

  q.push_back("a");
  q.push_back("b");
  q.push_back("c");

  parse_function(q);

  return 0;
}