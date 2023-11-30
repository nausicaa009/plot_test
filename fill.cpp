#include <cassert>
#include "fill.h"

// TODO: implement constructors

Fill::~Fill() {
}

// TODO: implement member functions
bool FillAbove::is_fill(double x, double y) {
    double y_val = m_fn->get_expr()->eval(x);
    return y > y_val;
}

bool FillBelow::is_fill(double x, double y) {
    double y_val = m_fn->get_expr()->eval(x);
    return y < y_val;
}

bool FillBetween::is_fill(double x, double y) {
    double y_val1 = m_fn1->get_expr()->eval(x);
    double y_val2 = m_fn2->get_expr()->eval(x);
    return y >= y_val1 && y <= y_val2;
}

