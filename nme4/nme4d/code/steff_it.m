function x_star = steff_it(f, x0, tol)
    x = 0;
    x_new = x0;
    if (nargin < 3), tol = 1E-6; end
    while (abs(x_new-x) > tol*x)
        x = x_new;
        x_new = steff_step(f, x);
    end
    
    x_star = x_new;
end