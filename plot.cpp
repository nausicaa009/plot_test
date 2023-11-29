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

  m_color_vector.empty();
  // Free m_function_map
  for (std::vector<Function*>::const_iterator it = m_function_vector.cbegin();
        it != m_function_vector.cend(); it++) {
    delete *it;
  }
  m_function_vector.empty();

  // Free m_fill_map
  for (std::vector<Fill*>::const_iterator it = m_fill_vector.cbegin();
        it != m_fill_vector.cend(); it++) {
    delete *it;
  }
  m_fill_vector.empty();
}

void Plot::add_color(Color color) {
  m_color_vector.push_back(color);
}

Color Plot::get_color(std::string fn_name) {
  for (std::vector<Color>::const_iterator it = m_color_vector.cbegin();
      it != m_color_vector.cend(); it++) {
    if (fn_name.compare(it->m_fn_name) == 0) {
      return *it;
    }
  }
  throw PlotException("Can't find function name");
}

void Plot::add_function(Function* function) {
  m_function_vector.push_back(function);
}

Function* Plot::get_function(std::string fn_name) {
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

Fill* Plot::get_fill(std::string fn_name) {
  for (std::vector<Fill*>::const_iterator it = m_fill_vector.cbegin();
      it != m_fill_vector.cend(); it++) {
    if (fn_name.compare((*it)->get_fn_name()) == 0) {
      return *it;
    }
  }
  throw PlotException("Can't find function name");
}
