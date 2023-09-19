# Create a one-dimensional simple ODE solver

import numpy as np
import matplotlib.pyplot as plt

# settings and initial conditions
nx = 100
dt = 0.01
nt = 1000
T = dt*nt
k=1
c=2.5
nu=0.02

# solve the heat equation
# u_t = nu u_xx
# solution
# u(t=0,x) = c*sin(kx)
# u(t,x) = c*sin(k*x)*exp(-nu*k^2*t)

x = np.linspace(0,2*np.pi*(nx-1)/nx,nx)
dx = x[1]-x[0]
unew = np.zeros(nx)
u = np.zeros(nx)
RHS = np.zeros(nx)

# initial condition
u0 = c*np.sin(k*x[:])
unew[:] = c*np.sin(k*x[:])
tnew = 0.0

# time stepping
for i in range(nt):
  u[:] = unew[:]
  told = tnew
  tnew = told + dt
  for j in range(nx-1):
    RHS[j] = nu * (u[j-1]-2*u[j]+u[j+1])/dx**2
  j=nx-1
  RHS[j] = nu * (u[j-1]-2*u[j]+u[0])/dx**2

  unew[:] = u[:] + dt * RHS[:]


# finalize and check plot
usol = c*np.sin(k*x[:])*np.exp(-nu*k**2*tnew)
plt.plot(x,u0,'k')
plt.plot(x,unew,'b')
plt.plot(x,usol,'r--')
plt.grid()
plt.show()
print('tnew',tnew)
print('unew')
print(unew)
print('usol')
print(usol)
print(x)
