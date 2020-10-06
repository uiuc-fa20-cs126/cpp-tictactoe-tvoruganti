#include "tictactoe/tictactoe.h"

#include <stdexcept>
#include <cmath>
#include <string>
#include <algorithm>

namespace tictactoe {

using std::string;

Board::Board(const string &board) {
  //tic tac toe board must have a length of at least 1 for a the smallest 1x1 board
  if (board.length() < 1 || !CheckSize(board.length())) {
    throw std::invalid_argument("The string provided is not a valid board.");
  }
  upper_case_board_ = board;
  side_length_ = sqrt(board.length());
  std::transform(upper_case_board_.begin(), upper_case_board_.end(),
                 upper_case_board_.begin(), ::toupper);
  o_winner_ = "";
  x_winner_ = "";
  for (int i = 0; i < side_length_; i++) {
    o_winner_ += "O";
    x_winner_ += "X";
  }
}

BoardState Board::EvaluateBoard() const {
  //checks number of x's and o's and sees if there's a legal amount
  int number_of_os = GetNumChar('O');
  int number_of_xs = GetNumChar('X');
  if (number_of_os > number_of_xs || number_of_xs - number_of_os > 1) {
    return BoardState::UnreachableState;
  }

  //counts the number of wins in columns and rows since only 1 win condition may exist in a board in all instances of it
  int wins_from_row = GetNumberOfRowOrColumnWins("row");
  int wins_from_col = GetNumberOfRowOrColumnWins("column");
  bool x_wins = GetPlayerWin(x_winner_);
  bool o_wins = GetPlayerWin(o_winner_);

  //diagonals must be legal
  if (!AreDiagonalsValid()) {
    return BoardState::UnreachableState;
    //there can only be one winning sequence
  } else if (wins_from_col > 1 || wins_from_row > 1) {
    return BoardState::UnreachableState;
    //a winning board must have a legal amount of moves by each player
  } else if ((x_wins && (number_of_os == number_of_xs)) || (o_wins && (number_of_os < number_of_xs))) {
    return BoardState::UnreachableState;
    //both players cannot win
  } else if (x_wins && o_wins) {
    return BoardState::UnreachableState;
  } else if (x_wins) {
    return BoardState::Xwins;
  } else if (o_wins) {
    return BoardState::Owins;
  }
  return BoardState::NoWinner;
}

/**
 * Checks to see if the parameter is a perfect square
 * @param num Length of the board
 * @return True if board length is a perfect square
 */
bool Board::CheckSize(int num) {
  double square_root = sqrt(num);
  return ((square_root - floor(square_root)) == 0);
}

/**
 * Finds The number of the passed character in the board sequence
 * @param Player character to look for
 * @return Amount of said character in the board
 */
int Board::GetNumChar(char player) const {
  int count = 0;
  for (char i : upper_case_board_) {
    if (i == player) {
      count++;
    }
  }
  return count;
}

/**
 * Gets a row from the board
 * @param rowNumber Which row to get from top to down
 * @return String representing row
 */
std::string Board::GetRow(int row_number) const {
  string row_string = "";
  int start = row_number * side_length_;
  for (int i = start; i < side_length_ + start; i++) {
    char ch = upper_case_board_[i];
    row_string += ch;
  }
  return row_string;
}

/**
 * Gets a column from the board
 * @param colNumber Which column to get from left to right
 * @return
 */
std::string Board::GetColumn(int column_number) const {
  string col_string = "";
  for (int i = column_number; i < upper_case_board_.length(); i += side_length_) {
    char ch = upper_case_board_[i];
    col_string += ch;
  }
  return col_string;
}

/**
 * Gets a diagonal from the board
 * @param diag1 Which diagonal to get, true is top left to bottom right
 * @return String representing the diagonal
 */
std::string Board::GetDiag(bool diag1) const {
  string diag_string = "";
  if (diag1) {
    int counter = 0;
    for (int i = 0; i < side_length_; i++) {
      char ch = upper_case_board_[side_length_ * counter + counter];
      diag_string += ch;
      counter++;
    }
  } else {
    int start = side_length_ - 1;
    for (int i = 1; i < side_length_ + 1; i++) {
      char ch = upper_case_board_[start * i];
      diag_string += ch;
    }
  }
  return diag_string;
}

/**
 * Goes through the board looking at each row, column, and diagonal to see if a
 * player has won
 * @param player_win Which player to look for, X or O
 * @return If the passed player has won or not
 */
bool Board::GetPlayerWin(const string& player_win) const {
  for (int i = 0; i < side_length_; i++) {
    string row_string = GetRow(i);
    string col_string = GetColumn(i);
    if (row_string == player_win || col_string == player_win) {
      return true;
    }
  }
  string diag_string1 = GetDiag(true);
  string diag_string2 = GetDiag(false);
  if (diag_string1 == player_win || diag_string2 == player_win) {
    return true;
  }
  return false;
}

/**
 * Counts number of wins in a given direction
 * @param sequence Either row or column to signify which to look at
 * @return Number of wins found in all rows or columns
 */
int Board::GetNumberOfRowOrColumnWins(const string& sequence) const {
  if (sequence != "row" && sequence != "column") {
    throw std::invalid_argument("The string provided does not represent a valid sequence.");
  }
  int count = 0;
  string potential_win = "";
  for (int i = 0; i < side_length_; i++) {
    if (sequence == "row") {
      potential_win = GetRow(i);
    } else if (sequence == "column") {
      potential_win = GetColumn(i);
    }
    if (potential_win == x_winner_ || potential_win == o_winner_) {
      count++;
    }
  }
  return count;
}

/**
 * Checks to see if the diagonals are valid, if a double win is possible in the
 * middle
 * @return True if the diagonals are logical
 */
bool Board::AreDiagonalsValid() const {
  string diag_string1 = GetDiag(true);
  string diag_string2 = GetDiag(false);
  bool diag1_xwin = (diag_string1 == x_winner_);
  bool diag1_owin = (diag_string1 == o_winner_);
  bool diag2_xwin = (diag_string2 == x_winner_);
  bool diag2_owin = (diag_string2 == o_winner_);

  //You can only win on diagonals if the board has an odd side length since the center tile will be shared
  if (((diag1_owin && diag2_owin) || (diag1_xwin && diag2_xwin)) &&
      (side_length_ % 2 == 0)) {
    return false;
  }
  return true;
}
}  // namespace tictactoe
