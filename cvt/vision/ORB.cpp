#include <cvt/vision/ORB.h>


namespace cvt {
   
	ORB::ORB( const Image& img, size_t octaves, float scalefactor, uint8_t cornerThreshold ) :
        _threshold( cornerThreshold )
	{
		float scale = 1.0f;
        IScaleFilterBilinear scaleFilter;
        detect( img, scale );
		for( size_t i = 1; i < octaves; i++ ) {
			Image pyrimg;
			scale *=  scalefactor;
			img.scale( pyrimg, ( size_t )( img.width() * scalefactor ), ( size_t )( img.height() * scalefactor ), scaleFilter );
			detect( pyrimg, scale );
		}
	}

	void ORB::detect( const Image& img, float scale )
	{
        // detect the features for this level
        size_t featureIdx = _features.size();

        size_t stride;
        const uint8_t * ptr = img.map( &stride );        
        detect9( ptr, stride, img.width(), img.height(), scale );        
        img.unmap( ptr );
        
        IntegralImage iimg( img );
        while( featureIdx < _features.size() ){
            centroidAngle( _features[ featureIdx ], iimg );
            descriptor( _features[ featureIdx ], iimg );
            featureIdx++;
        }
	}

	void ORB::centroidAngle( ORBFeature& feature, IntegralImage& iimg )
	{
	}

	void ORB::descriptor( ORBFeature& feature, IntegralImage& iimg )
	{
	}
    
    void ORB::detect9( const uint8_t* im, size_t stride, size_t width, size_t height, float scale )    
    {
		makeOffsets( stride );
        size_t h = height - _border;
        size_t w = width - _border;
        
        im += ( _border * stride + _border );
        
        _features.reserve( 1024 );
        int upperBound;        
        int lowerBound;

        for( size_t y = _border; y < h; y++ ){
            const uint8_t * curr = im;
            
            for( size_t x = _border; x < w; x++ ){
                lowerBound = *curr - _threshold;
                upperBound = *curr + _threshold;
                
                if( lowerBound && isDarkerCorner9( curr, lowerBound ) ){
                    _features.push_back( ORBFeature( x, y, 0.0f, scale ) );
                } else {
                    if( upperBound < 255 && isBrighterCorner9( curr, upperBound ) ){
                        _features.push_back( ORBFeature( x, y, 0.0f, scale ) );
                    }
                }
                curr++;
            }
            im += stride;
        }
        
    }
    
    void ORB::makeOffsets( size_t row_stride )
	{
        
        if( _lastStride == row_stride )
            return;
        
        _lastStride = row_stride;
    
        _pixel[0]  =  0 + _lastStride * 3;
		_pixel[1]  =  1 + _lastStride * 3;
		_pixel[2]  =  2 + _lastStride * 2;
		_pixel[3]  =  3 + _lastStride * 1;
		_pixel[4]  =  3;
		_pixel[5]  =  3 - _lastStride * 1;
		_pixel[6]  =  2 - _lastStride * 2;
		_pixel[7]  =  1 - _lastStride * 3;
		_pixel[8]  =    - _lastStride * 3;
		_pixel[9]  = -1 - _lastStride * 3;
		_pixel[10] = -2 - _lastStride * 2;
		_pixel[11] = -3 - _lastStride * 1;
		_pixel[12] = -3;
		_pixel[13] = -3 + _lastStride;
		_pixel[14] = -2 + _lastStride * 2;
		_pixel[15] = -1 + _lastStride * 3;
    }
    
