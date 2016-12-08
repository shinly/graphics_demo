#include "GraphicsTask.h"
#include "GraphicsTaskFactory.h"
#include "CImg.h"
#include "utils.h"
#include <iostream>

const int TASK_NUM = 7; //

using namespace cimg_library;
using namespace std;

int lineys[] = {35 , 85, 135, 185, 235, 285, 335, 385}; //

void clearLines( CImg<bool>* mainPalette ) 
{
	for (int i = 0; i < TASK_NUM; i ++)
	{
		mainPalette->draw_line(0, lineys[i], 299, lineys[i], COLOR_WHITE_BOOL);
		mainPalette->draw_line(0, lineys[i+1], 299, lineys[i+1], COLOR_WHITE_BOOL);
		mainPalette->draw_line(0, lineys[i], 0, lineys[i+1], COLOR_WHITE_BOOL);
		mainPalette->draw_line(299, lineys[i], 299, lineys[i+1], COLOR_WHITE_BOOL);
	}
}

void drawLines( int i, CImg<bool>* mainPalette ) 
{
	mainPalette->draw_line(0, lineys[i], 299, lineys[i], COLOR_BLACK_BOOL);
	mainPalette->draw_line(0, lineys[i+1], 299, lineys[i+1], COLOR_BLACK_BOOL);
	mainPalette->draw_line(0, lineys[i], 0, lineys[i+1], COLOR_BLACK_BOOL);
	mainPalette->draw_line(299, lineys[i], 299, lineys[i+1], COLOR_BLACK_BOOL);
}

int main(int argc, char **argv)
{
	CImg<bool> mainPalette(300, 512, 1, 1, 1);
	CImgDisplay mainWindow(mainPalette, "Graphics Homework");

	mainPalette.draw_text(5, 5, "Select one Item below to start.", COLOR_BLACK_BOOL);
	mainPalette.draw_text(30, 50, "-- Bresenham", COLOR_BLACK_BOOL, 0, 1, 30);
	mainPalette.draw_text(30, 100, "-- Bezier", COLOR_BLACK_BOOL, 0, 1, 30);
	mainPalette.draw_text(30, 150, "-- Ellipse", COLOR_BLACK_BOOL, 0, 1, 30);
	mainPalette.draw_text(30, 200, "-- Fill", COLOR_BLACK_BOOL, 0, 1, 30);
	mainPalette.draw_text(30, 250, "-- BSpline", COLOR_BLACK_BOOL, 0, 1, 30);
	mainPalette.draw_text(30, 300, "-- Fractal", COLOR_BLACK_BOOL, 0, 1, 30);
	mainPalette.draw_text(30, 350, "-- Scene", COLOR_BLACK_BOOL, 0, 1, 30);

	mainPalette.display(mainWindow);

	while (!mainWindow.is_closed() && !mainWindow.is_keyESC())
	{
		int y = mainWindow.mouse_y();
		for (int i = 0; i < TASK_NUM; i ++)
		{
			if (y >= lineys[i] && y < lineys[i+1])
			{
				clearLines(&mainPalette);
				drawLines(i, &mainPalette);
				break;
			}
		}

		if (y < lineys[0] || y > lineys[TASK_NUM])
		{
			clearLines(&mainPalette);
		}

		if (mainWindow.button() & 1)
		{
			mainWindow.set_button(1, false);
			for (int i = 0; i < TASK_NUM; i ++)
			{
				if (y >= lineys[i] && y < lineys[i+1])
				{
					IGraphicsTask *task = CGraphicsTaskFactory::createTask(i);
					if (task == NULL)
					{
						cerr << "No proper task to be created!" << endl;
						break;
					}

					task->executeTask();
					delete task;
					break;
				}
			} 
		}
		mainPalette.display(mainWindow);
	}

	
	return 0;
}

