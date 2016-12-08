#include "GraphicsBresenham.h"
#include "utils.h"


CGraphicsBresenham::CGraphicsBresenham(void)
{
}


CGraphicsBresenham::~CGraphicsBresenham(void)
{
}

void CGraphicsBresenham::executeTask()
{
	CImg<bool> palette(PALETTE_SIZE, PALETTE_SIZE, 1, 1, 1);
	palette.draw_text(5, 5, "Usage: Draw two points with your mouses, and the programme will draw a line between them. \n Press \'R\' to repaint, and \'ESC\' to quit", COLOR_BLACK_BOOL);
	CImgDisplay displayWindow(palette, "Bresenham");

	double controllPointX[2];
	double controllPointY[2];
	int controllPointsNumber = 0;

	while (!displayWindow.is_closed() && !displayWindow.is_keyESC())
	{

		CImgDisplay::wait(displayWindow);
		if (displayWindow.button())
		{
			controllPointsNumber ++;
			if (controllPointsNumber <= 2)
			{

				int x = displayWindow.mouse_x();
				int y = displayWindow.mouse_y();
				controllPointX[controllPointsNumber - 1] = x;
				controllPointY[controllPointsNumber - 1] = y;
				drawCross(x, y, &palette);
				char text[2];
				itoa(controllPointsNumber, text, 10);
				palette.draw_text(x > PALETTE_SIZE * 0.5 ? x - 13 : x + 3, y > PALETTE_SIZE * 0.5 ? y - 13: y + 3, text, COLOR_BLACK_BOOL);
				if (controllPointsNumber == 2)
				{
					bresenham(controllPointX, controllPointY, &palette);
				}
				palette.display(displayWindow);
			}
		}

		if (displayWindow.is_keyR())
		{
			palette.fill(true);
			controllPointsNumber = 0;
			palette.draw_text(5, 5, "Usage: Draw two points with your mouse, and the programme will draw a line between them. \n Press \'R\' to repaint, and \'ESC\' to quit", COLOR_BLACK_BOOL);
			palette.display(displayWindow);
		}
	}
}

void CGraphicsBresenham::bresenham( double *controllPointX, double *controllPointY, CImg<bool>* palette )
{
	int dx = ABS(controllPointX[0] - controllPointX[1]);
	int dy = ABS(controllPointY[0] - controllPointY[1]);
	if (dx > dy)
	{
		bool shouldInverse = controllPointY[0] > controllPointY[1] ? true : false;
		int p = 2 * dy - dx;
		int twoDy = 2 * dy;
		int twoDyDx = 2 * (dy - dx);
		int x, y, xEnd;
		if (controllPointX[0] > controllPointX[1])
		{
			x = controllPointX[1];
			y = controllPointY[1];
			xEnd = controllPointX[0];
			shouldInverse = !shouldInverse;
		} else
		{
			x = controllPointX[0];
			y = controllPointY[0];
			xEnd = controllPointX[1];
		}

		palette->draw_point(x, y, COLOR_BLACK_BOOL);

		while (x < xEnd)
		{
			x ++;
			if (p < 0)
			{
				p += twoDy;
			} else
			{
				if (shouldInverse)
				{
					y --;
				} else
				{
					y ++;
				}
				p += twoDyDx;
			}
			palette->draw_point(x, y, COLOR_BLACK_BOOL);
		}
	} 
	else
	{
		bool shouldInverse = controllPointX[0] > controllPointX[1] ? true : false;
		int p = 2 * dx - dy;
		int twoDx = 2 * dx;
		int twoDxDy = 2 * (dx - dy);
		int x, y, yEnd;
		if (controllPointY[0] > controllPointY[1])
		{
			y = controllPointY[1];
			x = controllPointX[1];
			yEnd = controllPointY[0];
			shouldInverse = !shouldInverse;
		} else
		{
			y = controllPointY[0];
			x = controllPointX[0];
			yEnd = controllPointY[1];
		}

		palette->draw_point(x, y, COLOR_BLACK_BOOL);

		while (y < yEnd)
		{
			y ++;
			if (p < 0)
			{
				p += twoDx;
			} else
			{
				if (shouldInverse)
				{
					x --;
				} else
				{
					x ++;
				}
				p += twoDxDy;
			}
			palette->draw_point(x, y, COLOR_BLACK_BOOL);
		}
	}
	

}
