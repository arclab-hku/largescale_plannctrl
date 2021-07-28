close all;
% clear all;

% parameters
freq = 50;
h = 1/freq;

% load
load plannctrl_posi.txt;
load plannctrl_velo.txt;

load plannctrl_posid.txt;
load plannctrl_velod.txt;

wayps = [0 0 4;
100 0 4;
0 0 4];
% wayps = [500 0 4;
% 200 50 4;
% 500 100 4;
% 0 2 3;
% 0 2 2;
% 100 2 3;
% 100 2 2;
% 0 4 4;
% 0 0 4];

% variables
p = plannctrl_posi;
v = plannctrl_velo;

p_d = plannctrl_posid;
v_d = plannctrl_velod;

steps = size(p,1);
end_time = (steps-1)/freq;
time = 0:h:end_time;

%%

newcolors = [
    135,206,235;      %light blue
    219,112,147;        % red
    154,205,50;        % light green
    0,0,205;      % dark blue
    139,0,0;        % dark red
    85,107,47;      % dark green
    ];
newcolors = newcolors/255;
colororder(newcolors);

%% plot states

figure(1);
y = 2;
x = 1;

subplot(y,x,1);
plot(time,p);
hold on;
grid on;
plot(time,p_d,'--');
legend ('x','y','z','x_d','y_d','z_d');

subplot(y,x,2);
plot(time,v);
hold on;
grid on;
plot(time,v_d,'--');
legend ('vx','vy','vz','vx_d','vy_d','vz_d');

% subplot(y,x,2);
% plot(time,euler);
% hold on;
% grid on;
% legend ('\phi','\theta','\psi');
% 
% subplot(y,x,4);
% plot(time,rate);
% hold on;
% grid on;
% legend ('p','q','r');

%% plot in 3d

figure(2);

x = p(:,1);
y = p(:,2);
z = p(:,3);

x_d = p_d(:,1);
y_d = p_d(:,2);
z_d = p_d(:,3);

px = wayps(:,1);
py = wayps(:,2);
pz = wayps(:,3);

plot3(x,y,z);
hold on;
grid on;
plot3(x_d,y_d,z_d);
plot3(px,py,pz,'*r');
legend ('traj','desire traj','waypointd');
xlabel('x');
ylabel('y');
zlabel('z');

