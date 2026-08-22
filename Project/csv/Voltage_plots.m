%% Import data
% Assumes each CSV has frequency in column 1, magnitude in column 2, no header row.
% If there IS a header row, add 'NumHeaderLines', 1 to readmatrix, or use readtable instead.

dataOff = readmatrix('off_line_volt.csv');
dataOn  = readmatrix('on_line_volt.csv');

timeOFF = dataOff(:,1);
voltOFF  = dataOff(:,2);

timeON  = dataOn(:,1);
voltON   = dataOn(:,2);

%% Plot lights off vs lights on
figure3;
plot(timeOFF, voltOFF, 'b-', 'LineWidth', 1.2); hold on;
plot(timeON, voltON, 'r-', 'LineWidth', 1.2);
xlabel('Time (ms)');
ylabel('Voltage (V)');
title('Voltage vs Time: Off Line vs On Line');
legend('Off Line', 'On Line');
grid on;

%% Filtering
fs = 1e3;
t = 1/fs;

x = voltON;

lowpass(x,150,fs)

highpass(x,110,fs);