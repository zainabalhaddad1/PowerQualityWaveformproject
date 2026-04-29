#ifndef WAVEFORM_H
#define WAVEFORM_H

typedef struct
{
    double timestamp;
    double phase_A_voltage;
    double phase_B_voltage;
    double phase_C_voltage;
    double line_current;
    double frequency;
    double power_factor;
    double thd_percent;

} WaveformSample;

void print_sample(WaveformSample sample);
double compute_rms(WaveformSample* samples, int count, char phase);
double compute_peak_to_peak(WaveformSample* samples, int count, char phase);
double compute_dc_offset(WaveformSample* samples, int count, char phase);
int count_clipped_samples(WaveformSample* samples, int count, char phase);
int check_compliance(double rms);
int count_total_clipped(WaveformSample* samples, int count);
#endif