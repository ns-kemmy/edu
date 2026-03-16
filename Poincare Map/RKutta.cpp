#include "RKutta.h"
#define _USE_MATH_DEFINES
#include<cmath>

RKutta::RKutta(double E, int N, double dt, void(*rhs)(double*, double*, double)) : E(E), N(N), h(dt)
{
	y0 = new double[N]; //начальные условия
	y1 = new double[N]; //решение
	dy = new double[N]; //правая часть уравнения dU/dx=f(x, U(x))
	dd = new double[N];
	RHS = rhs;
	isSetInit = false;
}

void RKutta::setinit(double* In)
{
	for (int i = 0; i < N; i++)
		y0[i] = In[i]; //начальные условия из массива
	y0[2]= sqrt(2. * E - y0[3] * y0[3] - (y0[0] * y0[0] + y0[1] * y0[1]) - 2. * y0[0] * y0[0] * y0[1] + 2. * y0[1] * y0[1] * y0[1] / 3.);
	isSetInit = true;
}

void RKutta::Step()
{
	if (isSetInit == false) return;
	RHS(y0, dy, h);
	for (int i = 0; i < N; i++)
	{
		dd[i] = dy[i];
		y1[i] = y0[i] + 0.5 * h * dy[i];
	}
	RHS(y1, dy, h);
	for (int i = 0; i < N; i++)
	{
		dd[i] += 2 * dy[i];
		y1[i] = y0[i] + 0.5 * h * dy[i];
	}
	RHS(y1, dy, h);
	for (int i = 0; i < N; i++)
	{
		dd[i] += 2 * dy[i];
		y1[i] = y0[i] + h * dy[i];
	}
	RHS(y1, dy, h);
	for (int i = 0; i < N; i++)
	{
		dd[i] += dy[i];
		y1[i] = y0[i] + h * dd[i] / 6;
		y0[i] = y1[i];
	}

}

RKutta::~RKutta()
{
	delete[]y0;
	delete[]y1;
	delete[]dy;
	delete[]dd;
}