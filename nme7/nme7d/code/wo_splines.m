% Interpolationsfunktion
%f = @(x) 1./x;
f = @(x) 1./(x.^2+1);

% betrachtetes Intervall
a=-5;
b=5;

% Auswertungspunkte f?r den Plot
xx = a:0.001:b;
yy = f(xx);

% Anzahl ?quidistanter St?tzstellen
n=5:-1:1;

hold all;
for i=n
    x = linspace(a,b,2^i);
    y = f(x);
    c = polyfit(x,y,2^i-1);
    yp = polyval(c,xx);
    
    figure(i);
    hold on;
    plot(x,y,'o')
    plot(xx,yp,'--');
    plot(xx,yy,'r');
    hold off;
end

