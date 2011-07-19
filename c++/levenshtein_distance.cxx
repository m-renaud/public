#include <iostream>

// Function to find the minimum of three numbers
// Used to calculate what should be placed in the current element of the grid
inline int minimum(int a, int b, int c)
{
  return std::min(a, std::min(b,c));
}

// Implementation using a basic c-style array, all that is really needed for
// this algorithm.  I'll eventually be improving it by removing common substrings
// before hand.
unsigned LevenshteinDistance(std::string const& str1, std::string const& str2)
{
  if(str1.empty())
    return str2.size();
  else if (str2.empty())
    return str1.size();

  const std::string::size_type m = str1.length();
  const std::string::size_type n = str2.length();

  unsigned d[m+1][n+1];
  unsigned i, j;

  for(i = 0; i <= m; ++i)
    d[i][0] = i;
  for(j = 0; j <= n; ++j)
    d[0][j] = j;

  for(j = 1; j <= n; ++j)
    for(i = 1; i <= m; ++i)
    {
      if(str1[i-1] == str2[j-1])
	d[i][j] = d[i-1][j-1];
      else
	d[i][j] = minimum(d[i-1][j] + 1,
			  d[i][j-1] + 1,
			  d[i-1][j-1] + 1);
    }

// Optional, this code is used to print out the grid generated
#if 0
  for(j = 0; j <= n; ++j)
  {
    for(i = 0; i <= m; ++i)
    {
      std::cout << d[i][j] << " ";
    }
    std::cout << std::endl;
  }
#endif

  return d[m][n];
}

int main()
{
  std::string s1, s2;
  while(1)
  {
    std::cin >> s1 >> s2;
    std::cout << LevenshteinDistance(s1, s2) << std::endl;
  }
  return 0;
}
