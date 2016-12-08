#include "GraphicsLily.h"


CGraphicsLily::CGraphicsLily(void)
{
}


CGraphicsLily::~CGraphicsLily(void)
{
}

void CGraphicsLily::lily_deform_xy(float a, float b, float u, float v, float &x, float &y, float &z)
{
	x = a * u + u * a * 0.6 * (sin(v * PI + 1)) + 0.05 * a * u * sin(0.8 * a * v * PI);
	y = b * v + (v - 0.5) * a * sin((u + 0.5) * PI) - 0.05 * a * (v - 0.5) * sin(10 * (u + 0.5) * PI);
	z = 20;
}
float CGraphicsLily::bh(float u, float v, float a, float b, float x, float y)
{
	float g = 0;
	g = (1 - 2 * fabs(v - 0.5)) * 0.15 * sin(12 * 2 * (u + 0.5) * PI) * (1 - 2 * fabs(u));
	g += 0.1 * a * exp(-25 * a * (u-0.05) * (u - 0.05)) + 0.1 * a * exp(-25 * a * (u + 0.05) * (u + 0.05));
	g += a * (sin(PI * y / b * 1 + 3)) + x * x * x / a / a / a * 10 * sin(PI * y /10);
	return g;
}
void CGraphicsLily::n_vector(float x[], float y[], float z[], float &a, float &b, float &c)
{
	a = (y[1] - y[0]) * (z[2] - z[0]) - (y[2] - y[0]) * (z[1] - z[0]);
	b = (z[1] - z[0]) * (x[2] - x[0]) - (z[2] - z[0]) * (x[1] - x[0]);
	c = (x[1] - x[0]) * (y[2] - y[0]) - (x[2] - x[0]) * (y[1] - y[0]);
	float nn = (sqrt(a * a + b * b + c * c));
	a = a / nn;
	b = b / nn;
	c = c / nn;
}
void CGraphicsLily::revolve_x(float cx, float xx, float yy, float zz, float &x, float &y, float &z)
{
	x = xx;
	y = yy * cos(cx) - zz * sin(cx);
	z = yy * sin(cx) + zz * cos(cx);
}
void CGraphicsLily::revolve_y(float cy, float xx, float yy, float zz, float &x, float &y, float &z)
{
	x = xx * cos(cy) + zz * sin(cy);
	y = yy;
	z = -xx * sin(cy) + zz * cos(cy);
}
void CGraphicsLily::revolve_z(float cz, float xx, float yy, float zz, float &x, float &y, float &z)
{
	x = xx * cos(cz) - yy * sin(cz);
	y = xx * sin(cz) + yy * cos(cz);
	z = zz;
}
void CGraphicsLily::hsi_rgb(double h, double s, double i, int &r, int &g, int &b)
{
	float p = (float) (PI / 180);
	if (h >= 0 && h <= 120 *p)
	{
		b = (int) (i * (1 - s));
		r = (int) (i * (1 + s * cos(h) / cos(60 * p - h)));
		g = (int) (3 * i - (b + r));
	}
	else if (h >= 120 * p && h <= 240 * p)
	{
		r = (int) (i * (1 -s));
		g = (int) (i * (1 + s * cos(h - 120 * p) / cos (PI - h)));
		b = (int) (3 * i - (g + r));
	}
	else if (h >= 240 * p && h <= 360 * p)
	{
		g = (int) (i * (1 - s));
		b = (int) (i * (1 + s * cos(h - 240 * p) / cos(300 * p - h)));
		r = (int) (3 * i - (g + b));
	}
}
int CGraphicsLily::nodical(int h, float x[], float y[], float xjd[], float yjd[])
{
	int k = 0;
	for (int i = 0; i < 4; i++)
	{
		if ((h - y[i]) * (h - y[i + 1]) < 0)
		{
			xjd[k] = x[i] + (x[i] - x[i + 1]) * (h - y[i]) / (y[i] - y[i+1]);
			k ++;
		}
	}
	if (k == 2)
	{
		if (xjd[0] > xjd[1])
		{
			float t = xjd[0];
			xjd[0] = xjd[1];
			xjd[1] = t;
		}
		return 1;
	}
	return 0;
}
void CGraphicsLily::cylinder(float a, float b, float u, float v, float &x, float &y, float &z)
{
	x = a * cos(u * 2 * PI);
	y = v * b;
	z = a * sin(u * 2 * PI);
}
void CGraphicsLily::ellipsoid(int x0, int y0, int z0, int a, int b, int c, float u, float v, float &x, float &y, float &z)
{
	x = x0 + a * cos(u) * cos(v);
	y = y0 + b * cos(u) * sin(v);
	z = z0 + c * sin(u);
}
void CGraphicsLily::plane_draw(float *x, float *y, float *z, float H, float I, float S, float gx, float gy, float gz, float km, float gd)
{

	float a, b, c, d, vx, vy, vz, xjd[2], yjd[2];
	int R, G, B;
	float zz;
	x[4] = x[0];
	y[4] = y[0];
	n_vector(x, y, z, a, b, c);
	if (c < 0)
	{
		return;
	}
	d = -(a * x[0] + b * y[0] + c * z[0]);
	vx = gx - x[0];
	vy = gy - y[0];
	vz = gz - z[0];
	float cos1 = (vx * a + vy * b + vz * c) / sqrt(vx * vx + vy * vy + vz * vz);
	float col = I * km * cos1 + gd;
	if (col < gd)
	{
		col = gd;
	}
	if (col > 255.0f)
	{
		col = 255.0f;
	}
	float ymin = y[0], ymax = y[0];

	for (int i = 0; i < 4; i++)
	{
		if (y[i] < ymin)
		{
			ymin = y[i];
		}
		if (y[i] > ymax)
		{
			ymax = y[i];
		}
	}



	for (int h = (int) ymin; h <= (int) ymax; h++)
	{
		if (nodical(h, x, y, xjd, yjd))
		{
			zz = - (a * xjd[0] + b * h + d) /c;
			for (int xp = (int) xjd[0]; xp < (int) xjd[1]; xp++)
			{
				if (zz > zuff[xp][h])
				{
					hsi_rgb(H, S, col, R, G, B);
					if (R > 255)
					{
						R = 255;
					}
					if (R < 0)
					{
						R = 0;
					}
					if (G > 255)
					{
						G = 255;
					}
					if (G < 0)
					{
						G = 0;
					}
					if (B > 255)
					{
						B = 255;
					}
					if (B < 0)
					{
						B = 0;
					}
					char color[] = {R, G, B};
					colors[xp][h][0] = R;
					colors[xp][h][1] = G;
					colors[xp][h][2] = B;
					//					palette.draw_point(xp, h, color);
					zuff[xp][h] = zz;
				}
				zz = zz - a / c;
			}
		}
	}
}

