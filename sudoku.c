#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
/*
 Intro Paragraph:
 This program solves a soduku. 
 It creates the following functions:
 is_val_in_row: checks if the value is valid within the row
 is_val_in_col: checks if the value is valid within the coloumn
 is_val_in_3x3_zone: checks if the value is valid within the 3x3 grid
 is_val_valid: checks if the value is valid based on the above functions
 check_sudoku_filled: checks if the sudoku has been filled
 find_empty: finds an empty pair of (i,j) coordinates and fills it in an array
*/
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {
  assert(i>=0 && i<9);   //makes sure (i>=0 and i<9) is true to stay in bounds
  // BEG TODO
  for (int j = 0; j<9; j++)  //checks all values in the row
  {
    if (sudoku[i][j] == val)  //it has found an invalid value, return 1
    {
      return 1;
    }
  }
  return 0; //valid value, return 0
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {
  assert(j>=0 && j<9);  //makes sure (j>=0 and j<9) is true to stay in bounds
  // BEG TODO
  for (int i = 0; i<9; i++)   //checks all values in the coloumn
  {
    if (sudoku[i][j] == val)  //it has found an invalid value, return 1
    {
      return 1;
    }
  }
  return 0; //valid value, return 0
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
  assert(i>=0 && i<9); //makes sure (i>=0 and i<9) is true to stay in bounds
  // BEG TODO
  for (int m = 0; m<3; m++)  //the rows of the 3x3 grid
  {
    for (int n = 0; n<3; n++)  //the coloumns of the 3x3 grid
    {
      int tempi = i - i%3;  //finds the location of the temporary element in the grid
      int tempj = j - j%3;  //finds the location of the temporary element in the grid
      if (sudoku[m+tempi][n+tempj] == val) //invalid value found, return 1
      {
        return 1;
      }
    }
  }
  return 0; //valid value found, return 0
  // END TODO
}

// Function: is_val_valid
// Return true if the val can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {
  assert(i>=0 && i<9 && j>=0 && j<9);  
  // BEG TODO
  if (!is_val_in_col(val, j, sudoku) && !is_val_in_row(val, i, sudoku) && !is_val_in_3x3_zone(val, i, j, sudoku))
  { //uses the above 3 functions to determine validity
    return 1;
  }
  return 0; 
  // END TODO
}

//checks if all cells are assigned by numbers 
//returns 1 if all cells are filled, 0 otherwise 
int check_sudoku_filled (const int sudoku [9][9]){
int i,j;
for(i = 0; i < 9; i++){
  for (j = 0; j < 9; j++){
    if (sudoku[i][j] <= 0) //found an empty value, sudoku is not filled
      return 0;
  }
}
return 1; //sudoku is filled
}

// finds a non-filled 0 cell 
// returns a non-filled 0 cell in the address of empty_cell[2]
void find_empty (int empty_cell [2], const int sudoku [9][9]){
int i, j;
for(i = 0; i < 9; i++){
  for (j = 0; j < 9; j++){
    if(sudoku[i][j] == 0 ){ //found empty value, return coordinates
      empty_cell[0] = i;
      empty_cell[1] = j;
      }
    }
  }
}


// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
  // BEG TODO.
  //base case - reached solution, no more values to be placed
  int i = 0;
  int j = 0;
  if (check_sudoku_filled(sudoku))  //the base case
  {
    return 1;
  }
  else  //the sudoku is not empty, start solving
  {
    int empty[2] = {0, 0};
    find_empty(empty, sudoku);
    i = empty[0];
    j = empty[1];
  }

   for (int num = 1; num <= 9; num++)
   {
    if (is_val_valid(num, i, j, sudoku))  //checks if the number can be placed at the empty coordinates
    {
      sudoku[i][j] = num; //fills the temporary solution in
      if (solve_sudoku(sudoku))  //calls the function on itself to see if it can be solved in the future with this solution
      {
        return 1;
      }
      sudoku [i][j] = 0; //keeps the value empty, try the next number
    }
   }
  return 0;  
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
