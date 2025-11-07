#pragma once

#include "rhombus.h"

#include <memory>

namespace figure {

template <Scalar T> Rhombus<T>::Rhombus() {
  vertices = std::make_unique<Point<T>[]>(RHOMB_VERTICES_CNT);
  vertices[0] = Point<T>(0, 0);
  vertices[1] = Point<T>(1, 1);
  vertices[2] = Point<T>(0, 2);
  vertices[3] = Point<T>(-1, 1);
}

template <Scalar T>
Rhombus<T>::Rhombus(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3,
                    const Point<T> &p4) {
  vertices = std::make_unique<Point<T>[]>(RHOMB_VERTICES_CNT);
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[2] = p3;
  vertices[3] = p4;
}

template <Scalar T> Rhombus<T>::Rhombus(const Rhombus<T> &other) {
  vertices = std::make_unique<Point<T>[]>(RHOMB_VERTICES_CNT);
  for (size_t i = 0; i < RHOMB_VERTICES_CNT; ++i) {
    vertices[i] = other.vertices[i];
  }
}

template <Scalar T> Rhombus<T> &Rhombus<T>::operator=(const Rhombus<T> &other) {
  if (this != &other) {
    vertices = std::make_unique<Point<T>[]>(RHOMB_VERTICES_CNT);
    for (size_t i = 0; i < RHOMB_VERTICES_CNT; ++i) {
      vertices[i] = other.vertices[i];
    }
  }
  return *this;
}

template <Scalar T> Point<T> Rhombus<T>::GeomCenter() const {
  T div = static_cast<T>(RHOMB_VERTICES_CNT);
  T x_centr = (vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x) /
              div;
  T y_centr = (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y) /
              div;
  return Point<T>(x_centr, y_centr);
}

template <Scalar T> double Rhombus<T>::Area() const {
  double area = 0.0;
  for (size_t i = 0; i < RHOMB_VERTICES_CNT; ++i) {
    size_t j = (i + 1) % RHOMB_VERTICES_CNT;
    area += vertices[i].x * vertices[j].y;
    area -= vertices[j].x * vertices[i].y;
  }
  return std::abs(area) / 2.0;
}

template <Scalar T> Rhombus<T>::operator double() const { return Area(); }

template <Scalar T> void Rhombus<T>::Print(std::ostream &os) const {
  os << "Rhombus: ";
  for (size_t i = 0; i < RHOMB_VERTICES_CNT; ++i) {
    os << "(" << vertices[i] << ")";
    if (i < RHOMB_VERTICES_CNT - 1)
      os << " ";
  }
}

template <Scalar T> void Rhombus<T>::Read(std::istream &is) {
  for (size_t i = 0; i < RHOMB_VERTICES_CNT; ++i) {
    is >> vertices[i];
  }
}

template <Scalar T> bool Rhombus<T>::operator==(const Rhombus<T> &other) const {
  for (size_t i = 0; i < RHOMB_VERTICES_CNT; ++i) {
    if (!(vertices[i] == other.vertices[i])) {
      return false;
    }
  }
  return true;
}

template <Scalar T> bool Rhombus<T>::operator!=(const Rhombus<T> &other) const {
  return !(*this == other);
}
} // namespace figure