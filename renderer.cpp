#include <iostream>
#include <cmath>
#include <cassert>
#include <memory>
#include "exception.h"
#include "renderer.h"

//#define DEBUG_FILL
//#define DEBUG_PLOT

Renderer::Renderer(const Plot &plot)
  : m_plot(plot)
  , m_img(nullptr) {
}

Renderer::~Renderer() {
  // Note: the Renderer object does not "own" the Image object,
  // since the render() member function transfers ownership of
  // the Image object to the caller (in the main function)
}

Image *Renderer::render() {
  int width = m_plot.get_width();
  int height = m_plot.get_height();

  // the unique_ptr will take care of deleting the Image object
  // if an exception is thrown
  std::unique_ptr<Image> img(new Image(width, height));
  m_img = img.get();

  // TODO: render the plot image
  std::vector<Fill*> fills = m_plot.get_all_fills();

  for (std::vector<Fill*>::const_iterator it = fills.cbegin(); it != fills.cend(); it++) {
    fill_color(*it);
  }

  std::vector<Function*> functions = m_plot.get_all_functions();
  for (std::vector<Function*>::const_iterator it = functions.cbegin(); it != functions.cend(); it++) {
    draw_function(*it);
  }

  return img.release();
}

// TODO: implement private helper functions

void Renderer::draw_function(Function* function) {
  Color color = m_plot.get_color(function->get_name());

  const int w = m_plot.get_width();
  const int h = m_plot.get_height();
  Bounds bounds = m_plot.get_bounds();
  const int xmin = bounds.getXmin();
  const double ymin = bounds.getYmin();
  const int xmax = bounds.getXmax();
  const double ymax = bounds.getYmax();

  Color* pixels = m_img->get_color_pixels();

  for (int j=0; j<w; j++) {
    double x =  (double)xmin + ((double)j/(double)w) * (double)(xmax - xmin);
    double y = function->get_expr()->eval(x);
    int i = h - 1 - floor(((double)(y - ymin)/(double)(ymax - ymin) * h));

    pixels[i * w + j] = color;
  }
}

void Renderer::fill_color(Fill* fill) {
  float opacity = fill->get_opacity();
  Color color = fill->get_color();

  const int w = m_plot.get_width();
  const int h = m_plot.get_height();
  Bounds bounds = m_plot.get_bounds();

  const int xmin = bounds.getXmin();
  const double ymin = bounds.getYmin();
  const int xmax = bounds.getXmax();
  const double ymax = bounds.getYmax();

  Color* pixels = m_img->get_color_pixels();

  for (int i=0; i<h; i++) {
    for (int j=0; j<w; j++) {
      double xj = (double)xmin + ((double)j / (double)w) * (double)(xmax - xmin);
      double yi = (double)ymin + ((double)(h - 1 - i)/(double)h) * (double)(ymax - ymin);

      if (fill->is_fill(xj, yi)) {
        Color orig_color = pixels[i * w + j];
        uint8_t red = (1 - opacity) * orig_color.r + opacity * color.r;
        uint8_t green =  (1 - opacity) * orig_color.g + opacity * color.g;
        uint8_t blue =  (1 - opacity) * orig_color.b + opacity * color.b;
        Color blend_color = { red, green, blue };
        pixels[i * w + j] = blend_color;
      }
    }
  }
}