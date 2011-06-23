#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

typedef vector<int> V_int;


//======================================================================
// Variadic arithmetic functions
//======================================================================

// sum
template <typename T1, typename T2>
auto v_sum(T1 val1, T2 val2) -> decltype(val1 + val2)
{
   return val1 + val2;
}

template <typename T, typename... TS>
auto v_sum(T val, TS... rest) -> decltype(val + v_sum<TS...>(rest...))
{
   return val + v_sum(rest...);
}

// product
template <typename T1, typename T2>
auto v_product(T1 val1, T2 val2) -> decltype(val1 + val2)
{
   return val1 * val2;
}

template <typename T, typename... TS>
T v_product(T val, TS... rest)
{
   return val * v_product<T>(rest...);
}

//======================================================================
// Variadic apply for arithmetic functions.
//======================================================================
template <typename T, typename Func>
T variadic_arithmetic(Func f, T val)
{
   return val;
}

template  <typename T, typename... TS, typename Func>
T variadic_arithmetic(Func f, T first, TS... rest)
{
   return f(first, variadic_arithmetic(f, rest...));
}

//======================================================================
// Variadic column sum over any iterable container types.
//======================================================================
template <typename IterIn, typename IterOut, typename... Iters>
IterOut column_sum(IterIn start, IterIn end, IterOut dest, Iters... rest)
{
   while (start != end)
   {
      *dest++ = v_sum(*start++, *rest++...);
   }
}
//======================================================================
// Variadic column product over any iterable container types.
//======================================================================
template <typename IterIn, typename IterOut, typename... Iters>
IterOut column_product(IterIn start, IterIn end, IterOut dest, Iters... rest)
{
   while(start != end)
   {
      *dest++ = v_product(*start++, *rest++...);
   }
}

//======================================================================
// Some testing code
//======================================================================
int main()
{
   // Declare some vectors with some integer values
   V_int vect_1 = {1,2,3,4};
   V_int vect_2 = {2,4,6,8};
   V_int vect_3 = {3,6,9,12};

   // Make 2 lists to hold the result of each
   list<int> sum_list, prod_list;

   // Compute the sum and product of the columns
   column_sum(vect_1.begin(), vect_1.end(), back_inserter(sum_list), vect_2.begin(), vect_3.begin());
   column_product(vect_1.begin(), vect_1.end(), back_inserter(prod_list), vect_2.begin(), vect_3.begin());

   // Output the results
   for_each(sum_list.begin(), sum_list.end(), [](int x) { cout << x << "\t";});
   cout << endl;
   for_each(prod_list.begin(), prod_list.end(), [](int x) { cout << x << "\t";});

   return 0;
}
