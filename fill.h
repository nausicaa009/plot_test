#ifndef FILL_H
#define FILL_H

#include <string>
#include "image.h"

class Fill {
private:
  // TODO: add fields to represent the fill
  std::string m_fn_name;
  float m_opacity;
  Color m_color;

public:
  // TODO: add appropriate constructors
  Fill(std::string fn_name, float opacity, Color color) :
    m_fn_name(fn_name), m_opacity(opacity), m_color(color) {
  }

  ~Fill();

  // TODO: add appropriate member functions
  std::string get_fn_name();

  float get_opacity();

  Color get_color();
};

class FillAbove : public Fill {
public:
  FillAbove(std::string fn_name, float opacity, Color color) : 
    Fill(fn_name, opacity, color) {
  }
};

class FillBelow : public Fill {
public:
  FillBelow(std::string fn_name, float opacity, Color color) : 
    Fill(fn_name, opacity, color) {
  }
};

class FillBetween : public Fill {
private:
  std::string m_second_fn_name;

public:
  FillBetween(std::string fn_name, std::string second_fn_name, float opacity, Color color) : 
    Fill(fn_name, opacity, color), m_second_fn_name(second_fn_name) {
  }
  
  std::string get_second_fn_name();
};

#endif // FILL_H
