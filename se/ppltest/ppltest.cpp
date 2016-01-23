// parallel-fibonacci.cpp
// compile with: /EHsc
#include <windows.h>
#include <ppl.h>
#include <concurrent_vector.h>
#include <array>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iostream>

using namespace concurrency;
using namespace std;

// --------------------------------------------------
// Simple heap consistency checks inserted to the example

#include <cassert>
#include <new>

void *checked_alloc(size_t sz)
{ // mark the block so that we know we have allocated it
	__int64 *ptr = (__int64 *)malloc(sz + 2 * sizeof(__int64));
	__int64 mark = (__int64)ptr;
	ptr[0] = mark;
	ptr[1] = ~mark;
	return ptr + 2;
}

void checked_free(void *p)
{ // if we are deallocating the block allocated by checked_alloc, marks should match
	if(!p) return;
	__int64 *ptr = (__int64 *)p - 2;
	__int64 mark = (__int64)ptr;
	assert(ptr[0] == mark);
	assert(ptr[1] == ~mark);
	free(ptr);
}

void *operator new(size_t size) throw(std::bad_alloc) { return checked_alloc(size); }
void operator  delete(void *ptr) throw()              { checked_free(ptr); }

void *operator new[](size_t size) throw(std::bad_alloc) { return checked_alloc(size); }
void operator  delete[](void *ptr) throw()              { checked_free(ptr); }

void *operator new(size_t size, const std::nothrow_t&) throw() { return checked_alloc(size); }
void operator  delete(void *ptr, const std::nothrow_t&) throw() { checked_free(ptr); }

void *operator new[](size_t size, const std::nothrow_t&) throw() { return checked_alloc(size); }
void operator  delete[](void *ptr, const std::nothrow_t&) throw() { checked_free(ptr); }

// end of a block of code inserted to the example
// ---------------------------------------------------

// Calls the provided work function and returns the number of milliseconds 
// that it takes to call that function.
template <class Function>
__int64 time_call(Function&& f)
{
   __int64 begin = GetTickCount();
   f();
   return GetTickCount() - begin;
}

// Computes the nth Fibonacci number.
int fibonacci(int n)
{
   if(n < 2)
      return n;
   return fibonacci(n-1) + fibonacci(n-2);
}

int wmain()
{
   __int64 elapsed;

   // An array of Fibonacci numbers to compute.
//   array<int, 4> a = { 24, 26, 41, 42 };
   array<int, 4> a = { 10 }; // no need to wait to demonstrate the issue

   // The results of the serial computation.
   vector<tuple<int,int>> results1;

   // The results of the parallel computation.
   concurrent_vector<tuple<int,int>> results2;

   // Use the for_each algorithm to compute the results serially.
   elapsed = time_call([&] 
   {
      for_each (begin(a), end(a), [&](int n) {
         results1.push_back(make_tuple(n, fibonacci(n)));
      });
   });   
   wcout << L"serial time: " << elapsed << L" ms" << endl;

   // Use the parallel_for_each algorithm to perform the same task.
   elapsed = time_call([&] 
   {
      parallel_for_each (begin(a), end(a), [&](int n) {
         results2.push_back(make_tuple(n, fibonacci(n)));
      });

      // Because parallel_for_each acts concurrently, the results do not 
      // have a pre-determined order. Sort the concurrent_vector object
      // so that the results match the serial version.
      sort(begin(results2), end(results2));
   });   
   wcout << L"parallel time: " << elapsed << L" ms" << endl << endl;

   // Print the results.
   for_each (begin(results2), end(results2), [](tuple<int,int>& pair) {
      wcout << L"fib(" << get<0>(pair) << L"): " << get<1>(pair) << endl;
   });
}
