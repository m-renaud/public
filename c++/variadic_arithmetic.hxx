#ifndef __MRR_VARIADIC_ARITHMETIC_HXX__
#define __MRR_VARIADIC_ARITHMETIC_HXX__

#include <iostream>
#include <type_traits>
#include <typeinfo>


template <typename T>
typename std::add_rvalue_reference<T>::type val();


//==================================================
// Variadic Sum Traits
template <typename T, typename... TS>
struct sum_type;

// Base Case:
template <typename T>
struct sum_type<T>
{
  typedef T type;
};

// Inductive Case:
template <typename  T, typename U, typename... TS>
struct sum_type<T, U, TS...>
  : sum_type
  <
  decltype(val<const T&>() + val<const U&>()),
  TS...
  >
{ };

//==================================================
// Variadic Product Traits
template <typename T, typename...TS>
struct prod_type;

// Base Case:
template <typename T>
struct prod_type<T>
{
  typedef T type;
};

// Inductive case:
template <typename T, typename U, typename... TS>
struct prod_type<T, U, TS...>
  : prod_type
  <
  decltype(val<const T&>() * val<const U&>()),
  TS...
  >
{ };

//==================================================
// Variadic sum function.
template <typename T>
typename sum_type<T>::type
sum(T val)
{
  return val;
}

template <typename T, typename... TS>
typename sum_type<T, TS...>::type
sum(T val, TS... rest)
{
  return val + sum(rest...);
}


//==================================================
// Variadic Product:
template<typename T>
typename prod_type<T>::type
prod(T val)
{
  return val;
}

template <typename T, typename... TS>
typename prod_type<T, TS...>::type
prod(T val, TS... rest)
{
  return val * prod(rest...);
}

//==================================================
// Variadic Average:
template <typename... Args>
int pack_size(Args... as)
{
  return (sizeof...(Args));
}

template <typename... TS>
auto avg(TS... vals) -> decltype(sum(vals...) / pack_size(vals...))
{
  return sum(vals...) / pack_size(vals...);
}

#endif // #ifndef __MRR_VARIADIC_ARITHMETIC_HXX_
