%% Import data
% Assumes each CSV has frequency in column 1, magnitude in column 2, no header row.
% If there IS a header row, add 'NumHeaderLines', 1 to readmatrix, or use readtable instead.

dataOff = readmatrix('off_new.csv');
dataOn  = readmatrix('whitenew.csv');

freqOff = dataOff(:,1);
magOff  = dataOff(:,2);

freqOn  = dataOn(:,1);
magOn   = dataOn(:,2);

%% Plot lights off vs lights on
figure;
plot(freqOff, magOff, 'b-', 'LineWidth', 1.2); hold on;
plot(freqOn, magOn, 'r-', 'LineWidth', 1.2);
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title('Frequency vs Magnitude: Lights Off vs Lights On');
legend('Lights Off', 'Lights On');
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