#include <iostream>
#include <sstream>
#include <string.h>


#include "reader.h"
#include "func.h"
#include "exception.h"

namespace 
{
/**
 * Tokenize str into vector
 */
std::deque<std::string> tokenize(std::string str) {
  std::stringstream ss(str);
  std::string token;
  std::deque<std::string> queue;
  while (std::getline(ss, token, ' ')) {
    queue.push_back(token);
  }
  return queue;
}


Expr* parsePfxExpr(std::deque<std::string> & tokens) {
  std::string n = tokens[0];
  tokens.pop_front(); // pop the first token

  Expr* expr = NULL;
  if (n.compare("x") == 0) {
    return new X_Expr();

  } else if (n.compare("pi") == 0) {
    return new PI_Expr();

  } else if (n.compare("(") == 0) {
    n = tokens[0];
    tokens.pop_front(); // pop first token from tokens
    
    if (n.compare("sin") == 0) {
      expr = new Sine_Expr();

    } else if (n.compare("cos") == 0) {
      expr = new Cosine_Expr();

    } else if (n.compare("+") == 0) {
      expr = new Plus_Expr();

    } else if (n.compare("-") == 0) {
      expr = new Minus_Expr();

    } else if (n.compare("*") == 0) {
      expr = new Multiply_Expr();

    } else if (n.compare("/") == 0) {
      expr = new Divide_Expr();

    } else {
      throw PlotException("invalid function name.");
    }

  } else {
    double value = strtod(n.c_str(), NULL); // convert string to double
    
    if (value == 0) {
      throw PlotException("Unexpected token.");
    } else {
     return new Value_Expr(value);
    }
  }

  std::vector<Expr*> args;
  while (tokens[0].compare(")") != 0) { // first token of tokesn is not right parentihis
    Expr* arg = parsePfxExpr(tokens);
    args.push_back(arg);
  }
  expr->set_operands(args); // add operands

  tokens.pop_front(); // should be right parenthesis

  return expr;
}

/**
 * Create Function instance 
 */
Function* parse_function(std::deque<std::string> tokens) {

  const int count = tokens.size();

  if (count < 2) {
    throw PlotException("Function directive misses function name.");
  } else if (count < 3) {
    throw PlotException("Function directive misses expression.");
  }

  const std::string fn_name = tokens[1];

  tokens.pop_front(); // pop directive
  tokens.pop_front(); // pop function name

  Expr *expr = parsePfxExpr(tokens);

  Function* fn = new Function(fn_name, expr);

  return fn;
}


} // namespace 

Reader::Reader() {
}

Reader::~Reader() {
}

void Reader::read_input(std::istream &in) {

  std::string buf;
  
  // Read line by line from istream
  while (getline(in, buf)) {
    std::deque<std::string> queue = tokenize(buf);
    if (queue.size() == 0) {
      continue;
    }
    std::string directive = queue[0];

    if (directive.compare("Function") == 0) {
      Function* fn = parse_function(queue);
      double value = fn->get_expr()->eval(1);
      std::cout << "value=" << value << "\n";

    } else if (directive.compare("Plot") == 0) {
      //TODO
    } else if (directive.compare("Color") == 0) {
      //TODO
    } else if (directive.compare("FillAbove") == 0) {
      //TODO
    } else if (directive.compare("FillBelow") == 0) {
      //TODO
    } else if (directive.compare("FillBetween") == 0) {
      //TODO
    } else {
      //TODO: throw exception
    }
  }

}
