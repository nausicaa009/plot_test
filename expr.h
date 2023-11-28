#ifndef EXPR_H
#define EXPR_H

#define UNUSED(param) (void)(param)

#include <vector>
#include <math.h>
#include "exception.h"


class Expr {
private:
  Expr(const Expr &);
  Expr &operator=(const Expr &);

protected:
  std::vector<Expr*> m_operands;

public:
  Expr();
  virtual ~Expr();

  virtual double eval(double x) const = 0;

  void set_operands(std::vector<Expr*> operands) {
    m_operands = operands;
  }
};

class X_Expr : public Expr {
public:
  X_Expr() : Expr() {
  }

  ~X_Expr() {
  }

  double eval(double x) const override {
    return x;
  }  
};

class PI_Expr: public Expr {
public:
  PI_Expr() : Expr() {
  }

  ~PI_Expr() {
  }

  double eval(double x) const override {
    UNUSED(x);
    return M_PI;
  }  
};

class Value_Expr: public Expr {
private:
  double m_value;
  
public:
  Value_Expr(double value) : m_value(value) {
  }

  ~Value_Expr() {
  }

  double eval(double x) const override {
    UNUSED(x);
    return m_value;
  }  
};

class Sine_Expr: public Expr {
public:
  Sine_Expr() : Expr() {
  }

  ~Sine_Expr() {
  }

  double eval(double x) const override {
    return sin(x);
  }  
};


class Cosine_Expr: public Expr {
public:
  Cosine_Expr() : Expr() {
  }

  ~Cosine_Expr() {
  }

  double eval(double x) const override {
    return cos(x);
  }  
};


class Plus_Expr: public Expr {
public:
  Plus_Expr() : Expr() {
  }

  ~Plus_Expr() {
  }

  double eval(double x) const override {
    double eval_value = 0;
    for (std::vector<Expr*>::const_iterator it = m_operands.cbegin(); 
      it != m_operands.cend(); it++) {
        eval_value += (*it)->eval(x);
    }
    return eval_value;
  }  
};


class Minus_Expr: public Expr {
public:
  Minus_Expr() : Expr() {
  }

  ~Minus_Expr() {
  }

  double eval(double x) const override {
    if (m_operands.size() != 2) {
      throw  PlotException("functions should hae exactly two argument expressions");
    }
    return m_operands.at(0)->eval(x) - m_operands.at(1)->eval(x);
  }  
};


class Multiply_Expr: public Expr {
public:
  Multiply_Expr() : Expr() {
  }

  ~Multiply_Expr() {
  }

  double eval(double x) const override {
    double eval_value = 1;
    for (std::vector<Expr*>::const_iterator it = m_operands.cbegin(); 
      it != m_operands.cend(); it++) {
        eval_value *= (*it)->eval(x);
    }
    return eval_value;
  }  
};


class Divide_Expr: public Expr {
public:
  Divide_Expr() : Expr() {
  }

  ~Divide_Expr() {
  }

  double eval(double x) const override {
    if (m_operands.size() != 2) {
      throw  PlotException("functions should hae exactly two argument expressions");
    }
    double denoninator = m_operands.at(1)->eval(x);
    if (denoninator == 0) {
      throw  PlotException("attempt to divide by 0");
    }
    return m_operands.at(0)->eval(x) /denoninator;
  }  
};


#endif