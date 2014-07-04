/*
   The MIT License (MIT)

   Copyright (c) 2011 - 2013, Philipp Heise and Sebastian Klose

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included in
   all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#ifndef CVT_SPHERE_H
#define CVT_SPHERE_H

#include <cvt/math/Vector.h>
#include <cvt/util/String.h>

#include <cvt/util/DataIterator.h>

namespace cvt
{
	template <typename T>
	class Sphere
	{
	public:

		Sphere();
		Sphere( const Vector3<T>& center, T radius );

		const Vector3<T>&	center() const;

		T 					radius() const;
		T 					diameter() const;

		void 				setCenter( const Vector3<T>& center );
		void 				setRadius( T radius );

		T 					volume() const;
		T 					surfaceArea() const;

	private:

		Vector3<T>	_center;
		T			_radius;
	};

	typedef Sphere<float> Spheref;
	typedef Sphere<double> Sphered;

	template <typename T>
	inline Sphere<T>::Sphere() :
		_center( 0, 0, 0 ),
		_radius( 0 )
	{
	}

	template <typename T>
	inline Sphere<T>::Sphere( const Vector3<T>& center, T radius ) :
		_center( center ),
		_radius( radius )
	{
	}

	template <typename T>
	inline const Vector3<T>& Sphere<T>::center() const
	{
		return _center;
	}

	template <typename T>
	inline T Sphere<T>::radius() const
	{
		return _radius;
	}

	template <typename T>
	inline T Sphere<T>::diameter() const
	{
		return _radius * ( T ) 2;
	}

	template <typename T>
	inline void Sphere<T>::setCenter( const Vector3<T>& center )
	{
		_center = center;
	}

	template <typename T>
	inline void Sphere<T>::setRadius( T radius )
	{
		_radius = radius;
	}	

	template <typename T>
	inline T Sphere<T>::volume() const
	{
		return ( ( T ) 4 / ( T ) 3 ) * Math::PI * _radius * _radius * _radius;
	}

	template <typename T>
	inline T Sphere<T>::surfaceArea() const
	{
		return ( T ) 4 * Math::PI * _radius * _radius;
	}
}

#endif
