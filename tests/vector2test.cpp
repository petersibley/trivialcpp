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
