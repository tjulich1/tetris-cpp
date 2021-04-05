#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "../src/block.hpp"

TEST_CASE("Test block", "[tetris]") {
  Block test_block{1, 2};
  REQUIRE(test_block.x == 1);
  REQUIRE(test_block.y == 2);
}
