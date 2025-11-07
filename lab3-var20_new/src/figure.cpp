#include "figure.h"

namespace figure {

Point::Point(double x, double y) : x(x), y(y) {}

bool operator==(const Point &left_p, const Point &right_p) {
  return std::abs(left_p.x - right_p.x) < EPS &&
         std::abs(left_p.y - right_p.y) < EPS;
}

bool operator!=(const Point &left_p, const Point &right_p) {
  return !(left_p == right_p);
}

std::ostream &operator<<(std::ostream &os, const Point &point) {
  os << point.x << " " << point.y;
  return os;
}

std::istream &operator>>(std::istream &is, Point &point) {
  is >> point.x >> point.y;
  return is;
}

std::ostream &operator<<(std::ostream &os, const Figure &fig) {
  fig.Print(os);
  return os;
}

std::istream &operator>>(std::istream &is, Figure &fig) {
  fig.Read(is);
  return is;
}
} // namespace figure