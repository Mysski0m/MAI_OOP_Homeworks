#include "trapezoid.h"

namespace figure {

    Trapezoid::Trapezoid() {
        vertices[0] = Point(0, 0);
        vertices[1] = Point(2, 0);
        vertices[2] = Point(1.5, 1);
        vertices[3] = Point(0, 1);
    }

    Trapezoid::Trapezoid(const Point& p1, const Point& p2, const Point& p3, const Point& p4) {
        vertices[0] = p1;
        vertices[1] = p2;
        vertices[2] = p3;
        vertices[3] = p4;
    }

    Point Trapezoid::GeomCenter() const {
        double x_centr = (vertices[0].x + vertices[1].x + vertices[2].x + vertices[3].x) / TRAPEZVERTICESCNT;
        double y_centr = (vertices[0].y + vertices[1].y + vertices[2].y + vertices[3].y) / TRAPEZVERTICESCNT;
        return Point(x_centr, y_centr);
    }

    double Trapezoid::Area() const {
        double area = 0.0;
        for (size_t i = 0; i < TRAPEZVERTICESCNT; ++i) {
            size_t j = (i + 1) % TRAPEZVERTICESCNT;
            area += vertices[i].x * vertices[j].y;
            area -= vertices[j].x * vertices[i].y;
        }
        return std::abs(area) / 2.0;
    }

    Trapezoid::operator double() const {
        return Area();
    }

    void Trapezoid::Print(std::ostream& os) const {
        for (size_t i = 0; i < TRAPEZVERTICESCNT; ++i) {
            os << "(" << vertices[i] << ")";
            if (i < TRAPEZVERTICESCNT - 1) os << " ";
        }
    }

    void Trapezoid::Read(std::istream& is) {
        for (size_t i = 0; i < TRAPEZVERTICESCNT; ++i) {
            is >> vertices[i];
        }
    }

    bool Trapezoid::operator==(const Trapezoid& other) const {
        for (size_t i = 0; i < TRAPEZVERTICESCNT; ++i) {
            if (!(vertices[i] == other.vertices[i])) return false;
        }
        return true;
    }

    bool Trapezoid::operator!=(const Trapezoid& other) const {
        return !(*this == other);
    }
}