#pragma once
#include "graphicstask.h"
#include "CImg.h"

#define RE_LEFT -2
#define IM_BOTTOM -1.5
#define N_T 100
#define WIDTH 800
#define HEIGHT 800

using namespace cimg_library;


class CGraphicsFractal :
	public IGraphicsTask
{
public:
	CGraphicsFractal(void);
	~CGraphicsFractal(void);

	virtual void executeTask();

private:
	int N_total;
	int *frac_data;
	bool is_first_iter;
	double step_x, step_y;
	double re_left, im_bottom;
	SIZE size;

	void calcData(SIZE rectSize, RECT rect);
	void refresh(CImg<unsigned char> *palette, CImgDisplay *window);
};

