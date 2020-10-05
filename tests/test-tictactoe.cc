#include <tictactoe/tictactoe.h>

#include <catch2/catch.hpp>
#include <string>

using tictactoe::Board;
using tictactoe::BoardState;

TEST_CASE("Invalid string provided to constructor") {
  SECTION("String length is not a perfect square") {
    REQUIRE_THROWS_AS(Board("xxooo"), std::invalid_argument);
  }
  SECTION("String length is 1") {
    REQUIRE_THROWS_AS(Board("o"), std::invalid_argument);
  }
  SECTION("Empty String") {
    REQUIRE_THROWS_AS(Board(""), std::invalid_argument);
  }
}

TEST_CASE("Boards with no winner") {
  SECTION("Full board with no winner") {
    REQUIRE(Board("xxoooxxxo").EvaluateBoard() == BoardState::NoWinner);
  }
  SECTION("Semi-Full board with no winner where X moved last") {
    REQUIRE(Board("O...X.X..").EvaluateBoard() == BoardState::NoWinner);
  }
  SECTION("Semi-Full board with no winner where O moved last") {
    REQUIRE(Board("OXO.X.X.O").EvaluateBoard() == BoardState::NoWinner);
  }
  SECTION("Empty Board") {
    REQUIRE(Board("eeeeeeeee").EvaluateBoard() == BoardState::NoWinner);
  }
}

TEST_CASE("O wins", "[o_wins]") {
  SECTION("Rows", "[row]") {
    SECTION("Row 1", "[row]") {
      REQUIRE(Board("OoOx.x.x.").EvaluateBoard() == BoardState::Owins);
    }
    SECTION("Row 2", "[row]") {
      REQUIRE(Board("x.xooo..x").EvaluateBoard() == BoardState::Owins);
    }
    SECTION("Row 3", "[row]") {
      REQUIRE(Board(".x.x.xooo").EvaluateBoard() == BoardState::Owins);
    }
  }
  SECTION("Columns", "[col]") {
    SECTION("Column 1", "[col]") {
      REQUIRE(Board("ox.o.xo.x").EvaluateBoard() == BoardState::Owins);
    }
    SECTION("Column 2", "[col]") {
      REQUIRE(Board(".oxxo..ox").EvaluateBoard() == BoardState::Owins);
    }
    SECTION("Column 3", "[col]") {
      REQUIRE(Board("xxo..o.xo").EvaluateBoard() == BoardState::Owins);
    }
  }
  SECTION("Diagonals") {
    SECTION("Diagonal 1", "[diagonal]") {
      REQUIRE(Board("ox..ox.xo").EvaluateBoard() == BoardState::Owins);
    }
    SECTION("Diagonal 2", "[diagonal]") {
      REQUIRE(Board("xxo.oxo..").EvaluateBoard() == BoardState::Owins);
    }
  }
}

TEST_CASE("X wins", "[x_wins]") {
  SECTION("Rows", "[row]") {
    SECTION("Row 1", "[row]") {
      REQUIRE(Board("xxxo.oxo.").EvaluateBoard() == BoardState::Xwins);
    }
    SECTION("Row 2", "[row]") {
      REQUIRE(Board(".ooxxxox.").EvaluateBoard() == BoardState::Xwins);
    }
    SECTION("Row 3", "[row]") {
      REQUIRE(Board(".o..o.xxx").EvaluateBoard() == BoardState::Xwins);
    }
  }
  SECTION("Columns", "[col]") {
    SECTION("Column 1", "[col]") {
      REQUIRE(Board("x..x..xoo").EvaluateBoard() == BoardState::Xwins);
    }
    SECTION("Column 2", "[col]") {
      REQUIRE(Board(".x..xoox.").EvaluateBoard() == BoardState::Xwins);
    }
    SECTION("Column 3", "[col]") {
      REQUIRE(Board("xox..xoox").EvaluateBoard() == BoardState::Xwins);
    }
  }
  SECTION("Diagonals") {
    SECTION("Diagonal 1", "[diagonal]") {
      REQUIRE(Board("x.oox...x").EvaluateBoard() == BoardState::Xwins);
    }
    SECTION("Diagonal 2", "[diagonal]") {
      REQUIRE(Board("..xoxox..").EvaluateBoard() == BoardState::Xwins);
    }
  }
}

TEST_CASE("Unreachable Tests") {
  SECTION("More O's than X's") {
    REQUIRE(Board("O...X...O").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("At least 2 more X's than O's") {
    REQUIRE(Board("XXXX..OO.").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("Both players win") {
    REQUIRE(Board("XXX...Ooo").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("All 1 player") {
    REQUIRE(Board("OOOOOOOOO").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("Double Win by one player") {
    REQUIRE(Board("XXXXXXXXXXO.O.O.O.O.O.OOO").EvaluateBoard() ==
            BoardState::UnreachableState);
  }
  SECTION("One move after X wins") {
    REQUIRE(Board("XXX.O.O.O").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("One move after O wins") {
    REQUIRE(Board("OOOXX.X.X").EvaluateBoard() == BoardState::UnreachableState);
  }
  SECTION("Double win on diagonals") {
    REQUIRE(Board("X....X....X....X").EvaluateBoard() ==
            BoardState::UnreachableState);
  }
}