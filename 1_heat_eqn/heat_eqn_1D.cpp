#include<iostream>
#include <math.h>       /* sin */
using namespace std;

int main()
{
// settings and initial conditions
int nx = 100;
double dt = 0.01;
int nt = 1000;
double T = dt*nt;
int k=1;
double c=2.5;
double nu=0.02;
double Lx = 2.0*3.14159265359
;
double dx = Lx/nx;
double dx2r = 1.0/dx/dx;
double told = 0.0;
double tnew = 0.0;

/* # solve the heat equation
# u_t = nu u_xx
# solution
# u(t=0,x) = c*sin(kx)
# u(t,x) = c*sin(k*x)*exp(-nu*k^2*t) */

double x[100];
double u[100];
double u0[100];
double unew[100];
double usol[100];
double RHS[100];

for (int j=0; j<nx; j++) {
  x[j] = j*dx;
  u0[j] = c*sin(k*x[j]);
  unew[j] = u0[j];
}

// time stepping
for (int i=0; i<nt; i++) {
  told = tnew;
  tnew = told + dt;

  for (int j=0; j<nx; j++) {
    u[j] = unew[j];
  }

  int j=0;
  // cout<< "u"<<u[nx-1]<<" "<<2*u[j]<<" "<<u[j+1]<<" "<<nu<<" "<<dx2r<<" "<<(u[nx-1]-2*u[j]+u[j+1])<<" "<<endl;
  RHS[j] = nu * (u[nx-1]-2*u[j]+u[j+1])*dx2r;
  for (int j=1; j<nx-1; j++) {
    RHS[j] = nu * (u[j-1]-2*u[j]+u[j+1])*dx2r;
  }
  j=nx-1;
  RHS[j] = nu * (u[j-1]-2*u[j]+u[0])*dx2r;

  for (int j=0; j<nx; j++) {
    unew[j] = u[j] + dt * RHS[j];
  }
}

cout << "RHS"<<endl;
for (int j=0; j<nx; j++) {
  cout << RHS[j] << " ";
}
cout <<endl;

cout << "unew"<<endl;
for (int j=0; j<nx; j++) {
  cout << unew[j] << " ";
}
cout <<endl;

cout << "usol"<<endl;
for (int j=0; j<nx; j++) {
  usol[j] = u0[j]*exp(-nu*k*k*tnew);
  cout << usol[j] << " ";
}
cout <<endl;

// # finalize and check plot
// usol = c*np.sin(k*x[:])*np.exp(-nu*k**2*tnew)
// plt.plot(x,u0,'k')
// plt.plot(x,unew,'b')
// plt.plot(x,usol,'r--')
// plt.grid()
// plt.show()

//   cout<<"dt="<<config.dt<<endl;
//   cout<<domain.ssh[0][0]<<endl;

  return 0;
}
