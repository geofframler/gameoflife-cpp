/*
  John Conway's Game of Life
  Programmed by Geoff Ramler on 10/01/2017

  Rules:
  Any live cell with fewer than two live neighbors dies, as if caused by underpopulation.
  Any live cell with two or three live neighbors lives on to the next generation.
  Any live cell with more than three live neighbors dies, as if by overpopulation.
  Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
*/

#include <ncurses.h>
#include <chrono>
#include <thread>

const int HEIGHT = 30;
const int WIDTH = 60;
const char LIFE = '0';
const char DEATH = ' ';

// Main 2D array
char initGrid[HEIGHT][WIDTH];

// Function declarations
void initial( char grid[HEIGHT][WIDTH] );
void neighbors( char grid[HEIGHT][WIDTH] );
void print( char grid[HEIGHT][WIDTH] );

// THE MAIN FUNCTION
int main()
{
  // Set initial array
  initial(initGrid);

  // Create ncurses window
  initscr();

  // The "GAME LOOP"
  while (true)
  {
    clear();
    neighbors(initGrid);
    print(initGrid);
    refresh();
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }

  // Close down ncurses and exit
  endwin();
  return 0;
}

// Function to set the initial array
void initial( char grid[HEIGHT][WIDTH] )
{
  //Fill array with random values
  srand(time(NULL));
  for(int r=0; r<HEIGHT; r++)
  {
    for (int c=0; c<WIDTH; c++)
    {
      grid[r][c] = DEATH;
      int random = rand() % 10 + 1;
      if(random == 5)
      {
        grid[r][c] = LIFE;
      }
    }
  }
}

// Function to check neighbors and determine what lives or dies
void neighbors( char grid[HEIGHT][WIDTH] )
{
  // Array to hold copy of board
  char gridCopy[HEIGHT][WIDTH];

  // Copy array
  for (int r=0; r<HEIGHT; r++)
  {
    for (int c=0; c<WIDTH; c++)
    {
      gridCopy[r][c] = grid[r][c];
    }
  }

  // Check neighbors for life
  for( int r=0; r<HEIGHT; r++)
  {
    for( int c=0; c<WIDTH; c++)
    {
      int check = 0;
      char v[]= { grid[r-1][c],
                  grid[r-1][c-1],
                  grid[r-1][c+1],
                  grid[r][c-1],
                  grid[r][c+1],
                  grid[r+1][c],
                  grid[r+1][c-1],
                  grid[r+1][c+1] };

      for (int n=0; n<8; ++n)
      {
        if(v[n] == LIFE)
        {
          check++;
        }
      }

      // Any live cell with fewer than two live neighbors dies, as if caused by underpopulation.
      // Any live cell with more than three live neighbors dies, as if by overpopulation.
      if(check < 2 || check > 3)
      gridCopy[r][c] = DEATH;

      // Any live cell with two or three live neighbors lives on to the next generation.
      if(check == 2)
      gridCopy[r][c] = grid[r][c];

      // Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
      if(check == 3)
      gridCopy[r][c] = LIFE;
    }
  }

  // Copy array back to main
  for (int r=0; r<HEIGHT; r++)
  {
    for (int c=0; c<WIDTH; c++)
    {
      grid[r][c] = gridCopy[r][c];
    }
  }
}

// Function to render the array
void print( char grid[HEIGHT][WIDTH] )
{
  for (int r=0; r<HEIGHT; r++)
  {
    for (int c=0; c<WIDTH; c++)
    {
      addch(grid[r][c]);
    }
    addch('\n');
  }
}