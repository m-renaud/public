#include <iostream>
#include <vector>

using namespace std;

// Function to find the minimum of three numbers
// Used to calculate what should be placed in the current element of the grid
int minimum(int a, int b, int c)
{
   int min = a;
   if(b < min)
      min = b;
   if(c < min)
      min = c;
   return min;
   
}

// Attempt at Levenshtein with a vector
// Getting very strange runtime results - it seems to not be creating the
// proper size vector
int LDVector(string s, string t)
{
   int m = s.length();
   int n = t.length();

   vector<vector<int> > d ((m+1), vector<int>(n+1, 0));

   for(int i = 0; i <= n; ++i)
      d[i][0] = i;
   for(int j = 0; j <= n; ++j)
      d[0][j] = j;

   for(int j = 1; j <= n; ++j)
      for(int i = 1; i <= m; ++i)
      {
	 if(s[i-1] == t[j-1])
	    d[i][j] = d[i-1][j-1];
	 else
	    d[i][j] = minimum(d[i-1][j] + 1,
			     d[i][j-1] + 1,
			     d[i-1][j-1] + 1);
      }

   return d[m][n];   
}

// Implementation using a basic c-style array, all that is really needed for
// this algorithm.  I'll eventually be improving it by removing common substrings
// before hand.
int LevenshteinDistance(string s, string t)
{
   int m = s.length();
   int n = t.length();

   int d[m+1][n+1];

   for(int i = 0; i <= m; ++i)
      d[i][0] = i;
   for(int j = 0; j <= n; ++j)
      d[0][j] = j;

   for(int j = 1; j <= n; ++j)
      for(int i = 1; i <= m; ++i)
      {
	 if(s[i-1] == t[j-1])
	    d[i][j] = d[i-1][j-1];
	 else
	    d[i][j] = minimum(d[i-1][j] + 1,
			     d[i][j-1] + 1,
			     d[i-1][j-1] + 1);
      }

   // Optional, this code is used to print out the grid generated
#if 0   
   for(int j = 0; j <= n; ++j)
   {
      for(int i = 0; i <= m; ++i)
      {
    	 cout << d[i][j] << " ";
      }
      cout << endl;
   }
#endif

   return d[m][n];
}

int main()
{
   string s1, s2;
   while(1)
   {
      cin >> s1 >> s2;
      cout << LevenshteinDistance(s1, s2) << endl;
      cout << LDVector(s1, s2) << endl;
   }
   return 0;
}
