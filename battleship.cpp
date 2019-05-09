/*-----------------------------------------------------------------------------
 *				HTBLA-Leonding / Class: <your class name here>
 *-----------------------------------------------------------------------------
 * Exercise Number: #exercise_number#
 * File:			battleship.c
 * Author(s):		Peter Bauer
 * Due Date:		#due#
 *-----------------------------------------------------------------------------
 * Description:
 * <your description here>
 *-----------------------------------------------------------------------------
*/
#include <stdio.h>

#include "battleship.h"

CellContent _my_field[FIELDSIZE][FIELDSIZE];
CellContent _other_field[FIELDSIZE][FIELDSIZE];
CellContent _my_guess[FIELDSIZE][FIELDSIZE];

void load_game()
{
  FILE* my_ship = fopen("battleship.my", "r+");
  FILE* other_ship = fopen("battleship.op", "r+");
  for (size_t i = 0; i < FIELDSIZE; i++)
  {
    for (size_t j = 0; j < FIELDSIZE; j++)
    {
      fread(&_my_field[i][j], sizeof(CellContent),1,my_ship	);
      fread(&_other_field[i][j], sizeof(CellContent),1,other_ship	);
      _my_guess[i][j] = Unknown;
    }
  }
}
CellContent get_shot(int row, int col)
{
  if (row >= FIELDSIZE || col >= FIELDSIZE || row < 0 || col < 0)
  {
    return OutOfRange;
  }
  return _my_field[row][col];
}
void uncover_water(int row, int col)
{
  if (row >= FIELDSIZE || col >= FIELDSIZE || row < 0 || col < 0)
  {
    return;
  }
    _my_guess[row][col]= Water;
}

bool shoot(int row, int col)
{
  if (row >= FIELDSIZE || col >= FIELDSIZE || row < 0 || col < 0)
  {
    return false;
  }
  if (_other_field[row][col] == Water)
  {
    _my_guess[row][col]= Water;
    return true;
  }
  _my_guess[row][col]= Boat;
  uncover_water(row+1,col+1);
  uncover_water(row,col+1);
  uncover_water(row+1,col);
  uncover_water(row-1,col-1);
  uncover_water(row-1, col);
  uncover_water(row,col-1);
  uncover_water(row+1,col-1);
  uncover_water(row-1,col+1);
  return true;
}

CellContent get_my_guess(int row, int col)
{
  if (row >= FIELDSIZE || col >= FIELDSIZE || row < 0 || col < 0)
  {
    return OutOfRange;
  }
  return _my_guess[row][col];
}
