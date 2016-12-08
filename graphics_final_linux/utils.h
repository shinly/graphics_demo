#pragma once
#include "CImg.h"
using namespace cimg_library;

#define  PALETTE_SIZE 512
#define ABS(x) ((x) > 0 ? (x) : -(x))

const bool COLOR_BLACK_BOOL[] = {false};
const bool COLOR_WHITE_BOOL[] = {true};

static void drawCross(int x, int y, CImg<bool> *palette)
{
	for (int i = x - 3; i <= x + 3; i ++)
	{
		if (i >=0 && i < PALETTE_SIZE - 1)
		{
			palette->draw_point(i, y, COLOR_BLACK_BOOL);
		}
	}
	for (int j = y - 3; j <= y + 3; j ++)
	{
		if (j >=0 && j < PALETTE_SIZE - 1)
		{
			palette->draw_point(x, j, COLOR_BLACK_BOOL);
		}
	}
}

static bool checkConnected(double *pointX, double *pointY)
{

	for (int i = 0; i < 3; i ++ )
	{
		if (ABS(pointX[i] - pointX[i+1]) > 1 || ABS(pointY[i] - pointY[i+1]) > 1)
		{
			return false;
		}
	}
	return true;
}