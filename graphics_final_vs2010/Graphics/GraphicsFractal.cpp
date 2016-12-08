#include "GraphicsFractal.h"
#include <math.h>


CGraphicsFractal::CGraphicsFractal(void)
{
}


CGraphicsFractal::~CGraphicsFractal(void)
{
}

void ifs(double *m, double *p, int len, int scale, int dx, int dy, CImg<unsigned char> *palette)
{
	int n=100000,t;
	double a,b,c,d,e,f,newx,newy,x=0,y=0;
	unsigned char green[3] = {0, 255, 0};
	while(n>0)
	{
		int c_p = p[0] * 100;
		t=rand()%101;
		if (t <= c_p)
		{
			a=m[0];b=m[1];c=m[2];d=m[3];e=m[4];f=m[5];
		}
		else
		{
			for (int i = 1; i < len; i++)
			{
				c_p += p[i] * 100;
				if (t <= c_p)
				{
					a=m[i*6];b=m[i*6+1];c=m[i*6+2];d=m[i*6+3];e=m[i*6+4];f=m[i*6+5];
					break;
				}
			}
		}
		newx=a*x+b*y+e;
		newy=c*x+d*y+f;
		x = newx;
		y = newy;
		palette->draw_point(int(dx+scale*x),int(dy-scale*y),green);
		n--;
	}
	
}

void CGraphicsFractal::executeTask()
{
	CImg<unsigned char> palette(WIDTH, HEIGHT, 1, 3, 0);
	CImgDisplay window(palette, "Mandelbrot");
	is_first_iter = true;
	re_left = RE_LEFT;
	im_bottom = IM_BOTTOM;
	N_total = N_T;
	frac_data = NULL;

	RECT rect;
	rect.left = 0;
	rect.right = WIDTH - 1;
	rect.top = 0;
	rect.bottom = HEIGHT - 1;
	size.cx = rect.right - rect.left + 1;
	size.cy = rect.bottom - rect.top + 1;

	calcData(size, rect);
	refresh(&palette, &window);

	int btnstate = 0;
	int x0, x1, y0, y1;

	while (!window.is_closed() && !window.is_keyESC())
	{
		if (window.button() & 1)
		{
			if (btnstate == 0)
			{
				btnstate = 1;
				x0 = window.mouse_x();
				y0 = window.mouse_y();
			}
			else
			{
				x1 = window.mouse_x();
				y1 = window.mouse_y();
			}
		}
		else
		{
			if (btnstate == 1)
			{
				btnstate = 0;
				x1 = window.mouse_x();
				y1 = window.mouse_y();
				if ((x1 - x0) < 10 || (y1 - y0) < 10)
				{
					continue;
				}
				RECT newRect;
				newRect.left = (x1 < x0) ? x1 : x0;
				newRect.right = newRect.left + ((abs(x1 - x0) <= abs(y1 - y0) ? abs(x1 - x0) : abs(y1 - y0)));
				newRect.top = (y1 < y0) ? y1 : y0;
				newRect.bottom = newRect.top + ((abs(x1 - x0) <= abs(y1 - y0) ? abs(x1 - x0) : abs(y1 - y0)));
				calcData(size, newRect);
				refresh(&palette, &window);
			}
		}
	}

	CImg<unsigned char> palette1(WIDTH, HEIGHT, 1, 3, 0);
	CImgDisplay window1(palette1, "Tree");
	srand((UINT)time(NULL));
	double m1[36] = {0.06,0,0,0.6,0,0,0.04,0,0,-0.5,0,1,0.46,-0.34,0.32,0.38,0,0.6,0.48,0.17,-0.15,0.42,0,1,0.43,-0.26,0.27,0.48,0,1,0.42,0.35,-0.36,0.31,0,0.8};
	double p1[6] = {0.1,0.1,0.1,0.23,0.23,0.24};
	ifs(m1, p1, 6, 150, 250, 400, &palette1);
	
	double m2[] ={0,0,0,0.16,0,0,0.85,0.04,-0.04,0.85,0,1.6,0.2,-0.25,0.23,0.22,0,1.6,-0.15,0.28,0.26,0.24,0,0.44};
	double p2[] = {0.01, 0.85, 0.07, 0.07};
	ifs(m2, p2, 4, 30, 500, 400, &palette1);
	
	double m3[] = {0.05,0,0,0.4,0,0,0.5,0,0,0.5,0,0.35,0.3536,0.3536,-0.3536,0.3536,0,0.15,0.433,-0.25,0.25,0.433,0,0.15};
	double p3[] = {0.0259,0.3247,0.3247,0.3247};
	ifs(m3, p3, 4, 450, 250, 780, &palette1);

	double m4[] = {0.001,0,0,0.25,0,0,0.8488,0.04344,-0.04449,0.8289,0,1,0.1,0.2165,-0.1732,0.125,0,0.6,0.1,-0.2165,0.1732,0.125,0,0.6};
	double p4[] = {0.01, 0.87, 0.06, 0.06};
	ifs(m4, p4, 4, 50, 500, 780, &palette1);

	palette1.display(window1);
	while (!window1.is_closed() && !window1.is_keyESC())
	{

	}
}

