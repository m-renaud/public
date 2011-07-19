#include <iostream>
#include "shift_encrypt.hxx"

int main()
{
  std::string test = "Hello! My name is Matt~";
  shift_encrypt(test, 27);
  std::cout << test << std::endl;
  shift_encrypt(test, -27);
  std::cout << test << std::endl;
}
