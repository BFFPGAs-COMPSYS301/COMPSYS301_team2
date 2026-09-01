%% Import Data
dataOff = readmatrix('og_offline_final.csv', 'NumHeaderLines', 1);
dataOn  = readmatrix('og_online_lo.csv', 'NumHeaderLines', 1);

% Clean missing values if present
dataOff = rmmissing(dataOff);
dataOn  = rmmissing(dataOn);

% Shift time vectors to start at 0 seconds
t_off_s = dataOff(:,1) - dataOff(1,1);
t_on_s  = dataOn(:,1) - dataOn(1,1);

% Convert time to milliseconds and extract voltages
timeOFF = t_off_s * 1000;
voltOFF = dataOff(:,2);
timeON  = t_on_s * 1000;
voltON  = dataOn(:,2);

%% Figure 3: Time Domain (Voltage vs Time)
figure(3);
plot(timeOFF, voltOFF, 'b-', 'LineWidth', 1.2); hold on;
plot(timeON, voltON, 'r--', 'LineWidth', 1.2); % Dashed line prevents solid overlap
xlabel('Time (ms)');
ylabel('Voltage (V)');
title('Voltage vs Time: Off Line vs On Line');
legend('Off Line', 'On Line');
grid on;

%% FFT Analysis (Frequency Spectrum)
% Sampling Intervals (s) and Sampling Frequencies (Hz)
dt_off = mean(diff(t_off_s)); 
fs_off = 1 / dt_off; 

dt_on = mean(diff(t_on_s)); 
fs_on = 1 / dt_on; 

% Number of samples for each signal
N_off = length(voltOFF);
N_on  = length(voltON);

% Compute FFT for Off Line
fft_off = fft(voltOFF);
magOFF  = abs(fft_off / N_off);
magOFF  = magOFF(1:floor(N_off/2)+1);
magOFF(2:end-1) = 2 * magOFF(2:end-1);
freqOFF = (0:floor(N_off/2)) * (fs_off / N_off);

% Compute FFT for On Line
fft_on = fft(voltON);
magON  = abs(fft_on / N_on);
magON  = magON(1:floor(N_on/2)+1);
magON(2:end-1) = 2 * magON(2:end-1);
freqON = (0:floor(N_on/2)) * (fs_on / N_on);

%% Figure 4: Frequency Domain (Magnitude Voltage vs Frequency)
figure(4);
semilogy(freqOFF, magOFF, 'b-', 'LineWidth', 1.2); hold on;
semilogy(freqON, magON, 'r--', 'LineWidth', 1.5); % Log-scale + dashed red line
xlabel('Frequency (Hz)');
ylabel('Magnitude Voltage (V)');
title('Magnitude Voltage vs Frequency Spectrum');
legend('Off Line', 'On Line');
xlim([0 1000]); 
grid on;