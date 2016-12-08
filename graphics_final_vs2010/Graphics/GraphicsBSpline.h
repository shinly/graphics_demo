#pragma once
#include "graphicstask.h"
#include "CImg.h"

#define CONTROLL_P_N 6
#define DEGREE 3
#define STEP 0.01
using namespace cimg_library;

class CGraphicsBSpline :
	public IGraphicsTask
{
public:
	CGraphicsBSpline(void);
	~CGraphicsBSpline(void);
	virtual void executeTask();

private:
	void deBoor(double *controllPointX, double *controllPointY, CImg<bool> *palette, int level);
	void iterDeboor(int k, int i, double u, double *knots, double *controllPointX, double *controllPointY, int *outX, int *outY);
};