void CGraphicsFractal::calcData( SIZE rectSize, RECT rect )
{
	if (is_first_iter)
	{
		re_left = RE_LEFT;
		im_bottom = IM_BOTTOM;

		step_x = (1-re_left)/(rectSize.cx - 1);
		step_y = (1.5 - im_bottom)/(rectSize.cy - 1);

		N_total = N_T;
		is_first_iter = false;
	}
	else
	{
		re_left = re_left + step_x * rect.left;
		im_bottom = im_bottom + step_y * (rectSize.cy - rect.bottom);

		step_x = step_x * (rect.right - rect.left) / rectSize.cx;
		step_y = step_y * (rect.bottom - rect.top) / rectSize.cy;

		N_total = (int) (50*floor(log10(1/step_x)));
	}

	if (frac_data != NULL)
	{
		delete[] frac_data;
		frac_data = NULL;
	}
	frac_data = new int[rectSize.cx * rectSize.cy];

	double C_x, C_y;
	double x, y;
	for (int j = 0; j < rectSize.cy; j ++)
	{
		for (int i = 0; i < rectSize.cx; i++)
		{
			x = 0;
			y = 0;

			C_x = re_left + i * step_x;
			C_y = im_bottom + j * step_y;

			for (int k = 0; k < N_total; k++)
			{
				double x_temp = x * x - y * y + C_x;
				y = 2 * x * y + C_y;
				x = x_temp;
				if ((x * x + y * y) > 4)
				{
					frac_data[i + j * rectSize.cx] = k + 1;
					break;
				}
				if (k == N_total - 1 && (x * x + y * y) <= 4)
				{
					frac_data[i + j * rectSize.cx] = k + 2;
				}
			}
		}
	}
}

void CGraphicsFractal::refresh( CImg<unsigned char> *palette, CImgDisplay *window )
{
	for (int j = 0; j < size.cy; j++)
	{
		for (int i = 0; i < size.cx; i++)
		{
			unsigned char color[3] = {0, 0, 0};
			if (frac_data[i + j * size.cx] <= N_total/2)
			{

				color[0] = frac_data[i + j * size.cx] * 4 + 50;
				color[1] = frac_data[i + j * size.cx] * 4 + 50;
				color[2] = frac_data[i + j * size.cx] * 3 + 100;
			}
			else if (frac_data[i + j * size.cx] > N_total/2 && frac_data[i + j * size.cx] < N_total)
			{
				color[0] = frac_data[i + j * size.cx] + 3 * 50;
				color[1] = 0;
				color[2] = frac_data[i + j * size.cx] + 3 * 50;
			}
			palette->draw_point(i, size.cy - j - 1, color);
		}
	}
	palette->display(*window);
}
