#include<iostream>
#include<fstream>
#include<cmath>
#include<stdlib.h>
#include<ctime>
#include<tbb/blocked_range.h>
#include<tbb/parallel_reduce.h>
#include<tbb/parallel_for.h>
#include<tbb/parallel_scan.h>
#include<tbb/blocked_range2d.h>
#include<tbb/tick_count.h>

using namespace std;
using namespace tbb;


double Linear_f(double x, double y);
double f(double x, double y);
void MC_interpolation_functor(int n, double N, double*x, double*y);
void Linear_interpolation_functor(int n, double N, double*x, double*y);
//double monte(int n, double**MC, double N, double*x, double*y);
void MC_interpolation_lambda(int n, double N, double*x, double*y);
void Linear_interpolation_lambda(int n, double N, double*x, double*y);

class Linear
{
private:
    int n;
    double**z;
    double*x;
    double*y;
public:
    Linear(int n, double**z, double *x, double* y)
    {
        this->z=z;
        this->x=x;
        this->y=y;
        this->n=n;
    }
    void operator()(const blocked_range<int>&r) const
    {
        for (int i=r.begin(); i<r.end(); i++)
        //for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            //for (int j=r.begin(); j<r.end(); j++)
            {
        z[i][j]=Linear_f(x[i],y[j]);
                //file << z[i][j] << endl;
            }
        }
    }
};

class Carlo
{
private:
    int n, eps;
    double**MC;
    double*x;
    double*y;
public:
    Carlo(int n, double**MC, double *x, double* y, int eps)
    {
        this->eps=eps;
        this->MC=MC;
        this->x=x;
        this->y=y;
        this->n=n;
    }
    void operator()(const blocked_range<int>&r) const
    {
        double e0, e1;
        //ofstream file1("MC_tbb_functor.txt");
        for (int i=r.begin(); i<r.end(); i++)
        //for (int i=0; i<n; i++)
        {
            for (int j=0; j<n; j++)
            {
                for (int k=0; k<eps; k++)
                //for (int k=r.begin(); k<r.end(); k++)
                {
                    e0=(1.*rand()/RAND_MAX<x[i])?1:0;
                    e1=(1.*rand()/RAND_MAX<y[j])?1:0;
                    //s+=f(e0,e1);
                    MC[i][j]+=f(e0,e1)/eps;
                }
            }
            }
    }
};


int main()
{
    double N=1000; //Определяем число узлов сетки по координатам x и y = 26
    int n=26;
    double h=1.0/(n-1);
    double*x=new double[n];
    double*y=new double[n];
    for (int i=0; i<n; i++)
    {
        x[i]=h*i;
        y[i]=h*i;
    }
    tick_count t0 = tick_count::now();
    Linear_interpolation_functor(n,N, x, y);
    tick_count t1 = tick_count::now();
    cout << "Linear_interpolation_functor time: " << (t1-t0).seconds() << endl;
    
    t0 = tick_count::now();
    Linear_interpolation_lambda(n, N, x , y);
    t1 = tick_count::now();
    cout << "Linear_interpolation_lambda time: " << (t1-t0).seconds() << endl;
    
    t0 = tick_count::now();
    MC_interpolation_functor(n, N, x , y);
    t1 = tick_count::now();
    cout << "MC_interpolation_functor time: " << (t1-t0).seconds() << endl;
    
    t0 = tick_count::now();
    MC_interpolation_lambda(n, N, x , y);
    t1= tick_count::now();
    cout << "MC_interpolation_lambda time: " << (t1-t0).seconds() << endl;
        //monte(n,MC,N,x,y);
    delete[]x; delete[]y;
    return 0;
}

void Linear_interpolation_functor(int n, double N, double*x, double*y)
{
    ofstream file2("Linear_tbb_functor.txt");
    double**z=new double*[n];
    for (int i=0; i<n; i++) z[i]=new double[n];
    Linear L(n,z,x,y);
    parallel_for(blocked_range<int>(0,n), L);
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            file2 << x[i] << "\t" << y[j] << "\t" << z[i][j] << endl;
        }
        file2 << endl;
    }
    file2.close();
    for (int i=0; i<n; i++) delete[]z[i];
    delete[]z;
}

double Linear_f(double x, double y)
{
    double z;
    z=(1-x)*(1-y)*f(0,0)+x*(1-y)*f(1,0)+(1-x)*y*f(0,1)+x*y*f(1,1);
    return z;
}

void MC_interpolation_functor(int n, double N, double*x, double*y)
{
    srand(time(NULL));
    ofstream file1("MC_tbb_functor.txt");
    double**Monte_Carlo=new double*[n];
    for (int i=0; i<n; i++)
    {
        Monte_Carlo[i]=new double[n];
        for (int j=0; j<n; j++)
        {
            Monte_Carlo[i][j]=0;
        }
    }
    Carlo C(n, Monte_Carlo, x,y,N);
    parallel_for(blocked_range<int>(0,n), C);
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            file1 << x[i] << "\t" << y[j] << "\t" << Monte_Carlo[i][j] << endl;
        }
        file1 << endl;
    }
    file1.close();
    for (int i=0; i<n; i++) delete[]Monte_Carlo[i];
    delete[]Monte_Carlo;
    
}

double f(double x, double y) //Определение интерполируемой функции в узлах квадрата
{
    return (-1+x+y)*(-1+x+y);
}


void MC_interpolation_lambda(int n, double N, double*x, double*y)
{
    srand(time(NULL));
    ofstream file4("MC_tbb_lambda.txt");
    double**MC=new double*[n];
    for (int i=0; i<n; i++)
    {
        MC[i]=new double[n];
        for (int j=0; j<n; j++)
        {
            MC[i][j]=0;
        }
    }
    parallel_for(blocked_range<int>(0,n),
                 [&](const blocked_range<int>&r)
                 {
        double e0, e1;
        for (int i=r.begin(); i<r.end(); i++)
        {
            for (int j=0; j<n; j++)
            {
                for (int k=0; k<N; k++)
                {
                    e0=(1.*rand()/RAND_MAX<x[i])?1:0;
                    e1=(1.*rand()/RAND_MAX<y[j])?1:0;
                    MC[i][j]+=f(e0,e1)/N;
                }
            }
            }
    });
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            file4 << x[i] << "\t" << y[j] << "\t" << MC[i][j] << endl;
        }
        file4 << endl;
    }
    file4.close();
    for (int i=0; i<n; i++) delete[]MC[i]; delete[]MC;
}


void Linear_interpolation_lambda(int n, double N, double*x, double*y)
{
    ofstream file3("Linear_tbb_lambda.txt");
    double**z=new double*[n];
    for (int i=0; i<n; i++) z[i]=new double[n];
    parallel_for(blocked_range<int>(0,n),
                 [&](const blocked_range<int>&r){
        for (int i=r.begin(); i<r.end(); i++)
        {
            for (int j=0; j<n; j++)
            {
        z[i][j]=Linear_f(x[i],y[j]);
            }
        }
        
    }
                 );
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            file3 << x[i] << "\t" << y[j] << "\t" << z[i][j] << endl;
        }
        file3 << endl;
    }
    file3.close();
    for (int i=0; i<n; i++) delete[]z[i];
    delete[]z;
}

