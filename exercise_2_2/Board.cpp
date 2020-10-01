#include "Board.h"
#include <algorithm>
#include <iostream>

/**
 * constructor
 *  - Fill data array with Empty Markers
 *  - Set winner to Empty
 */
Board::Board() {
  for (int i = 0; i < data.size(); i++) {
    data[i] = Marker::Empty;
  }
    winner = Marker::Empty;
}

/**
 * placeMarker
 * @param r  integer, row coordinate where marker should be placed
 * @param c  integer, column coordinate where marker should be placed
 * @param marker Marker, marker to be placed
 *
 * @return true, if <r,c> was Empty and now contains marker; false otherwise
 *
 * @note Be sure to call updateWinner after placing the marker
 */
bool Board::placeMarker(int r, int c, Marker marker) {
  auto &space = data[locationToIndex(r,c)];

  if(space != Marker::Empty) {
    return false;
  }

  space = marker;

  updateWinner(r,c);

  return true;
}

/**
 * getMarker
 * @param r  integer, row coordinate of place to read
 * @param c  integer, column coordinate of place to read
 * @return marker contained at <r,c>
 */
Marker Board::getMarker(int r, int c) {
  return data[locationToIndex(r, c)];
}

/**
 * isOver
 * @return true if the game is over, false otherwise
 * @note The game is over if no more moves can be made or if one player has won the game
 */
bool Board::isOver() {
  //no more available spaces
  if (!std::count(data.begin(), data.end(), Marker::Empty)) {
    return true;
  }
  for (int r = 0; r < 3; r++) {
    if (data[locationToIndex(r, 0)] == data[locationToIndex(r, 1)]
      && data[locationToIndex(r, 0)] == data[locationToIndex(r, 2)]
      && data[locationToIndex(r, 0)] != Marker::Empty) {
      return true;
    }
  }
  for (int c = 0; c < 3; c++) {
    if (data[locationToIndex(0, c)] == data[locationToIndex(1, c)]
      && data[locationToIndex(0, c)] == data[locationToIndex(2, c)]
      && data[locationToIndex(0, c)] != Marker::Empty) {
      return true;
    }
  }
  if (data[locationToIndex(0, 0)] == data[locationToIndex(1, 1)]
      && data[locationToIndex(0, 0)] == data[locationToIndex(2, 2)]
      && data[locationToIndex(0, 0)] != Marker::Empty) {
      return true;
    }
    if (data[locationToIndex(0, 2)] == data[locationToIndex(1, 1)]
      && data[locationToIndex(0, 2)] == data[locationToIndex(2, 0)]
      && data[locationToIndex(0, 2)] != Marker::Empty) {
      return true;
    }
    return false;
}

/**
 * getWinner
 * @return The current winner, or Empty if tie or in-progress game
 */
Marker Board::getWinner() {
  return winner;
}

/**
 * locationToIndex
 * @param r  integer, row coordinate
 * @param c  integer, column coordinate
 * @return index (of type size_t) for data array corresponding to <r,c>
 * @note data should be row-ordered, so each row of the board should be
 *       saved contiguously in data immediately following the row above it.
 */
size_t Board::locationToIndex(int r, int c) {
  return 3 * r + c;
}

/**
 * updateWinner, If we have a winning condition the last person to place a marker is the winner
 * @param last_r  integer, row coordinate of last move
 * @param last_c  integer, column coordinate of last move
 * @note pseudo-code algorithm:
 *       col=row=diag=rdiag=0
 *       winner=Empty
 *       for i=0 to 2
 *         if cell[x,i]=player then col++
 *         if cell[i,y]=player then row++
 *         if cell[i,i]=player then diag++
 *         if cell[i,2-i]=player then rdiag++
 *       if row=n or col=n or diag=n or rdiag=n then winner=player
 */
void Board::updateWinner(int last_r, int last_c) {
  int hor = 0;
  int ver = 0;
  int diag1 = 0;
  int diag2 = 0;
  Marker player = getMarker(last_r, last_c);
  for( int i = 0; i < 3; i++) {
    if (getMarker(last_r, i) == player)
      hor++;
    if (getMarker(i,last_c) == player)
      ver++;
    if (getMarker(i,i) == player)
      diag1++;
    if (getMarker(i,2-i) == player)
      diag2++;
  }

  if (hor == 3 || ver == 3 || diag1 == 3 || diag2 == 3) {
    winner = player;
  }
}
