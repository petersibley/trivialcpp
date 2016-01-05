#include <iostream>
#include <vector>
#include <exception>
#include <cmath>
#include <algorithm>
#include <functional>
#include <numeric>
#include <type_traits>


using namespace std;


template <typename Scalar, size_t N>
class Array {

    Scalar _data[N];

    public:

    Array() = default;
    Array(const Array &) = default;
    Array(Array &&) = default;

    // ctors

    // generic ctor w/ initializer lists.
    Array(std::initializer_list<Scalar> v)  noexcept :_data(v) {
        static_assert(N == v.size(), "Arity of ctor must match type");
    }
    // You could use enable_if and SFINEA to do this 
    // 4 cases are easy enough to enumerate and static_if provides more readable error message at the cost of method bloat.
    constexpr Array(Scalar v0) noexcept {
        static_assert(N == 1, "member wise convince functions only work with correct dimension template paramters");
        _data[0] = v0;
    };


    constexpr Array(Scalar v0, Scalar v1) noexcept {
        static_assert(N == 2, "member wise convince functions only work with correct dimension template paramters");
        _data[0] = v0;
        _data[1] = v1;
    };

    constexpr Array(Scalar v0, Scalar v1, Scalar v2) noexcept {
        static_assert(N == 3, "member wise convince functions only work with correct dimension template paramters");
        _data[0] = v0;
        _data[1] = v1;
        _data[2] = v2;
    };

    constexpr Array(Scalar v0, Scalar v1, Scalar v2, Scalar v3) noexcept {
        static_assert(N == 3, "member wise convince functions only work with correct dimension template paramters");
        _data[0] = v0;
        _data[1] = v1;
        _data[2] = v2;
        _data[3] = v3;
    };




    // You could use enable_if and SFINEA to do this 
    // 4 cases are easy enough to enumerate and static_if provides more readable error message at the cost of method bloat.
    Scalar& x() noexcept {
        static_assert(N >= 1 && N <= 4, "member wise convince functions only work with correct dimension template paramters");
        return _data[0];
    }

    Scalar& y() noexcept {
        static_assert(N >= 2 && N <= 4, "member wise convince functions only work with correct dimension template paramters");
        return _data[1];
    }

    Scalar& z() noexcept {
        static_assert(N >= 3 && N <= 4, "member wise convince functions only work with correct dimension template paramters");
        return _data[2];
    }

    Scalar& w() noexcept {
        static_assert(N >= 4 && N <= 4, "member wise convince functions only work with correct dimension template paramters");
        return _data[3];
    }

    constexpr Scalar x() const noexcept  {
        static_assert(N >= 1 && N <= 4, "member wise convince functions only work with correct dimension template paramters");
        return _data[0];
    }

    constexpr Scalar y() const noexcept  {
        static_assert(N >= 2 && N <= 4, "member wise convince functions only work with correct dimension template paramters");
        return _data[1];
    }

    constexpr Scalar z() const noexcept  {
        static_assert(N >= 3 && N <= 4, "member wise convince functions only work with correct dimension template paramters");
        return _data[2];
    }

    constexpr Scalar w() const noexcept  {
        static_assert(N >= 4 && N <= 4, "member wise convince functions only work with correct dimension template paramters");
        return _data[3];
    }

    inline static constexpr Array Zeros() noexcept {
        return Constant(0);
    }

    inline static constexpr Array Ones() noexcept {
        return Constant(1);
    }

    inline static constexpr Array Constant(Scalar s) noexcept {
        Array v;
        for(size_t i = 0; i < N; ++i) {
            v._data[i] = s;
        }
        return v;
    }

};

int main(int argc, char** argv)
{
    try
    {
        //Go!
        auto a = Array<float, 1>{};
        auto x = a.x();
       //  a.y() ;//illeage.
        auto b = Array<float, 2>{};
        auto y = b.y();
        b.x() = 2.0f;
        auto c = Array<float, 2>::Zeros();
    }
    catch (std::exception & e)
    {
        cerr << "unexpected exception:" << e.what() << endl;
    }
    

    return 0;
}
