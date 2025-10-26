#pragma once

#include <stdexcept>
#include <string>

namespace exceptions {
class InvalidIndex : std::runtime_error {
public:
  explicit InvalidIndex(const std::string &text) : std::runtime_error(text) {}
};

class VectorIsNull : std::runtime_error {
public:
  explicit VectorIsNull(const std::string &text) : std::runtime_error(text) {}
};
} // namespace exceptions