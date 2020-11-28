#include <iostream>
#include <string>

#ifndef MATH_VACTOR_H
#define MATH_VACTOR_H

namespace math {
    template<typename TYPE_D = double>
    class vector {
        TYPE_D values[2];
    public:
        constexpr vector(const TYPE_D *values) noexcept {
            for (int i = 0; i < 2; ++i)
                this->values[i] = values;
        }

        constexpr vector(TYPE_D x, TYPE_D y) noexcept {
            values[0] = x;
            values[1] = y;
        }

        constexpr vector() noexcept {
            values[0] = values[1] = 0;
        }

        constexpr vector(const vector<TYPE_D> &v) noexcept {
            for (int i = 0; i < 2; ++i)
                values[i] = v.values[i];
        }

        std::string toString() {
            std::string str("vector<");
            str += std::to_string(values[0]);
            str += ';';
            str += std::to_string(values[1]);
            str += ">";
            return str;
        }

        constexpr TYPE_D &operator[](size_t index) noexcept {
            return values[index];
        }

        constexpr vector<TYPE_D> operator+(const vector<TYPE_D> &v) const {
            return vector<TYPE_D>(values[0] + v.values[0], values[1] + v.values[1]);
        }
        constexpr vector<TYPE_D> operator+(TYPE_D v) const {
            return vector<TYPE_D>(values[0] + v, values[1] + v);
        }
        constexpr vector<TYPE_D> operator-(const vector<TYPE_D> &v) const {
            return vector<TYPE_D>(values[0] - v.values[0], values[1] - v.values[1]);
        }
        constexpr vector<TYPE_D> operator-(TYPE_D v) const {
            return vector<TYPE_D>(values[0] - v, values[1] - v);
        }
        constexpr vector<TYPE_D> operator*(const vector<TYPE_D> &v) const {
            return vector<TYPE_D>(values[0] * v.values[0], values[1] * v.values[1]);
        }
        constexpr vector<TYPE_D> operator*(TYPE_D v) const {
            return vector<TYPE_D>(values[0] * v, values[1] * v);
        }

        constexpr vector<TYPE_D>& operator=(const math::vector<TYPE_D>& vector)
        {
            values[0] = vector.values[0];
            values[1] = vector.values[1];
            return *this;
        }

        constexpr vector<TYPE_D>& operator=(TYPE_D value)
        {
            values[0] = values[1] = value;
            return *this;
        }
    };
}
#endif