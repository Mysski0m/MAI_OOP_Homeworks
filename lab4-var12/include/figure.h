#pragma once

#include "concepts.hpp"

#include <cmath>
#include <iostream>
#include <memory>

namespace figure {
constexpr const double EPS = 1e-9;
constexpr const int8_t TRAPEZ_VERTICES_CNT = 4;
constexpr const int8_t RHOMB_VERTICES_CNT = 4;
constexpr const int8_t PENTAG_VERTICES_CNT = 5;

template <Scalar T> class Point {
public:
  T x = 0.0;
  T y = 0.0;
  Point() = default;
  Point(T x, T y) : x(x), y(y){}
};

template <Scalar T>
bool operator==(const Point<T> &left_p, const Point<T> &right_p);

template <Scalar T>
bool operator!=(const Point<T> &left_p, const Point<T> &right_p);

template <Scalar T>
std::ostream &operator<<(std::ostream &os, const Point<T> &point);

template <Scalar T> std::istream &operator>>(std::istream &is, Point<T> &point);

template <Scalar T> class Figure {
public:
  virtual Point<T> GeomCenter() const = 0;

  virtual double Area() const = 0;

  virtual operator double() const = 0;

  virtual void Print(std::ostream &os) const = 0;

  virtual void Read(std::istream &is) = 0;

  virtual ~Figure() = default;
};

template <Scalar T>
std::ostream &operator<<(std::ostream &os, const Figure<T> &fig);

template <Scalar T> std::istream &operator>>(std::istream &is, Figure<T> &fig);
} // namespace figure

#include "figure.ipp"