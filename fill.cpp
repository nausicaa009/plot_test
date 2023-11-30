#include <cassert>
#include "fill.h"

// TODO: implement constructors - DONE on fill.h

Fill::~Fill() {
}

// TODO: implement member functions - DONE
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
    double y_min = std::min(y_val1, y_val2);
    double y_max = std::max(y_val1, y_val2);

    return y > y_min && y < y_max;
}

