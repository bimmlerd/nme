scale = 2 .^ (5:12);
c = length(scale);
tries = 3;
res = zeros(c, 2);
tt = zeros(2,tries);
for i = 1:c
    n = scale(i);
    a = rand(n,1);
    d = rand(n,1);
    x = rand(n,1);
    for t = 1:tries
        tic
        y = arrowmatvec(d,a,x);
        tt(1,t) = toc;
        tic
        yy = arrowmatvec2(d,a,x);
        tt(2,t) = toc;
        if (y ~= yy)
            error ('mismatch');
        end
    end
    res(i,1) = min(tt(1,:));
    res(i,2) = min(tt(2,:));
end

loglog(scale, res(:,1));
hold on;
loglog(scale, res(:,2));
xlabel('n');
ylabel('time');
legend('arrowmatvec', 'arrowmatvec2', 'Location', 'east');