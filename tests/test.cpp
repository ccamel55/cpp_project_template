#include <catch2/catch_test_macros.hpp>
#include <example_class.hpp>

TEST_CASE("Integers can be added.")
{
    SECTION("negative addition")
    {
        REQUIRE(example_class::add_int(-1, -256) == -257);
    }

    SECTION("positive addition")
    {
        REQUIRE(example_class::add_int(128, 128) == 256);
    }

    SECTION("arithmetic overflow")
    {
        REQUIRE(example_class::add_int(INT32_MAX, 1) == INT32_MIN);
    }
}