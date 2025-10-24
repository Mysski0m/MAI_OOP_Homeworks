#pragma once
#include "figure.h"

namespace figure {
    class Trapezoid : public Figure {
        private:
            Point vertices[TRAPEZVERTICESCNT];
        
        public:
            Trapezoid();

            Trapezoid(const Point& p1, const Point& p2, const Point& p3, const Point& p4);

            Trapezoid(const Trapezoid& other) = default;

            Trapezoid& operator=(const Trapezoid& other) = default;

            Trapezoid(Trapezoid&& other) noexcept = default;

            Trapezoid& operator=(Trapezoid&& other) noexcept = default;

            ~Trapezoid() = default;

            bool operator==(const Trapezoid& other) const;

            bool operator!=(const Trapezoid& other) const;

            Point GeomCenter() const override;

            double Area() const override;

            operator double() const override;

            void Print(std::ostream& os) const override;
            
            void Read(std::istream& is) override;
    };
}