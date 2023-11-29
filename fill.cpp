#include <cassert>
#include "fill.h"

// TODO: implement constructors

Fill::~Fill() {
}

// TODO: implement member functions
std::string Fill::get_fn_name() { 
    return m_fn_name; 
}

float Fill::get_opacity() { 
    return m_opacity; 
}

Color Fill::get_color() { 
    return m_color; 
}

std::string FillBetween::get_second_fn_name() {
    return m_second_fn_name;
}
