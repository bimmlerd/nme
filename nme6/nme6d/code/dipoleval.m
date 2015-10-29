function dp = dipoleval( t, y, x )
% Returns the row vector (p'(x)) for a p interpolating (t,y)
y_prime = zeros(length(x), length(y));
y = repmat(y, length(x), 1);
for i = 1:length(y)
    for k=i-1:-1:1
        div = t(i)-t(k);
        thing = (y(:, k+1)-y(:, k));
        thing2 = x-t(i);
        y_prime(:, k) = y_prime(:, k+1) + (thing + thing2' .* (y_prime(:, k+1) - y_prime(:, k)))/div;
        y(:, k) = y(:, k+1)+(thing.*thing2')/div;
    end
end
dp = y_prime(:, 1);
end