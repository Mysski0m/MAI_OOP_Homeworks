#pragma once

#include "pentagon.h"

#include <memory>

namespace figure {

template <Scalar T> Pentagon<T>::Pentagon() {
  vertices = std::make_unique<Point<T>[]>(PENTAG_VERTICES_CNT);
  vertices[0] = Point<T>(1, 0);
  vertices[1] = Point<T>(0.309, 0.951);
  vertices[2] = Point<T>(-0.809, 0.588);
  vertices[3] = Point<T>(-0.809, -0.588);
  vertices[4] = Point<T>(0.309, -0.951);
}

template <Scalar T>
Pentagon<T>::Pentagon(const Point<T> &p1, const Point<T> &p2,
                      const Point<T> &p3, const Point<T> &p4,
                      const Point<T> &p5) {
  vertices = std::make_unique<Point<T>[]>(PENTAG_VERTICES_CNT);
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[2] = p3;
  vertices[3] = p4;
  vertices[4] = p5;
}

template <Scalar T> Pentagon<T>::Pentagon(const Pentagon<T> &other) {
  vertices = std::make_unique<Point<T>[]>(PENTAG_VERTICES_CNT);
  for (size_t i = 0; i < PENTAG_VERTICES_CNT; ++i) {
    vertices[i] = other.vertices[i];
  }
}

template <Scalar T>
Pentagon<T> &Pentagon<T>::operator=(const Pentagon<T> &other) {
  if (this != &other) {
    vertices = std::make_unique<Point<T>[]>(PENTAG_VERTICES_CNT);
    for (size_t i = 0; i < PENTAG_VERTICES_CNT; ++i) {
      vertices[i] = other.vertices[i];
    }
  }
  return *this;
}

template <Scalar T> Point<T> Pentagon<T>::GeomCenter() const {
  T div = static_cast<T>(PENTAG_VERTICES_CNT);
  T x_centr = (vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x +
               vertices[4].x) /
              div;
  T y_centr = (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y +
               vertices[4].y) /
              div;
  return Point<T>(x_centr, y_centr);
}

template <Scalar T> double Pentagon<T>::Area() const {
  double area = 0.0;
  for (size_t i = 0; i < PENTAG_VERTICES_CNT; ++i) {
    size_t j = (i + 1) % PENTAG_VERTICES_CNT;
    area += vertices[i].x * vertices[j].y;
    area -= vertices[j].x * vertices[i].y;
  }
  return std::abs(area) / 2.0;
}

template <Scalar T> Pentagon<T>::operator double() const { return Area(); }

template <Scalar T> void Pentagon<T>::Print(std::ostream &os) const {
  os << "Pentagon: ";
  for (size_t i = 0; i < PENTAG_VERTICES_CNT; ++i) {
    os << "(" << vertices[i] << ")";
    if (i < PENTAG_VERTICES_CNT - 1)
      os << " ";
  }
}

template <Scalar T> void Pentagon<T>::Read(std::istream &is) {
  for (size_t i = 0; i < PENTAG_VERTICES_CNT; ++i) {
    is >> vertices[i];
  }
}

template <Scalar T>
bool Pentagon<T>::operator==(const Pentagon<T> &other) const {
  for (size_t i = 0; i < PENTAG_VERTICES_CNT; ++i) {
    if (!(vertices[i] == other.vertices[i])) {
      return false;
    }
  }
  return true;
}

template <Scalar T>
bool Pentagon<T>::operator!=(const Pentagon<T> &other) const {
  return !(*this == other);
}
} // namespace figure