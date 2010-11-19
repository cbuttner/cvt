#ifdef CVT_VECTOR_H

namespace cvt {

    template<typename T>
	class Vector3 {
	    public:
					Vector3();
					Vector3( T x, T y, T z );
					Vector3( const Vector3<T>& vec2 );

		void		set( T x, T y, T z );
		void		zero( void );

		T			operator[]( int index ) const;
		T&			operator[]( int index );
		Vector3<T>	operator-() const;
		T			operator*( const Vector3<T> &v ) const;
		Vector3<T>	operator*( const T c ) const;
		Vector3<T>	cmul( const Vector3<T>& v ) const;
		Vector3<T>	cross( const Vector3<T> &v ) const;
		Vector3<T>& cross( const Vector3<T>& a, const Vector3<T>& b );
		Vector3<T>	operator/( const T c ) const;
		Vector3<T>	operator+( const Vector3<T> &v ) const;
		Vector3<T>	operator-( const Vector3<T> &v ) const;
		Vector3<T>&	operator+=( const Vector3<T> &v );
		Vector3<T>&	operator-=( const Vector3<T> &v );
		Vector3<T>&	operator/=( const Vector3<T> &v );
		Vector3<T>&	operator+=( const T c );
		Vector3<T>&	operator-=( const T c );
		Vector3<T>&	operator/=( const T c );
		Vector3<T>&	operator*=( const T c );

/*		int		compare( const Vector3<T> &v ) const; **/
		bool		operator==( const Vector3<T> &v ) const;
		bool		operator!=( const Vector3<T> &v ) const;

		T			length( void ) const;
		T			lengthSqr( void ) const;
		T			normalize( void );		// returns length
		void		clamp( const Vector3<T> &min, const Vector3<T> &max );

		int			dimension( void ) const;

		const T*	ptr( void ) const;
		T*			ptr( void );

		void		mix( const Vector3<T> &v1, const Vector3<T> &v2, float alpha );

		T x, y, z;
	};

    template<typename T>
	inline Vector3<T>::Vector3()
	{
	    this->x = 0;
	    this->y = 0;
	    this->z = 0;
	}

    template<typename T>
	inline Vector3<T>::Vector3( T x, T y, T z )
	{
	    this->x = x;
	    this->y = y;
	    this->z = z;
	}

    template<typename T>
	inline Vector3<T>::Vector3( const Vector3<T>& v )
	{
	    x = v.x;
	    y = v.y;
	    z = v.z;
	}

    template<typename T>
	inline void Vector3<T>::set( T x, T y, T z )
	{
	    this->x = x;
	    this->y = y;
	    this->z = z;
	}

    template<typename T>
	inline void Vector3<T>::zero( )
	{
	    x = 0;
	    y = 0;
		z = 0;
	}

    template<typename T>
	inline T Vector3<T>::operator[]( int index ) const
	{
	    return ( &x )[ index ];
	}

    template<typename T>
	inline T& Vector3<T>::operator[]( int index )
	{
	    return ( &x )[ index ];
	}

    template<typename T>
	inline Vector3<T> Vector3<T>::operator-() const
	{
	    return Vector3<T>( -x, -y, -z );
	}

    template<typename T>
	inline Vector3<T> operator*( float c, const Vector3<T> &v )
	{
	    return Vector3<T>( c * v.x, c * v.y, c * v.z );
	}

    template<typename T>
	inline Vector3<T> Vector3<T>::operator*( const T c ) const
	{
	    return Vector3<T>( x * c, y * c, z * c );
	}

    template<typename T>
	inline Vector3<T> Vector3<T>::cmul( const Vector3<T>& v ) const
	{
	    return Vector3<T>( v.x * x, v.y * y, v.z * z );
	}

	template<typename T>
	inline Vector3<T> Vector3<T>::cross( const Vector3<T> &v ) const
	{
		return Vector3<T>( y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x );
	}

	template<typename T>
	inline Vector3<T>& Vector3<T>::cross( const Vector3<T>& a, const Vector3<T>& b )
	{
		x = a.y * b.z - a.z * b.y;
		y = a.z * b.x - a.x * b.z;
		z = a.x * b.y - a.y * b.x;
		return *this;
	}


    template<typename T>
	inline T Vector3<T>::operator*( const Vector3<T>& v ) const
	{
	    return v.x * x + v.y * y + v.z * z;
	}

    template<typename T>
	inline Vector3<T> Vector3<T>::operator/( const T c ) const
	{
	    T inv = ( ( T ) 1.0 ) / c;
	    return Vector3<T>( x * inv, y * inv, z * inv );
	}

    template<>
	inline Vector3<float> Vector3<float>::operator/( const float c ) const
	{
	    float inv = 1.0f / c;
	    return Vector3<float>( x * inv, y * inv, z * inv );
	}

    template<>
	inline Vector3<double> Vector3<double>::operator/( const double c ) const
	{
	    double inv = 1.0 / c;
	    return Vector3<double>( x * inv, y * inv, z * inv );
	}

