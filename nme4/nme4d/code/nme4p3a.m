%f = @(x)(x * exp(x) - 1);
f = @(x)(x - (1/exp(x)));
x0 = 1;
x = x0;

x_star = steff_it(f, 1);

it_count = 8;

errs = zeros(it_count, 1);
ps = zeros(it_count, 1);

for i = 1:it_count
    x_next = steff_step(f, x);
    errs(i) = abs(x_star - x_next);
    x = x_next;
end
for i = 2:it_count - 1
    ps(i) = (log(errs(i+1)) - log(errs(i))) / (log(errs(i)) - log(errs(i-1)));
end
ps = ps(2:it_count - 1);
