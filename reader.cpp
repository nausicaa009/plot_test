#include <iostream>
#include <sstream>
#include <string.h>


#include "reader.h"
#include "expr_parser.h"
#include "func.h"
#include "exception.h"

namespace 
{
  std::deque<std::string> tokenize(std::string str) {
    std::stringstream ss(str);
    std::string token;
    std::deque<std::string> queue;
    while (std::getline(ss, token, ' ')) {
      queue.push_back(token);
    }
    return queue;
  }

  void parsePlotDirective(std::deque<std::string> tokens, Plot &plot) {
    if (tokens.size() != 7) {
      throw PlotException("Invalid Plot directive in plot input file.");
    }

    int xmin = stoi(tokens[1]);
    double ymin = stod(tokens[2]);
    int xmax = stoi(tokens[3]);
    double ymax = stod(tokens[4]);
    int width = stoi(tokens[5]);
    int height = stoi(tokens[6]);

    if (xmin > xmax) {
      throw PlotException("xmin is not less than xmax.");
    }
    if (ymin > ymax) {
      throw PlotException("ymin is not less than ymax.");
    }
    if (width < 0) {
      throw PlotException("width is not positive.");
    }
    if (height < 0) {
      throw PlotException("height is not positive.");
    }

    plot.set_bounds(new Bounds(xmin, ymin, xmax, ymax));
    plot.set_width(width);
    plot.set_height(height);
  }

  void parseColorDirective(std::deque<std::string> tokens, Plot &plot) {
    if (tokens.size() != 5) {
      throw PlotException("Invalid Color directive in plot input file.");
    }
    std::string fn_name = tokens[1];
    Color color;
    color.r = stoi(tokens[2]);
    color.g = stoi(tokens[3]);
    color.b = stoi(tokens[4]);

    plot.add_color(fn_name, color);
  }

  void parseFillAboveDirective(std::deque<std::string> tokens, Plot &plot) {
    if (tokens.size() != 6) {
      throw PlotException("Invalid FillAbove directives in plot input file.");
    }

    std::string fn_name = tokens[1];
    float opacity = stof(tokens[2]);
    Color color;
    color.r = stoi(tokens[3]);
    color.g = stoi(tokens[4]);
    color.b = stoi(tokens[5]);

    Function* fn = plot.get_function(fn_name);
    FillAbove* fill = new FillAbove(fn, opacity, color);
    plot.add_fill(fill);
  }  


  void parseFillBelowDirective(std::deque<std::string> tokens, Plot &plot) {
    if (tokens.size() != 6) {
      throw PlotException("Invalid FillBelow directives in plot input file.");
    }

    std::string fn_name = tokens[1];
    float opacity = stof(tokens[2]);
    Color color;
    color.r = stoi(tokens[3]);
    color.g = stoi(tokens[4]);
    color.b = stoi(tokens[5]);

    Function* fn = plot.get_function(fn_name);
    FillBelow* fill = new FillBelow(fn, opacity, color);
    plot.add_fill(fill);
  }  

  void parseFillBetweenDirective(std::deque<std::string> tokens, Plot &plot) {
    if (tokens.size() != 7) {
      throw PlotException("Invalid FillBetween directives in plot input file.");
    }

    std::string fn_name = tokens[1];
    std::string second_fn_name = tokens[2];
    float opacity = stof(tokens[3]);
    Color color;
    color.r = stoi(tokens[4]);
    color.g = stoi(tokens[5]);
    color.b = stoi(tokens[6]);

    Function* fn1 = plot.get_function(fn_name);
    Function* fn2 = plot.get_function(second_fn_name);
    FillBetween* fill = new FillBetween(fn1, fn2, opacity, color);
    plot.add_fill(fill);
  }  
}

Reader::Reader() {
}

Reader::~Reader() {
}

void Reader::read_input(std::istream &in, Plot &plot) {

  // Read line by line from istream
  std::string buf;
  while (getline(in, buf)) {

    std::deque<std::string> tokens = tokenize(buf);
    std::stringstream ss = std::stringstream(buf);
    std::string directive;
    ss >> directive;

    if (directive.compare("Function") == 0) {
      std::string fn_name;
      ss >> fn_name;

      ExprParser parser;
      Expr* expr = parser.parse(ss);
      Function* fn = new Function(fn_name, expr);
      plot.add_function(fn);

    } else if (directive.compare("Plot") == 0) {
      parsePlotDirective(tokens, plot);

    } else if (directive.compare("Color") == 0) {
      parseColorDirective(tokens, plot);

     } else if (directive.compare("FillAbove") == 0) {
      parseFillAboveDirective(tokens, plot);

    } else if (directive.compare("FillBelow") == 0) {
      parseFillBelowDirective(tokens, plot);

    } else if (directive.compare("FillBetween") == 0) {
      parseFillBetweenDirective(tokens, plot);

    } else {
      throw PlotException("Unknown directive.");
    }
  }

}
