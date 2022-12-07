#ifndef MATH_ARRAY_H
#define MATH_ARRAY_H

#include <iostream>
#include <array>
#include <cassert>

template<typename T, size_t N>
class MathArray {
    private:
        std::array<T, N> data;

        template <typename Iter, size_t... Is>
            constexpr std::array<T, sizeof...(Is)> 
            make_array_from_iterators(Iter first, std::index_sequence<Is...>) {
                return {{first[Is]...}};
            }

        template <size_t ... Is>
            constexpr std::array<T, sizeof...(Is)>
            make_array(T value, std::index_sequence<Is...>) {
                // cast Is to void to remove the warning: unused value
                return {{(static_cast<void>(Is), value)...}};
            }

    public:

        template <typename Iter>
            constexpr explicit MathArray(Iter first, Iter last) noexcept {
                assert(last - first == N); 
                data = make_array_from_iterators(first, std::make_index_sequence<N>{});
            }

        constexpr explicit MathArray(const T& value) noexcept {
            data = make_array(value, std::make_index_sequence<N>());
        }
        
        constexpr explicit MathArray(const std::array<T, N>& array_value) noexcept {
            data = array_value;
        }

        constexpr explicit MathArray() noexcept {
            T value = T(0);
            data = make_array(value, std::make_index_sequence<N>());
        }

        MathArray(MathArray&& another_)         = default;
        MathArray(const MathArray& )            = default;
        MathArray& operator=(const MathArray&)  = default;
        MathArray& operator=(MathArray&&)       = default;
            
        std::array<T, N>& GetData() noexcept {
            return data;
        }

        const std::array<T, N>& GetData() const noexcept {
            return data;
        }
        const T* begin() noexcept {
            return data.begin();
        }

        const T* end() noexcept {
            return data.end();
        }

        const T* cbegin() const {
            return data.cbegin();
        }

        const T* cend() const {
            return data.cend();
        }

        T& operator [] (size_t i) {
            return data[i];
        }

        const T& operator [] (size_t i) const {
            return data.at(i);
        }

        size_t size() const {
            return N;
        }

        constexpr MathArray<T, N> inner_product(MathArray<T, N>& v) const {
            auto tmp = *this;
            for (size_t i = 0; i != N; ++i) {
                tmp[i] *= v[i];
            }
            return tmp;
        }
};

// Output format: (1, 2, 3, 4, 5)
template<typename T, size_t N>
std::ostream& operator << (std::ostream& out, const MathArray<T, N>& v) {
    out << '(';
    for (size_t i = 0; i != N; ++i) {
        if (i > 0) {
            out << ", ";
        }
        out << v[i];
    }
    out << ')';
    return out;
}

template<typename T, size_t N>
constexpr MathArray<T, N>& operator *= (MathArray<T, N>& v, const T& scalar) {
    for (size_t i = 0; i != N; ++i) {
        v[i] *= scalar;
    }
    return v;
}

template<typename T, size_t N>
constexpr MathArray<T, N> operator * (const MathArray<T, N>& v, const T& scalar) {
    auto tmp(v);
    tmp *= scalar;
    return tmp;
}

template<typename T, size_t N>
constexpr MathArray<T, N> operator * (const T& scalar, const MathArray<T, N>& v) {
    return v * scalar;
}

template<typename T, size_t N>
constexpr MathArray<T, N>& operator += (MathArray<T, N>& v1, const MathArray<T, N>& v2) {
    for (size_t i = 0; i != N; ++i) {
        v1[i] += v2[i];
    }
    return v1;
}

template<typename T, size_t N>
constexpr MathArray<T, N>& operator -= (MathArray<T, N>& v1, const MathArray<T, N>& v2) {
    for (size_t i = 0; i != N; ++i) {
        v1[i] -= v2[i];
    }
    return v1;
}

template<typename T, size_t N>
constexpr MathArray<T, N> operator + (const MathArray<T, N>& v1, const MathArray<T, N>& v2) {
    MathArray<T, N> tmp = v1;
    tmp += v2;
    return tmp;
}

template<typename T, size_t N>
constexpr MathArray<T, N> operator - (const MathArray<T, N>& v1, const MathArray<T, N>& v2) {
    MathArray<T, N> tmp = v1;
    tmp -= v2;
    return tmp;
}

template<typename T, size_t N>
constexpr bool operator == (const MathArray<T, N>& v1, const MathArray<T, N>& v2) {
    for (size_t i = 0; i != N; ++i) {
        if (v1[i] != v2[i]) {
            return false;
        }
    }
    return true;
}

#endif // MATH_ARRAY_H
