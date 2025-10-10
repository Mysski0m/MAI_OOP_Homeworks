#pragma once

#include "vector.h"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <initializer_list>
#include <string>
#include <utility>

namespace thirteen {
    class Thirteen {
      private:
        vector::Vector arr_;

      public:
        Thirteen();

        Thirteen(const size_t& n, unsigned char t = 0);

        Thirteen(const std::initializer_list<unsigned char>& t);

        Thirteen(const std::string& t);

        Thirteen(const Thirteen& other);

        Thirteen(Thirteen&& other) noexcept;

        ~Thirteen() noexcept;

        static Thirteen Add(const Thirteen& other1, const Thirteen& other2);

        static Thirteen Sub(const Thirteen& other1, const Thirteen& other2);

        static int8_t ToDecimal(const unsigned char value);

        static unsigned char ToThirteen(const int8_t value);

        std::string Show() const;

        void Copy(const Thirteen& other);

        bool GreaterThen(const Thirteen& other) const;

        bool LessThen(const Thirteen& other) const;

        bool Equal(const Thirteen& other) const;
    };
}