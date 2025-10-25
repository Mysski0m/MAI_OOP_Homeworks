#pragma once
#include "figure.h"
 
namespace figure {
    class Pentagon : public Figure {
        private:
            Point vertices[PENTAGVERTICESCNT];
        
        public:
            Pentagon();

            Pentagon(const Point& p1, const Point& p2, const Point& p3, const Point& p4, const Point& p5);

            Pentagon(const Pentagon& other) = default;

            Pentagon& operator=(const Pentagon& other) = default;

            Pentagon(Pentagon&& other) noexcept = default;

            Pentagon& operator=(Pentagon&& other) noexcept = default;

            ~Pentagon() = default;

            bool operator==(const Pentagon& other) const;

            bool operator!=(const Pentagon& other) const;

            Point GeomCenter() const override;

            double Area() const override;

            operator double() const override;

            void Print(std::ostream& os) const override;
            
            void Read(std::istream& is) override;
    };
}