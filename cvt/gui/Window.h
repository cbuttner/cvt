#ifndef CVTWINDOW_H
#define CVTWINDOW_H

#include <cvt/gui/Widget.h>

namespace cvt {

	class Window : public Widget
	{
		public:
			Window( const std::string& title );
			virtual ~Window();

			virtual void closeEvent( CloseEvent* event );
			virtual void moveEvent( MoveEvent* event );
			virtual void paintEvent( PaintEvent* event, GFX* gfx );
			virtual void mousePressEvent( MousePressEvent* event );
			virtual void mouseReleaseEvent( MouseReleaseEvent* event );
			virtual void mouseMoveEvent( MouseMoveEvent* event );

		private:
			Window( const Window& w );
			bool mouse;
			int mx, my;
	};
}

#endif