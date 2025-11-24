#pragma once

#include "trapezoid.h"

#include <memory>

namespace figure {

template <Scalar T> Trapezoid<T>::Trapezoid() {
  vertices = std::make_unique<Point<T>[]>(TRAPEZ_VERTICES_CNT);
  vertices[0] = Point<T>(0, 0);
  vertices[1] = Point<T>(2, 0);
  vertices[2] = Point<T>(1.5, 1);
  vertices[3] = Point<T>(0, 1);
}

template <Scalar T>
Trapezoid<T>::Trapezoid(const Point<T> &p1, const Point<T> &p2,
                        const Point<T> &p3, const Point<T> &p4) {
  vertices = std::make_unique<Point<T>[]>(TRAPEZ_VERTICES_CNT);
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[2] = p3;
  vertices[3] = p4;
}

template <Scalar T> Trapezoid<T>::Trapezoid(const Trapezoid<T> &other) {
  vertices = std::make_unique<Point<T>[]>(TRAPEZ_VERTICES_CNT);
  for (size_t i = 0; i < TRAPEZ_VERTICES_CNT; ++i) {
    vertices[i] = other.vertices[i];
  }
}

template <Scalar T>
Trapezoid<T> &Trapezoid<T>::operator=(const Trapezoid<T> &other) {
  if (this != &other) {
    vertices = std::make_unique<Point<T>[]>(TRAPEZ_VERTICES_CNT);
    for (size_t i = 0; i < TRAPEZ_VERTICES_CNT; ++i) {
      vertices[i] = other.vertices[i];
    }
  }
  return *this;
}

template <Scalar T> Point<T> Trapezoid<T>::GeomCenter() const {
  T div = static_cast<T>(TRAPEZ_VERTICES_CNT);
  T x_centr = (vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x) /
              div;
  T y_centr = (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y) /
              div;
  return Point<T>(x_centr, y_centr);
}

template <Scalar T> double Trapezoid<T>::Area() const {
  double area = 0.0;
  for (size_t i = 0; i < TRAPEZ_VERTICES_CNT; ++i) {
    size_t j = (i + 1) % TRAPEZ_VERTICES_CNT;
    area += vertices[i].x * vertices[j].y;
    area -= vertices[j].x * vertices[i].y;
  }
  return std::abs(area) / 2.0;
}

template <Scalar T> Trapezoid<T>::operator double() const { return Area(); }

template <Scalar T> void Trapezoid<T>::Print(std::ostream &os) const {
  os << "Trapezoid: ";
  for (size_t i = 0; i < TRAPEZ_VERTICES_CNT; ++i) {
    os << "(" << vertices[i] << ")";
    if (i < TRAPEZ_VERTICES_CNT - 1)
      os << " ";
  }
}

template <Scalar T> void Trapezoid<T>::Read(std::istream &is) {
  for (size_t i = 0; i < TRAPEZ_VERTICES_CNT; ++i) {
    is >> vertices[i];
  }
}

template <Scalar T>
bool Trapezoid<T>::operator==(const Trapezoid<T> &other) const {
  for (size_t i = 0; i < TRAPEZ_VERTICES_CNT; ++i) {
    if (!(vertices[i] == other.vertices[i])) {
      return false;
    }
  }
  return true;
}

template <Scalar T>
bool Trapezoid<T>::operator!=(const Trapezoid<T> &other) const {
  return !(*this == other);
}
} // namespace figure