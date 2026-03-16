#include<iostream>
#include<fstream>
#include<cmath>
#include<stdlib.h>
#include<ctime>
#include<tbb/tick_count.h>

using namespace std;
using namespace tbb;


double Linear_f(double x, double y);
double f(double x, double y);
void MC_interpolation(int n1, int n2, double N, double*x, double*y);
void Linear_interpolation(int n1, int n2, double N, double*x, double*y);

int main()
{
    double N=1000;
    //Определяем число узлов сетки по координатам x1 и x2
    int n1=26,n2=26;
    double h1=1.0/(n1-1);
    double h2=1.0/(n2-1);
    double*x=new double[n1];
    double*y=new double[n2];
    for (int i=0; i<n1; i++)
    {
        x[i]=h1*i;
    }
    for (int j=0; j<n2; j++)
    {
        y[j]=h2*j;
    }
    
    
    tick_count t0=tick_count::now();
    Linear_interpolation(n1,n2,N, x, y);
    tick_count t1=tick_count::now();
    cout << "Linear interpolation time: " << (t1-t0).seconds() << endl;
    
    /*clock_t t1, t2;
    t1 = clock();
    Linear_interpolation(n1,n2,N, x, y);
    t2 = clock();
    cout << "Linear_interpolation time: " << (t2-t1)/CLOCKS_PER_SEC << endl;
     
    t1 = clock();
    MC_interpolation(n1, n2, N, x , y);
    t2 = clock();
    cout << "MonteCarlo_interpolation time: " << (t2-t1)/CLOCKS_PER_SEC << endl;
   */
    
    t0=tick_count::now();
    MC_interpolation(n1, n2, N, x , y);
    t1=tick_count::now();
    cout << "Monte Carlo interpolation time: " << (t1-t0).seconds() << endl;
    delete[]x; delete[]y;
    return 0;
}

void Linear_interpolation(int n1, int n2, double N, double*x, double*y)
{
    ofstream file("Linear.txt");
    double**z=new double*[n1];
    for (int i=0; i<n1; i++)
        z[i]=new double[n2];
    for (int i=0; i<n1; i++)
    {
        for (int j=0; j<n2; j++)
        {
    z[i][j]=Linear_f(x[i],y[j]);
            file << x[i] << "\t" << y[j] << "\t" << z[i][j] << endl;
        }
        file << endl;
    }
    file.close();
    for (int i=0; i<n1; i++) delete[]z[i];
    delete[]z;
}

double Linear_f(double x, double y)
{
    double z;
    z=(1-x)*(1-y)*f(0,0)+x*(1-y)*f(1,0)+(1-x)*y*f(0,1)+x*y*f(1,1);
    return z;
}

void MC_interpolation(int n1, int n2, double N, double*x, double*y)
{
    ofstream file2("MC.txt");
    srand(time(NULL));
    double s;
    double*e=new double[2];
    double**Monte_Carlo=new double*[n1];
    for (int i=0; i<n1; i++)
        Monte_Carlo[i]=new double[n2];
    
    for (int i=0; i<n1; i++)
    {
        for (int j=0; j<n2; j++)
        {
            s=0;
            for (int k=0; k<N; k++)
            {
                e[0]=(1.*rand()/RAND_MAX<x[i])?1:0;
                e[1]=(1.*rand()/RAND_MAX<y[j])?1:0;
                s+=f(e[0],e[1]);
            }
            Monte_Carlo[i][j]=s/N;
            file2 << x[i] << "\t" << y[j] << "\t" << Monte_Carlo[i][j] << endl;
        }
        file2 << endl;
        }
    file2.close();
    for (int i=0; i<n1; i++) delete[]Monte_Carlo[i];
    delete[]Monte_Carlo; delete[]e;
}

double f(double x, double y)
{
    return (-1+x+y)*(-1+x+y);
}
