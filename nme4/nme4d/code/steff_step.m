function x_next = steff_step(f, x)
    fx = f(x);
    gx =(f(x + fx) - fx)/fx;
    x_next = x - (fx/gx);
end