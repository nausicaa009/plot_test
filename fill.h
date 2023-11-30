#ifndef FILL_H
#define FILL_H

#include <string>
#include "image.h"
#include "func.h"

class Fill {
private:
  // TODO: add fields to represent the fill - DONE
  float m_opacity;
  Color m_color;

public:
  // TODO: add appropriate constructors - DONE
  Fill(float opacity, Color color) :
    m_opacity(opacity), m_color(color) {
  }

  virtual ~Fill();

  // TODO: add appropriate member functions - DONE
  float get_opacity() { return m_opacity;  };

  Color get_color() { return m_color; }

  virtual bool is_fill(double x, double y) = 0;
};

class FillAbove : public Fill {
private:
  Function* m_fn;

public:
  FillAbove(Function* fn, float opacity, Color color) : 
    Fill(opacity, color), m_fn(fn) {
  }

  ~FillAbove() override {
  }

  bool is_fill(double x, double y) override;
};

class FillBelow : public Fill {
private:
  Function* m_fn;

public:
  FillBelow(Function* fn, float opacity, Color color) : 
    Fill(opacity, color), m_fn(fn) {
  }

  ~FillBelow() override {
  }

  bool is_fill(double x, double y) override;
};

class FillBetween : public Fill {
private:
  Function* m_fn1;
  Function* m_fn2;

public:
  FillBetween(Function* fn1, Function* fn2,float opacity, Color color) : 
    Fill(opacity, color), m_fn1(fn1), m_fn2(fn2) {
  }

  ~FillBetween() override {
  }

  bool is_fill(double x, double y) override;
};

#endif // FILL_H
