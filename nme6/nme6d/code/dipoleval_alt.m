function dp = dipoleval_alt( t, y, x)
degree = length(t) - 1;
a = polyfit(t,y,degree);
a = polyder(a);
dp = polyval(a, x);
end