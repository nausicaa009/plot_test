#include <string>
#include <sstream>
#include <memory>
#include <deque>
#include "exception.h"
#include "expr.h"
#include "expr_parser.h"

namespace 
{

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
    args.push_back(parsePfxExpr(tokens));
  }
  expr->set_operands(args); // add operands

  tokens.pop_front(); // should be right parenthesis

  return expr;
}

} // namespace 

ExprParser::ExprParser() {
}

ExprParser::~ExprParser() {
}


Expr *ExprParser::parse(std::istream &in) {
  // Recommended strategy: read all of the tokens in the expression
  // from the istream and put them in a sequence collection
  // such as a vector or deque. The call a recursive helper function
  // which parses the tokens and returns a pointer to an Expr object
  // repersenting the parsed expression.
  std::string token;
  std::deque<std::string> tokens;
  while (std::getline(in, token, ' ')) {
    if (token.size() > 0) { // Skip empty string
      tokens.push_back(token);
    }
  }

  return parsePfxExpr(tokens);
}
