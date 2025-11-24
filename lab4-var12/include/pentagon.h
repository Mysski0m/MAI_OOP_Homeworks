#pragma once

#include "figure.h"

#include <memory>

namespace figure {
template<Scalar T> class Pentagon : public Figure<T> {
private:
  std::unique_ptr<Point<T>[]> vertices;

public:
  Pentagon();

  Pentagon(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3,
           const Point<T> &p4, const Point<T> &p5);

  Pentagon(const Pentagon<T> &other);

  Pentagon<T> &operator=(const Pentagon<T> &other);

  Pentagon(Pentagon<T> &&other) noexcept = default;

  Pentagon<T> &operator=(Pentagon<T> &&other) noexcept = default;

  ~Pentagon() = default;

  bool operator==(const Pentagon<T> &other) const;

  bool operator!=(const Pentagon<T> &other) const;

  Point<T> GeomCenter() const override;

  double Area() const override;

  operator double() const override;

  void Print(std::ostream &os) const override;

  void Read(std::istream &is) override;
};
} // namespace figure

#include "pentagon.ipp"