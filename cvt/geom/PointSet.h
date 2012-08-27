/*
			CVT - Computer Vision Tools Library

 	 Copyright (c) 2012, Philipp Heise, Sebastian Klose

 	THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 	KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 	IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 	PARTICULAR PURPOSE.
 */
#ifndef CVT_POINTSET_H
#define CVT_POINTSET_H

#include <cvt/util/SIMD.h>
#include <cvt/geom/Ellipse.h>
#include <cvt/math/Vector.h>
#include <cvt/math/Matrix.h>
#include <cvt/util/Exception.h>
#include <vector>
#include <Eigen/SVD>

namespace cvt
{
	template<int dim, typename _T>	class PointSet;

	typedef PointSet<2,float> PointSet2f;
	typedef PointSet<3,float> PointSet3f;
	typedef PointSet<2,double> PointSet2d;
	typedef PointSet<3,double> PointSet3d;

	template<int dim, typename _T>
	class PointSet
	{
			typedef typename Vector<dim,_T>::TYPE PTTYPE;
			typedef typename Matrix<dim,_T>::TYPE MATTYPENT;
			typedef typename Matrix<dim + 1,_T>::TYPE MATTYPE;

		public:
			PointSet();
			~PointSet();
			PointSet( const PointSet<dim,_T>& ptset );
			PointSet( const _T* data, size_t npts );
			void add( const PTTYPE& pt );
			void clear();
			PTTYPE& operator[]( int i );
			const PTTYPE& operator[]( int i ) const;
			PTTYPE mean() const;
			PTTYPE variance() const;
			size_t size() const;
			void resize( size_t );
			void translate( const PTTYPE& t );
			void scale( _T t );
			void transform( const MATTYPENT& mat );
			void transform( const MATTYPE& mat );
			void normalize( MATTYPE& mat );
			void normalize( );
			_T	 ssd( const PointSet<dim, _T>& ptset ) const;
			_T	 maxSquaredDistance( const PointSet<dim, _T>& ptset ) const;
			MATTYPE alignRigid( const PointSet<dim,_T>& ptset ) const;
			MATTYPE alignSimilarity( const PointSet<dim,_T>& ptset ) const;
			Matrix3<_T> alignPerspective( const PointSet<dim,_T>& ptset ) const;

			_T	 fitEllipse( Ellipse<_T>& ellipse ) const;

			/**
				 * Computes the essential matrix between two views from the same camera
				 * @param other the second point set
				 * @param K     intrinsic calibration matrix
				 * @return      3x3 essential Matrix from this to other
				 */
			Matrix3<_T> essentialMatrix( const PointSet<dim, _T>& other, const Matrix3<_T> & K ) const;

			/**
				 * Computes the essential matrix between two views from different cameras
				 * @param other the second point set
				 * @param K1 intrinsic matrix for this
				 * @param K2 intrinsic matrix for other
				 * @return 3x3 essential Matrix from this to other
				 */
			Matrix3<_T> essentialMatrix( const PointSet<dim, _T>& other, const Matrix3<_T> & K1, const Matrix3<_T> & K2 ) const;

			const _T* ptr() const;

		private:
			std::vector<PTTYPE>	_pts;
	};

	template<int dim, typename _T>
	inline PointSet<dim,_T>::PointSet()
	{
	}

	template<int dim, typename _T>
	inline PointSet<dim,_T>::~PointSet()
	{
	}

	template<int dim, typename _T>
		inline PointSet<dim,_T>::PointSet( const PointSet<dim,_T>& ptset ) : _pts( ptset._pts )
	{
	}

	template<int dim, typename _T>
	inline PointSet<dim,_T>::PointSet( const _T* data, size_t npts )
	{
		resize( npts );
		SIMD::instance()->Memcpy( ( uint8_t* ) &_pts[ 0 ], ( uint8_t* ) data, npts * sizeof( _T ) * dim );
	}

	template<int dim, typename _T>
	inline void PointSet<dim,_T>::clear()
	{
		_pts.clear();
	}

	template<int dim, typename _T>
	inline void PointSet<dim,_T>::add( const PTTYPE& pt )
	{
		_pts.push_back( pt );
	}

	template<int dim, typename _T>
	inline typename PointSet<dim, _T>::PTTYPE& PointSet<dim,_T>::operator[]( int i )
	{
		return _pts[ i ];
	}

	template<int dim, typename _T>
	inline const typename PointSet<dim,_T>::PTTYPE& PointSet<dim,_T>::operator[]( int i ) const
	{
		return _pts[ i ];
	}

