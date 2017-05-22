filename = 'Readings.csv';
M = csvread(filename);
x = M(:,1);
y = M(:,2);
title('Projectile Graph');
xlabel('X');
ylabel('Y');
plot (x,y,'--gs')