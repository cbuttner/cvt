/*
			CVT - Computer Vision Tools Library

 	 Copyright (c) 2012, Philipp Heise, Sebastian Klose

 	THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 	KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 	IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 	PARTICULAR PURPOSE.
 */
#ifndef CVT_FEATURE_ANALYZER_H
#define CVT_FEATURE_ANALYZER_H

#include <cvt/gfx/Image.h>

namespace cvt
{
	class FeatureAnalyzer
	{
		public:
			FeatureAnalyzer( size_t featuresPerRow, size_t patchSize, size_t lineSpacing = 20 );

			void addPatches( const Image & i0, const Vector2f & p0, 
							 const Image & i1, const Vector2f & p1 );

			const Image & image() const { return _img; }

		private:
			size_t  _featuresPerRow;
			size_t  _patchSize;
			size_t	_lineSpacing;
			size_t	_currLine;
			size_t	_currPos;
			size_t  _lineHeight;
			size_t  _maxLines;
			Image	_img;
			
			void resizeImage();
	};

	inline FeatureAnalyzer::FeatureAnalyzer( size_t featuresPerRow, size_t patchSize, size_t lineSpacing ) :
		_featuresPerRow( featuresPerRow ),
		_patchSize( patchSize ),
		_lineSpacing( lineSpacing ),
		_currLine( 0 ),
		_currPos( 0 ),
		_lineHeight( 2 * _patchSize + _lineSpacing )
	{
		size_t width = _featuresPerRow * _patchSize;
		_maxLines = ( 1024 / _lineHeight );
		size_t height = ( 1024 / _lineHeight ) * _lineHeight;
		_img.reallocate( width, height, IFormat::GRAY_UINT8 );
		_img.fill( Color::BLACK );
	}

	inline void FeatureAnalyzer::resizeImage()
	{
		Image tmp = _img;
		_img.reallocate( tmp.width(), tmp.height() + 10 * _lineHeight, tmp.format() );
		_maxLines += 10;
		_img.copyRect( 0, 0, tmp, tmp.rect() );
	}
			
	inline void FeatureAnalyzer::addPatches( const Image & i0, const Vector2f & p0, 
											 const Image & i1, const Vector2f & p1 )
	{
		Recti r( 0, 0, ( int )_patchSize, ( int )_patchSize );

		size_t xPos = _patchSize * _currPos;
		size_t yPos = _lineHeight * _currLine;

		r.x = ( int )p0.x; 
		r.y = ( int )p0.y;
		_img.copyRect( xPos, yPos, i0, r );

		r.x = ( int )p1.x; 
		r.y = ( int )p1.y;
		_img.copyRect( xPos, yPos + _patchSize, i1, r );
		
		_currPos++;

		if( _currPos == _featuresPerRow ){
			_currLine++;
			_currPos = 0;
			if( _currLine >= _maxLines )
				resizeImage();
		}
	}
}

#endif