#include <iostream>
#include <math.h>

using namespace std;

template<typename T>
T set(T a, T b)
{
   return a | b;
}

template<typename T>
T unset(T a, T b)
{
   return a & ~b;
}

template<typename T>
T toggle(T a, T b)
{
   return a ^ b;
}

template<typename T>
T status(T a, T b)
{
   return a & b;
}

int main()
{
   int a = 0x04;
   cout << "a = " << hex << a << endl;
   cout << "Setting the 1 bit..." << endl;
   cout << "a = " << hex << set(a, 1) << endl;
   cout << "Unsetting the 1 bit..." << endl;
   cout << "a = " << hex << unset(a, 1) << endl;
   cout << "Toggleing the 4 bit..." << endl;
   cout << "a = " << hex << toggle(a, 4) << endl;
   cout << "Status of 3rd bit: " << endl;
   cout << (status(a, 8) ? "On" : "Off") << endl;
   return 0;
}

int iexp(int x, unsigned n);
int iexp(int x, unsigned n)
{
   int p, y;

   y = 1;   // Initalize result
   p = x;   // and p

   for(;;)
   {
      if(n & 1)
	 y = p * y;
      n = n >> 1;
      if(n == 0)
	 return y;
      p = p*p;
   }
}
