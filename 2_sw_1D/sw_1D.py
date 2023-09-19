# Create a 1D shallow water solver

import numpy as np
import matplotlib.pyplot as plt

# settings and initial conditions
nx = 100
dt = 0.001
nt = 10
T = dt*nt
k=1
c=2.5
g=10
H = 100
sgH = np.sqrt(g*H)

# solve the 1D SW equations nonlinear:
# u_t = -u*u_x -g grad(h)
# h_t = -d/dx(hu)
# linear:
# u_t = - g h_x
# h_t = -H d/dx(u)
# u_tt = -g grad(h_t) = gH u_xx
# solution
# u(t,x) =  c/2*sin(k*(x - sqrt(gH)*t)) + c/2*sin(k*(x + sqrt(gH)*t))
# h(t,x) = -(c/2*cos(k*(x - sqrt(gH)*t)) + c/2*cos(k*(x + sqrt(gH)*t))) * sqrt(gH)/g
# u(t=0,x) = c*sin(kx)
# h(t=0,x) = c*cos(kx) * sqrt(gH)/g

x = np.linspace(0,2*np.pi*(nx-1)/nx,nx)
dx = x[1]-x[0]
unew = np.zeros(nx)
hnew = np.zeros(nx)
u = np.zeros(nx)
h = np.zeros(nx)
unew = np.zeros(nx)
RHSu = np.zeros(nx)
RHSh = np.zeros(nx)

# initial condition
u0 = c*np.sin(k*x[:])
h0 = -c*np.cos(k*x[:]) * np.sqrt(H/g)
unew[:] = u0[:]
hnew[:] = h0[:]
tnew = 0.0

# time stepping
for i in range(nt):
  u[:] = unew[:]
  h[:] = hnew[:]
  told = tnew
  tnew = told + dt

  # u_t = - g h_x
  j=0
  RHSu[j] = -g*(h[j+1] - h[nx-1])/(2*dx)
  for j in range(1,nx-1):
    RHSu[j] = -g*(h[j+1] - h[j-1])/(2*dx)
  j=nx-1
  RHSu[j] = -g*(h[0] - h[j-1])/(2*dx)
  unew[:] = u[:] + dt * RHSu[:]
  print('unew',unew)

  # h_t = -H d/dx(u)
  j=0
  RHSh[j] = -H*(u[j+1] - u[nx-1])/(2*dx)
  for j in range(1,nx-1):
    RHSh[j] = -H*(u[j+1] - u[j-1])/(2*dx)
  j=nx-1
  RHSh[j] = -H*(u[0] - u[j-1])/(2*dx)
  hnew[:] = h[:] + dt * RHSh[:]

# finalize and check plot
# u(t,x) =  c/2*sin(k*(x - sqrt(gH)*t)) + c/2*sin(k*(x + sqrt(gH)*t))
# h(t,x) = -(c/2*cos(k*(x - sqrt(gH)*t)) + c/2*cos(k*(x + sqrt(gH)*t))) * sqrt(gH)/g
usol = c/2*np.sin(k*(x[:] - np.sqrt(g*H))) + c/2*np.sin(k*(x + np.sqrt(g*H)*tnew))
hsol =-c*np.cos(k*x[:])*np.sin(np.sqrt(g*H)*k*tnew) * np.sqrt(H/g)
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