	template<int dim, typename _T>
	inline	typename PointSet<dim,_T>::PTTYPE PointSet<dim,_T>::mean() const
	{
		const PTTYPE* pt = &_pts[ 0 ];
		PTTYPE mean;
		size_t n = _pts.size();

		mean.setZero();
		while( n-- )
			mean += *pt++;

		mean /= ( _T ) size();
		return mean;
	}

	template<>
	inline PointSet<2,float>::PTTYPE PointSet<2,float>::mean() const
	{
		const PTTYPE* pt = &_pts[ 0 ];
		PTTYPE mean;
		size_t n = _pts.size();

		SIMD::instance()->sumPoints( mean, pt, n );

		mean /= ( float ) size();
		return mean;
	}

	template<>
	inline PointSet<3,float>::PTTYPE PointSet<3,float>::mean() const
	{
		const PTTYPE* pt = &_pts[ 0 ];
		PTTYPE mean;
		size_t n = _pts.size();

		SIMD::instance()->sumPoints( mean, pt, n );

		mean /= ( float ) size();
		return mean;
	}

	template<int dim, typename _T>
	inline	typename PointSet<dim,_T>::PTTYPE PointSet<dim,_T>::variance() const
	{
		const PTTYPE* pt = &_pts[ 0 ];
		size_t n = size();
		PTTYPE mu = mean();
		PTTYPE var;

		var.setZero();
		while( n-- )
			var += ( *pt++ - mu ).lengthSqr();

		var /= ( _T ) size();
		return var;
	}


	template<int dim, typename _T>
	inline void PointSet<dim,_T>::translate( const PTTYPE& t )
	{
		PTTYPE* pt = &_pts[ 0 ];
		size_t n = _pts.size();
		while( n-- )
			*pt++ += t;
	}

	template<>
	inline void PointSet<2,float>::translate( const PTTYPE& t )
	{
		PTTYPE* pt = &_pts[ 0 ];
		size_t n = _pts.size();
		SIMD::instance()->translatePoints( pt, pt, t, n );
	}

	template<>
	inline void PointSet<3,float>::translate( const PTTYPE& t )
	{
		PTTYPE* pt = &_pts[ 0 ];
		size_t n = _pts.size();
		SIMD::instance()->translatePoints( pt, pt, t, n );
	}


	template<int dim, typename _T>
	inline void PointSet<dim,_T>::scale( _T s )
	{
		PTTYPE* pt = &_pts[ 0 ];
		size_t n = _pts.size();
		while( n-- )
			*pt++ *= s;
	}

	template<>
	inline void PointSet<2,float>::scale( float s )
	{
		float* pt = ( float* ) &_pts[ 0 ];
		size_t n = _pts.size();
		SIMD::instance()->MulValue1f( pt, pt, s, n * 2 );
	}

	template<>
	inline void PointSet<3,float>::scale( float s )
	{
		float* pt = ( float* ) &_pts[ 0 ];
		size_t n = _pts.size();
		SIMD::instance()->MulValue1f( pt, pt, s, n * 3 );
	}

	template<int dim, typename _T>
	inline void PointSet<dim,_T>::transform( const MATTYPENT& mat )
	{
		PTTYPE* pt = &_pts[ 0 ];
		size_t n = _pts.size();
		while( n-- ) {
			*pt = mat * *pt;
			pt++;
		}
	}


	template<>
	inline void PointSet<2,float>::transform( const MATTYPE& mat )
	{
		PTTYPE* pt = &_pts[ 0 ];
		size_t n = _pts.size();

		/* if last row is [ 0 0 1 ], split mat into 2 x 2 matrix and translation */
		if( mat[ 2 ] == Vector3f( 0, 0, 1.0f ) ) {
			SIMD::instance()->transformPoints( pt, mat, pt, n );
		} else {
			SIMD::instance()->transformPointsHomogenize( pt, mat, pt, n );
		}
	}

	template<>
	inline void PointSet<2,double>::transform( const MATTYPE& mat )
	{
		PTTYPE* pt = &_pts[ 0 ];
		size_t n = _pts.size();

		/* if last row is [ 0 0 1 ], split mat into 2 x 2 matrix and translation */
		if( mat[ 2 ] == Vector3d( 0, 0, 1.0 ) ) {
			Matrix2d _mat( mat );
			Vector2d trans( mat[ 0 ][ 2 ], mat[ 1 ][ 2 ] );
			while( n-- ) {
				*pt = _mat * *pt;
				*pt += trans;
				pt++;
			}
		} else {
			while( n-- ) {
				*pt = mat * *pt;
				pt++;
			}
		}
	}

