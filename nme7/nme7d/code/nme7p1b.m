function [ ] = nme7p1b( a, b )
s1=@(a,b,x)((x+1).^4 + a*(x-1).^4 + 1);
s2=@(a,b,x)(-x.^3 - 8*a*x + 1);
s3=@(a,b,x)(b * x.^3 + 8 * x.^2 + 11/3);

xs1 = linspace(-1,0,34);
xs2 = linspace(0,1,34); xs2 = xs2(1:end-1);
xs3 = linspace(1,2,34); xs3 = xs3(1:end-1);

xs = [xs1,xs2,xs3];
ys = [s1(a,b,xs1), s2(a,b,xs2), s3(a,b,xs3)];

plot(xs, ys)

end

