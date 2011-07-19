#include <iostream>

template <typename T>
T grayToBin(T g)
{
  T b;
  b = g ^ (g >> 1);
  b ^= b >> 2;
  b ^= b >> 4;
  b ^= b >> 8;
  b ^= b >> 16;

  return b;
}

template <typename T>
T binToGray(T b)
{
  return b ^ (b >> 1);
}

int main()
{
  for(int a = 1; a <= 20; ++a)
    std::cout << "Bin: "  << a << "\t\t"
	      << "Gray: " << binToGray(a)
	      << std::endl;

  std::string name = "Matt is my name";

  for(char &x: name)
  {
    x = binToGray(static_cast<int>(x));
    std::cout << x;
  }

  std::cout << std::endl;
  for(char &x: name)
  {
    x = grayToBin(x);
    std::cout << x;
  }

  return 0;
}
