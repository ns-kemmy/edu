#include<iostream>
#include<fstream>
#include<cmath>
#include<stdlib.h>
#include<ctime>
#include<omp.h>

using namespace std;


double Linear_f(double x, double y);
double f(double x, double y);
void MC_interpolation_omp(int n, double N, double*x, double*y);
void Linear_interpolation_omp(int n, double N, double*x, double*y);

int main()
{
    double N=1000;
    //Определяем число узлов сетки по координатам x1 и x2
    int n=101;
    double h=1.0/(n-1);
    double*x=new double[n];
    double*y=new double[n];
    for (int i=0; i<n; i++)
    {
        x[i]=h*i;
        y[i]=h*i;
    }


    double start_time, end_time, tick;
    start_time=omp_get_wtime();
    Linear_interpolation_omp(n ,N, x, y);
    end_time=omp_get_wtime();
    tick=end_time-start_time;
    cout << "Linear interpolation omp time: " << tick << endl;

    start_time=omp_get_wtime();
    MC_interpolation_omp(n, N, x , y);
    end_time=omp_get_wtime();
    tick=end_time-start_time;
    cout << "MC interpolation omp time: " << tick << endl;
    delete[]x; delete[]y;
    return 0;

}

void Linear_interpolation_omp(int n, double N, double*x, double*y)
{
    ofstream file("Linear_omp.txt");
    double**z=new double*[n];
    for (int i=0; i<n; i++)
        z[i]=new double[n];
#pragma omp parallel for
    {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                z[i][j] = Linear_f(x[i], y[j]);
            }

        }
    }
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++)
    file << x[i] << "\t" << y[j] << "\t" << z[i][j] << endl;
    file.close();
    //удаление массивов
    for (int i=0; i<n; i++) delete[]z[i];
    delete[]z;
}

double Linear_f(double x, double y)
{
    double z;
    z=(1-x)*(1-y)*f(0,0)+x*(1-y)*f(1,0)+(1-x)*y*f(0,1)+x*y*f(1,1);
    return z;
}

void MC_interpolation_omp(int n, double N, double*x, double*y)
{
    ofstream file2("MC_omp.txt");
    srand(time(NULL));
    double s;
    double*e=new double[2];
    double**Monte_Carlo=new double*[n];
    for (int i=0; i<n; i++)
        Monte_Carlo[i]=new double[n];
#pragma omp parallel for //num_threads(1)//количество потоков для максимальной эффектинвости работы алгоритма 3 потока
    {
//#pragma omp for
        {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    for (int k = 0; k < N; k++) {
                        e[0] = (1. * rand() / RAND_MAX < x[i]) ? 1 : 0;
                        e[1] = (1. * rand() / RAND_MAX < y[j]) ? 1 : 0;
                        Monte_Carlo[i][j] += f(e[0], e[1]) / N;
                    }
                }
            }
        }
    }
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++) file2 << x[i] << "\t" << y[j] << "\t" << Monte_Carlo[i][j] << endl;
    file2.close();

    //удаление массивов
    for (int i=0; i<n; i++) delete[]Monte_Carlo[i];
    delete[]Monte_Carlo; delete[]e;
}

double f(double x, double y) //Определение интерполируемой функции в узлах квадрата
{
    return (-1+x+y)*(-1+x+y);
}
