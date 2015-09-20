function res = nme1p2a
    x = 1.2;
    res = zeros(21,2);
    for i = -20:0
        h = 10^i;
        res(i+21,:) = [f2(x,h)/h,f1(x,h)/h];
    end
    
function y = f1(x0,h)
y = sin(x0 + h) - sin(x0);
    
function y = f2(x0, h)
y = 2 * cos(x0 + (h/2)) * sin(h/2);