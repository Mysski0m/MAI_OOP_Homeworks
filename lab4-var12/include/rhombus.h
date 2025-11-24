#pragma once

#include "figure.h"

#include <memory>

namespace figure {
template <Scalar T> class Rhombus : public Figure<T> {
private:
  std::unique_ptr<Point<T>[]> vertices;

public:
  Rhombus();

  Rhombus(const Point<T> &p1, const Point<T> &p2, const Point<T> &p3,
          const Point<T> &p4);

  Rhombus(const Rhombus<T> &other);

  Rhombus<T> &operator=(const Rhombus<T> &other);

  Rhombus(Rhombus<T> &&other) noexcept = default;

  Rhombus<T> &operator=(Rhombus<T> &&other) noexcept = default;

  ~Rhombus() = default;

  bool operator==(const Rhombus<T> &other) const;

  bool operator!=(const Rhombus<T> &other) const;

  Point<T> GeomCenter() const override;

  double Area() const override;

  operator double() const override;

  void Print(std::ostream &os) const override;

  void Read(std::istream &is) override;
};
} // namespace figure

#include "rhombus.ipp"