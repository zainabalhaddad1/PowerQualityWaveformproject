#include <stdio.h>
#include "waveform.h"
#include <math.h>
void print_sample(WaveformSample sample)
{
printf("Timestamp: %.4f\n", sample.timestamp);
printf("Phase A voltage: %.2f V\n", sample.phase_A_voltage);
printf("Phase B voltage: %.2f V\n", sample.phase_B_voltage);
printf("Phase C voltage: %.2f V\n", sample.phase_C_voltage);
printf("Line current: %.2f A\n", sample.line_current);
printf("Frequency: %.2f Hz\n", sample.frequency);
printf("Power factor: %.2f\n", sample.power_factor);
printf("THD: %.2f %%\n", sample.thd_percent);
}
double compute_rms(WaveformSample* samples, int count, char phase)
{
double sum_square = 0.0;
double voltage = 0.0;

for (int i = 0; i < count; i++)
{
if (phase == 'A')
{
voltage = samples[i].phase_A_voltage;
}
else if (phase == 'B')
{
voltage = samples[i].phase_B_voltage;
}
else if (phase == 'C')
{
voltage = samples[i].phase_C_voltage;
}

sum_square += voltage * voltage;
}

return sqrt(sum_square / count);
}
double compute_peak_to_peak(WaveformSample* samples, int count, char phase)
{
double voltage = 0.0;
double max_voltage;
double min_voltage;

if (phase == 'A')
{
max_voltage = samples[0].phase_A_voltage;
min_voltage = samples[0].phase_A_voltage;
}
else if (phase == 'B')
{
max_voltage = samples[0].phase_B_voltage;
min_voltage = samples[0].phase_B_voltage;
}
else
{
max_voltage = samples[0].phase_C_voltage;
min_voltage = samples[0].phase_C_voltage;
}

for (int i = 0; i < count; i++)
{
if (phase == 'A')
{
voltage = samples[i].phase_A_voltage;
}
else if (phase == 'B')
{
voltage = samples[i].phase_B_voltage;
}
else if (phase == 'C')
{
voltage = samples[i].phase_C_voltage;
}

if (voltage > max_voltage)
{
max_voltage = voltage;
}

if (voltage < min_voltage)
{
min_voltage = voltage;
}
}

return max_voltage - min_voltage;
}
double compute_dc_offset(WaveformSample* samples, int count, char phase)
{
double sum = 0.0;
double voltage = 0.0;

for (int i = 0; i < count; i++)
{
if (phase == 'A')
{
voltage = samples[i].phase_A_voltage;
}
else if (phase == 'B')
{
voltage = samples[i].phase_B_voltage;
}
else if (phase == 'C')
{
voltage = samples[i].phase_C_voltage;
}

sum += voltage;
}

return sum / count;
}
int count_clipped_samples(WaveformSample* samples, int count, char phase)
{
int clipped_count = 0;
double voltage = 0.0;

for (int i = 0; i < count; i++)
{
if (phase == 'A')
{
voltage = samples[i].phase_A_voltage;
}
else if (phase == 'B')
{
voltage = samples[i].phase_B_voltage;
}
else if (phase == 'C')
{
voltage = samples[i].phase_C_voltage;
}

if (fabs(voltage) >= 324.9)
{
clipped_count++;
}
}

return clipped_count;
}
int check_compliance(double rms)
{
if (rms >= 207.0 && rms <= 253.0)
{
return 1;
}
else
{
return 0;
}
}
int count_total_clipped(WaveformSample* samples, int count)
{
int total = 0;

for (int i = 0; i < count; i++)
{
if (fabs(samples[i].phase_A_voltage) >= 324.9 ||
fabs(samples[i].phase_B_voltage) >= 324.9 ||
fabs(samples[i].phase_C_voltage) >= 324.9)
{
total++;
}
}

return total;
}