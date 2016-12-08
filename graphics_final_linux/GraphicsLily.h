#pragma once
#include "GraphicsTask.h"
#include "CImg.h"
#include <math.h>
#include <iostream>
#include <ctime>
#include <cstdlib>

#define PI 3.1415927
#define PI_F PI/180
#define P_WIDTH 700
#define P_HEIGHT 360
#define MAXINT 32767

using namespace cimg_library;
using namespace std;

class CGraphicsLily :
	public IGraphicsTask
{
public:
	CGraphicsLily(void);
	~CGraphicsLily(void);

	virtual void executeTask();
private:
	float zuff[P_WIDTH][P_HEIGHT];
	unsigned char colors[P_WIDTH][P_HEIGHT][3];

	void lily_deform_xy(float a, float b, float u, float v, float &x, float &y, float &z);
	float bh(float u, float v, float a, float b, float x, float y);
	void n_vector(float x[], float y[], float z[], float &a, float &b, float &c);
	void revolve_x(float cx, float xx, float yy, float zz, float &x, float &y, float &z);
	void revolve_y(float cy, float xx, float yy, float zz, float &x, float &y, float &z);
	void revolve_z(float cz, float xx, float yy, float zz, float &x, float &y, float &z);
	void hsi_rgb (double h, double s, double i, int &r, int &g, int &b);
	int nodical(int h, float x[], float y[], float xjd[], float yjd[]);
	void cylinder(float a, float b, float u, float v, float &x, float &y, float &z);
	void ellipsoid(int x0, int y0, int z0, int a, int b, int c, float u, float v, float &x, float &y, float &z);
	void lily_pistil_draw(int au, int bv, float cx, float cy, float cz, float dx, float dy);
	void plane_draw(float *x, float *y, float *z, float H, float I, float S, float gx, float gy, float gz, float km, float gd);
	void lily_stamen_draw(int au, int bv, float cx1, float cy1, float cx, float cy, float cz, float dx, float dy);
	void lily_petal_draw(int au, int bv, float cx1, float cy1, float cx, float cy, float cz, float dx, float dy);
};

