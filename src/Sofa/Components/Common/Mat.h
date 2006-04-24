#ifndef SOFA_COMPONENTS_COMMON_MAT_H
#define SOFA_COMPONENTS_COMMON_MAT_H

#include "Vec.h"
//#include <boost/static_assert.hpp>
#define BOOST_STATIC_ASSERT(a)

namespace Sofa
{

namespace Components
{

namespace Common
{

template <int L, int C, class real=float>
class Mat : public fixed_array<Vec<C,real>,L>
    //class Mat : public Vec<L,Vec<C,real> >
{
public:

    enum { N = L*C };

    typedef Vec<C,real> Line;
    typedef Vec<L,real> Col;

    Mat()
    {
    }

    /*
      /// Specific constructor with a single line.
      Mat(Line r1)
      {
        BOOST_STATIC_ASSERT(L == 1);
        this->elems[0]=r1;
      }
    */

    /// Specific constructor with 2 lines.
    Mat(Line r1, Line r2)
    {
        BOOST_STATIC_ASSERT(L == 2);
        this->elems[0]=r1;
        this->elems[1]=r2;
    }

    /// Specific constructor with 3 lines.
    Mat(Line r1, Line r2, Line r3)
    {
        BOOST_STATIC_ASSERT(L == 3);
        this->elems[0]=r1;
        this->elems[1]=r2;
        this->elems[2]=r3;
    }

    /// Specific constructor with 4 lines.
    Mat(Line r1, Line r2, Line r3, Line r4)
    {
        BOOST_STATIC_ASSERT(L == 4);
        this->elems[0]=r1;
        this->elems[1]=r2;
        this->elems[2]=r3;
        this->elems[3]=r4;
    }

    /// Constructor from an array of elements (stored per line).
    template<typename real2>
    explicit Mat(const real2* p)
    {
        std::copy(p, p+N, this->begin()->begin());
    }

    /// Assignment from an array of elements (stored per line).
    void operator=(const real* p)
    {
        std::copy(p, p+N, this->begin()->begin());
    }

    /// Assignment from a matrix of different size.
    template<int L2, int C2> void operator=(const Mat<L2,C2,real>& m)
    {
        std::copy(m.begin(), m.begin()+(L>L2?L2:L), this->begin());
    }

    /// Sets each element to 0.
    void clear()
    {
        for (int i=0; i<L; i++)
            this->elems[i].clear();
    }

    /// Sets each element to r.
    void fill(real r)
    {
        for (int i=0; i<L; i++)
            this->elems[i].fill(r);
    }

    /// Read-only access to line i.
    const Line& line(int i) const
    {
        return this->elems[i];
    }

    /// Copy of column j.
    Col col(int j) const
    {
        Col c;
        for (int i=0; i<L; i++)
            c[i]=this->elems[i][j];
        return c;
    }

    /// Write acess to line i.
    Line& operator[](int i)
    {
        return this->elems[i];
    }

    /// Read-only access to line i.
    const Line& operator[](int i) const
    {
        return this->elems[i];
    }

    /// Write acess to line i.
    Line& operator()(int i)
    {
        return this->elems[i];
    }

    /// Read-only access to line i.
    const Line& operator()(int i) const
    {
        return this->elems[i];
    }

    /// Write access to element (i,j).
    real& operator()(int i, int j)
    {
        return this->elems[i][j];
    }

    /// Read-only access to element (i,j).
    const real& operator()(int i, int j) const
    {
        return this->elems[i][j];
    }

    /// Cast into a standard C array of lines (read-only).
    const Line* lptr() const
    {
        return this->elems;
    }

    /// Cast into a standard C array of lines.
    Line* lptr()
    {
        return this->elems;
    }

    /// Cast into a standard C array of elements (stored per line) (read-only).
    const real* ptr() const
    {
        return this->elems[0].ptr();
    }

    /// Cast into a standard C array of elements (stored per line).
    real* ptr()
    {
        return this->elems[0].ptr();
    }

    /// Special access to first line.
    Line& x() { BOOST_STATIC_ASSERT(L >= 1); return this->elems[0]; }
    /// Special access to second line.
    Line& y() { BOOST_STATIC_ASSERT(L >= 2); return this->elems[1]; }
    /// Special access to third line.
    Line& z() { BOOST_STATIC_ASSERT(L >= 3); return this->elems[2]; }
    /// Special access to fourth line.
    Line& w() { BOOST_STATIC_ASSERT(L >= 4); return this->elems[3]; }

    /// Special access to first line (read-only).
    const Line& x() const { BOOST_STATIC_ASSERT(L >= 1); return this->elems[0]; }
    /// Special access to second line (read-only).
    const Line& y() const { BOOST_STATIC_ASSERT(L >= 2); return this->elems[1]; }
    /// Special access to thrid line (read-only).
    const Line& z() const { BOOST_STATIC_ASSERT(L >= 3); return this->elems[2]; }
    /// Special access to fourth line (read-only).
    const Line& w() const { BOOST_STATIC_ASSERT(L >= 4); return this->elems[3]; }

    /// Set matrix to identity.
    void identity()
    {
        BOOST_STATIC_ASSERT(L == C);
        clear();
        for (int i=0; i<L; i++)
            this->elems[i][i]=1;
    }

    /// Set matrix as the transpose of m.
    void transpose(const Mat<C,L,real> &m)
    {
        for (int i=0; i<L; i++)
            for (int j=0; j<C; j++)
                this->elems[i][j]=m[j][i];
    }

    /// Set matrix as the transpose of m.
    Mat transposed()
    {
        Mat m;
        for (int i=0; i<L; i++)
            for (int j=0; j<C; j++)
                m[j][i]=this->elems[i][j];
        return m;
    }

    /// Transpose current matrix.
    void transpose()
    {
        BOOST_STATIC_ASSERT(L == C)
        for (int i=0; i<L; i++)
            for (int j=i+1; j<C; j++)
            {
                real t = this->elems[i][j];
                this->elems[i][j] = this->elems[j][i];
                this->elems[j][i] = t;
            }
    }

    // LINEAR ALGEBRA

    /// Matrix multiplication operator.
    template <int P>
    Mat<L,P,real> operator*(const Mat<C,P,real>& m) const
    {
        Mat<L,P,real> r;
        for(int i=0; i<L; i++)
            for(int j=0; j<P; j++)
            {
                r[i][j]=(*this)[i][0] * m[0][j];
                for(int k=1; k<C; k++)
                    r[i][j] += (*this)[i][k] * m[k][j];
            }
        return r;
    }

    /// Matrix addition operator.
    Mat<L,C,real> operator+(const Mat<L,C,real>& m) const
    {
        Mat r;
        for(int i = 0; i < L; i++)
            r[i] = (*this)[i] + m[i];
        return r;
    }

    /// Matrix subtraction operator.
    Mat<L,C,real> operator-(const Mat<L,C,real>& m) const
    {
        Mat r;
        for(int i = 0; i < L; i++)
            r[i] = (*this)[i] - m[i];
        return r;
    }

    /// Multiplication operator Matrix * Column.
    Col operator*(const Line& v) const
    {
        Col r;
        for(int i=0; i<L; i++)
        {
            r[i]=(*this)[i][0] * v[0];
            for(int j=1; j<C; j++)
                r[i] += (*this)[i][j] * v[j];
        }
        return r;
    }

    /// Scalar multiplication operator.
    Mat<L,C,real> operator*(real f) const
    {
        Mat<L,C,real> r;
        for(int i=0; i<L; i++)
            for(int j=0; j<C; j++)
                r[i][j] = (*this)[i][j] * f;
        return r;
    }

    /// Scalar multiplication assignment operator.
    void operator *=(real r)
    {
        for(int i=0; i<L; i++)
            this->elems[i]*=r;
    }

    /// Addition assignment operator.
    void operator +=(const Mat<L,C,real>& m)
    {
        for(int i=0; i<L; i++)
            this->elems[i]+=m[i];
    }

    /// Determinant of the matrix.
    /// @ATTENTION: determinant currently only implemented for 3x3 matrices.
    real determinant() const
    {
        BOOST_STATIC_ASSERT(L == 3);
        BOOST_STATIC_ASSERT(C == 3);
        return (*this)(0,0)*(*this)(1,1)*(*this)(2,2)
                + (*this)(1,0)*(*this)(2,1)*(*this)(0,2)
                + (*this)(2,0)*(*this)(0,1)*(*this)(1,2)
                - (*this)(0,0)*(*this)(2,1)*(*this)(1,2)
                - (*this)(1,0)*(*this)(0,1)*(*this)(2,2)
                - (*this)(2,0)*(*this)(1,1)*(*this)(0,2);
    }

    /// Invert matrix m
    bool invert(const Mat<L,C,real>& m)
    {
        return invertMatrix(*this, m);
    }

};

/// Matrix inversion (general case).
template<int S, class real>
bool invertMatrix(Mat<S,S,real>& dest, const Mat<S,S,real>& from)
{
    int i, j, k;
    Vec<S,int> r, c, row, col;

    Mat<S,S,real> m1 = from;
    Mat<S,S,real> m2;
    m2.identity();

    for ( k = 0; k < S; k++ )
    {
        // Choosing the pivot
        real pivot = 0;
        for (i = 0; i < S; i++)
        {
            if (row[i])
                continue;
            for (j = 0; j < S; j++)
            {
                if (col[j])
                    continue;
                real t = m1[i][j]; if (t<0) t=-t;
                if ( t > pivot)
                {
                    pivot = t;
                    r[k] = i;
                    c[k] = j;
                }
            }
        }

        if (pivot <= 1e-10)
        {
            return false;
        }

        row[r[k]] = col[c[k]] = 1;
        pivot = m1[r[k]][c[k]];

        // Normalization
        m1[r[k]] /= pivot; m1[r[k]][c[k]] = 1;
        m2[r[k]] /= pivot;

        // Reduction
        for (i = 0; i < S; i++)
        {
            if (i != r[k])
            {
                real f = m1[i][c[k]];
                m1[i] -= m1[r[k]]*f; m1[i][c[k]] = 0;
                m2[i] -= m2[r[k]]*f;
            }
        }
    }

    for (i = 0; i < S; i++)
        for (j = 0; j < S; j++)
            if (c[j] == i)
                row[i] = r[j];

    for ( i = 0; i < S; i++ )
        dest[i] = m2[row[i]];

    return true;
}

/// Matrix inversion (special case 3x3).
template<class real>
bool invertMatrix(Mat<3,3,real>& dest, const Mat<3,3,real>& from)
{
    real det=from.determinant();

    if ( -1e-10<=det && det<=1e-10)
        return false;

    dest(0,0)= (from(1,1)*from(2,2) - from(2,1)*from(1,2))/det;
    dest(1,0)= (from(1,2)*from(2,0) - from(2,2)*from(1,0))/det;
    dest(2,0)= (from(1,0)*from(2,1) - from(2,0)*from(1,1))/det;
    dest(0,1)= (from(2,1)*from(0,2) - from(0,1)*from(2,2))/det;
    dest(1,1)= (from(2,2)*from(0,0) - from(0,2)*from(2,0))/det;
    dest(2,1)= (from(2,0)*from(0,1) - from(0,0)*from(2,1))/det;
    dest(0,2)= (from(0,1)*from(1,2) - from(1,1)*from(0,2))/det;
    dest(1,2)= (from(0,2)*from(1,0) - from(1,2)*from(0,0))/det;
    dest(2,2)= (from(0,0)*from(1,1) - from(1,0)*from(0,1))/det;

    return true;
}

/// Matrix inversion (special case 2x2).
template<class real>
bool invertMatrix(Mat<2,2,real>& dest, const Mat<2,2,real>& from)
{
    real det=from(0,0)*from(1,1)-from(0,1)*from(1,0);

    if ( -1e-10<=det && det<=1e-10)
        return false;

    dest(0,0)=  from(1,1)/det;
    dest(0,1)= -from(0,1)/det;
    dest(1,0)= -from(1,0)/det;
    dest(1,1)=  from(0,0)/det;

    return true;
}

typedef Mat<3,3,float> Mat3x3f;
typedef Mat<3,3,double> Mat3x3d;

typedef Mat<3,4,float> Mat3x4f;
typedef Mat<3,4,double> Mat3x4d;

typedef Mat<4,4,float> Mat4x4f;
typedef Mat<4,4,double> Mat4x4d;

typedef Mat3x3d Matrix3;
typedef Mat4x4d Matrix4;

#undef BOOST_STATIC_ASSERT



template <int L, int C, typename real>
std::ostream& operator<<(std::ostream& o, const Mat<L,C,real>& m)
{
    o << '<' << m[0];
    for (int i=1; i<L; i++)
        o << ',' << m[i];
    o << '>';
    return o;
}

template <int L, int C, typename real>
std::istream& operator>>(std::istream& in, Sofa::Components::Common::Mat<L,C,real>& m)
{
    int c;
    c = in.peek();
    while (c==' ' || c=='\n' || c=='<')
    {
        in.get();
        c = in.peek();
    }
    in >> m[0];
    for (int i=1; i<L; i++)
    {
        c = in.peek();
        while (c==' ' || c==',')
        {
            in.get();
            c = in.peek();
        }
        in >> m[i];
    }
    c = in.peek();
    while (c==' ' || c=='\n' || c=='>')
    {
        in.get();
        c = in.peek();
    }
    return in;
}

} // namespace Common

} // namespace Components

} // namespace Sofa

// iostream



/// Scalar matrix multiplication operator.
template <int L, int C, typename real>
Sofa::Components::Common::Mat<L,C,real> operator*(real r, const Sofa::Components::Common::Mat<L,C,real>& m)
{
    return m*r;
}

#endif
