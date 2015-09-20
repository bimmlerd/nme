res = nme1p2a';
scale = 10 .^ (-20:0);
loglog(scale, abs(res(1,:) - cos(1.2)))
hold on;
loglog(scale, abs(res(2,:) - cos(1.2)))
legend('f2','f1','Location','east')
xlabel('h')
ylabel('Error')