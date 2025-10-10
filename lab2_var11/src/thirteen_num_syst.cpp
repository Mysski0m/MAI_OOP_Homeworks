#include "thirteen_num_syst.h"
#include "exceptions.h"

namespace thirteen {

    Thirteen::Thirteen(): arr_(vector::Vector(1, 0)) {}

    Thirteen::Thirteen(const size_t& n, unsigned char t): arr_(vector::Vector(n, t)) {}

    Thirteen::Thirteen(const std::initializer_list<unsigned char>& t): arr_(vector::Vector(t.size(), 0)) {
        size_t i = t.size() - 1;
        for (unsigned char c: t) {
            arr_.Get(i) = c;
            --i;
        }

        while (arr_.Size() > 1 && arr_.Back() == 0) {
            arr_.PopBack();
        }
    }

    Thirteen::Thirteen(const std::string& t): arr_(vector::Vector()) {
        if (t.empty()) {
            arr_.PushBack(0);
            return;
        }

        for (int64_t i = t.size() - 1; i >= 0; --i) {
            char cur = t[i];
            if ((cur > '9' || cur < '0') && (cur != 'A' && cur != 'B' && cur != 'C')) {
                throw exception::ExceptionNull("Not a number");
            }
            if (cur == 'A') {
                arr_.PushBack(10);
            } else if (cur == 'B') {
                arr_.PushBack(11);
            } else if (cur == 'C') {
                arr_.PushBack(12);
            } else {
                arr_.PushBack(cur - '0');
            }
        }
        while (arr_.Size() > 1 && arr_.Back() == 0) {
            arr_.PopBack();
        }
    }

    Thirteen::Thirteen(const Thirteen& other): arr_(other.arr_) {}

    Thirteen::Thirteen(Thirteen&& other) noexcept: arr_(std::move(other.arr_)) {}

    Thirteen::~Thirteen() noexcept {
        arr_.Clear();
    }

    Thirteen Thirteen::Add(const Thirteen& other1, const Thirteen& other2) {
        Thirteen result;
        result.arr_.PopBack();
        unsigned char mind_sum = 0;
        unsigned char sum;
        size_t max_size = std::max(other1.arr_.Size(), other2.arr_.Size()) + 1;

        for (size_t i = 0; i < max_size || mind_sum != 0; ++i) {
            sum = mind_sum;
            if (i < other1.arr_.Size()) {
                sum += other1.arr_.Get(i);
            }
            if (i < other2.arr_.Size()) {
                sum += other2.arr_.Get(i);
            }
            result.arr_.PushBack(sum % 13);
            mind_sum = sum / 13;
        }

        while (result.arr_.Size() > 1 && result.arr_.Back() == 0) {
            result.arr_.PopBack();
        }

        return result;
    }

    Thirteen Thirteen::Sub(const Thirteen& other1, const Thirteen& other2) {
        if (other1.LessThen(other2)) {
            throw exception::NegativeException("Negative answer: first number shouldn't be less than second.");
        }

        if (other1.Equal(other2)) {
            return Thirteen();
        }

        Thirteen result;
        result.Copy(other1);
        int8_t bor = 0;

        for (size_t i = 0; i < result.arr_.Size(); ++i) {
            int8_t first = static_cast<int8_t>(result.arr_.Get(i));
            int8_t second = (i < other2.arr_.Size()) ? static_cast<int8_t>(other2.arr_.Get(i)) : 0;
            first -= bor;
            if (first < second) {
                result.arr_.Get(i) = static_cast<unsigned char>(first + 13 - second);
                bor = 1;
            } else {
                result.arr_.Get(i) = static_cast<unsigned char>(first - second);
                bor = 0;
            }
        }

        while (result.arr_.Size() > 1 && result.arr_.Back() == 0) {
            result.arr_.PopBack();
        }

        return result;
    }

    void Thirteen::Copy(const Thirteen& other) {
        arr_.Copy(other.arr_);
    }

    std::string Thirteen::Show() const {
        if (arr_.Size() == 0) {
            return "0";
        }
        std::string num;
        for (int64_t i = arr_.Size() - 1; i >= 0; --i) {
            num += Thirteen::ToThirteen(arr_.Get(i));
        }
        return num;
    }

    int8_t Thirteen::ToDecimal(const unsigned char value) {
        if (value >= '0' && value <= '9') {
            return value - '0';
        } else if (value == 'A') {
            return 10;
        } else if (value == 'B') {
            return 11;
        } else if (value == 'C') {
            return 12;
        }
        return 0;
    }

    unsigned char Thirteen::ToThirteen(const int8_t value) {
        if (value < 10) {
            return '0' + static_cast<unsigned char>(value);
        } else {
            return 'A' + static_cast<unsigned char>(value - 10);
        }
    }

    bool Thirteen::GreaterThen(const Thirteen& other) const {
        if (arr_.Size() > other.arr_.Size()) {
            return true;
        } else if (arr_.Size() < other.arr_.Size()) {
            return false;
        }

        for (int64_t i = arr_.Size() - 1; i >= 0; --i) {
            if (arr_.Get(i) > other.arr_.Get(i)) {
                return true;
            } else if (arr_.Get(i) < other.arr_.Get(i)) {
                return false;
            }
        }
        
        return false;
    }

    bool Thirteen::LessThen(const Thirteen& other) const {
        if (arr_.Size() > other.arr_.Size()) {
            return false;
        } else if (arr_.Size() < other.arr_.Size()) {
            return true;
        }

        for (int64_t i = arr_.Size() - 1; i >= 0; --i) {
            if (arr_.Get(i) > other.arr_.Get(i)) {
                return false;
            } else if (arr_.Get(i) < other.arr_.Get(i)) {
                return true;
            }
        }
        
        return false;
    }

    bool Thirteen::Equal(const Thirteen& other) const {
        if (arr_.Size() != other.arr_.Size()) {
            return false;
        }

        for (int64_t i = arr_.Size() - 1; i >= 0; --i) {
            if (arr_.Get(i) != other.arr_.Get(i)) {
                return false;
            }
        }
        
        return true;
    }
}