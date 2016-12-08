#pragma once
#include "graphicstask.h"
#include "CImg.h"
using namespace cimg_library;

class CGraphicsBresenham :
	public IGraphicsTask
{
public:
	CGraphicsBresenham(void);
	~CGraphicsBresenham(void);
	virtual void executeTask();
	void static bresenham( double *controllPointX, double *controllPointY, CImg<bool>* palette );
};

