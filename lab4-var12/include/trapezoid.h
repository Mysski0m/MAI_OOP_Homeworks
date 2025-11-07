#pragma once

#include "figure.h"

#include <memory>

namespace figure {
template <Scalar T> class Trapezoid : public Figure<T> {
private:
  std::unique_ptr<Point<T>[]> vertices;

public:
  Trapezoid();

  Trapezoid(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3,
            const Point<T> &p4);

  Trapezoid(const Trapezoid<T> &other);

  Trapezoid<T> &operator=(const Trapezoid<T> &other);

  Trapezoid(Trapezoid<T> &&other) noexcept = default;

  Trapezoid<T> &operator=(Trapezoid<T> &&other) noexcept = default;

  ~Trapezoid() = default;

  bool operator==(const Trapezoid<T> &other) const;

  bool operator!=(const Trapezoid<T> &other) const;

  Point<T> GeomCenter() const override;

  double Area() const override;

  operator double() const override;

  void Print(std::ostream &os) const override;

  void Read(std::istream &is) override;
};
} // namespace figure

#include "trapezoid.ipp"