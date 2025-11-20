#include "vector.h"

namespace vector {
const int8_t START_MEMORY_ALLOCATE = 10;

Vector::Vector() {
  arr_ = nullptr;
  sz_ = 0;
  cap_ = 0;
}

Vector::Vector(size_t count, unsigned char value) {
  arr_ = nullptr;
  sz_ = 0;
  cap_ = 0;
  for (size_t i = 0; i < count; ++i) {
    PushBack(value);
  }
}

Vector::Vector(const Vector &other) {
  arr_ = nullptr;
  sz_ = 0;
  cap_ = 0;
  for (size_t i = 0; i < other.sz_; ++i) {
    PushBack(other.arr_[i]);
  }
}

Vector &Vector::Copy(const Vector &other) {
  if (&other == this) {
    return *this;
  }
  Vector cur = other;
  Swap(cur);
  return *this;
}

Vector::Vector(Vector &&other) noexcept {
  arr_ = other.arr_;
  sz_ = other.sz_;
  cap_ = other.cap_;
  other.arr_ = nullptr;
  other.sz_ = 0;
  other.cap_ = 0;
}

Vector::Vector(std::initializer_list<unsigned char> init) {
  arr_ = nullptr;
  sz_ = 0;
  cap_ = 0;
  for (const auto &value : init) {
    PushBack(value);
  }
}

unsigned char &Vector::Get(size_t pos) { return arr_[pos]; }

unsigned char Vector::Get(size_t pos) const { return arr_[pos]; }

unsigned char &Vector::Front() const noexcept { return arr_[0]; }

bool Vector::IsEmpty() const noexcept { return sz_ == 0; }

unsigned char &Vector::Back() const noexcept { return arr_[sz_ - 1]; }

unsigned char *Vector::Data() const noexcept { return arr_; }

size_t Vector::Size() const noexcept { return sz_; }

size_t Vector::Capacity() const noexcept { return cap_; }

void Vector::Reserve(size_t new_cap) {
  if (new_cap <= cap_) {
    return;
  }
  unsigned char *new_arr =
      reinterpret_cast<unsigned char *>(new int8_t[new_cap]);
  for (size_t i = 0; i < sz_; i++) {
    new (new_arr + i) unsigned char(std::move(arr_[i]));
  }
  delete[] reinterpret_cast<int8_t *>(arr_);
  arr_ = new_arr;
  cap_ = new_cap;
}

void Vector::Clear() noexcept {
  delete[] reinterpret_cast<int8_t *>(arr_);
  arr_ = nullptr;
  sz_ = 0;
}

void Vector::Insert(size_t pos, unsigned char value) {
  if (cap_ == 0) {
    Reserve(START_MEMORY_ALLOCATE);
  }
  if (cap_ < sz_ + 1) {
    Reserve(2 * cap_);
  }
  PushBack(Back());
  for (size_t i = sz_ - 1; i > pos; --i) {
    arr_[i] = arr_[i - 1];
  }
  arr_[pos] = value;
}

void Vector::Erase(size_t begin_pos, size_t end_pos) {
  if (end_pos > sz_) {
    return;
  }
  for (size_t i = end_pos; i < sz_; ++i) {
    arr_[i - (end_pos - begin_pos)] = arr_[i];
  }
  for (size_t i = begin_pos; i < end_pos; ++i) {
    PopBack();
  }
}

void Vector::PushBack(unsigned char value) {
  if (cap_ == 0) {
    Reserve(START_MEMORY_ALLOCATE);
  }
  if (cap_ == sz_) {
    Reserve(2 * cap_);
  }
  new (arr_ + sz_) unsigned char(std::move(value));
  ++sz_;
}

void Vector::PopBack() { --sz_; }

void Vector::Resize(size_t count, const unsigned char &value) {
  if (count > cap_) {
    Reserve(count);
  }
  for (size_t i = sz_; i < count; ++i) {
    new (arr_ + i) unsigned char(std::move(value));
  }
  sz_ = count;
}

Vector::~Vector() { delete[] reinterpret_cast<int8_t *>(arr_); }
} // namespace vector