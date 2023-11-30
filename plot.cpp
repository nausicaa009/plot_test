#include <cassert>
#include "plot.h"

Plot::Plot()
  // TODO: initialize fields
{
}

Plot::~Plot()
{
  // TODO: delete dynamically-allocated objects
  delete m_bounds;

  // Free m_function_map
  for (std::vector<Function*>::const_iterator it = m_function_vector.cbegin();
        it != m_function_vector.cend(); it++) {
    delete *it;
  }

  // Free m_fill_map
  for (std::vector<Fill*>::const_iterator it = m_fill_vector.cbegin();
        it != m_fill_vector.cend(); it++) {
    delete *it;
  }
}

void Plot::add_color(std::string fn_name, Color color) {
  m_color_map.insert({ fn_name, color });
}

Color Plot::get_color(std::string fn_name) const {
  std::map<std::string, Color>::const_iterator it = m_color_map.find(fn_name);
  if (it != m_color_map.end()) {
    return it->second;
  } else {
    throw PlotException("unknown function name in color");
  }
}

void Plot::add_function(Function* function) {
  m_function_vector.push_back(function);
}

Function* Plot::get_function(std::string fn_name) const {
  for (std::vector<Function*>::const_iterator it = m_function_vector.cbegin();
      it != m_function_vector.cend(); it++) {
    if (fn_name.compare((*it)->get_name()) == 0) {
      return *it;
    }
  }
  throw PlotException("Can't find function name");
}

void Plot::add_fill(Fill* fill) {
  m_fill_vector.push_back(fill);
}

// Fill* Plot::get_fill(std::string fn_name) const {
//   for (std::vector<Fill*>::const_iterator it = m_fill_vector.cbegin();
//       it != m_fill_vector.cend(); it++) {
//     if (fn_name.compare((*it)->get_fn_name()) == 0) {
//       return *it;
//     }
//   }
//   return NULL;
// }

std::vector<Function*> Plot::get_all_functions() const {
  return m_function_vector;
}

std::vector<Fill*> Plot::get_all_fills() const {
  return m_fill_vector;
}