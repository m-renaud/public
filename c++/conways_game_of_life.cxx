#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <ctime>
#include <tr1/random>

enum { HEIGHT = 68, WIDTH = 235, BUFFERS = 2};
const char RED[] = "\033[0;31m";	   /* Color constants */
const char GREEN[] = "\033[0;32m";
const char BLUE[] = "\033[0;34m";
const char DEFAULT[] = "\033[0m";

class Life
{
protected:
   // Private Variables to Life Class.
   int array[BUFFERS][HEIGHT + 2][WIDTH + 2];
   int currentBuffer;
   int otherBuffer;
   int lifeDensity;
   char life;
   char death;

   ////////////////////////////////////////////////////
   // Private Functions to Life Class.
   void showLife(int generation, char life, char death)
   {
      std::cout << "\e[H";
      std::cout << std::setw(10) << "Generation: " << generation << std::endl << std::endl;
      for(int i = 0; i < WIDTH; i++)
      {
	 std::cout << "_";
      }

      for(int row = 1; row < HEIGHT + 1; ++row)
      {
	 std::cout << std::endl << "|";
	 for(int col = 1; col < WIDTH + 1; ++col)
	 {
	    if(array[currentBuffer][row][col] == 1)
	    {
//	       std::cout << GREEN;
	       std::cout << life;
	    }
	    else
	    {
//	       std::cout << RED;
	       std::cout << death;
	    }
	 } // for(col)
	 std::cout << "|";
      } // for(row)
//      std::cout << DEFAULT;

      std::cout << std::endl << "|";

      // Draw bottom line of game box
      for(int i = 0; i < WIDTH; i++)
      {
	 std::cout << "_";
      }
      std::cout << std::endl;
   } // showLife

   int applyRules()
   {
      int isDone = 1;
      int numNeighbours;
      
      // Create the next generation of life.
      for(int row = 1; row < HEIGHT + 1; ++row)
      {
	 for(int col = 1; col < WIDTH + 1; ++col)
	 {
	    numNeighbours = checkNeighbours(row, col);

	    if(array[currentBuffer][row][col] == 1) // If life in the current box.
	    {
	       if(numNeighbours == 2 || numNeighbours == 3) // If 2 or 3 neighbours, stays alive.
	       {
		  array[otherBuffer][row][col] = 1;
	       }
	       else
	       {
		  array[otherBuffer][row][col] = 0;
		  isDone = 0;
	       }
	    }
	    else // If no life in current box.
	    {
	       if(numNeighbours == 3)
	       {
		  array[otherBuffer][row][col] = 1;
		  isDone = 0;
	       }
	       else
	       {
		  array[otherBuffer][row][col] = 0;
	       }
	    }
	 } // for(col)
      } // for(row)

      return isDone;
   }

   int checkNeighbours(int row, int col)
   {
      int numNeighbours = 0;

      if ((array[currentBuffer][row-1][col-1])==1)
	 numNeighbours++;
      if ((array[currentBuffer][row-1][col])==1)
	 numNeighbours++;
      if ((array[currentBuffer][row-1][col+1])==1)
	 numNeighbours++;
      if ((array[currentBuffer][row][col-1])==1)
	 numNeighbours++;
      if ((array[currentBuffer][row][col+1])==1)
	 numNeighbours++;
      if ((array[currentBuffer][row+1][col-1])==1)
	 numNeighbours++;
      if ((array[currentBuffer][row+1][col])==1)
	 numNeighbours++;
      if ((array[currentBuffer][row+1][col+1])==1)
	 numNeighbours++;

      return numNeighbours;
   }
   
   void setNextGeneration()
   {
      if(currentBuffer == 0)
      {
	 currentBuffer = 1;
	 otherBuffer = 0;
      }
      else
      {
	 currentBuffer = 0;
	 otherBuffer = 1;
      }
   }


public:
   void initialize()
   {

      using std::tr1::mt19937;
      using std::tr1::uniform_real;
      using std::tr1::variate_generator;

      mt19937 gen(std::time(0));      // Use this random # generator with seed from time()
      uniform_real<> dist(1,6);       // with a uniform distribution between 1 and 6...
      variate_generator< mt19937&, uniform_real<> > rnd(gen,dist);  // as object "rnd"

      currentBuffer = 0;
      otherBuffer = 1;
      
      int setR;
      int setC;
      int makeRandomly;

      std::cin >> makeRandomly;
      std::cin >> lifeDensity;
      std::cin >> life;
      death = ' ';

      if(makeRandomly == 1)
      {
	 for(int row = 1; row < HEIGHT + 2; ++row)
	 {
	    for(int col = 1; col < WIDTH + 2; ++col)
	    {
	       int randomInt = (rand() % lifeDensity);
	       if(randomInt == 0)
	       {
		  array[currentBuffer][row][col] = 1;
	       }
	       else
	       {
		  array[currentBuffer][row][col] = 0;
	       }
	    } // for(col)
	 } // for(row)
      }
      else
      {
	 for(int row = 1; row < HEIGHT + 2; ++row)
	 {
	    for(int col = 1; col < WIDTH + 2; ++col)
	    {
	       array[currentBuffer][row][col] = 0;
	    } // for(col)
	 } // for(row)

	 std::cin >> setR;
	 while(setR != -1)
	 {
	    std::cin >> setC;
	    array[currentBuffer][setR][setC] = 1;
	    std::cin >> setR;
	 }
      }
   }

   int run()
   {

      int numGenerations = 1;
      int isDone = 0;

      std::cout << "\e[2J";
      showLife(numGenerations, life, death);
      usleep(500000);
      while(isDone != 1)
      {
	 showLife(numGenerations, life, death);
	 isDone = applyRules();
	 usleep(60000);
	 setNextGeneration();
	 ++numGenerations;
      }
      showLife(numGenerations, life, death);
      std::cout << std::endl << std::endl;
      std::cout << "Simulation ran for " << numGenerations << " generations." << std::endl;
   }
};


int main()
{
   Life simulation;

   simulation.initialize();
   simulation.run();
   
   return 0;
} /* Main */
