#pragma once

#include <string>

namespace tictactoe {

/**
 * This enumeration specifies the possible results of the evaluation of a
 * Tic-Tac-Toe board.
 */
enum class BoardState {
  NoWinner,
  Xwins,
  Owins,
  UnreachableState,
};

/**
 * This class can store a Tic-Tac-Toe board and evaluate its state.
 */
class Board {
 public:
  /**
   * Constructs a Board from a string consisting of 9 characters in row-major
   * order (i.e. the first three characters specify the first row).
   *
   * An 'X' or 'x' represents that the corresponding square is filled with an X,
   * an 'O' or 'o' represents that the corresponding square is filled with an O,
   * and any other character represents that the corresponding square is empty.
   *
   * This method throws a std::invalid_argument exception if the string provided
   * is not a valid board.
   */
  Board(const std::string& board);

  /**
   * Evaluates the state of the board.
   */
  BoardState EvaluateBoard() const;

 private:
  std::string upper_case_board_;
  int side_length_;
  std::string o_winner_;
  std::string x_winner_;
  bool CheckSize(int num);
  int GetNumChar(char player) const;
  std::string GetRow(int row_number) const;
  std::string GetColumn(int col_number) const;
  std::string GetDiag(bool diag1) const;
  bool GetPlayerWin(std::string player_win) const;
  int GetNumberOfRowOrColumnWins(std::string sequence) const;
  bool AreDiagonalsValid() const;
};

}  // namespace tictactoe
