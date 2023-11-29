#ifndef BOUNDS_H
#define BOUNDS_H

class Bounds {
private:
  // TODO: add fields
  int m_xmin;
  double m_ymin;
  int m_xmax;
  double m_ymax;

public:
  // TODO: add member functions
  Bounds(int xmin, double ymin, int xmax, double ymax) : 
    m_xmin(xmin), m_ymin(ymin), m_xmax(xmax), m_ymax(ymax) {
  }

  int getXmin();
  double getYmin();
  int getXmax();
  double getYmax();
};

#endif // BOUNDS_H
