#include "GraphicsTaskFactory.h"


CGraphicsTaskFactory::CGraphicsTaskFactory(void)
{
}


CGraphicsTaskFactory::~CGraphicsTaskFactory(void)
{
}

IGraphicsTask* CGraphicsTaskFactory::createTask( int taskId )
{
	switch (taskId)
	{
	case  graphics_task::TASK_BRESENHAM:
		return new CGraphicsBresenham();
		break;
	case graphics_task::TASK_BEZIER:
		return new CGraphicsBezier();
		break;
	case graphics_task::TASK_ELLISPE:
		return new CGraphicsEllipse();
		break;
	case graphics_task::TASK_FILL:
		return new CGraphicsFill();
		break;
	case graphics_task::TASK_BSPLINE:
		return new CGraphicsBSpline();
		break;
	case graphics_task::TASK_FRACTAL:
		return new CGraphicsFractal();
		break;
	case graphics_task::TASK_SCENE:
		return new CGraphicsLily();
		break;
	default:
		return NULL;
		break;
	}
}
