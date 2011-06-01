// This file is part of Eigen, a lightweight C++ template library
// for linear algebra.
//
// Copyright (C) 2008-2009 Gael Guennebaud <gael.guennebaud@inria.fr>
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

#include "main.h"

template<typename Scalar, int Size, int OtherSize> void symm(int size = Size, int othersize = OtherSize)
{
  typedef typename NumTraits<Scalar>::Real RealScalar;

  typedef Matrix<Scalar, Size, Size> MatrixType;
  typedef Matrix<Scalar, Size, OtherSize> Rhs1;
  typedef Matrix<Scalar, OtherSize, Size> Rhs2;
  enum { order = OtherSize==1 ? 0 : RowMajor };
  typedef Matrix<Scalar, Size, OtherSize,order> Rhs3;
  typedef typename MatrixType::Index Index;

  Index rows = size;
  Index cols = size;

  MatrixType m1 = MatrixType::Random(rows, cols),
             m2 = MatrixType::Random(rows, cols), m3;

  m1 = (m1+m1.adjoint()).eval();

  Rhs1 rhs1 = Rhs1::Random(cols, othersize), rhs12(cols, othersize), rhs13(cols, othersize);
  Rhs2 rhs2 = Rhs2::Random(othersize, rows), rhs22(othersize, rows), rhs23(othersize, rows);
  Rhs3 rhs3 = Rhs3::Random(cols, othersize), rhs32(cols, othersize), rhs33(cols, othersize);

  Scalar s1 = internal::random<Scalar>(),
         s2 = internal::random<Scalar>();

  m2 = m1.template triangularView<Lower>();
  m3 = m2.template selfadjointView<Lower>();
  VERIFY_IS_EQUAL(m1, m3);
  VERIFY_IS_APPROX(rhs12 = (s1*m2).template selfadjointView<Lower>() * (s2*rhs1),
                   rhs13 = (s1*m1) * (s2*rhs1));

  m2 = m1.template triangularView<Upper>(); rhs12.setRandom(); rhs13 = rhs12;
  m3 = m2.template selfadjointView<Upper>();
  VERIFY_IS_EQUAL(m1, m3);
  VERIFY_IS_APPROX(rhs12 += (s1*m2).template selfadjointView<Upper>() * (s2*rhs1),
                   rhs13 += (s1*m1) * (s2*rhs1));

  m2 = m1.template triangularView<Lower>();
  VERIFY_IS_APPROX(rhs12 = (s1*m2).template selfadjointView<Lower>() * (s2*rhs2.adjoint()),
                   rhs13 = (s1*m1) * (s2*rhs2.adjoint()));

  m2 = m1.template triangularView<Upper>();
  VERIFY_IS_APPROX(rhs12 = (s1*m2).template selfadjointView<Upper>() * (s2*rhs2.adjoint()),
                   rhs13 = (s1*m1) * (s2*rhs2.adjoint()));

  m2 = m1.template triangularView<Upper>();
  VERIFY_IS_APPROX(rhs12 = (s1*m2.adjoint()).template selfadjointView<Lower>() * (s2*rhs2.adjoint()),
                   rhs13 = (s1*m1.adjoint()) * (s2*rhs2.adjoint()));

  // test row major = <...>
  m2 = m1.template triangularView<Lower>(); rhs12.setRandom(); rhs13 = rhs12;
  VERIFY_IS_APPROX(rhs12 -= (s1*m2).template selfadjointView<Lower>() * (s2*rhs3),
                   rhs13 -= (s1*m1) * (s2 * rhs3));

  m2 = m1.template triangularView<Upper>();
  VERIFY_IS_APPROX(rhs12 = (s1*m2.adjoint()).template selfadjointView<Lower>() * (s2*rhs3).conjugate(),
                   rhs13 = (s1*m1.adjoint()) * (s2*rhs3).conjugate());


  m2 = m1.template triangularView<Upper>(); rhs13 = rhs12;
  VERIFY_IS_APPROX(rhs12.noalias() += s1 * ((m2.adjoint()).template selfadjointView<Lower>() * (s2*rhs3).conjugate()),
                   rhs13 += (s1*m1.adjoint()) * (s2*rhs3).conjugate());

  m2 = m1.template triangularView<Lower>();
  VERIFY_IS_APPROX(rhs22 = (rhs2) * (m2).template selfadjointView<Lower>(), rhs23 = (rhs2) * (m1));
  VERIFY_IS_APPROX(rhs22 = (s2*rhs2) * (s1*m2).template selfadjointView<Lower>(), rhs23 = (s2*rhs2) * (s1*m1));

}

void test_product_symm()
{
  for(int i = 0; i < g_repeat ; i++)
  {
    CALL_SUBTEST_1(( symm<float,Dynamic,Dynamic>(internal::random<int>(1,320),internal::random<int>(1,320)) ));
    CALL_SUBTEST_2(( symm<double,Dynamic,Dynamic>(internal::random<int>(1,320),internal::random<int>(1,320)) ));
    CALL_SUBTEST_3(( symm<std::complex<float>,Dynamic,Dynamic>(internal::random<int>(1,200),internal::random<int>(1,200)) ));
    CALL_SUBTEST_4(( symm<std::complex<double>,Dynamic,Dynamic>(internal::random<int>(1,200),internal::random<int>(1,200)) ));

    CALL_SUBTEST_5(( symm<float,Dynamic,1>(internal::random<int>(1,320)) ));
    CALL_SUBTEST_6(( symm<double,Dynamic,1>(internal::random<int>(1,320)) ));
    CALL_SUBTEST_7(( symm<std::complex<float>,Dynamic,1>(internal::random<int>(1,320)) ));
    CALL_SUBTEST_8(( symm<std::complex<double>,Dynamic,1>(internal::random<int>(1,320)) ));
  }
}
