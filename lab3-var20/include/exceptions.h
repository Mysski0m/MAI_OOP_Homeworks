#pragma once

#include <stdexcept>
#include <string>

namespace exception {
    class InvalidPointException: std::runtime_error {
    public:
        explicit InvalidPointException(const std::string& text):
            std::runtime_error(text) {}
    };
}