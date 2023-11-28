#include "expr.h"

#define OPERAND_INCREMENT 10

Expr:: Expr() {
}


Expr:: ~Expr() {
  for (size_t i=0; i<m_operands.size(); i++) {
    delete m_operands[i];
  }
  m_operands.empty();
}
