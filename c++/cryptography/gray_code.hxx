#ifndef __GRAY_CODE_HXX__
#define __GRAY_CODE_HXX__

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

#endif // __GRAY_CODE_HXX__
