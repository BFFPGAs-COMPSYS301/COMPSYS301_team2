%% Import data
% Assumes each CSV has frequency in column 1, magnitude in column 2, no header row.
% If there IS a header row, add 'NumHeaderLines', 1 to readmatrix, or use readtable instead.

dataOff = readmatrix('19_08_offline.csv');
dataOn  = readmatrix('19_08_online.csv');

timeOFF = dataOff(:,1);
voltOFF  = dataOff(:,2);
freqOff = dataOff(:,3);
magOff  = dataOff(:,4);

timeON  = dataOn(:,1);
voltON   = dataOn(:,2);
freqOn  = dataOn(:,3);
magOn   = dataOn(:,4);


%% Plot off line vs on line
figure;
plot(timeOFF, voltOFF, 'b-', 'LineWidth', 1.2); hold on;
plot(timeON, voltON, 'r-', 'LineWidth', 1.2);
xlabel('Time (ms)');
ylabel('Voltage (V)');
title('Voltage vs Time: Off Line vs On Line');
legend('Off Line', 'On Line');
grid on;

%% Plot off line vs on line
figure;
plot(freqOff, magOff, 'b-', 'LineWidth', 1.2); hold on;
plot(freqOn, magOn, 'r-', 'LineWidth', 1.2);
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title('Frequency vs Magnitude: Off Line vs On Line');
legend('Off Line', 'On Line');
grid on;