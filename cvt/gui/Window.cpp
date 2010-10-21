#include <cvt/gui/Window.h>
#include <cvt/gui/Application.h>

#include <cstdio>

namespace cvt {
	Window::Window( const std::string& title ) : Widget( NULL ), mouse( false )
	{
		setTitle( title );
	}

	Window::~Window( )
	{
	}

	void Window::closeEvent( CloseEvent* event )
	{
		Application::exit();
	}

	void Window::moveEvent( MoveEvent* event )
	{
		update();
	}

	void Window::mousePressEvent( MousePressEvent* event )
	{
		mouse = true;
		event->getPosition( mx, my );
		update();
	}

	void Window::mouseReleaseEvent( MouseReleaseEvent* event )
	{
		mouse = false;
		update();
	}


	void Window::mouseMoveEvent( MouseMoveEvent* event )
	{
		event->getPosition( mx, my );
		update();
	}


	void Window::paintEvent( PaintEvent* event, GFX* gfx )
	{
		int w, h, x, y;
		getSize( w, h );
		gfx->getColor().set( 0.4f, 0.4f, 0.4f, 1.0f );
		gfx->fillRect( 0, 0, w, h );
//		gfx->getColor().set( 0.0f, 1.0f, 0.0f, 1.0f );
//		gfx->fillRect( 100, 100, 100, 100 );


		gfx->getColor().set( 0.0f, 0.0f, 0.0f, 1.0f );
		char buf[ 200 ];

		sprintf( buf, "Size: %d x %d", w, h );
		gfx->drawText( 10, 20, buf );

		getPosition( x, y );
		sprintf( buf, "Position: %d x %d", x, y );
		gfx->drawText( 10, 32, buf );

		if( mouse ) {
			sprintf( buf, "MousePress: %d x %d", mx, my );
			gfx->drawText( 10, 44, buf );

			gfx->getColor().set( 0.0f, 1.0f, 0.0f, 1.0f );
			gfx->fillRect( mx - 5, my - 5, 10, 10 );
		}

//		gfx->getColor().set( 0.0f, 1.0f, 1.0f, 1.0f );
//		gfx->fillRect( 10, 20, 1, 1 );

	}

}