% Interpolationsfunktion
f = @(x) 1./(x.^2+1);

% betrachtetes Intervall
a=-5;
b=5;

% Auswertungspunkte
xx = a:0.001:b;
yy = f(xx);

% Anzahl ?quidistanter St?tzstellen
n=5:-1:1;

hold all;
for i=n
    x = linspace(a,b,2^i);
    y = f(x);
    ys = spline(x,y,xx);
    
    figure(i);
    hold on;
    plot(x,y,'o')
    plot(xx,ys,'--');
    plot(xx,yy,'r');
    hold off;
end