	template<>
	inline void PointSet<3,float>::transform( const MATTYPE& mat )
	{
		PTTYPE* pt = &_pts[ 0 ];
		size_t n = _pts.size();

		/* if last row is [ 0 0 0 1 ], split mat into 3 x 3 matrix and translation */
		if( mat[ 2 ] == Vector4f( 0, 0, 0, 1.0f ) ) {
			SIMD::instance()->transformPoints( pt, mat, pt, n );
		} else {
			SIMD::instance()->transformPointsHomogenize( pt, mat, pt, n );
		}
	}

	template<>
	inline void PointSet<3,double>::transform( const MATTYPE& mat )
	{
		PTTYPE* pt = &_pts[ 0 ];
		size_t n = _pts.size();

		/* if last row is [ 0 0 0 1 ], split mat into 3 x 3 matrix and translation */
		if( mat[ 3 ] == Vector4d( 0, 0, 0, 1 ) ) {
			Matrix3d _mat( mat );
			Vector3d trans( mat[ 0 ][ 3 ], mat[ 1 ][ 3 ], mat[ 2 ][ 3 ] );
			while( n-- ) {
				*pt = _mat * *pt;
				*pt += trans;
				pt++;
			}
		} else {
			while( n-- ) {
				*pt = mat * *pt;
				pt++;
			}
		}
	}

	template<int dim, typename _T>
	inline void PointSet<dim,_T>::normalize( MATTYPE& mat )
	{
		PTTYPE* pt = &_pts[ 0 ];
		PTTYPE m = mean();
		_T s = 0;
		size_t n = size();


		/* remove mean */
		while( n-- ) {
			*pt -= m;
			s += pt->length();
			pt++;
		}

		/* scale */
		s = ( Math::sqrt( ( _T ) 2 ) * ( _T ) size() ) / s;
		scale( s );

		mat.setIdentity();
		for( int i = 0; i < mat.dimension() - 1; i++ ) {
			mat[ i ][ i ] = s;
			mat[ i ][ mat.dimension() - 1 ] = -m[ i ] * s;
		}
	}

	template<int dim, typename _T>
	inline void PointSet<dim,_T>::normalize()
	{
		PTTYPE* pt = &_pts[ 0 ];
		PTTYPE m = mean();
		_T s = 0;
		size_t n = size();


		/* remove mean */
		while( n-- ) {
			*pt -= m;
			s += pt->length();
			pt++;
		}

		/* scale */
		s = ( Math::sqrt( ( _T ) 2 ) * ( _T ) size() ) / s;
		scale( s );
	}

	template<int dim, typename _T>
	inline size_t PointSet<dim,_T>::size( ) const
	{
		return _pts.size();
	}

	template<int dim, typename _T>
	inline void PointSet<dim,_T>::resize( size_t n )
	{
		return _pts.resize( n );
	}

	template<int dim, typename _T>
	inline const _T* PointSet<dim,_T>::ptr() const
	{
		return ( _T* ) &_pts[ 0 ];
	}

    template<int dim, typename _T>
    inline Matrix3<_T> PointSet<dim,_T>::alignPerspective( const PointSet<dim,_T>& ) const
    {
        Matrix3<_T> ret;
        ret.setZero();
        return ret;
    }

    template<int dim, typename _T>
    inline Matrix3<_T> PointSet<dim, _T>::essentialMatrix( const PointSet<dim, _T>&, const Matrix3<_T> & ) const
        {
            Matrix3<_T> E;
            E.setZero();
            return E;
        }

    template<int dim, typename _T>
    inline Matrix3<_T> PointSet<dim, _T>::essentialMatrix( const PointSet<dim, _T>&, const Matrix3<_T> &, const Matrix3<_T> & ) const
    {
        // default implementation for dimensions that do not make sense
        Matrix3<_T> E;
        E.setZero();
        return E;
    }

	template<int dim, typename _T>
	inline std::ostream& operator<<( std::ostream& out, const PointSet<dim,_T>& ptset )
	{
		out << "PointSet" << dim << " ( " << ptset.size() << " entries ):" << std::endl;
		const typename Vector<dim,_T>::TYPE* pt = &ptset[ 0 ];
		size_t n = ptset.size();
		while( n-- )
			std::cout << "\t" << ( *pt++ ) << std::endl;
		return out;
	}

}
#endif