void CGraphicsLily::lily_pistil_draw(int au, int bv, float cx, float cy, float cz, float dx, float dy)
{
	float uu[4], vv[4], x[5], y[5], z[5], xd[5], yd[5], zd[5], a, b, c;
	float du = 0.2, dv = 0.1;
	float cc = rand() % 5;
	for (float u = 0.0f; u <= 1.0f; u = u + du)
	{
		for (float v = 0.0f; v <= 1.0f; v = v + dv)
		{
			uu[0] = u;
			uu[3] = u;
			vv[0] = v;
			vv[1] = v;
			uu[1] = u + du;
			uu[2] = u + du;
			vv[2] = v + dv;
			vv[3] = v + dv;
			for (int i = 0; i < 4; i++)
			{
				cylinder(au, bv, uu[i], vv[i], x[i], y[i], z[i]);
			}
			for (int i = 0; i < 4; i ++)
			{
				x[i] = x[i] - cc * sin(vv[i] * 2 * PI);
				z[i] = z[i] - cc * sin(vv[i] * 2 * PI);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_x(cx, x[i], y[i], z[i], xd[i], yd[i], zd[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_y(cy, xd[i], yd[i], zd[i], x[i], y[i], z[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_z(cz, x[i], y[i], z[i], xd[i], yd[i], zd[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				x[i] = xd[i] + dx;
				y[i] = dy - yd[i];
				z[i] = zd[i];
			}
			plane_draw(x, y, z, 60 * PI_F, 0, 0.8, 100, 200, 150, 0.8, 50);
		}
		int x0 = x[0];
		int y0 = y[0];
		du = 0.3;
		dv = 0.3;
		for (float u = -PI/2.0f; u <= PI/2.0f; u = u + du)
		{
			for (float v = 0.0f; v <= 2.0f*PI; v = v + dv)
			{
				uu[0] = u;
				uu[3] = u;
				vv[0] = v;
				vv[1] = v;
				uu[1] = u + du;
				uu[2] = u + du;
				vv[2] = v + dv;
				vv[3] = v + dv;
				for (int i = 0; i < 4; i++)
				{
					ellipsoid(0, 0, 0, 4, 2, 4, uu[i], vv[i], x[i], y[i], z[i]);
				}
				for (int i = 0; i < 4; i ++)
				{
					x[i] = x[i] - cc * sin(vv[i] * 2 * PI);
					z[i] = z[i] - cc * sin(vv[i] * 2 * PI);
				}
				for (int i = 0; i < 4; i++)
				{
					revolve_x(cx, x[i], y[i], z[i], xd[i], yd[i], zd[i]);
				}
				for (int i = 0; i < 4; i++)
				{
					revolve_y(cy, xd[i], yd[i], zd[i], x[i], y[i], z[i]);
				}
				for (int i = 0; i < 4; i++)
				{
					revolve_z(cz, x[i], y[i], z[i], xd[i], yd[i], zd[i]);
				}
				for (int i = 0; i < 4; i++)
				{
					x[i] = xd[i] + x0;
					y[i] = yd[i] + y0;
					z[i] = zd[i];
				}
				plane_draw(x, y, z, 300 * PI_F, 0, 0.8, 100, 200, 150, 0.8, 50); 
			}
		}
	}
}
void CGraphicsLily::lily_stamen_draw(int au, int bv, float cx1, float cy1, float cx, float cy, float cz, float dx, float dy)
{
	float uu[4], vv[4], x[5], y[5], z[5], xd[5], yd[5], zd[5], a, b, c;
	float du = 0.01, dv = 0.01;
	float cc = rand() % 5;
	for (float u = 0.0f; u <= 1.0f; u = u + du)
	{
		for (float v = 0.0f; v <= 1.0f; v = v + dv)
		{
			uu[0] = u;
			uu[3] = u;
			vv[0] = v;
			vv[1] = v;
			uu[1] = u + du;
			uu[2] = u + du;
			vv[2] = v + dv;
			vv[3] = v + dv;
			for (int i = 0; i < 4; i++)
			{
				cylinder(au, bv, uu[i], vv[i], x[i], y[i], z[i]);
			}
			n_vector(x, y, z, a, b, c);
			for (int i = 0; i < 4; i++)
			{
				x[i] = x[i] + cc * sin(vv[i] * PI);
				z[i] = z[i] + cc * sin(vv[i] * PI);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_x(cx1, x[i], y[i], z[i], xd[i], yd[i], zd[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_y(cy1, xd[i], yd[i], zd[i], x[i], y[i], z[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_x(cx, x[i], y[i], z[i], xd[i], yd[i], zd[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_y(cy, xd[i], yd[i], zd[i], x[i], y[i], z[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_z(cz, x[i], y[i], z[i], xd[i], yd[i], zd[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				x[i] = xd[i] + dx;
				y[i] = dy - yd[i];
				z[i] = zd[i];
			}
			plane_draw(x, y, z, 80 * PI_F, 0, 0.8, 100, 200, 150, 0.8, 50);
		}
	}

	int x0 = x[0];
	int y0 = y[0];
	du = 0.3;
	dv = 0.3;
	for (float u = -0.5f * PI; u <= 0.5f * PI; u = u + du)
	{
		for (float v = 0.0f; v <= 2.0f * PI; v = v + dv)
		{
			uu[0] = u;
			uu[3] = u;
			vv[0] = v;
			vv[1] = v;
			uu[1] = u + du;
			uu[2] = u + du;
			vv[2] = v + dv;
			vv[3] = v + dv;
			for (int i = 0; i < 4; i++)
			{
				ellipsoid(0, 0, 0, 2, 2, 15, uu[i], vv[i], x[i], y[i], z[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_x(cx1, x[i], y[i], z[i], xd[i], yd[i], zd[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_y(cy1, xd[i], yd[i], zd[i], x[i], y[i], z[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_x(cx, x[i], y[i], z[i], xd[i], yd[i], zd[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_y(cy, xd[i], yd[i], zd[i], x[i], y[i], z[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_z(cz, x[i], y[i], z[i], xd[i], yd[i], zd[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				x[i] = xd[i] + x0;
				y[i] = yd[i] + y0;
				z[i] = zd[i];
			}
			plane_draw(x, y, z, 0 * PI_F, 0, 0.8, 100, 200, 150, 0.8, 50);
		}
	}
}

void CGraphicsLily::lily_petal_draw(int au, int bv, float cx1, float cy1, float cx, float cy, float cz, float dx, float dy)
{
	float uu[4], vv[4], x[5], y[5], z[5], xd[5], yd[5], zd[5], a, b, c;
	float du = 0.01, dv = 0.01;
	for (float u = -0.5; u <= 0.5; u = u + du)
	{
		for (float v = 0.0; v <= 1.0; v = v + dv)
		{
			uu[0] = u;
			uu[3] = u;
			vv[0] = v;
			vv[1] = v;
			uu[1] = u + du;
			uu[2] = u + du;
			vv[2] = v + dv;
			vv[3] = v + dv;
			for (int i = 0; i < 4; i++)
			{
				lily_deform_xy(au, bv, uu[i], vv[i], x[i], y[i], z[i]);
			}
			
			n_vector(x, y, z, a, b, c);

			for (int i = 0; i < 4; i++)
			{
				float x0 = x[i], y0 = y[i];
				x[i] = x[i] + bh(uu[i], vv[i], au, bv, x0, y0) * a;
				y[i] = y[i] + bh(uu[i], vv[i], au, bv, x0, y0) * b;
				z[i] = z[i] + bh(uu[i], vv[i], au, bv, x0, y0) * c;
			}

			for (int i = 0; i < 4; i++)
			{
				revolve_x(cx1, x[i], y[i], z[i], xd[i], yd[i], zd[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_y(cy1, xd[i], yd[i], zd[i], x[i], y[i], z[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_x(cx, x[i], y[i], z[i], xd[i], yd[i], zd[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_y(cy, xd[i], yd[i], zd[i], x[i], y[i], z[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_z(cz, x[i], y[i], z[i], xd[i], yd[i], zd[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				x[i] = xd[i] + dx;
				y[i] = dy - yd[i];
				z[i] = zd[i];
			}
			float I, S = 0.5;
			I = 60 + 500 * fabs(u) + 200 * v;
			if (v < 0.3 && u > -0.2 && u < 0.2)
			{
				if (rand() % 5 == 3)
				{
					I = 20;
					S = 0.8;
				}
				else if (v < 0.3 && u > -0.3 && u < 0.3)
				{
					if (rand() % 20 ==3)
					{
						I = 20;
						S = 0.8; 
					}
				}
				else if (v < 0.4 && u > -0.4 && u < 0.4)
				{
					if (rand() % 30 == 10)
					{
						I = 20;
						S = 0.8;
					}
				}
			}
			plane_draw(x, y, z, 340 * PI_F, I, S, 100, 200, 150, 1, 50);
		}
	}
}


void CGraphicsLily::executeTask()
{
	CImg<unsigned char> palette(P_WIDTH, P_HEIGHT, 1, 3, 0);
	CImgDisplay window(palette, "Lily");
	srand((unsigned int) time(0));
	for (int w = 0; w < P_WIDTH; w++)
	{
		for (int h = 0; h < P_HEIGHT; h++)
		{
			zuff[w][h] = -MAXINT;
		}
	}
	memset(colors, 0, P_WIDTH * P_HEIGHT * 3 * sizeof(unsigned char));
	
	lily_petal_draw(35, 90, 90*PI_F, 30*PI_F, 60*PI_F, 0, 0, 220, 165);
	lily_petal_draw(35, 90, 90*PI_F, 150*PI_F, 60*PI_F, 0, 0, 210, 150);
	lily_petal_draw(35, 90, 90*PI_F, 270*PI_F, 60*PI_F, 0, 0, 180, 160);
	lily_petal_draw(35, 90, 85*PI_F, 90*PI_F, 60*PI_F, 0, 0, 210, 140);
	lily_petal_draw(35, 90, 85*PI_F, 210*PI_F, 60*PI_F, 0, 0, 175, 140);
	lily_petal_draw(35, 90, 85*PI_F, 330*PI_F, 60*PI_F, 0, 0, 190, 160);

	lily_pistil_draw(1, 70, 60*PI_F, 0, 0, 195, 170);

	lily_stamen_draw(1, 50, 30*PI_F, 20*PI_F, 60*PI_F, 0, 0, 195, 170);
	lily_stamen_draw(1, 50, 30*PI_F, 80*PI_F, 60*PI_F, 0, 0, 195, 170);
	lily_stamen_draw(1, 50, 30*PI_F, 140*PI_F, 60*PI_F, 0, 0, 195, 170);
	lily_stamen_draw(1, 50, 30*PI_F, 200*PI_F, 60*PI_F, 0, 0, 195, 170);
	lily_stamen_draw(1, 50, 30*PI_F, 260*PI_F, 60*PI_F, 0, 0, 195, 170);
	lily_stamen_draw(1, 50, 30*PI_F, 320*PI_F, 60*PI_F, 0, 0, 195, 170);
	
	

	/**Î÷¹Ï**/

	float uu[4], vv[4], du = 0.01, dv = 0.01, a, b, c;
	float x[5], y[5], z[5], xd[5], yd[5], zd[5];
	for (float u = -0.5 * PI; u <= 0.5 * PI; u = u + du)
	{
		for (float v = 0.0f; v <= 2*PI; v = v + dv)
		{
			uu[0] = u - 0.001;
			vv[0] = v - 0.001;
			uu[1] = u + du + 0.001;
			vv[1] = v - 0.001;
			uu[2] = u + du + 0.001;
			vv[2] = v + dv + 0.001;
			uu[3] = u - 0.001;
			vv[3] = v + dv + 0.001;
			for (int i = 0; i < 4; i++)
			{
				ellipsoid(0, 0, 0, 80, 80, 100, uu[i], vv[i], x[i], y[i], z[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_x(50*PI_F, x[i], y[i], z[i], xd[i], yd[i], zd[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				revolve_z(20*PI_F, xd[i], yd[i], zd[i], x[i], y[i], z[i]);
			}
			for (int i = 0; i < 4; i++)
			{
				x[i] = x[i] + 500;
				y[i] = 180 - y[i];
				z[i] = z[i];
			}
			float S = 0.8 * fabs(sin(5*v) + 0.15*sin(30*u));
			if (S <=0.4)
			{
				S = 0.4;
			}
			else
			{
				S = 0.8;
			}
			plane_draw(x, y, z, 110*PI_F, 200,S, 100, 200, 150, 0.7, 50);
		}
	}

	/****/

	for (int i = 0; i < P_WIDTH; ++i)
	{
		for (int j = 0; j < P_HEIGHT; ++j)
		{
			if (zuff[i][j] > -30000)
			{
				unsigned char thiscolor[3] = {colors[i][j][0], colors[i][j][1], colors[i][j][2]};
				palette.draw_point(i, j, thiscolor);
			}
		}
	}

	palette.display(window);
	while (! window.is_closed() && !window.is_keyESC())
	{

	}
}
