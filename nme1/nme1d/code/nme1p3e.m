tt = zeros(3,5);
tt2 = zeros(3,5);
res = zeros(1,5);
res2 = zeros(1,5);
scale = 2 .^(2:6);
for i = 1:5
    n = 2^(i+1);
    A = rand(n);
    B = rand(n);
    x = rand(n^2,1);
    for t = 1:3
        tic
        y = reshape( B * reshape(x,n,n) * A', n*n, 1 );
        tt(t, i) = toc;
        tic
        y = kron(A,B) * x;
        tt2(t, i) = toc;
    end
    res(i) = min(tt(:,i));
    res2(i) = min(tt2(:,i));
end

semilogy(scale, res);
hold on;
semilogy(scale, res2);
xlabel('n');
ylabel('time');
legend('reshape', 'kron', 'Location', 'east');