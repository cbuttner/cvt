/*
			CVT - Computer Vision Tools Library

	 Copyright (c) 2012, Philipp Heise, Sebastian Klose

	THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
	KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
	PARTICULAR PURPOSE.
 */
#ifndef CVT_STEREOCAMERACALIBRATION
#define CVT_STEREOCAMERACALIBRATION

#include <cvt/vision/CameraCalibration.h>
#include <cvt/gfx/Image.h>
#include <cvt/gfx/ifilter/IWarp.h>

namespace cvt {
	class StereoCameraCalibration
	{
		public:
			StereoCameraCalibration();
			StereoCameraCalibration( const CameraCalibration& first, const CameraCalibration& second );
			StereoCameraCalibration( const CameraCalibration& first, const CameraCalibration& second, const Matrix4f& extrinsics );

			void					 setFirstCamera( const CameraCalibration& firstcam );
			void					 setSecondCamera( const CameraCalibration& second );

			const CameraCalibration& firstCamera() const;
			const CameraCalibration& secondCamera() const;

			const Matrix4f&			 extrinsics() const;
			void					 setExtrinsics( const Matrix4f & extr );

			void					 undistortRectify( StereoCameraCalibration& stereo, Image& warpleft, Image& warpright,
													   size_t width, size_t height, bool verticalstereo = false ) const;

		private:
			struct UndistortRectifyWarp {
				UndistortRectifyWarp( const Vector2f& fnew, const Vector2f& cnew, const Matrix3f& rotation,
									  const Vector3f& radial, const Vector2f& tangential, const Vector2f& fold, const Vector2f& cold ) :
					_fnew( fnew ),
					_cnew( cnew ),
					_rot( rotation ),
					_radial( radial ),
					_tangential( tangential ),
					_fold( fold ),
					_cold( cold )
				{
				}

				Vector2f operator()( const Vector2f& pt ) const
				{
					// Point to ray and rotate
					Vector2f p = _rot * ( ( pt - _cnew ) / _fnew  );
					// Undistort
					float r2 = p.lengthSqr();
					float r4 = Math::sqr( r2 );
					float r6 = r2 * r4;
					float poly = ( 1.0f + _radial[ 0 ] * r2 + _radial[ 1 ] * r4 + _radial[ 2 ] * r6 );
					float xy2 = 2.0f * p.x * p.y;
					p.x = _fold.x * ( p.x * poly + xy2 * _tangential[ 0 ] + _tangential[ 1 ] * ( r2 + 2.0f * p.x * p.x ) ) + _cold.x;
					p.y = _fold.y * ( p.y * poly + xy2 * _tangential[ 1 ] + _tangential[ 0 ] * ( r2 + 2.0f * p.y * p.y ) ) + _cold.y;
					return p;
				}

				Vector2f _fnew;
				Vector2f _cnew;
				Matrix3f _rot;
				Vector3f _radial;
				Vector2f _tangential;
				Vector2f _fold;
				Vector2f _cold;
			};

			CameraCalibration _first;
			CameraCalibration _second;
			Matrix4f		  _extrinsics;
	};

	inline StereoCameraCalibration::StereoCameraCalibration()
	{
		_extrinsics.setIdentity();
	}

	inline StereoCameraCalibration::StereoCameraCalibration( const CameraCalibration& first, const CameraCalibration& second ) :
	   _first( first ),
	   _second( second )
	{
		_extrinsics =  _second.extrinsics() * _first.extrinsics().inverse();
	}

	inline StereoCameraCalibration::StereoCameraCalibration( const CameraCalibration& first, const CameraCalibration& second, const Matrix4f& extrinsics ) :
		_first( first ),
		_second( second ),
		_extrinsics( extrinsics )
	{
		_second.setExtrinsics( extrinsics * _first.extrinsics() );
	}

	inline void StereoCameraCalibration::setFirstCamera( const CameraCalibration& firstcam )
	{
		_first = firstcam;
	}

	inline void StereoCameraCalibration::setSecondCamera( const CameraCalibration& second )
	{
		_second = second;
	}


	inline const CameraCalibration& StereoCameraCalibration::firstCamera() const
	{
		return _first;
	}

	inline const CameraCalibration& StereoCameraCalibration::secondCamera() const
	{
		return _second;
	}

	inline const Matrix4f& StereoCameraCalibration::extrinsics() const
	{
		return _extrinsics;
	}

    inline void StereoCameraCalibration::setExtrinsics( const Matrix4f & extr )
    {
        _extrinsics = extr;
    }

