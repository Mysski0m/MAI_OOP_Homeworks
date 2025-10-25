#include "vector.h"
 

namespace vector {
    const int8_t START_MEMORY_ALLOCATE = 10;

    Vector::Vector() : sz_(0), cap_(0), arr_(nullptr) {}

    Vector::Vector(std::initializer_list<figure::Figure*> init) : sz_(init.size()), cap_(init.size()) {
        arr_ = new figure::Figure*[init.size()];
        size_t i = 0;
        for (figure::Figure* fig : init) {
            arr_[i] = fig;
            ++i;
        }
    }

    figure::Figure& Vector::operator[](size_t pos) {
        return *arr_[pos];
    }

    const figure::Figure& Vector::operator[](size_t pos) const {
        return *arr_[pos];
    }

    figure::Figure& Vector::Front() const noexcept {
        return *arr_[0];
    }

    bool Vector::IsEmpty() const noexcept {
        return sz_ == 0;
    }

    figure::Figure& Vector::Back() const noexcept {
        return *arr_[sz_ - 1];
    }

    figure::Figure** Vector::Data() const noexcept {
        return arr_;
    }

    size_t Vector::Size() const noexcept {
        return sz_;
    }

    size_t Vector::Capacity() const noexcept {
        return cap_;
    }

    void Vector::Reserve(size_t new_cap) {
        if (new_cap <= cap_) {
            return;
        }
        figure::Figure** new_arr = new figure::Figure*[new_cap];
        for (size_t i = 0; i < sz_; i++) {
            new_arr[i] = arr_[i];
        }
        delete[] arr_;
        arr_ = new_arr;
        cap_ = new_cap;
    }

    void Vector::Clear() noexcept {
        delete[] arr_;
        arr_ = nullptr;
        sz_ = 0;
    }

    void Vector::Insert(size_t pos, figure::Figure* value) {
        if (cap_ == sz_) {
            Reserve(cap_ == 0 ? START_MEMORY_ALLOCATE : cap_ * 2);
        }
        for (size_t i = sz_ - 1; i > pos; --i) {
            arr_[i] = arr_[i - 1];
        }
        arr_[pos] = value;
        ++sz_;
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

    void Vector::Erase(size_t pos) {
        Erase(pos, pos + 1);
    }

    void Vector::PushBack(figure::Figure* value) {
        if (cap_ == 0) {
            Reserve(START_MEMORY_ALLOCATE);
        }
        if (cap_ == sz_) {
            Reserve(2 * cap_);
        }
        arr_[sz_] = value;
        ++sz_;
    }

    void Vector::PopBack() {
        if (sz_ == 0) return;
        delete arr_[sz_ - 1];
        --sz_;
    }

    double Vector::TotalArea() const {
        double total = 0.0;
        for (size_t i = 0; i < sz_; ++i) {
            total += arr_[i]->Area();
        }
        return total;
    }

    void Vector::PrintAllCenters() const {
        for (size_t i = 0; i < sz_; ++i) {
            std::cout << "Центр фигуры " << (i + 1) << ": " << arr_[i]->GeomCenter() << std::endl;
        }
    }

    void Vector::PrintAllAreas() const {
        for (size_t i = 0; i < sz_; ++i) {
            std::cout << "Площадь фигуры " << (i + 1) << ": " << arr_[i]->Area() << std::endl;
        }
    }

    Vector::~Vector() {
        delete[] arr_;
    }
}