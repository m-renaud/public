#ifndef __XOR_ENCRYPTION_HXX__
#define __XOR_ENCRYPTION_HXX__

void xor_encrypt(std::string & str, std::string const& key)
{
  std::string::size_type y = 0;
  std::string::size_type str_length = str.length();
  std::string::size_type key_length = key.length();

  for(std::string::size_type i = 0; i < str_length; ++i)
  {
    str[i] ^= key[y];
    ++y;

    if(y % key_length == 0)
      y = 0;
  }
}

#endif // __XOR_ENCRYPTION_HXX__
