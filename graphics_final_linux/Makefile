all: Graphics

Graphics: CImg.h Graphics.o GraphicsTaskFactory.o GraphicsLily.o GraphicsFractal.o GraphicsFill.o GraphicsEllipse.o GraphicsBSpline.o GraphicsBezier.o GraphicsBresenham.o GraphicsTask.o
	g++  Graphics.o GraphicsFill.o GraphicsFractal.o GraphicsLily.o GraphicsTask.o GraphicsTaskFactory.o GraphicsEllipse.o GraphicsBSpline.o GraphicsBezier.o GraphicsBresenham.o -o Graphics -O2 -L/usr/X11R6/lib -lm -lpthread -lX11

Graphics.o: CImg.h Graphics.cpp
	g++ -c  Graphics.cpp

GraphicsTaskFactory.o: GraphicsTaskFactory.h GraphicsTaskFactory.cpp GraphicsTask.o GraphicsBresenham.o GraphicsBezier.o GraphicsBSpline.o GraphicsEllipse.o GraphicsFill.o GraphicsFractal.o GraphicsLily.o
	g++ -c  GraphicsTaskFactory.cpp

GraphicsLily.o: CImg.h GraphicsLily.h GraphicsLily.cpp GraphicsTask.o
	g++ -c  GraphicsLily.cpp

GraphicsFractal.o: CImg.h GraphicsFractal.h GraphicsFractal.cpp GraphicsTask.o
	g++ -c  GraphicsFractal.cpp

GraphicsFill.o: utils.h CImg.h GraphicsFill.h GraphicsFill.cpp GraphicsTask.o
	g++ -c  GraphicsFill.cpp

GraphicsEllipse.o: utils.h CImg.h GraphicsEllipse.h GraphicsEllipse.cpp GraphicsTask.o
	g++ -c  GraphicsEllipse.cpp

GraphicsBSpline.o: utils.h CImg.h GraphicsBSpline.h GraphicsBSpline.cpp GraphicsTask.o GraphicsBresenham.o
	g++ -c  GraphicsBSpline.cpp

GraphicsBezier.o: utils.h CImg.h GraphicsBezier.h GraphicsBezier.cpp GraphicsTask.o GraphicsBresenham.o
	g++ -c  GraphicsBezier.cpp

GraphicsBresenham.o: utils.h CImg.h GraphicsBresenham.h GraphicsBresenham.cpp GraphicsTask.o
	g++ -c  GraphicsBresenham.cpp

GraphicsTask.o: GraphicsTask.h GraphicsTask.cpp
	g++ -c  GraphicsTask.cpp

clean:
	rm -rf *.o Graphics
