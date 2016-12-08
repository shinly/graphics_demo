#include "GraphicsEllipse.h"
#include "utils.h"

CGraphicsEllipse::CGraphicsEllipse(void)
{
}


CGraphicsEllipse::~CGraphicsEllipse(void)
{
}

void CGraphicsEllipse::executeTask()
{
	CImgDisplay displayWindow(PALETTE_SIZE, PALETTE_SIZE, "Mid Point Ellispe", 3);

	int centerX;
	int centerY;
	int Rx;
	int Ry;

	int actionNumer = 0;
	while (!displayWindow.is_closed() && !displayWindow.is_keyESC())
	{
		CImg<bool> palette(PALETTE_SIZE, PALETTE_SIZE, 1, 1, 1);
		palette.draw_text(5, 5, "Usage: Draw the center point first, and then select ellispe Rx, and then Ry.\n Press \'R\' to repaint, and \'ESC\' to quit", COLOR_BLACK_BOOL);
		int x = displayWindow.mouse_x();
		int y = displayWindow.mouse_y();

		if (displayWindow.is_keyR())
		{
			actionNumer = 0;
			palette.fill(false);
			continue;
		}

		if (displayWindow.button() && actionNumer == 0)
		{
			centerX = x;
			centerY = y;
			actionNumer ++;
			displayWindow.set_button();
		}

		if (actionNumer > 0)
		{
			drawCross(centerX, centerY, &palette);
		}

		if (actionNumer == 1)
		{
			if (2 * centerX - x >= PALETTE_SIZE)
			{
				x = 2 * centerX - PALETTE_SIZE + 1;
			} else if (x - centerX > centerX)
			{
				x = centerX + centerX;
			}
			palette.draw_line(x, 0, x, palette.height() - 1, COLOR_BLACK_BOOL);
			palette.draw_line(2 * centerX - x, 0, 2 * centerX - x, palette.height() - 1, COLOR_BLACK_BOOL);
			if (displayWindow.button())
			{
				Rx = ABS(centerX - x);
				actionNumer ++;
				displayWindow.set_button();
			}
		}

		if (actionNumer > 1)
		{
			palette.draw_line(centerX - Rx, centerY - 3, centerX - Rx, centerY + 3, COLOR_BLACK_BOOL);
			palette.draw_line(centerX + Rx, centerY - 3, centerX + Rx, centerY + 3, COLOR_BLACK_BOOL);
		}

		if (actionNumer == 2)
		{
			if (2 * centerY - y >= PALETTE_SIZE)
			{
				y = 2 * centerY - PALETTE_SIZE + 1;
			} else if (y - centerY > centerY)
			{
				y = centerY + centerY;
			}
			palette.draw_line(0, y, palette.width() - 1, y, COLOR_BLACK_BOOL);
			palette.draw_line(0, 2 * centerY - y, palette.width() - 1, 2 * centerY - y, COLOR_BLACK_BOOL);
			if (displayWindow.button())
			{
				Ry = ABS(centerY - y);
				actionNumer ++;
				displayWindow.set_button();
				drawEllipse(centerX, centerY, Rx, Ry, &palette);
			}
		}

		if (actionNumer > 2)
		{
			palette.draw_line(centerX - 3, centerY - Ry, centerX + 3, centerY - Ry, COLOR_BLACK_BOOL);
			palette.draw_line(centerX - 3, centerY + Ry, centerX + 3, centerY + Ry, COLOR_BLACK_BOOL);
			drawEllipse(centerX, centerY, Rx, Ry, &palette);
		}

		palette.display(displayWindow);
	}
}

void CGraphicsEllipse::drawEllipse( int centerX, int centerY, int Rx, int Ry, CImg<bool>* palette )
{
	int Rx2 = Rx * Rx;
	int Ry2 = Ry * Ry;
	int twoRx2 = 2 * Rx2;
	int twoRy2 = 2 * Ry2;
	int p;
	int x = 0;
	int y = Ry;
	int px = 0;
	int py = twoRx2 * y;

	ellipsePlotPoints(centerX, centerY, x, y, palette);

	p = (int) (Ry2 - (Rx2 * Ry) + (0.25 * Rx2) + 0.5);
	while (px < py)
	{
		x ++;
		px += twoRy2;
		if (p < 0)
		{
			p += Ry2 + px;
		} else
		{
			y --; 
			py -= twoRx2;
			p += Ry2 + px - py;
		}
		ellipsePlotPoints(centerX, centerY, x, y, palette);
	}

	p = (int) (Ry2 * (x + 0.5) * (x + 0.5) + Rx2 * (y - 1) * (y - 1) - Rx2 * Ry2);
	while (y > 0)
	{
		y --;
		py -= twoRx2;
		if (p > 0)
		{
			p += Rx2 - py;
		} 
		else
		{
			x ++;
			px += twoRy2;
			p += Rx2 - py + px;
		}
		ellipsePlotPoints(centerX, centerY, x, y, palette);
	}
}

void CGraphicsEllipse::ellipsePlotPoints( int centerX, int centerY, int x, int y, CImg<bool>* palette )
{
	palette->draw_point(centerX - x, centerY - y, COLOR_BLACK_BOOL);
	palette->draw_point(centerX + x, centerY - y, COLOR_BLACK_BOOL);
	palette->draw_point(centerX - x, centerY + y, COLOR_BLACK_BOOL);
	palette->draw_point(centerX + x, centerY + y, COLOR_BLACK_BOOL);
}
