#pragma once
#include "GraphicsTask.h"
#include "CImg.h"

using namespace cimg_library;

class CGraphicsFill :
	public IGraphicsTask
{
public:
	CGraphicsFill(void);
	~CGraphicsFill(void);
	virtual void executeTask();
private:
	CImg<bool> palette;
	void boundaryFill( int x, int y, CImg<bool>* palette );
	int fillLineLeft( int x, int y, CImg<bool>* palette );
	int fillLineRight( int x, int y, CImg<bool>* palette );
};

