#include "rhombus.h"

namespace figure {

Rhombus::Rhombus() {
  vertices[0] = Point(0, 0);
  vertices[1] = Point(1, 1);
  vertices[2] = Point(0, 2);
  vertices[3] = Point(-1, 1);
}

Rhombus::Rhombus(const Point &p1, const Point &p2, const Point &p3,
                 const Point &p4) {
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[2] = p3;
  vertices[3] = p4;
}

Point Rhombus::GeomCenter() const {
  double x_centr =
      (vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x) /
      RHOMB_VERTICES_CNT;
  double y_centr =
      (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y) /
      RHOMB_VERTICES_CNT;
  return Point(x_centr, y_centr);
}

double Rhombus::Area() const {
  double area = 0.0;
  for (size_t i = 0; i < RHOMB_VERTICES_CNT; ++i) {
    size_t j = (i + 1) % RHOMB_VERTICES_CNT;
    area += vertices[i].x * vertices[j].y;
    area -= vertices[j].x * vertices[i].y;
  }
  return std::abs(area) / 2.0;
}

Rhombus::operator double() const { return Area(); }

void Rhombus::Print(std::ostream &os) const {
  os << "Rhombus: ";
  for (size_t i = 0; i < RHOMB_VERTICES_CNT; ++i) {
    os << "(" << vertices[i] << ")";
    if (i < RHOMB_VERTICES_CNT - 1)
      os << " ";
  }
}

void Rhombus::Read(std::istream &is) {
  for (size_t i = 0; i < RHOMB_VERTICES_CNT; ++i) {
    is >> vertices[i];
  }
}

bool Rhombus::operator==(const Rhombus &other) const {
  for (size_t i = 0; i < RHOMB_VERTICES_CNT; ++i) {
    if (!(vertices[i] == other.vertices[i])) {
      return false;
    }
  }
  return true;
}

bool Rhombus::operator!=(const Rhombus &other) const {
  return !(*this == other);
}
} // namespace figure