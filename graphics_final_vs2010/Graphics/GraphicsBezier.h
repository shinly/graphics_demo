#pragma once
#include "graphicstask.h"
#include "CImg.h"
using namespace cimg_library;
#define MAX_LEVEL 5

class CGraphicsBezier :
	public IGraphicsTask
{
public:
	CGraphicsBezier(void);
	~CGraphicsBezier(void);

	virtual void executeTask();

private:
	void casteljau(double *controllPointX, double *controllPointY, CImg<bool> *palette, int level);
};

