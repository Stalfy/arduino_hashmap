#include "catch.hpp"

#include "hashmap.hpp"
#include "iostream"

TEST_CASE("Constructor Tests.", "[hashmap]") {
    HashMap hmap(3);

    REQUIRE(0 == hmap.getSize());
    REQUIRE(3 == hmap.getBuckets());
}
