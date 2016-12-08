#include "GraphicsFill.h"
#include "utils.h"

#include <iostream>
using namespace std;


CGraphicsFill::CGraphicsFill(void)
{
}


CGraphicsFill::~CGraphicsFill(void)
{
}

void CGraphicsFill::executeTask()
{
	CImg<bool> palette(PALETTE_SIZE, PALETTE_SIZE, 1, 1, 1);
	
	CImgDisplay displayWindow(palette, "Fill Area");

	int lastPointX;
	int lastPointY;

	int startPointX;
	int startPointY;

	int actionNumber = 0;

	while (!displayWindow.is_closed() && !displayWindow.is_keyESC())
	{
		palette.draw_text(5, 5, "Usage: Draw polygon with some points and then click in your polygon to fill it. \
								\n Press \'R\' to repaint, and \'C\' to close your polygon, and \'ESC\' to quit. \n \
								You'd better avoid drawing in the text area.\
								", COLOR_BLACK_BOOL);
		CImgDisplay::wait(displayWindow);
		int x = displayWindow.mouse_x();
		int y = displayWindow.mouse_y();

		if (displayWindow.button() & 1)
		{
			if (actionNumber == 0)
			{
				palette.draw_point(x, y, COLOR_BLACK_BOOL);
				startPointX = x;
				startPointY = y;
				actionNumber ++;
				lastPointX = x;
				lastPointY = y;
			} else if (actionNumber < 4)
			{
				palette.draw_line(lastPointX, lastPointY, x, y, COLOR_BLACK_BOOL);
				lastPointX = x;
				lastPointY = y;
				actionNumber ++;
				if (actionNumber == 4)
				{
					actionNumber = 3;
				}
			} else if (actionNumber == 4)
			{
				boundaryFill(x, y, &palette);
				actionNumber ++;
			}
		}

		if (displayWindow.is_keyC() && actionNumber == 3)
		{
			palette.draw_line(lastPointX, lastPointY, startPointX, startPointY, COLOR_BLACK_BOOL);
			actionNumber ++;
		}

		if (displayWindow.is_keyR())
		{
			actionNumber = 0;
			palette.fill(true);
		}

		palette.display(displayWindow);
	}
}

void CGraphicsFill::boundaryFill( int x, int y, CImg<bool>* palette )
{
	if (palette->at(x + y * palette->width()))
	{
		int startPointX = fillLineLeft(x, y, palette);
		int endPointX = fillLineRight(x, y, palette);
		for (int i = startPointX; i <= endPointX; i ++)
		{
			palette->draw_point(i, y, COLOR_BLACK_BOOL);
		}
		for (int i = startPointX; i <= endPointX; i ++)
		{
			if (y < palette->height() - 1 && palette->at(i + (y + 1) * palette->width()))
			{
				boundaryFill(i, y + 1, palette);
			}
			if (y > 0 && palette->at(i + (y - 1) * palette->width()))
			{
				boundaryFill(i, y - 1, palette);
			}
			/*if (y < palette->height() - 1 && palette->at(i + (y + 1) * palette->width()) && ( i == 0 || !palette->at( i - 1 + (y + 1) * palette->width())))
			{
				boundaryFill(i, y + 1, palette);
			}
			if (y > 0 && palette->at(i + (y - 1) * palette->width()) && ( i == 0 || !palette->at( i - 1 + (y - 1) * palette->width())))
			{
				boundaryFill(i, y - 1, palette);
			}*/
		}
	}
}

int CGraphicsFill::fillLineLeft( int x, int y, CImg<bool>* palette )
{
	if (x == 0 && palette->at(x + y * palette->width()))
	{
		//palette->draw_point(x, y, COLOR_BLACK_BOOL);
		return x;
	}
	if ( !palette->at(x + y * palette->width()))
	{
		return x + 1;
	} else
	{
		//palette->draw_point(x, y, COLOR_BLACK_BOOL);
		return fillLineLeft(x - 1, y, palette);
	}
}

int CGraphicsFill::fillLineRight( int x, int y, CImg<bool>* palette )
{
	if (x == palette->width() - 1 && palette->at(x + y * palette->width()))
	{
		//palette->draw_point(x, y, COLOR_BLACK_BOOL);
		return x;
	}
	if ( !palette->at(x + y * palette->width()))
	{
		return x - 1;
	} else
	{
		//palette->draw_point(x, y, COLOR_BLACK_BOOL);
		return fillLineRight(x + 1, y, palette);
	}
}

