#ifndef __ROT_13_HXX__
#define __ROT_13_HXX__

void rot13(std::string & str)
{
  std::string::size_type str_length = str.length();
  std::cout << "String length: " << str_length << std::endl;

  for(std::string::size_type i = 0; i < str_length; ++i)
  {
    int temp = static_cast<int>(str[i]) + 47;
    if(temp > 126)
      temp -= 95;

    str[i] = static_cast<char>(temp);
  }
}

#endif // __ROT_13_HXX__
