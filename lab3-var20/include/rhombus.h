#pragma once
#include "figure.h"

namespace figure {
    class Rhombus : public Figure {
        private:
            Point vertices[RHOMBVERTICESCNT];
        
        public:
            Rhombus();

            Rhombus(const Point& p1, const Point& p2, const Point& p3, const Point& p4);

            Rhombus(const Rhombus& other) = default;
            
            Rhombus& operator=(const Rhombus& other) = default;

            Rhombus(Rhombus&& other) noexcept = default;

            Rhombus& operator=(Rhombus&& other) noexcept = default;

            ~Rhombus() = default;

            bool operator==(const Rhombus& other) const;

            bool operator!=(const Rhombus& other) const;

            Point GeomCenter() const override;

            double Area() const override;

            operator double() const override;

            void Print(std::ostream& os) const override;
            
            void Read(std::istream& is) override;
    };
}