#pragma once

#include "exceptions.h"
#include "figure.h"

#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <iostream>
#include <string>
#include <utility>

namespace vector {
const int8_t START_CAPACITY = 10;

class Vector {
public:
  Vector();

  Vector(std::initializer_list<figure::Figure *> init);

  figure::Figure &operator[](size_t pos);

  const figure::Figure &operator[](size_t pos) const;

  figure::Figure &Front() const noexcept;

  figure::Figure &Back() const noexcept;

  figure::Figure **Data() const noexcept;

  bool IsEmpty() const noexcept;

  size_t Size() const noexcept;

  size_t Capacity() const noexcept;

  void Reserve(size_t new_cap);

  void Clear() noexcept;

  void Insert(size_t pos, figure::Figure *value);

  void Erase(size_t begin_pos, size_t end_pos);

  void Erase(size_t pos);

  void PushBack(figure::Figure *value);

  void PopBack();

  double TotalArea() const;

  void PrintAllCenters() const;

  void swap(Vector &other) noexcept {
    std::swap(other.arr_, arr_);
    std::swap(other.sz_, sz_);
    std::swap(other.cap_, cap_);
  }

  void PrintAllAreas() const;

  ~Vector();

private:
  figure::Figure **arr_;
  size_t sz_;
  size_t cap_;
};

inline void swap(Vector &left, Vector &right) noexcept { left.swap(right); }
} // namespace vector

namespace std {
template <>
inline void swap<vector::Vector>(vector::Vector &left,
                                 vector::Vector &right) noexcept {
  vector::swap(left, right);
}
} // namespace std