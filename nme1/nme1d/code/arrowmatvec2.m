function y = arrowmatvec2(d,a,x)
if (length(d) ~= length(a)), error ('size mismatch'); end
a(end) = 0;
yy = d .* x + x(end) * a;
yy(end) = yy(end) + dot(a(1:end-1),x(1:end-1));
y = d .* yy + yy(end) * a;
y(end) = y(end) + dot(a(1:end-1),yy(1:end-1));
