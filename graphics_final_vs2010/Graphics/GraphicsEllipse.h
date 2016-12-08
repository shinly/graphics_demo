#pragma once
#include "graphicstask.h"
#include "CImg.h"

using namespace cimg_library;

class CGraphicsEllipse :
	public IGraphicsTask
{
public:
	CGraphicsEllipse(void);
	~CGraphicsEllipse(void);
	virtual void executeTask();
	void drawEllipse( int centerX, int centerY, int Rx, int Ry, CImg<bool>* palette );
private:
	void ellipsePlotPoints( int centerX, int centerY, int x, int y, CImg<bool>* palette );
};

