#include "GraphicsBezier.h"
#include "GraphicsBresenham.h"
#include "utils.h"


CGraphicsBezier::CGraphicsBezier(void)
{
}


CGraphicsBezier::~CGraphicsBezier(void)
{
}

void CGraphicsBezier::executeTask()
{
	CImg<bool> palette(PALETTE_SIZE, PALETTE_SIZE, 1, 1, 1);
	palette.draw_text(5, 5, "Usage: Draw four points with your mouses, and the programme will draw Bezier curve. \n Press \'R\' to repaint, and \'ESC\' to quit", COLOR_BLACK_BOOL);
	CImgDisplay displayWindow(palette, "Bezier");

	double controllPointX[4];
	double controllPointY[4];
	int controllPointsNumber = 0;

	while (!displayWindow.is_closed() && !displayWindow.is_keyESC())
	{

		CImgDisplay::wait(displayWindow);
		if (displayWindow.button())
		{
			controllPointsNumber ++;
			if (controllPointsNumber <= 4)
			{

				int x = displayWindow.mouse_x();
				int y = displayWindow.mouse_y();
				controllPointX[controllPointsNumber - 1] = x;
				controllPointY[controllPointsNumber - 1] = y;
                drawCross(x, y, &palette);
                char text[2];
                sprintf(text, "%d", controllPointsNumber);
				palette.draw_text(x > PALETTE_SIZE * 0.5 ? x - 13 : x + 3, y > PALETTE_SIZE * 0.5 ? y - 13: y + 3, text, COLOR_BLACK_BOOL);
				if (controllPointsNumber == 4)
				{
					casteljau(controllPointX, controllPointY, &palette, 0);
				}
				palette.display(displayWindow);
			}
		}

		if (displayWindow.is_keyR())
		{
			palette.fill(true);
			controllPointsNumber = 0;
			palette.draw_text(5, 5, "Usage: Draw four points with your mouses, and the programme will draw Bezier curve. \n Press \'R\' to repaint, and \'ESC\' to quit", COLOR_BLACK_BOOL);
			palette.display(displayWindow);
		}
	}
}
/*
void CGraphicsBezier::casteljau(double *controllPointX, double *controllPointY, CImg<bool> *palette, int level) 
{
	if (checkConnected(controllPointX, controllPointY))
	{
		for (int i = 0; i < 4; i++)
		{
			palette->draw_point(controllPointX[i], controllPointY[i], COLOR_BLACK_BOOL);
		}
		return;
	}
	if (level == MAX_LEVEL)
	{
		double pointsX[2] = {controllPointX[0], controllPointX[3]};
		double pointsY[2] = {controllPointY[0], controllPointY[3]};
		CGraphicsBresenham::bresenham(pointsX, pointsY, palette);
		return;
	}

	double firstHalfPointsX[4];
	double firstHalfPointsY[4];
	double lastHalfPointsX[4];
	double lastHalfPointsY[4];

	double p11X = (controllPointX[1] + controllPointX[2]) / 2.0;
	double p11Y = (controllPointY[1] + controllPointY[2]) / 2.0;

	firstHalfPointsX[0] = controllPointX[0];
	firstHalfPointsY[0] = controllPointY[0];
	firstHalfPointsX[1] = (controllPointX[0] + controllPointX[1]) / 2.0;
	firstHalfPointsY[1] = (controllPointY[0] + controllPointY[1]) / 2.0;
	firstHalfPointsX[2] = (firstHalfPointsX[1] + p11X) / 2.0;
	firstHalfPointsY[2] = (firstHalfPointsY[1] + p11Y) / 2.0;

	lastHalfPointsX[0] = controllPointX[3];
	lastHalfPointsY[0] = controllPointY[3];
	lastHalfPointsX[1] = (controllPointX[2] + controllPointX[3]) / 2.0;
	lastHalfPointsY[1] = (controllPointY[2] + controllPointY[3]) / 2.0;
	lastHalfPointsX[2] = (lastHalfPointsX[1] + p11X) / 2.0;
	lastHalfPointsY[2] = (lastHalfPointsY[1] + p11Y) / 2.0;

	firstHalfPointsX[3] = (firstHalfPointsX[2] + lastHalfPointsX[2]) / 2.0;
	firstHalfPointsY[3] = (firstHalfPointsY[2] + lastHalfPointsY[2]) / 2.0;
	lastHalfPointsX[3] = firstHalfPointsX[3];
	lastHalfPointsY[3] = firstHalfPointsY[3];

	casteljau(firstHalfPointsX, firstHalfPointsY, palette, level + 1);
	casteljau(lastHalfPointsX, lastHalfPointsY, palette, level + 1);
}*/

void CGraphicsBezier::casteljau(double *controllPointX, double *controllPointY, CImg<bool> *palette, int level) 
{
	float step = 0.05;
	int x0, y0, x1, y1;
	x0 = controllPointX[0];
	y0 = controllPointY[0];
	for (float t = 0; t <=1; t += step)
	{
		int px[4], py[4];
		for (int i = 0; i < 4; i++)
		{
			px[i] = controllPointX[i];
			py[i] = controllPointY[i];
		}

		for ( int i = 1; i < 4; i ++ )
		{
			for ( int j = 0; j < 4 - i; j++ )
			{
				px[j] = (1-t) * px[j] + t * px[j+1];
				py[j] = (1-t) * py[j] + t * py[j+1];
			}
		}
		x1 = px[0];
		y1 = py[0];
		palette->draw_line(x0, y0, x1, y1, COLOR_BLACK_BOOL);
		x0 = x1;
		y0 = y1;
	}
}
