#ifndef PLOT_H
#define PLOT_H

#include <vector>
#include <map>
#include <string>
#include "bounds.h"
#include "image.h"
#include "func.h"
#include "fill.h"

class Plot {
private:
  // TODO: add fields to represent plot bounds, functions, fills, etc.
  int m_width;
  int m_height;
  Bounds* m_bounds;

  std::vector<Color> m_color_vector;
  std::vector<Function*> m_function_vector;
  std::vector<Fill*> m_fill_vector;

  // value semantics are prohibited
  Plot(const Plot &);
  Plot &operator=(const Plot &);

public:
  Plot();
  ~Plot();

  // TODO: add member functions to set and modify plot data
  int get_width() const { return m_width; }
  int get_height() const { return m_height; }
  void set_width(int width) { m_width = width; }
  void set_height(int height) { m_height = height; }  

  Bounds& get_bounds() const { return *m_bounds; }
  void set_bounds(Bounds* bounds) { m_bounds = bounds; }

  void add_color(Color color);
  Color get_color(std::string fn_name);

  void add_function(Function* function);
  Function* get_function(std::string fn_name);

  void add_fill(Fill* fill);
  Fill* get_fill(std::string fn_name);
};

#endif // PLOT_H
