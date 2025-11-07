#include "pentagon.h"

namespace figure {

Pentagon::Pentagon() {
  vertices[0] = Point(1, 0);
  vertices[1] = Point(0.309, 0.951);
  vertices[2] = Point(-0.809, 0.588);
  vertices[3] = Point(-0.809, -0.588);
  vertices[4] = Point(0.309, -0.951);
}

Pentagon::Pentagon(const Point &p1, const Point &p2, const Point &p3,
                   const Point &p4, const Point &p5) {
  vertices[0] = p1;
  vertices[1] = p2;
  vertices[2] = p3;
  vertices[3] = p4;
  vertices[4] = p5;
}

Point Pentagon::GeomCenter() const {
  double x_centr = (vertices[0].x + vertices[1].x + vertices[2].x +
                    vertices[3].x + vertices[4].x) /
                   PENTAG_VERTICES_CNT;
  double y_centr = (vertices[0].y + vertices[1].y + vertices[2].y +
                    vertices[3].y + vertices[4].y) /
                   PENTAG_VERTICES_CNT;
  return Point(x_centr, y_centr);
}

double Pentagon::Area() const {
  double area = 0.0;
  for (size_t i = 0; i < PENTAG_VERTICES_CNT; ++i) {
    size_t j = (i + 1) % PENTAG_VERTICES_CNT;
    area += vertices[i].x * vertices[j].y;
    area -= vertices[j].x * vertices[i].y;
  }
  return std::abs(area) / 2.0;
}

Pentagon::operator double() const { return Area(); }

void Pentagon::Print(std::ostream &os) const {
  os << "Pentagon: ";
  for (size_t i = 0; i < PENTAG_VERTICES_CNT; ++i) {
    os << "(" << vertices[i] << ")";
    if (i < PENTAG_VERTICES_CNT - 1)
      os << " ";
  }
}

void Pentagon::Read(std::istream &is) {
  for (size_t i = 0; i < PENTAG_VERTICES_CNT; ++i) {
    is >> vertices[i];
  }
}

bool Pentagon::operator==(const Pentagon &other) const {
  for (size_t i = 0; i < PENTAG_VERTICES_CNT; ++i) {
    if (!(vertices[i] == other.vertices[i])) {
      return false;
    }
  }
  return true;
}

bool Pentagon::operator!=(const Pentagon &other) const {
  return !(*this == other);
}
} // namespace figure