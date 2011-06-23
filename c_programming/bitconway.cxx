// Conways game of life using bits instead of 

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <time.h>
#include "bitwiseFunctions.hxx"

#define BINARY_OUTPUT

void DEBUG()
{
#ifdef DEBUG
   cout << "DEBUG MESSAGE\n" << endl;
#endif
}


using namespace std;

class Conway
{
protected:
   ull grid[2][BITS];
   int s;
   int pop3 [8];
   unsigned sum;
   ull mask;
   
   int loop();
   
   int calcNextGen(unsigned sum, unsigned on)
   {
      return (sum == 3) || (sum == 4 && on);
   }
   
public:
   Conway() : s(0), sum(0), mask(0x00), pop3({0,1,1,2,1,2,2,3}) {}

   int initialize();
   int run();
};

int Conway::initialize()
{
   srand( time(NULL) );

    for(int i = 0; i < BITS; ++i)
    {
       grid[s][i] = rand();
       grid[s][i] <<= 32;
       grid[s][i] += rand();
    }

   return 0;
}

int Conway::run()
{
#ifdef BINARY_OUTPUT
   system("clear");
   cout << "\e[2J";
#endif
   for(int i = 0; i < 50000; ++i)
   {
      loop();
#ifdef BINARY_OUTPUT
      usleep(500000);
      cout << "Generation: " << i << endl;
#endif
   }

   return 0;
}

int Conway::loop()
{
   mask = 0x01ull;
   int i;
   
   sum = pop3[ grid[s][0] & 3] + pop3[ grid[s][1] & 3];
   grid[!s][0] = calcNextGen(sum, grid[s][0] & 1);
   DEBUG();

   sum += pop3[ grid[s][2] & 3];
   grid[!s][1] = calcNextGen(sum, grid[s][1] & 1);
   DEBUG();
   
   for(i = 2; i < 63; ++i)
   {
      sum += pop3[ grid[s][i + 1] & 3] - pop3[ grid[s][i - 2] & 3];
      grid[!s][i] = calcNextGen(sum, grid[s][i] & 1);
      DEBUG();
   }

   sum -= pop3[ grid[s][61] & 3];
   DEBUG();
   grid[!s][63] = calcNextGen(sum, grid[s][63] & 1);

   while(mask <<= 1)
   {
      sum = pop3[ grid[s][0] & 7] + pop3[ grid[s][1] & 7];
      grid[!s][0] |= calcNextGen(sum, grid[s][0] & 2) ? mask : 0;

      sum += pop3[ grid[s][2] & 7];
      grid[!s][1] |= calcNextGen(sum, grid[s][1] & 2) ? mask : 0;

      for(i = 2; i < 63; ++i)
      {
	 sum += pop3[ grid[s][i + 1] & 7] - pop3[ grid[s][i - 2] & 7];
	 grid[!s][i] |= calcNextGen(sum, grid[s][i] & 2) ? mask : 0;
	 grid[s][i - 2] >>= 1;
      }

      sum -= pop3[ grid[s][61] & 7];
      grid[!s][63] |= calcNextGen(sum, grid[s][63] & 2) ? mask : 0;
      grid[s][61] >>= 1;
      grid[s][62] >>= 1;
      grid[s][63] >>= 1;
   } 
   #ifdef BINARY_OUTPUT
   cout << "\e[H";
   #endif
   s = !s;
   
#ifdef BINARY_OUTPUT
   displayAsBinary(grid[s]);
#endif
   
#ifdef HEX_OUTPUT
   displayAsHex(grid[s]);
#endif

#ifdef DECIMAL_OUTPUT
   displayAsDecimal(grid[s]);
#endif


   return 0;
}

int main()
{
   Conway simulation;

   simulation.initialize();
   simulation.run();

#if 0
   displayAsBinary(grid[s]);
   displayAsDecimal(grid[s]);
   cout << "HERE" << endl;
   displayAsDecimal(grid[!s]);
   displayAsHex(grid);
#endif

   return 0;
}
