f = @(x) 1./(1e-4 + x.^2);

q = quad24(f,-1,1,1e-3);

[q;200*atan(100)]