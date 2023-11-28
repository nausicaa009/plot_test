#ifndef FUNC_H
#define FUNC_H

#include <string>
#include "expr.h"

class Function {
private:
  std::string m_name;
  Expr *m_expr;

  Function(const Function &);
  Function &operator=(const Function &);

public:
  Function(const std::string &name, Expr *expr);
  ~Function();

  std::string get_name() const { return m_name; }
  Expr *get_expr() const       { return m_expr; }
};
#endif