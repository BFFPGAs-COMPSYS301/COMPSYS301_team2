%% Import data
% Assumes each CSV has frequency in column 1, magnitude in column 2, no header row.
% If there IS a header row, add 'NumHeaderLines', 1 to readmatrix, or use readtable instead.

dataOff = readmatrix('d_lo_33k.csv');
dataOn  = readmatrix('w_lo_33k.csv');



freqOff = dataOff(:,3);
magOff  = dataOff(:,4);

freqOn  = dataOn(:,3);
magOn   = dataOn(:,4);

%% Plot lights off vs lights on
figure;
plot(freqOff, magOff, 'b-', 'LineWidth', 1.2); hold on;
plot(freqOn, magOn, 'r-', 'LineWidth', 1.2);
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title('Frequency vs Magnitude: Off Line vs On Line');
legend('Off Line', 'On Line');
grid on;

%% Compute difference (Lights On - Lights Off)
% Only valid directly if freqOff and freqOn are identical (same length, same frequency points).
if isequal(freqOff, freqOn)
    magDiff = magOn - magOff;
    freqDiff = freqOff;
else
    % If frequency vectors differ, interpolate onto a common frequency axis
    freqDiff = freqOff; % or choose a common grid, e.g. union of both ranges
    magOnInterp = interp1(freqOn, magOn, freqDiff, 'linear', 'extrap');
    magDiff = magOnInterp - magOff;
end

%% Plot the difference
figure;
plot(freqDiff, magDiff, 'k-', 'LineWidth', 1.2);
xlabel('Frequency (Hz)');
ylabel('Magnitude Difference (On - Off)');
title('Difference in Magnitude: Lights On minus Lights Off');
grid on;
yline(0, '--'); % reference line at zero difference


%% Import data
% Assumes each CSV has frequency in column 1, magnitude in column 2, no header row.
% If there IS a header row, add 'NumHeaderLines', 1 to readmatrix, or use readtable instead.

timeOFF = dataOff(:,1);
voltOFF  = dataOff(:,2);

timeON  = dataOn(:,1);
voltON   = dataOn(:,2);

%% Plot lights off vs lights on
figure;
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

v_filt = lowpass(x,150,fs);

v_filt = highpass(v_filt,110,fs);

figure;
plot(timeON, v_filt);
xlabel('Time (ms)');
ylabel('Voltage (V)');
title('Voltage Filtered vs Time');
grid on;

% figure;
% plot(v_filt_freq, );
% xlabel('Time (ms)');
% ylabel('Voltage (V)');
% title('Voltage Filtered vs Time');
% grid on;