#include "catch.hpp"
#include <elm/Vector2f.h>

using namespace fiftythree::elm;

TEST_CASE("Can create vector","[vector2f]") {

    // make sure default ctors do something sane
    auto v = Vector2f();

    // ensure initializer syntax works
    auto w = Vector2f{1.0f,1.0f};

    // ensure assignment operator is invokable
    v = w;
    REQUIRE(v.x() == 1.0f);
    REQUIRE(v.y() == 1.0f);
}

TEST_CASE("Static members","[vector2f]") {

    // make sure default ctors do something sane
    auto x = Vector2f::UnitX();
    REQUIRE(x.x() == 1.0f);
    REQUIRE(x.y() == 0.0f);

    auto y = Vector2f::UnitY();
    REQUIRE(y.x() == 0.0f);
    REQUIRE(y.y() == 1.0f);

    auto z = Vector2f::Zero();
    REQUIRE(z.x() == 0.0f);
    REQUIRE(z.y() == 0.0f);

    auto ones = Vector2f::Ones();
    REQUIRE(ones.x() == 1.0f);
    REQUIRE(ones.y() == 1.0f);
}


TEST_CASE("[]","[vector2f]") {

    // make sure default ctors do something sane
    auto x = Vector2f{0.0,0.0};
    x[0] = 1.0f;
    REQUIRE(x.x() == 1.0f);
    REQUIRE(x.y() == 0.0f);
    //makesure const version plays nicely
    x[1] = 10.0f;
    const auto y = x; 
    const auto & xY = y[1];
    REQUIRE(xY == 10.0f);
}

TEST_CASE("op + assign","[vector2f]") {

    // make sure default ctors do something sane
    auto x = Vector2f{0.0,-1.0};
    auto y = Vector2f{4.0,5.0};
    y += x; 
    REQUIRE(y.x() == 4.0);
    REQUIRE(y.y() == 4.0);
    x -= y; 

    REQUIRE(x.x() == -4.0);
    REQUIRE(x.y() == -5.0);

    x *= 2.0f;

    REQUIRE(x.x() == -8.0);
    REQUIRE(x.y() == -10.0);

    x /= 2.0f;

    REQUIRE(x.x() == -4.0);
    REQUIRE(x.y() == -5.0);

    auto z = x + Vector2f{3,3}; 
    REQUIRE(z.x() == -1.0);
    REQUIRE(z.y() == -2.0);

    z = x - Vector2f{1.0,2.0};
    REQUIRE(z.x() == -5.0);
    REQUIRE(z.y() == -7.0);
}
TEST_CASE("memfun","[vector2f]") {

    {
    // make sure default ctors do something sane
    auto x = Vector2f{0.0,1.0};
    auto y = Vector2f{0.0,0.5};

    auto d = x.dot(y);
    REQUIRE(d == 0.5);
    auto n = y.norm();
    REQUIRE(n == 0.5);
    }
    {
    auto x = Vector2f{100.0,0.0};
    x.normalize();
    REQUIRE(x.norm() == 1.0);
    auto x2 = Vector2f{100.0,0.0};
    auto z = x2.normalized();
    REQUIRE(x2.norm() == 100.0);
    REQUIRE(z.norm() == 1.0);
    }

    {
        auto x = Vector2f{2.0,2.0};
        auto y = Vector2f{1.0, 2.0};
        auto z = x.cwiseProduct(y);
        REQUIRE(z.x() == 2.0);
        REQUIRE(z.y() == 4.0);
        z = z.cwiseQuotient(x);
        REQUIRE(z.x() == 1.0);
        REQUIRE(z.y() == 2.0);
        z = x.cwiseMin(y); 
        REQUIRE(z.x() == 1.0); 
        REQUIRE(z.y() == 2.0);
        z = x.cwiseMax(y);
        REQUIRE(z.x() == 2.0); 
        REQUIRE(z.y() == 2.0);
    }
    {
        auto x = Vector2f{-1.0,2.0};
        REQUIRE(x.cwiseAbs().x() == 1.0);
        REQUIRE(x.cwiseAbs().y() == 2.0);
    }
    {
        auto x = Vector2f{4.0, 16.0};
        REQUIRE(x.cwiseSqrt().x() == 2.0);
        REQUIRE(x.cwiseSqrt().y() == 4.0);
    }
    {
        auto x = Vector2f{4.0, 16.0};
        REQUIRE(x.minCoeff() == 4.0);
        REQUIRE(x.maxCoeff() == 16.0);
    }



}




