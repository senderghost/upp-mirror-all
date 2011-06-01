// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2011 Gael Guennebaud <gael.guennebaud@inria.fr>
//
// Eigen is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or (at your option) any later version.
//
// Alternatively, you can redistribute it and/or
// modify it under the terms of the GNU General Public License as
// published by the Free Software Foundation; either version 2 of
// the License, or (at your option) any later version.
//
// Eigen is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License and a copy of the GNU General Public License along with
// Eigen. If not, see <http://www.gnu.org/licenses/>.


// Various sanity tests with exceptions:
//  - no memory leak when a custom scalar type trow an exceptions
//  - todo: complete the list of tests!

#define EIGEN_STACK_ALLOCATION_LIMIT 100000000

#include "main.h"

struct my_exception
{
  my_exception() {}
  ~my_exception() {}
};
    
class ScalarWithExceptions
{
  public:
    ScalarWithExceptions() { init(); }
    ScalarWithExceptions(const float& _v) { init(); *v = _v; }
    ScalarWithExceptions(const ScalarWithExceptions& other) { init(); *v = *(other.v); }
    ~ScalarWithExceptions() {
      delete v;
      instances--;
    }

    void init() {
      v = new float;
      instances++;
    }

    ScalarWithExceptions operator+(const ScalarWithExceptions& other) const
    {
      countdown--;
      if(countdown<=0)
        throw my_exception();
      return ScalarWithExceptions(*v+*other.v);
    }
    
    ScalarWithExceptions operator-(const ScalarWithExceptions& other) const
    { return ScalarWithExceptions(*v-*other.v); }
    
    ScalarWithExceptions operator*(const ScalarWithExceptions& other) const
    { return ScalarWithExceptions((*v)*(*other.v)); }
    
    ScalarWithExceptions& operator+=(const ScalarWithExceptions& other)
    { *v+=*other.v; return *this; }
    ScalarWithExceptions& operator-=(const ScalarWithExceptions& other)
    { *v-=*other.v; return *this; }
    ScalarWithExceptions& operator=(const ScalarWithExceptions& other)
    { *v = *(other.v); return *this; }
  
    bool operator==(const ScalarWithExceptions& other) const
    { return *v==*other.v; }
    bool operator!=(const ScalarWithExceptions& other) const
    { return *v!=*other.v; }
    
    float* v;
    static int instances;
    static int countdown;
};

int ScalarWithExceptions::instances = 0;
int ScalarWithExceptions::countdown = 0;


#define CHECK_MEMLEAK(OP) {                                 \
    ScalarWithExceptions::countdown = 100;                  \
    int before = ScalarWithExceptions::instances;           \
    bool exception_thrown = false;                         \
    try { OP; }                              \
    catch (my_exception) {                                  \
      exception_thrown = true;                              \
      VERIFY(ScalarWithExceptions::instances==before && "memory leak detected in " && EIGEN_MAKESTRING(OP)); \
    } \
    VERIFY(exception_thrown && " no exception thrown in " && EIGEN_MAKESTRING(OP)); \
  }

void memoryleak()
{
  typedef Eigen::Matrix<ScalarWithExceptions,Dynamic,1> VectorType;
  typedef Eigen::Matrix<ScalarWithExceptions,Dynamic,Dynamic> MatrixType;
  
  {
    int n = 50;
    VectorType v0(n), v1(n);
    MatrixType m0(n,n), m1(n,n), m2(n,n);
    v0.setOnes(); v1.setOnes();
    m0.setOnes(); m1.setOnes(); m2.setOnes();
    CHECK_MEMLEAK(v0 = m0 * m1 * v1);
    CHECK_MEMLEAK(m2 = m0 * m1 * m2);
    CHECK_MEMLEAK((v0+v1).dot(v0+v1));
  }
  VERIFY(ScalarWithExceptions::instances==0 && "global memory leak detected in " && EIGEN_MAKESTRING(OP)); \
}

void test_exceptions()
{
  CALL_SUBTEST( memoryleak() );
}
