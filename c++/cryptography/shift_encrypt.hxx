#ifndef __SHIFT_ENCRYPT_HXX__
#define __SHIFT_ENCRYPT_HXX__

void shift_encrypt(std::string & str, int shift)
{
  std::string::size_type str_length = str.length();

  for(std::string::size_type i = 0; i < str_length; ++i)
  {
    str[i] = static_cast<char>(
      static_cast<int>(str[i]) + shift);
  }
}

#endif // __SHIFT_ENCRYPT_HXX__
