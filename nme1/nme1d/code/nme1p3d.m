res = zeros(1,5);
tt = zeros(3,5);
scale = 2 .^(2:6);
for i = 1:5
    n = 2^(i+1);
    A = rand(n);
    B = rand(n);
    x = rand(n^2,1);
    for t = 1:3
        tic
        y = kron(A,B) * x;
        tt(t, i) = toc;
    end
    res(i) = min(tt(:,i)); 
end

semilogy(scale, res);
xlabel('n');
ylabel('time');