	inline void StereoCameraCalibration::undistortRectify( StereoCameraCalibration& stereo, Image& warpleft, Image& warpright, size_t width, size_t height, bool verticalstereo ) const
	{
		/*
			Algorithm from Matlab Camera Calibration Toolbox
		 */
		Vector3f axis, t, u;
		Vector2f cleft, cright;
		float fleft, fright, fnew;
		float angle;
		_extrinsics.toMatrix3().toAxisAngle( axis, angle );
		Matrix3f Rleft, Rright, R2;
		CameraCalibration cam0, cam1;

		/* align orientation of cameras, by rotating both cameras with half of the extrinsic rotation */
		Rleft.setRotation( axis,   0.5f * angle );
		Rright.setRotation( axis, -0.5f * angle );
		t = Rright * Vector3f( _extrinsics.col( 3 ) );

		/* find rotation so that the translation vector matches u */
		if( verticalstereo ) {
			u.set( 0.0f, 1.0f, 0.0f );
		} else {
			u.set( 1.0f, 0.0f, 0.0f );
		}
		if( u.dot( t ) < 0 )
			u = - u;

		axis = t.cross( u );
		axis.normalize();
		angle = Math::acos( Math::abs( t.dot( u ) ) / ( t.length() ) );
		R2.setRotation( axis, angle );

		/* apply the rotation to the left/right cameras*/
		Rright = R2 * Rright;
		Rleft  = R2 * Rleft;

		/* save the extrinsics of the new camera system*/
		Matrix4f extnew;
		extnew.setIdentity();
		cam0.setExtrinsics( extnew ); // cam0 is origin
		u = Rright * t;
		extnew[ 0 ][ 3 ] = u.x;
		extnew[ 1 ][ 3 ] = u.y;
		extnew[ 2 ][ 3 ] = u.z;
		cam1.setExtrinsics( extnew );
		stereo.setExtrinsics( extnew );

		/* the new focal lengths */
		fleft = _first.focalLength().y;
/*		if( _first.radialDistortion().x < 0 ) {
			fleft *= ( 1.0f + _first.radialDistortion().x * ( Math::sqr<float>( width ) + Math::sqr<float>( height ) ) / ( 4.0f * Math::sqr( _first.focalLength().y ) ) );
		}*/

		fright = _second.focalLength().y;
/*		if( _second.radialDistortion().x < 0 ) {
			fright *= ( 1.0f + _second.radialDistortion().x * ( Math::sqr<float>( width ) + Math::sqr<float>( height ) ) / ( 4.0f * Math::sqr( _second.focalLength().y ) ) );
		}*/

		fnew = Math::min( fleft, fright );

		/* the new principal points */
		cleft = _first.center();
		cright = _second.center();

		// FIXME: find 'optimal' new centers
		if( verticalstereo ) {
			cleft.x = cright.x = ( cleft.x + cright.x ) * 0.5f;
		} else {
			float newy = ( cleft.y + cright.y ) * 0.5f;
			cleft.y = newy;
			cright.y = newy;
		}

		/* Calculate the warp maps */

		UndistortRectifyWarp leftop( Vector2f( fnew, fnew ), cleft, Rleft.transpose(), _first.radialDistortion(), _first.tangentialDistortion(), _first.focalLength(), _first.center() );
		UndistortRectifyWarp rightop( Vector2f( fnew, fnew ), cright, Rright.transpose(), _second.radialDistortion(), _second.tangentialDistortion(), _second.focalLength(), _second.center() );

		IWarp::warpGeneric( warpleft, leftop );
		IWarp::warpGeneric( warpright, rightop );

		/* set the new cameras
		   - intrinsics set to new values
		   - distortion is set to zero
		*/
		cam0.setIntrinsics( Matrix3f(  fnew,	    0, cleft.x,
											0, fnew,	cleft.y,
											0,	    0,		  1 ) );
		cam0.setDistortion( Vector3f( 0.0f, 0.0f, 0.0f ), Vector2f( 0.0f, 0.0f ) );

		cam1.setIntrinsics( Matrix3f( fnew,	   0, cright.x,
										   0, fnew, cright.y,
										   0,      0,		 1 ) );
		cam1.setDistortion( Vector3f( 0.0f, 0.0f, 0.0f ), Vector2f( 0.0f, 0.0f ) );
        stereo.setFirstCamera( cam0 );
        stereo.setSecondCamera( cam1 );
	}

}

#endif
