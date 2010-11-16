#ifndef DC1394CAMERA_H
#define DC1394CAMERA_H

#include <cvt/io/Camera.h>
#include <dc1394/dc1394.h>
#include <cvt/gfx/Image.h>

namespace cvt
{

	class DC1394Camera : public Camera
	{

		public:
			DC1394Camera(size_t camIndex = 0, 
						 size_t width=640, 
						 size_t height=480, 
						 size_t fps = 30, 
						 IOrder order = IOrder::BGRA,
						 IType type = IType::UBYTE);
		
			~DC1394Camera();

			void open();
			void close();
			void init();
			void reset();
			void startCapture();
			void stopCapture();
									
			void nextFrame();
			const Image& frame() const;
			size_t width() const { return _width;}
			size_t height() const { return _height;}
			IOrder order() const { return _order;}
			IType type() const { return _type;}

			static size_t count();
			static void cameraInfo( size_t index, CameraInfo & info );

		private:
			void enableWhiteBalanceAuto(bool enable);
			void getWhiteBalance(unsigned int* ubValue, unsigned int* vrValue);
			void setWhiteBalance(unsigned int ubValue, unsigned int vrValue);
			void enableShutterAuto(bool enable);
			void getShutter(unsigned int* value);
			void setShutter(unsigned int value);
			void enableGainAuto(bool enable);
			void enableIrisAuto(bool enable);

			int _dmaBufNum;
			size_t _camIndex;
			Image _frame;
			size_t _width;
			size_t _height;
			size_t _fps;
			IOrder _order;
			IType _type;

			bool _capturing;
			dc1394_t* _dcHandle;
			dc1394camera_t* _camera;
			dc1394speed_t _speed;
			dc1394video_mode_t _mode;
			dc1394framerate_t _framerate;
	};

}

#endif
