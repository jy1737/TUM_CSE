

function result = adams_moulton(t0, dt, tmax, initial, boundary, forcing)
% ADAMS_MOULTON uses an implicit Adams-Moulton scheme with the builtin sparse
% solver to integrate the PDE du/dt = L(u)+f, where L is the Laplacian. 
% This assumes a uniform rectangular mesh and Dirichlet boundary conditions.
% 
%   t0:        The starting time
%   dt:        The timestep size
%   tmax:      The stopping time
%   initial:   a (m+2)*(n+2) matrix containing initial conditions at each grid point
%   boundary:  a (m+2)*(n+2) sparse matrix containing Dirichlet boundary 
%              conditions at the edges of the grid.
%   forcing:   a (m+2*n+2) matrix containing the forcing term at each grid point
%
%
%   returns:   a struct containing a (m+2)*(n+2) matrix representing the 
%              solution (including boundary conditions) 


% Reshape initial condition matrix as vector
initial = initial(2:end-1, 2:end-1);
solution = reshape(initial', [numel(initial) 1]);

[ny,nx] = size(initial);
A = speye(ny*nx) - dt/2*laplacian(nx,ny);
B = speye(ny*nx) + dt/2*laplacian(nx,ny);
M = A\B;

iters = floor((tmax-t0)/dt);
solution = (M^iters) * solution;

solution_full = full(boundary);
solution_full(2:end-1,2:end-1) = reshape(solution, [nx ny]);

result.method = 'Adams-Moulton';
result.n = size(initial,1);
result.dt = dt;
result.t = tmax;
result.solution = solution_full;

lambdas = eigs(M,2);
result.eigMin = min(lambdas);
result.eigMax = max(lambdas);