    bool ORB::isDarkerCorner9( const uint8_t * p, const int barrier )
	{
		if( !( p[ _pixel[ 15 ] ] < barrier ) ) {     // ???????????????-
            if( !(p[ _pixel[ 8 ] ] < barrier ) ) {   // ????????-??????-
				return false;
			}                                       // ????????@??????-
            if( !(p[ _pixel[ 7 ] ] < barrier ) ) {   // ???????-@??????-
				return false;
			}										// ???????@@??????-
            if( !(p[ _pixel[ 6 ] ] < barrier ) ) {   // ??????-@@??????-
				return false;
			}                                           // ??????@@@??????-
            if( !(p[ _pixel[ 3 ] ] < barrier ) ) {		// ??????@@@??????-
                if( !(p[ _pixel[ 10 ] ] < barrier ) ){  // ?????-@@@?????--
					return false;
				}                               // ?????-@@@?????@- :p13
                if( !(p[ _pixel[ 11 ] ] < barrier ) ) {   // ?????-@@@????-@-
					return false;
				}                               // ?????-@@@????@@-
                if( !(p[ _pixel[ 15 ] ] < barrier ) ) {  // ?????-@@@-???@@-
					return false;
				}                               // ?????-@@@@???@@-
                if( !(p[ _pixel[ 14 ] ] < barrier ) ) { // ?????-@@@@-??@@-
					return false;
				} // ?????-@@@@@??@@-
                if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // ?????-@@@@@-?@@-
					return false;
				} // ?????-@@@@@@?@@-
                if( !(p[ _pixel[ 12 ] ] < barrier ) ) { // ?????-@@@@@@-@@-
					return false;
				} // ?????-@@@@@@@@@-
				return true;
			} // ?????@@@@??????-
            if( !(p[ _pixel[ 4 ] ] < barrier ) ) { // ????-@@@@??????-
                if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // ????-@@@@????-?-
					return false;
				} // ????-@@@@????@?-
                if( !(p[ _pixel[ 15 ] ] < barrier ) ) { // ????-@@@@-???@?-
					return false;
				} // ????-@@@@@???@?-
                if( !(p[ _pixel[ 14 ] ] < barrier ) ) { // ????-@@@@@-??@?-
					return false;
				} // ????-@@@@@@??@?-
                if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // ????-@@@@@@-?@?-
					return false;
				} // ????-@@@@@@@?@?-
                if( !(p[ _pixel[ 12 ] ] < barrier ) ) { // ????-@@@@@@@-@?-
					return false;
				} // ????-@@@@@@@@@?-
				return true;
			} // ????@@@@@??????-
            if( !(p[ _pixel[ 5 ] ] < barrier ) ) { // ???-@@@@@??????-
                if( !(p[ _pixel[ 15 ] ] < barrier ) ) { // ???-@@@@@-?????-
					return false;
				} // ???-@@@@@@?????-
                if( !(p[ _pixel[ 14 ] ] < barrier ) ) { // ???-@@@@@@-????-
					return false;
				} // ???-@@@@@@@????-
                if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // ???-@@@@@@@-???-
					return false;
				} // ???-@@@@@@@@???-
                if( !(p[ _pixel[ 12 ] ] < barrier ) ) { // ???-@@@@@@@@-??-
					return false;
				} // ???-@@@@@@@@@??-
				return true;
			} // ???@@@@@@??????-
            if( !(p[ _pixel[ 15 ] ] < barrier ) ) { // ???@@@@@@-?????-
                if( !(p[ _pixel[ 8 ] ] < barrier ) ) { // -??@@@@@@-?????-
					return false;
				} // @??@@@@@@-?????-
                if( !(p[ _pixel[ 7 ] ] < barrier ) ) { // @-?@@@@@@-?????-
					return false;
				} // @@?@@@@@@-?????-
                if( !(p[ _pixel[ 6 ] ] < barrier ) ) { // @@-@@@@@@-?????-
					return false;
				} // @@@@@@@@@-?????-
				return true;
			} // ???@@@@@@@?????-
            if( !(p[ _pixel[ 6 ] ] < barrier ) ) { // ??-@@@@@@@?????-
                if( !(p[ _pixel[ 14 ] ] < barrier ) ) { // ??-@@@@@@@-????-
					return false;
				} // ??-@@@@@@@@????-
                if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // ??-@@@@@@@@-???-
					return false;
				} // ??-@@@@@@@@@???-
				return true;
			} // ??@@@@@@@@?????-
            if( !(p[ _pixel[ 14 ] ] < barrier ) ) { // ??@@@@@@@@-????-
                if( !(p[ _pixel[ 7 ] ] < barrier ) ) { // ?-@@@@@@@@-????-
					return false;
				} // ?@@@@@@@@@-????-
				return true;
			} // ??@@@@@@@@@????-
			return true;
		} // ???????????????@
        if( !(p[ _pixel[ 10 ] ] < barrier ) ) { // ??????????????-@
            if( !(p[ _pixel[ 3 ] ] < barrier ) ) { // ?????-????????-@
				return false;
			} // ?????@????????-@
            if( !(p[ _pixel[ 1 ]] < barrier ) ) { // ?????@?-??????-@
				return false;
			} // ?????@?@??????-@
            if( !(p[ _pixel[ 2 ] ] < barrier ) ) { // ?????@-@??????-@
				return false;
			} // ?????@@@??????-@
            if( !(p[ _pixel[ 4 ] ] < barrier ) ) { // ????-@@@??????-@
                if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // ????-@@@?????--@
					return false;
				} // ????-@@@?????@-@
                if( !(p[ _pixel[ 12 ] ] < barrier ) ) { // ????-@@@????-@-@
					return false;
				} // ????-@@@????@@-@
                if( !(p[ _pixel[ 0 ]] < barrier ) ) { // ????-@@@-???@@-@
					return false;
				} // ????-@@@@???@@-@
                if( !(p[ _pixel[ 15 ] ] < barrier ) ) { // ????-@@@@-??@@-@
					return false;
				} // ????-@@@@@??@@-@
                if( !(p[ _pixel[ 14 ] ] < barrier ) ) { // ????-@@@@@-?@@-@
					return false;
				} // ????-@@@@@@?@@-@
                if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // ????-@@@@@@-@@-@
					return false;
				} // ????-@@@@@@@@@-@
				return true;
			} // ????@@@@??????-@
            if( !(p[ _pixel[ 5 ] ] < barrier ) ) { // ???-@@@@??????-@
                if( !(p[ _pixel[ 12 ] ] < barrier ) ) { // ???-@@@@????-?-@
					return false;
				} // ???-@@@@????@?-@
                if( !(p[ _pixel[ 0 ]] < barrier ) ) { // ???-@@@@-???@?-@
					return false;
				} // ???-@@@@@???@?-@
                if( !(p[ _pixel[ 15 ] ] < barrier ) ) { // ???-@@@@@-??@?-@
					return false;
				} // ???-@@@@@@??@?-@
                if( !(p[ _pixel[ 14 ] ] < barrier ) ) { // ???-@@@@@@-?@?-@
					return false;
				} // ???-@@@@@@@?@?-@
                if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // ???-@@@@@@@-@?-@
					return false;
				} // ???-@@@@@@@@@?-@
				return true;
			} // ???@@@@@??????-@
            if( !(p[ _pixel[ 6 ] ] < barrier ) ) { // ??-@@@@@??????-@
                if( !(p[ _pixel[ 0 ]] < barrier ) ) { // ??-@@@@@-?????-@
					return false;
				} // ??-@@@@@@?????-@
                if( !(p[ _pixel[ 15 ] ] < barrier ) ) { // ??-@@@@@@-????-@
					return false;
				} // ??-@@@@@@@????-@
                if( !(p[ _pixel[ 14 ] ] < barrier ) ) { // ??-@@@@@@@-???-@
					return false;
				} // ??-@@@@@@@@???-@
                if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // ??-@@@@@@@@-??-@
					return false;
				} // ??-@@@@@@@@@??-@
				return true;
			} // ??@@@@@@??????-@
            if( !(p[ _pixel[ 7 ] ] < barrier ) ) { // ?-@@@@@@??????-@
                if( !(p[ _pixel[ 0 ]] < barrier ) ) { // ?-@@@@@@-?????-@
					return false;
				} // ?-@@@@@@@?????-@
                if( !(p[ _pixel[ 15 ] ] < barrier ) ) { // ?-@@@@@@@-????-@
					return false;
				} // ?-@@@@@@@@????-@
                if( !(p[ _pixel[ 14 ] ] < barrier ) ) { // ?-@@@@@@@@-???-@
					return false;
				} // ?-@@@@@@@@@???-@
				return true;
			} // ?@@@@@@@??????-@
            if( !(p[ _pixel[ 8 ] ] < barrier ) ) { // -@@@@@@@??????-@
                if( !(p[ _pixel[ 0 ]] < barrier ) ) { // -@@@@@@@-?????-@
					return false;
				} // -@@@@@@@@?????-@
                if( !(p[ _pixel[ 15 ] ] < barrier ) ) { // -@@@@@@@@-????-@
					return false;
				} // -@@@@@@@@@????-@
				return true;
			} // @@@@@@@@??????-@
			return true;
		} // ??????????????@@
        if( !(p[ _pixel[ 8 ] ] < barrier ) ) { // -?????????????@@
            if( !(p[ _pixel[ 1 ]] < barrier ) ) { // -??????-??????@@
				return false;
			} // -??????@??????@@
            if( !(p[ _pixel[ 15 ] ] < barrier ) ) { // -??????@?-????@@
				return false;
			} // -??????@?@????@@
            if( !(p[ _pixel[ 0 ]] < barrier ) ) { // -??????@-@????@@
				return false;
			} // -??????@@@????@@
            if( !(p[ _pixel[ 14 ] ] < barrier ) ) { // -??????@@@-???@@
                if( !(p[ _pixel[ 2 ] ] < barrier ) ) { // -?????-@@@-???@@
					return false;
				} // -?????@@@@-???@@
                if( !(p[ _pixel[ 3 ] ] < barrier ) ) { // -????-@@@@-???@@
					return false;
				} // -????@@@@@-???@@
                if( !(p[ _pixel[ 7 ] ] < barrier ) ) { // --???@@@@@-???@@
					return false;
				} // -@???@@@@@-???@@
                if( !(p[ _pixel[ 6 ] ] < barrier ) ) { // -@-??@@@@@-???@@
					return false;
				} // -@@??@@@@@-???@@
                if( !(p[ _pixel[ 5 ] ] < barrier ) ) { // -@@-?@@@@@-???@@
					return false;
				} // -@@@?@@@@@-???@@
                if( !(p[ _pixel[ 4 ] ] < barrier ) ) { // -@@@-@@@@@-???@@
					return false;
				} // -@@@@@@@@@-???@@
				return true;
			} // -??????@@@@???@@
            if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // -??????@@@@-??@@
                if( !(p[ _pixel[ 2 ] ] < barrier ) ) { // -?????-@@@@-??@@
					return false;
				} // -?????@@@@@-??@@
                if( !(p[ _pixel[ 6 ] ] < barrier ) ) { // -?-???@@@@@-??@@
					return false;
				} // -?@???@@@@@-??@@
                if( !(p[ _pixel[ 5 ] ] < barrier ) ) { // -?@-??@@@@@-??@@
					return false;
				} // -?@@??@@@@@-??@@
                if( !(p[ _pixel[ 4 ] ] < barrier ) ) { // -?@@-?@@@@@-??@@
					return false;
				} // -?@@@?@@@@@-??@@
                if( !(p[ _pixel[ 3 ] ] < barrier ) ) { // -?@@@-@@@@@-??@@
					return false;
				} // -?@@@@@@@@@-??@@
				return true;
			} // -??????@@@@@??@@
            if( !(p[ _pixel[ 12 ] ] < barrier ) ) { // -??????@@@@@-?@@
                if( !(p[ _pixel[ 5 ] ] < barrier ) ) { // -??-???@@@@@-?@@
					return false;
				} // -??@???@@@@@-?@@
                if( !(p[ _pixel[ 4 ] ] < barrier ) ) { // -??@-??@@@@@-?@@
					return false;
				} // -??@@??@@@@@-?@@
                if( !(p[ _pixel[ 3 ] ] < barrier ) ) { // -??@@-?@@@@@-?@@
					return false;
				} // -??@@@?@@@@@-?@@
                if( !(p[ _pixel[ 2 ] ] < barrier ) ) { // -??@@@-@@@@@-?@@
					return false;
				} // -??@@@@@@@@@-?@@
				return true;
			} // -??????@@@@@@?@@
            if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // -??????@@@@@@-@@
                if( !(p[ _pixel[ 4 ] ] < barrier ) ) { // -???-??@@@@@@-@@
					return false;
				} // -???@??@@@@@@-@@
                if( !(p[ _pixel[ 3 ] ] < barrier ) ) { // -???@-?@@@@@@-@@
					return false;
				} // -???@@?@@@@@@-@@
                if( !(p[ _pixel[ 2 ] ] < barrier ) ) { // -???@@-@@@@@@-@@
					return false;
				} // -???@@@@@@@@@-@@
				return true;
			} // -??????@@@@@@@@@
			return true;
		} // @?????????????@@
        if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // @????????????-@@
            if( !(p[ _pixel[ 2 ] ] < barrier ) ) { // @?????-??????-@@
				return false;
			} // @?????@??????-@@
            if( !(p[ _pixel[ 3 ] ] < barrier ) ) { // @????-@??????-@@
				return false;
			} // @????@@??????-@@
            if( !(p[ _pixel[ 4 ] ] < barrier ) ) { // @???-@@??????-@@
				return false;
			} // @???@@@??????-@@
            if( !(p[ _pixel[ 5 ] ] < barrier ) ) { // @??-@@@??????-@@
                if( !(p[ _pixel[ 12 ] ] < barrier ) ) { // @??-@@@?????--@@
					return false;
				} // @??-@@@?????@-@@
                if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // @??-@@@????-@-@@
					return false;
				} // @??-@@@????@@-@@
                if( !(p[ _pixel[ 1 ]] < barrier ) ) { // @??-@@@-???@@-@@
					return false;
				} // @??-@@@@???@@-@@
                if( !(p[ _pixel[ 0 ]] < barrier ) ) { // @??-@@@@-??@@-@@
					return false;
				} // @??-@@@@@??@@-@@
                if( !(p[ _pixel[ 15 ] ] < barrier ) ) { // @??-@@@@@-?@@-@@
					return false;
				} // @??-@@@@@@?@@-@@
                if( !(p[ _pixel[ 14 ] ] < barrier ) ) { // @??-@@@@@@-@@-@@
					return false;
				} // @??-@@@@@@@@@-@@
				return true;
			} // @??@@@@??????-@@
            if( !(p[ _pixel[ 6 ] ] < barrier ) ) { // @?-@@@@??????-@@
                if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // @?-@@@@????-?-@@
					return false;
				} // @?-@@@@????@?-@@
                if( !(p[ _pixel[ 1 ]] < barrier ) ) { // @?-@@@@-???@?-@@
					return false;
				} // @?-@@@@@???@?-@@
                if( !(p[ _pixel[ 0 ]] < barrier ) ) { // @?-@@@@@-??@?-@@
					return false;
				} // @?-@@@@@@??@?-@@
                if( !(p[ _pixel[ 15 ] ] < barrier ) ) { // @?-@@@@@@-?@?-@@
					return false;
				} // @?-@@@@@@@?@?-@@
                if( !(p[ _pixel[ 14 ] ] < barrier ) ) { // @?-@@@@@@@-@?-@@
					return false;
				} // @?-@@@@@@@@@?-@@
				return true;
			} // @?@@@@@??????-@@
            if( !(p[ _pixel[ 7 ] ] < barrier ) ) { // @-@@@@@??????-@@
                if( !(p[ _pixel[ 1 ]] < barrier ) ) { // @-@@@@@-?????-@@
					return false;
				} // @-@@@@@@?????-@@
                if( !(p[ _pixel[ 0 ]] < barrier ) ) { // @-@@@@@@-????-@@
					return false;
				} // @-@@@@@@@????-@@
                if( !(p[ _pixel[ 15 ] ] < barrier ) ) { // @-@@@@@@@-???-@@
					return false;
				} // @-@@@@@@@@???-@@
                if( !(p[ _pixel[ 14 ] ] < barrier ) ) { // @-@@@@@@@@-??-@@
					return false;
				} // @-@@@@@@@@@??-@@
				return true;
			} // @@@@@@@??????-@@
			return true;
		} // @????????????@@@
        if( !(p[ _pixel[ 7 ] ] < barrier ) ) { // @-???????????@@@
            if( !(p[ _pixel[ 14 ] ] < barrier ) ) { // @-????????-??@@@
				return false;
			} // @-????????@??@@@
            if( !(p[ _pixel[ 15 ] ] < barrier ) ) { // @-???????-@??@@@
				return false;
			} // @-???????@@??@@@
            if( !(p[ _pixel[ 0 ]] < barrier ) ) { // @-??????-@@??@@@
				return false;
			} // @-??????@@@??@@@
            if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // @-??????@@@-?@@@
                if( !(p[ _pixel[ 1 ]] < barrier ) ) { // @-?????-@@@-?@@@
					return false;
				} // @-?????@@@@-?@@@
                if( !(p[ _pixel[ 2 ] ] < barrier ) ) { // @-????-@@@@-?@@@
					return false;
				} // @-????@@@@@-?@@@
                if( !(p[ _pixel[ 6 ] ] < barrier ) ) { // @--???@@@@@-?@@@
					return false;
				} // @-@???@@@@@-?@@@
                if( !(p[ _pixel[ 5 ] ] < barrier ) ) { // @-@-??@@@@@-?@@@
					return false;
				} // @-@@??@@@@@-?@@@
                if( !(p[ _pixel[ 4 ] ] < barrier ) ) { // @-@@-?@@@@@-?@@@
					return false;
				} // @-@@@?@@@@@-?@@@
                if( !(p[ _pixel[ 3 ] ] < barrier ) ) { // @-@@@-@@@@@-?@@@
					return false;
				} // @-@@@@@@@@@-?@@@
				return true;
			} // @-??????@@@@?@@@
            if( !(p[ _pixel[ 12 ] ] < barrier ) ) { // @-??????@@@@-@@@
                if( !(p[ _pixel[ 1 ]] < barrier ) ) { // @-?????-@@@@-@@@
					return false;
				} // @-?????@@@@@-@@@
                if( !(p[ _pixel[ 5 ] ] < barrier ) ) { // @-?-???@@@@@-@@@
					return false;
				} // @-?@???@@@@@-@@@
                if( !(p[ _pixel[ 4 ] ] < barrier ) ) { // @-?@-??@@@@@-@@@
					return false;
				} // @-?@@??@@@@@-@@@
                if( !(p[ _pixel[ 3 ] ] < barrier ) ) { // @-?@@-?@@@@@-@@@
					return false;
				} // @-?@@@?@@@@@-@@@
                if( !(p[ _pixel[ 2 ] ] < barrier ) ) { // @-?@@@-@@@@@-@@@
					return false;
				} // @-?@@@@@@@@@-@@@
				return true;
			} // @-??????@@@@@@@@
			return true;
		} // @@???????????@@@
        if( !(p[ _pixel[ 12 ] ] < barrier ) ) { // @@??????????-@@@
            if( !(p[ _pixel[ 3 ] ] < barrier ) ) { // @@???-??????-@@@
				return false;
			} // @@???@??????-@@@
            if( !(p[ _pixel[ 4 ] ] < barrier ) ) { // @@??-@??????-@@@
				return false;
			} // @@??@@??????-@@@
            if( !(p[ _pixel[ 5 ] ] < barrier ) ) { // @@?-@@??????-@@@
				return false;
			} // @@?@@@??????-@@@
            if( !(p[ _pixel[ 6 ] ] < barrier ) ) { // @@-@@@??????-@@@
                if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // @@-@@@?????--@@@
					return false;
				} // @@-@@@?????@-@@@
                if( !(p[ _pixel[ 14 ] ] < barrier ) ) { // @@-@@@????-@-@@@
					return false;
				} // @@-@@@????@@-@@@
                if( !(p[ _pixel[ 2 ] ] < barrier ) ) { // @@-@@@-???@@-@@@
					return false;
				} // @@-@@@@???@@-@@@
                if( !(p[ _pixel[ 1 ]] < barrier ) ) { // @@-@@@@-??@@-@@@
					return false;
				} // @@-@@@@@??@@-@@@
                if( !(p[ _pixel[ 0 ]] < barrier ) ) { // @@-@@@@@-?@@-@@@
					return false;
				} // @@-@@@@@@?@@-@@@
                if( !(p[ _pixel[ 15 ] ] < barrier ) ) { // @@-@@@@@@-@@-@@@
					return false;
				} // @@-@@@@@@@@@-@@@
				return true;
			} // @@@@@@??????-@@@
			return true;
		} // @@??????????@@@@
        if( !(p[ _pixel[ 6 ] ] < barrier ) ) { // @@-?????????@@@@
            if( !(p[ _pixel[ 15 ] ] < barrier ) ) { // @@-??????-??@@@@
				return false;
			} // @@-??????@??@@@@
            if( !(p[ _pixel[ 14 ] ] < barrier ) ) { // @@-??????@-?@@@@
				return false;
			} // @@-??????@@?@@@@
            if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // @@-??????@@-@@@@
				return false;
			} // @@-??????@@@@@@@
			return true;
		} // @@@?????????@@@@
        if( !(p[ _pixel[ 11 ] ] < barrier ) ) { // @@@????????-@@@@
            if( !(p[ _pixel[ 5 ] ] < barrier ) ) { // @@@-???????-@@@@
				return false;
			} // @@@@???????-@@@@
            if( !(p[ _pixel[ 4 ] ] < barrier ) ) { // @@@@-??????-@@@@
				return false;
			} // @@@@@??????-@@@@
			return true;
		} // @@@????????@@@@@
        if( !(p[ _pixel[ 5 ] ] < barrier ) ) { // @@@-???????@@@@@
            if( !(p[ _pixel[ 14 ] ] < barrier ) ) { // @@@-??????-@@@@@
				return false;
			} // @@@-??????@@@@@@
			return true;
		} // @@@@???????@@@@@
		return true;
	}
    /* pixel, stride, 3x stride barrier (center+thres)
	 */
    bool ORB::isBrighterCorner9( const uint8_t * p, const int barrier )
	{
		if( !( p[ _pixel[ 9 ] ] > barrier ) ) {	// ???????????????-
            if( !(p[ _pixel[ 0 ]] > barrier ) ) {		// ???????-???????-
				return false;
			}								// ????????@??????-
            if( !(p[ _pixel[ 1 ]] > barrier ) ) {		// ???????-@??????-
				return false;
			}								// ???????@@??????-
            if( !(p[ _pixel[ 2 ] ] > barrier ) ) {		// ??????-@@??????-
				return false;
			}								// ??????@@@??????-
            if( !(p[ _pixel[ 3 ] ] > barrier ) ) {		// ?????-@@@??????-
                if( !(p[ _pixel[ 10 ] ] > barrier ) ){ // ?????-@@@?????--
					return false;
				} // ?????-@@@?????@-
                if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // ?????-@@@????-@-
					return false;
				} // ?????-@@@????@@-
                if( !(p[ _pixel[ 15 ] ] > barrier ) ) { // ?????-@@@-???@@-
					return false;
				} // ?????-@@@@???@@-
                if( !(p[ _pixel[ 14 ] ] > barrier ) ) { // ?????-@@@@-??@@-
					return false;
				} // ?????-@@@@@??@@-
                if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // ?????-@@@@@-?@@-
					return false;
				} // ?????-@@@@@@?@@-
                if( !(p[ _pixel[ 12 ] ] > barrier ) ) { // ?????-@@@@@@-@@-
					return false;
				} // ?????-@@@@@@@@@-
				return true;
			} // ?????@@@@??????-
            if( !(p[ _pixel[ 4 ] ] > barrier ) ) { // ????-@@@@??????-
                if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // ????-@@@@????-?-
					return false;
				} // ????-@@@@????@?-
                if( !(p[ _pixel[ 15 ] ] > barrier ) ) { // ????-@@@@-???@?-
					return false;
				} // ????-@@@@@???@?-
                if( !(p[ _pixel[ 14 ] ] > barrier ) ) { // ????-@@@@@-??@?-
					return false;
				} // ????-@@@@@@??@?-
                if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // ????-@@@@@@-?@?-
					return false;
				} // ????-@@@@@@@?@?-
                if( !(p[ _pixel[ 12 ] ] > barrier ) ) { // ????-@@@@@@@-@?-
					return false;
				} // ????-@@@@@@@@@?-
				return true;
			} // ????@@@@@??????-
            if( !(p[ _pixel[ 5 ] ] > barrier ) ) { // ???-@@@@@??????-
                if( !(p[ _pixel[ 15 ] ] > barrier ) ) { // ???-@@@@@-?????-
					return false;
				} // ???-@@@@@@?????-
                if( !(p[ _pixel[ 14 ] ] > barrier ) ) { // ???-@@@@@@-????-
					return false;
				} // ???-@@@@@@@????-
                if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // ???-@@@@@@@-???-
					return false;
				} // ???-@@@@@@@@???-
                if( !(p[ _pixel[ 12 ] ] > barrier ) ) { // ???-@@@@@@@@-??-
					return false;
				} // ???-@@@@@@@@@??-
				return true;
			} // ???@@@@@@??????-
            if( !(p[ _pixel[ 15 ] ] > barrier ) ) { // ???@@@@@@-?????-
                if( !(p[ _pixel[ 8 ] ] > barrier ) ) { // -??@@@@@@-?????-
					return false;
				} // @??@@@@@@-?????-
                if( !(p[ _pixel[ 7 ] ] > barrier ) ) { // @-?@@@@@@-?????-
					return false;
				} // @@?@@@@@@-?????-
                if( !(p[ _pixel[ 6 ] ] > barrier ) ) { // @@-@@@@@@-?????-
					return false;
				} // @@@@@@@@@-?????-
				return true;
			} // ???@@@@@@@?????-
            if( !(p[ _pixel[ 6 ] ] > barrier ) ) { // ??-@@@@@@@?????-
                if( !(p[ _pixel[ 14 ] ] > barrier ) ) { // ??-@@@@@@@-????-
					return false;
				} // ??-@@@@@@@@????-
                if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // ??-@@@@@@@@-???-
					return false;
				} // ??-@@@@@@@@@???-
				return true;
			} // ??@@@@@@@@?????-
            if( !(p[ _pixel[ 14 ] ] > barrier ) ) { // ??@@@@@@@@-????-
                if( !(p[ _pixel[ 7 ] ] > barrier ) ) { // ?-@@@@@@@@-????-
					return false;
				} // ?@@@@@@@@@-????-
				return true;
			} // ??@@@@@@@@@????-
			return true;
		} // ???????????????@
        if( !(p[ _pixel[ 10 ] ] > barrier ) ) { // ??????????????-@
            if( !(p[ _pixel[ 3 ] ] > barrier ) ) { // ?????-????????-@
				return false;
			} // ?????@????????-@
            if( !(p[ _pixel[ 1 ]] > barrier ) ) { // ?????@?-??????-@
				return false;
			} // ?????@?@??????-@
            if( !(p[ _pixel[ 2 ] ] > barrier ) ) { // ?????@-@??????-@
				return false;
			} // ?????@@@??????-@
            if( !(p[ _pixel[ 4 ] ] > barrier ) ) { // ????-@@@??????-@
                if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // ????-@@@?????--@
					return false;
				} // ????-@@@?????@-@
                if( !(p[ _pixel[ 12 ] ] > barrier ) ) { // ????-@@@????-@-@
					return false;
				} // ????-@@@????@@-@
                if( !(p[ _pixel[ 0 ]] > barrier ) ) { // ????-@@@-???@@-@
					return false;
				} // ????-@@@@???@@-@
                if( !(p[ _pixel[ 15 ] ] > barrier ) ) { // ????-@@@@-??@@-@
					return false;
				} // ????-@@@@@??@@-@
                if( !(p[ _pixel[ 14 ] ] > barrier ) ) { // ????-@@@@@-?@@-@
					return false;
				} // ????-@@@@@@?@@-@
                if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // ????-@@@@@@-@@-@
					return false;
				} // ????-@@@@@@@@@-@
				return true;
			} // ????@@@@??????-@
            if( !(p[ _pixel[ 5 ] ] > barrier ) ) { // ???-@@@@??????-@
                if( !(p[ _pixel[ 12 ] ] > barrier ) ) { // ???-@@@@????-?-@
					return false;
				} // ???-@@@@????@?-@
                if( !(p[ _pixel[ 0 ]] > barrier ) ) { // ???-@@@@-???@?-@
					return false;
				} // ???-@@@@@???@?-@
                if( !(p[ _pixel[ 15 ] ] > barrier ) ) { // ???-@@@@@-??@?-@
					return false;
				} // ???-@@@@@@??@?-@
                if( !(p[ _pixel[ 14 ] ] > barrier ) ) { // ???-@@@@@@-?@?-@
					return false;
				} // ???-@@@@@@@?@?-@
                if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // ???-@@@@@@@-@?-@
					return false;
				} // ???-@@@@@@@@@?-@
				return true;
			} // ???@@@@@??????-@
            if( !(p[ _pixel[ 6 ] ] > barrier ) ) { // ??-@@@@@??????-@
                if( !(p[ _pixel[ 0 ]] > barrier ) ) { // ??-@@@@@-?????-@
					return false;
				} // ??-@@@@@@?????-@
                if( !(p[ _pixel[ 15 ] ] > barrier ) ) { // ??-@@@@@@-????-@
					return false;
				} // ??-@@@@@@@????-@
                if( !(p[ _pixel[ 14 ] ] > barrier ) ) { // ??-@@@@@@@-???-@
					return false;
				} // ??-@@@@@@@@???-@
                if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // ??-@@@@@@@@-??-@
					return false;
				} // ??-@@@@@@@@@??-@
				return true;
			} // ??@@@@@@??????-@
            if( !(p[ _pixel[ 7 ] ] > barrier ) ) { // ?-@@@@@@??????-@
                if( !(p[ _pixel[ 0 ]] > barrier ) ) { // ?-@@@@@@-?????-@
					return false;
				} // ?-@@@@@@@?????-@
                if( !(p[ _pixel[ 15 ] ] > barrier ) ) { // ?-@@@@@@@-????-@
					return false;
				} // ?-@@@@@@@@????-@
                if( !(p[ _pixel[ 14 ] ] > barrier ) ) { // ?-@@@@@@@@-???-@
					return false;
				} // ?-@@@@@@@@@???-@
				return true;
			} // ?@@@@@@@??????-@
            if( !(p[ _pixel[ 8 ] ] > barrier ) ) { // -@@@@@@@??????-@
                if( !(p[ _pixel[ 0 ]] > barrier ) ) { // -@@@@@@@-?????-@
					return false;
				} // -@@@@@@@@?????-@
                if( !(p[ _pixel[ 15 ] ] > barrier ) ) { // -@@@@@@@@-????-@
					return false;
				} // -@@@@@@@@@????-@
				return true;
			} // @@@@@@@@??????-@
			return true;
		} // ??????????????@@
        if( !(p[ _pixel[ 8 ] ] > barrier ) ) { // -?????????????@@
            if( !(p[ _pixel[ 1 ]] > barrier ) ) { // -??????-??????@@
				return false;
			} // -??????@??????@@
            if( !(p[ _pixel[ 15 ] ] > barrier ) ) { // -??????@?-????@@
				return false;
			} // -??????@?@????@@
            if( !(p[ _pixel[ 0 ]] > barrier ) ) { // -??????@-@????@@
				return false;
			} // -??????@@@????@@
            if( !(p[ _pixel[ 14 ] ] > barrier ) ) { // -??????@@@-???@@
                if( !(p[ _pixel[ 2 ] ] > barrier ) ) { // -?????-@@@-???@@
					return false;
				} // -?????@@@@-???@@
                if( !(p[ _pixel[ 3 ] ] > barrier ) ) { // -????-@@@@-???@@
					return false;
				} // -????@@@@@-???@@
                if( !(p[ _pixel[ 7 ] ] > barrier ) ) { // --???@@@@@-???@@
					return false;
				} // -@???@@@@@-???@@
                if( !(p[ _pixel[ 6 ] ] > barrier ) ) { // -@-??@@@@@-???@@
					return false;
				} // -@@??@@@@@-???@@
                if( !(p[ _pixel[ 5 ] ] > barrier ) ) { // -@@-?@@@@@-???@@
					return false;
				} // -@@@?@@@@@-???@@
                if( !(p[ _pixel[ 4 ] ] > barrier ) ) { // -@@@-@@@@@-???@@
					return false;
				} // -@@@@@@@@@-???@@
				return true;
			} // -??????@@@@???@@
            if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // -??????@@@@-??@@
                if( !(p[ _pixel[ 2 ] ] > barrier ) ) { // -?????-@@@@-??@@
					return false;
				} // -?????@@@@@-??@@
                if( !(p[ _pixel[ 6 ] ] > barrier ) ) { // -?-???@@@@@-??@@
					return false;
				} // -?@???@@@@@-??@@
                if( !(p[ _pixel[ 5 ] ] > barrier ) ) { // -?@-??@@@@@-??@@
					return false;
				} // -?@@??@@@@@-??@@
                if( !(p[ _pixel[ 4 ] ] > barrier ) ) { // -?@@-?@@@@@-??@@
					return false;
				} // -?@@@?@@@@@-??@@
                if( !(p[ _pixel[ 3 ] ] > barrier ) ) { // -?@@@-@@@@@-??@@
					return false;
				} // -?@@@@@@@@@-??@@
				return true;
			} // -??????@@@@@??@@
            if( !(p[ _pixel[ 12 ] ] > barrier ) ) { // -??????@@@@@-?@@
                if( !(p[ _pixel[ 5 ] ] > barrier ) ) { // -??-???@@@@@-?@@
					return false;
				} // -??@???@@@@@-?@@
                if( !(p[ _pixel[ 4 ] ] > barrier ) ) { // -??@-??@@@@@-?@@
					return false;
				} // -??@@??@@@@@-?@@
                if( !(p[ _pixel[ 3 ] ] > barrier ) ) { // -??@@-?@@@@@-?@@
					return false;
				} // -??@@@?@@@@@-?@@
                if( !(p[ _pixel[ 2 ] ] > barrier ) ) { // -??@@@-@@@@@-?@@
					return false;
				} // -??@@@@@@@@@-?@@
				return true;
			} // -??????@@@@@@?@@
            if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // -??????@@@@@@-@@
                if( !(p[ _pixel[ 4 ] ] > barrier ) ) { // -???-??@@@@@@-@@
					return false;
				} // -???@??@@@@@@-@@
                if( !(p[ _pixel[ 3 ] ] > barrier ) ) { // -???@-?@@@@@@-@@
					return false;
				} // -???@@?@@@@@@-@@
                if( !(p[ _pixel[ 2 ] ] > barrier ) ) { // -???@@-@@@@@@-@@
					return false;
				} // -???@@@@@@@@@-@@
				return true;
			} // -??????@@@@@@@@@
			return true;
		} // @?????????????@@
        if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // @????????????-@@
            if( !(p[ _pixel[ 2 ] ] > barrier ) ) { // @?????-??????-@@
				return false;
			} // @?????@??????-@@
            if( !(p[ _pixel[ 3 ] ] > barrier ) ) { // @????-@??????-@@
				return false;
			} // @????@@??????-@@
            if( !(p[ _pixel[ 4 ] ] > barrier ) ) { // @???-@@??????-@@
				return false;
			} // @???@@@??????-@@
            if( !(p[ _pixel[ 5 ] ] > barrier ) ) { // @??-@@@??????-@@
                if( !(p[ _pixel[ 12 ] ] > barrier ) ) { // @??-@@@?????--@@
					return false;
				} // @??-@@@?????@-@@
                if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // @??-@@@????-@-@@
					return false;
				} // @??-@@@????@@-@@
                if( !(p[ _pixel[ 1 ]] > barrier ) ) { // @??-@@@-???@@-@@
					return false;
				} // @??-@@@@???@@-@@
                if( !(p[ _pixel[ 0 ]] > barrier ) ) { // @??-@@@@-??@@-@@
					return false;
				} // @??-@@@@@??@@-@@
                if( !(p[ _pixel[ 15 ] ] > barrier ) ) { // @??-@@@@@-?@@-@@
					return false;
				} // @??-@@@@@@?@@-@@
                if( !(p[ _pixel[ 14 ] ] > barrier ) ) { // @??-@@@@@@-@@-@@
					return false;
				} // @??-@@@@@@@@@-@@
				return true;
			} // @??@@@@??????-@@
            if( !(p[ _pixel[ 6 ] ] > barrier ) ) { // @?-@@@@??????-@@
                if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // @?-@@@@????-?-@@
					return false;
				} // @?-@@@@????@?-@@
                if( !(p[ _pixel[ 1 ]] > barrier ) ) { // @?-@@@@-???@?-@@
					return false;
				} // @?-@@@@@???@?-@@
                if( !(p[ _pixel[ 0 ]] > barrier ) ) { // @?-@@@@@-??@?-@@
					return false;
				} // @?-@@@@@@??@?-@@
                if( !(p[ _pixel[ 15 ] ] > barrier ) ) { // @?-@@@@@@-?@?-@@
					return false;
				} // @?-@@@@@@@?@?-@@
                if( !(p[ _pixel[ 14 ] ] > barrier ) ) { // @?-@@@@@@@-@?-@@
					return false;
				} // @?-@@@@@@@@@?-@@
				return true;
			} // @?@@@@@??????-@@
            if( !(p[ _pixel[ 7 ] ] > barrier ) ) { // @-@@@@@??????-@@
                if( !(p[ _pixel[ 1 ]] > barrier ) ) { // @-@@@@@-?????-@@
					return false;
				} // @-@@@@@@?????-@@
                if( !(p[ _pixel[ 0 ]] > barrier ) ) { // @-@@@@@@-????-@@
					return false;
				} // @-@@@@@@@????-@@
                if( !(p[ _pixel[ 15 ] ] > barrier ) ) { // @-@@@@@@@-???-@@
					return false;
				} // @-@@@@@@@@???-@@
                if( !(p[ _pixel[ 14 ] ] > barrier ) ) { // @-@@@@@@@@-??-@@
					return false;
				} // @-@@@@@@@@@??-@@
				return true;
			} // @@@@@@@??????-@@
			return true;
		} // @????????????@@@
        if( !(p[ _pixel[ 7 ] ] > barrier ) ) { // @-???????????@@@
            if( !(p[ _pixel[ 14 ] ] > barrier ) ) { // @-????????-??@@@
				return false;
			} // @-????????@??@@@
            if( !(p[ _pixel[ 15 ] ] > barrier ) ) { // @-???????-@??@@@
				return false;
			} // @-???????@@??@@@
            if( !(p[ _pixel[ 0 ]] > barrier ) ) { // @-??????-@@??@@@
				return false;
			} // @-??????@@@??@@@
            if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // @-??????@@@-?@@@
                if( !(p[ _pixel[ 1 ]] > barrier ) ) { // @-?????-@@@-?@@@
					return false;
				} // @-?????@@@@-?@@@
                if( !(p[ _pixel[ 2 ] ] > barrier ) ) { // @-????-@@@@-?@@@
					return false;
				} // @-????@@@@@-?@@@
                if( !(p[ _pixel[ 6 ] ] > barrier ) ) { // @--???@@@@@-?@@@
					return false;
				} // @-@???@@@@@-?@@@
                if( !(p[ _pixel[ 5 ] ] > barrier ) ) { // @-@-??@@@@@-?@@@
					return false;
				} // @-@@??@@@@@-?@@@
                if( !(p[ _pixel[ 4 ] ] > barrier ) ) { // @-@@-?@@@@@-?@@@
					return false;
				} // @-@@@?@@@@@-?@@@
                if( !(p[ _pixel[ 3 ] ] > barrier ) ) { // @-@@@-@@@@@-?@@@
					return false;
				} // @-@@@@@@@@@-?@@@
				return true;
			} // @-??????@@@@?@@@
            if( !(p[ _pixel[ 12 ] ] > barrier ) ) { // @-??????@@@@-@@@
                if( !(p[ _pixel[ 1 ]] > barrier ) ) { // @-?????-@@@@-@@@
					return false;
				} // @-?????@@@@@-@@@
                if( !(p[ _pixel[ 5 ] ] > barrier ) ) { // @-?-???@@@@@-@@@
					return false;
				} // @-?@???@@@@@-@@@
                if( !(p[ _pixel[ 4 ] ] > barrier ) ) { // @-?@-??@@@@@-@@@
					return false;
				} // @-?@@??@@@@@-@@@
                if( !(p[ _pixel[ 3 ] ] > barrier ) ) { // @-?@@-?@@@@@-@@@
					return false;
				} // @-?@@@?@@@@@-@@@
                if( !(p[ _pixel[ 2 ] ] > barrier ) ) { // @-?@@@-@@@@@-@@@
					return false;
				} // @-?@@@@@@@@@-@@@
				return true;
			} // @-??????@@@@@@@@
			return true;
		} // @@???????????@@@
        if( !(p[ _pixel[ 12 ] ] > barrier ) ) { // @@??????????-@@@
            if( !(p[ _pixel[ 3 ] ] > barrier ) ) { // @@???-??????-@@@
				return false;
			} // @@???@??????-@@@
            if( !(p[ _pixel[ 4 ] ] > barrier ) ) { // @@??-@??????-@@@
				return false;
			} // @@??@@??????-@@@
            if( !(p[ _pixel[ 5 ] ] > barrier ) ) { // @@?-@@??????-@@@
				return false;
			} // @@?@@@??????-@@@
            if( !(p[ _pixel[ 6 ] ] > barrier ) ) { // @@-@@@??????-@@@
                if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // @@-@@@?????--@@@
					return false;
				} // @@-@@@?????@-@@@
                if( !(p[ _pixel[ 14 ] ] > barrier ) ) { // @@-@@@????-@-@@@
					return false;
				} // @@-@@@????@@-@@@
                if( !(p[ _pixel[ 2 ] ] > barrier ) ) { // @@-@@@-???@@-@@@
					return false;
				} // @@-@@@@???@@-@@@
                if( !(p[ _pixel[ 1 ]] > barrier ) ) { // @@-@@@@-??@@-@@@
					return false;
				} // @@-@@@@@??@@-@@@
                if( !(p[ _pixel[ 0 ]] > barrier ) ) { // @@-@@@@@-?@@-@@@
					return false;
				} // @@-@@@@@@?@@-@@@
                if( !(p[ _pixel[ 15 ] ] > barrier ) ) { // @@-@@@@@@-@@-@@@
					return false;
				} // @@-@@@@@@@@@-@@@
				return true;
			} // @@@@@@??????-@@@
			return true;
		} // @@??????????@@@@
        if( !(p[ _pixel[ 6 ] ] > barrier ) ) { // @@-?????????@@@@
            if( !(p[ _pixel[ 15 ] ] > barrier ) ) { // @@-??????-??@@@@
				return false;
			} // @@-??????@??@@@@
            if( !(p[ _pixel[ 14 ] ] > barrier ) ) { // @@-??????@-?@@@@
				return false;
			} // @@-??????@@?@@@@
            if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // @@-??????@@-@@@@
				return false;
			} // @@-??????@@@@@@@
			return true;
		} // @@@?????????@@@@
        if( !(p[ _pixel[ 11 ] ] > barrier ) ) { // @@@????????-@@@@
            if( !(p[ _pixel[ 5 ] ] > barrier ) ) { // @@@-???????-@@@@
				return false;
			} // @@@@???????-@@@@
            if( !(p[ _pixel[ 4 ] ] > barrier ) ) { // @@@@-??????-@@@@
				return false;
			} // @@@@@??????-@@@@
			return true;
		} // @@@????????@@@@@
        if( !(p[ _pixel[ 5 ] ] > barrier ) ) { // @@@-???????@@@@@
            if( !(p[ _pixel[ 14 ] ] > barrier ) ) { // @@@-??????-@@@@@
				return false;
			} // @@@-??????@@@@@@
			return true;
		} // @@@@???????@@@@@
		return true;
	}

#include "ORBPatterns.h"
}
