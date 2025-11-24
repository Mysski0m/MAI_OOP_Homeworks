#pragma once

#include "figure.h"

namespace figure {

template <Scalar T>
bool operator==(const Point<T> &left_p, const Point<T> &right_p) {
  return std::abs(left_p.x - right_p.x) < EPS &&
         std::abs(left_p.y - right_p.y) < EPS;
}

template <Scalar T>
bool operator!=(const Point<T> &left_p, const Point<T> &right_p) {
  return !(left_p == right_p);
}

template <Scalar T>
std::ostream &operator<<(std::ostream &os, const Point<T> &point) {
  os << point.x << " " << point.y;
  return os;
}

template <Scalar T>
std::istream &operator>>(std::istream &is, Point<T> &point) {
  is >> point.x >> point.y;
  return is;
}

template <Scalar T>
std::ostream &operator<<(std::ostream &os, const Figure<T> &fig) {
  fig.Print(os);
  return os;
}

template <Scalar T> std::istream &operator>>(std::istream &is, Figure<T> &fig) {
  fig.Read(is);
  return is;
}
} // namespace figure