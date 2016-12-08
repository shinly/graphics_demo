#include "GraphicsBSpline.h"
#include "GraphicsBresenham.h"
#include "utils.h"

CGraphicsBSpline::CGraphicsBSpline(void)
{
}


CGraphicsBSpline::~CGraphicsBSpline(void)
{
}

void CGraphicsBSpline::executeTask()
{
	CImg<bool> palette(PALETTE_SIZE, PALETTE_SIZE, 1, 1, 1);
	palette.draw_text(5, 5, "Usage: Draw four points with your mouses, and the programme will draw Bezier curve. \n Press \'R\' to repaint, and \'ESC\' to quit", COLOR_BLACK_BOOL);
	CImgDisplay displayWindow(palette, "B-Spline");

	double controllPointX[CONTROLL_P_N];
	double controllPointY[CONTROLL_P_N];
	int controllPointsNumber = 0;

	while (!displayWindow.is_closed() && !displayWindow.is_keyESC())
	{

		CImgDisplay::wait(displayWindow);
		if (displayWindow.button())
		{
			controllPointsNumber ++;
			if (controllPointsNumber <= CONTROLL_P_N)
			{

				int x = displayWindow.mouse_x();
				int y = displayWindow.mouse_y();
				controllPointX[controllPointsNumber - 1] = x;
				controllPointY[controllPointsNumber - 1] = y;
				drawCross(x, y, &palette);
				char text[2];
				itoa(controllPointsNumber, text, 10);
				palette.draw_text(x > PALETTE_SIZE * 0.5 ? x - 13 : x + 3, y > PALETTE_SIZE * 0.5 ? y - 13: y + 3, text, COLOR_BLACK_BOOL);
				if (controllPointsNumber == CONTROLL_P_N)
				{
					deBoor(controllPointX, controllPointY, &palette, 0);
				}
				palette.display(displayWindow);
			}
		}

		if (displayWindow.is_keyR())
		{
			palette.fill(true);
			controllPointsNumber = 0;
			palette.draw_text(5, 5, "Usage: Draw six points with your mouses, and the programme will draw B-Spine curve. \n Press \'R\' to repaint, and \'ESC\' to quit", COLOR_BLACK_BOOL);
			palette.display(displayWindow);
		}
	}
}

void CGraphicsBSpline::deBoor( double *controllPointX, double *controllPointY, CImg<bool> *palette, int level )
{
	double knots[CONTROLL_P_N+DEGREE+1];
	for (int i = 1; i < CONTROLL_P_N; i ++)
	{
		double pointsx[2] = {controllPointX[i-1], controllPointX[i]};
		double pointsy[2] = {controllPointY[i-1], controllPointY[i]};
		CGraphicsBresenham::bresenham( pointsx, pointsy, palette);
	}
	for (int i = 0; i < CONTROLL_P_N + DEGREE + 1; i ++ )
	{
		knots[i] = i * 1.0 / (CONTROLL_P_N + DEGREE);
	}

	int pos_i;
	int x0, x1, y0, y1;
	for (double u = knots[DEGREE]; u <= knots[CONTROLL_P_N]; u += STEP)
	{
		for ( pos_i = 0; pos_i < CONTROLL_P_N + DEGREE; pos_i ++ )
		{
			if ( u >= knots[pos_i] && u <= knots[pos_i + 1] )
			{
				break;
			}
		}
		int outX = 0, outY = 0;
		iterDeboor(DEGREE - 1, pos_i, u, knots, controllPointX, controllPointY,  &outX, &outY);
		if (u == knots[DEGREE])
		{
			x0 = outX;
			y0 = outY;
		}
		else
		{
			x1 = outX;
			y1 = outY;
			double pointsx[2] = {x0, x1};
			double pointsy[2] = {y0, y1};
			CGraphicsBresenham::bresenham(pointsx, pointsy, palette);
			x0 = x1;
			y0 = y1;
		}
	}
}

void CGraphicsBSpline::iterDeboor( int k, int i, double u, double *knots, double *controllPointX, double *controllPointY, int *outX, int *outY )
{
	if (k == 0)
	{
		*outX = controllPointX[i];
		*outY = controllPointY[i];
		return;
	}
	double alpha = (u - knots[i]) / (knots[i+DEGREE-k] - knots[i]);
	double newCtPointX1[CONTROLL_P_N];
	double newCtPointY1[CONTROLL_P_N];
	double newCtPointX2[CONTROLL_P_N];
	double newCtPointY2[CONTROLL_P_N];
	
	for (int j = 0; j < CONTROLL_P_N; j ++)
	{
		newCtPointX1[j] = controllPointX[j] * (1-alpha);
		newCtPointY1[j] = controllPointY[j] * (1-alpha);
		newCtPointX2[j] = controllPointX[j] * alpha;
		newCtPointY2[j] = controllPointY[j] * alpha;
	}

	int outX1 = 0, outY1 = 0, outX2 = 0, outY2 = 0;
	iterDeboor(k-1, i-1, u, knots, newCtPointX1, newCtPointY1, &outX1, &outY1);
	iterDeboor(k-1, i, u, knots, newCtPointX2, newCtPointY2, &outX2, &outY2);

	*outX = outX1 + outX2;
	*outY = outY1 + outY2;
}
