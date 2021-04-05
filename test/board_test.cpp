#define CONFIG_CATCH_MAIN
#include "catch.hpp"
#include "../src/tetris_board.hpp"

TEST_CASE("Test default board constructor", "[tetris-board]") {
  TetrisBoard test_board;
  REQUIRE(test_board.get_x_offset() == 0);
  REQUIRE(test_board.get_y_offset() == 0);
  REQUIRE(test_board.get_block_dim() == 10);
}


TEST_CASE("Test non-default board constructor", "[tetris-board]") {
  TetrisBoard test_board(10, -13, 4);
  REQUIRE(test_board.get_x_offset() == 10);
  REQUIRE(test_board.get_y_offset() == -13);
  REQUIRE(test_board.get_block_dim() == 4);
}