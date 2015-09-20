function y = arrowmatvec2(d,a,x)
if (length(d) ~= length(a)), error ('size mismatch'); end
A = [diag(d(1:end-1).^2+a(1:end-1).^2),(d(1:end-1) + d(4)) .* a(1:end-1)];
r
A = A + tril(A',-1); % make symmetric
y = A * x;
