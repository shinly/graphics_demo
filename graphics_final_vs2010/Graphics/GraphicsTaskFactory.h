#pragma once
#include "GraphicsTask.h"
#include "GraphicsBresenham.h"
#include "GraphicsBezier.h"
#include "GraphicsBSpline.h"
#include "GraphicsEllipse.h"
#include "GraphicsFill.h"
#include "GraphicsFractal.h"
#include "GraphicsLily.h"

namespace graphics_task {
	const int TASK_BRESENHAM = 0;
	const int TASK_BEZIER = 1;
	const int TASK_ELLISPE = 2;
	const int TASK_FILL = 3;
	const int TASK_BSPLINE = 4;
	const int TASK_FRACTAL = 5;
	const int TASK_SCENE = 6;
}


class CGraphicsTaskFactory
{
public:
	CGraphicsTaskFactory(void);
	~CGraphicsTaskFactory(void);

	static IGraphicsTask* createTask(int taskId);
};

