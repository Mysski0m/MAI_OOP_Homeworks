#pragma once

#include <cmath>
#include <iostream>

namespace figure {
constexpr const double EPS = 1e-9;
constexpr const int8_t TRAPEZ_VERTICES_CNT = 4;
constexpr const int8_t RHOMB_VERTICES_CNT = 4;
constexpr const int8_t PENTAG_VERTICES_CNT = 5;
class Point {
public:
  double x = 0.0;
  double y = 0.0;
  Point() = default;
  Point(double x, double y);
};

bool operator==(const Point &left_p, const Point &right_p);
bool operator!=(const Point &left_p, const Point &right_p);
std::ostream &operator<<(std::ostream &os, const Point &point);
std::istream &operator>>(std::istream &is, Point &point);

class Figure {
public:
  virtual Point GeomCenter() const = 0;

  virtual double Area() const = 0;

  virtual operator double() const = 0;

  virtual void Print(std::ostream &os) const = 0;

  virtual void Read(std::istream &is) = 0;

  virtual ~Figure() = default;
};

std::ostream &operator<<(std::ostream &os, const Figure &fig);
std::istream &operator>>(std::istream &is, Figure &fig);
} // namespace figure