    template<typename T>
	inline Vector3<T> Vector3<T>::operator+( const Vector3<T> &v ) const
	{
	    return Vector3<T>( x + v.x, y + v.y, z + v.z );
	}

    template<typename T>
	inline Vector3<T> Vector3<T>::operator-( const Vector3<T> &v ) const
	{
	    return Vector3<T>( x - v.x, y - v.y, z - v.z );
	}

    template<typename T>
	inline Vector3<T>& Vector3<T>::operator+=( const Vector3<T> &v )
	{
	    x += v.x;
	    y += v.y;
		z += v.z;
	    return *this;
	}

    template<typename T>
	inline Vector3<T>& Vector3<T>::operator-=( const Vector3<T> &v )
	{
	    x -= v.x;
	    y -= v.y;
		z -= v.z;
	    return *this;
	}

    template<typename T>
	inline Vector3<T>& Vector3<T>::operator/=( const Vector3<T> &v )
	{
	    x /= v.x;
	    y /= v.y;
	    z /= v.z;
	    return *this;
	}

    template<typename T>
	inline Vector3<T>& Vector3<T>::operator+=( const T c )
	{
	    x += c;
	    y += c;
		z += c;
	    return *this;
	}

    template<typename T>
	inline Vector3<T>& Vector3<T>::operator-=( const T c )
	{
	    x -= c;
	    y -= c;
	    z -= c;
	    return *this;
	}


    template<typename T>
	inline Vector3<T>& Vector3<T>::operator/=( const T c )
	{
	    x /= c;
	    y /= c;
	    z /= c;
	    return *this;
	}

    template<typename T>
	inline Vector3<T>& Vector3<T>::operator*=( const T c )
	{
	    x *= c;
	    y *= c;
	    z *= c;
	    return *this;
	}

	template<>
	inline bool Vector3<float>::operator==( const Vector3<float> &v ) const
	{
		return Math::abs( v.x - x ) < Math::EPSILONF
			&& Math::abs( v.y - y ) < Math::EPSILONF
			&& Math::abs( v.z - z ) < Math::EPSILONF;
	}

	template<>
	inline bool Vector3<float>::operator!=( const Vector3<float> &v ) const
	{
		return Math::abs( v.x - x ) > Math::EPSILONF
			|| Math::abs( v.y - y ) > Math::EPSILONF
			|| Math::abs( v.z - z ) > Math::EPSILONF;
	}

	template<>
	inline bool Vector3<double>::operator==( const Vector3<double> &v ) const
	{
		return Math::abs( v.x - x ) < Math::EPSILOND
			&& Math::abs( v.y - y ) < Math::EPSILOND
			&& Math::abs( v.z - z ) < Math::EPSILOND;
	}

	template<>
	inline bool Vector3<double>::operator!=( const Vector3<double> &v ) const
	{
		return Math::abs( v.x - x ) > Math::EPSILOND
			|| Math::abs( v.y - y ) > Math::EPSILOND
			|| Math::abs( v.z - z ) > Math::EPSILOND;
	}


    template<typename T>
	inline T Vector3<T>::length( void ) const
	{
	    return Math::sqrt( x * x + y * y + z * z );
	}

    template<typename T>
	inline T Vector3<T>::lengthSqr( void ) const
	{
	    return x * x + y * y + z * z;
	}

    template<typename T>
	T Vector3<T>::normalize( void )
	{
	    T lenSqr, lenInv;

	    lenSqr = x * x + y * y + z * z;
	    lenInv = Math::invSqrt( lenSqr );
	    x *= lenInv;
	    y *= lenInv;
	    return lenSqr * lenInv;
	}

    template<typename T>
	void Vector3<T>::clamp( const Vector3<T> &min, const Vector3<T> &max )
	{
	    x = Math::clamp( x, min.x, max.x );
	    y = Math::clamp( y, min.y, max.y );
	    z = Math::clamp( z, min.z, max.z );
	}

    template<typename T>
	int Vector3<T>::dimension( void ) const
	{
	    return 3;
	}

    template<typename T>
	const T* Vector3<T>::ptr( void ) const
	{
	    return &x;
	}

    template<typename T>
	T* Vector3<T>::ptr( void )
	{
	    return &x;
	}

    template<typename T>
	void Vector3<T>::mix( const Vector3<T> &v1, const Vector3<T> &v2, float alpha )
	{
	    x = Math::mix( v1.x, v2.x, alpha );
	    y = Math::mix( v1.y, v2.y, alpha );
	    z = Math::mix( v1.z, v2.z, alpha );
	}

	template<typename T>
	std::ostream& operator<<( std::ostream& out, const Vector3<T> &v )
	{
		out << " [ " << v.x << " " << v.y << " " << v.z << " ] ";
		return out;
	}


	typedef Vector3<float> Vector3f;
	typedef Vector3<double> Vector3d;
}

#endif