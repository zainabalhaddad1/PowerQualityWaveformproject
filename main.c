#include <stdio.h>
#include <stdlib.h>
#include "waveform.h"
#include "io.h"

int main(void)
{
WaveformSample* samples = NULL;
int count;

count = load_samples("x.csv", &samples);

printf("Number of samples loaded: %d\n\n", count);

if (count > 0)
{
double rms_A = compute_rms(samples, count, 'A');
double rms_B = compute_rms(samples, count, 'B');
double rms_C = compute_rms(samples, count, 'C');


printf("RMS Phase A: %.2f V\n", rms_A);
printf("RMS Phase B: %.2f V\n", rms_B);
printf("RMS Phase C: %.2f V\n", rms_C);

printf("\nCompliance Phase A: %s\n", check_compliance(rms_A) ? "COMPLIANT" : "NOT COMPLIANT");
printf("Compliance Phase B: %s\n", check_compliance(rms_B) ? "COMPLIANT" : "NOT COMPLIANT");
printf("Compliance Phase C: %s\n", check_compliance(rms_C) ? "COMPLIANT" : "NOT COMPLIANT");

double vpp_A = compute_peak_to_peak(samples, count, 'A');
double vpp_B = compute_peak_to_peak(samples, count, 'B');
double vpp_C = compute_peak_to_peak(samples, count, 'C');

printf("\nPeak-to-peak Phase A: %.2f V\n", vpp_A);
printf("Peak-to-peak Phase B: %.2f V\n", vpp_B);
printf("Peak-to-peak Phase C: %.2f V\n", vpp_C);

double dc_A = compute_dc_offset(samples, count, 'A');
double dc_B = compute_dc_offset(samples, count, 'B');
double dc_C = compute_dc_offset(samples, count, 'C');

printf("\nDC offset Phase A: %.6f V\n", dc_A);
printf("DC offset Phase B: %.6f V\n", dc_B);
printf("DC offset Phase C: %.6f V\n", dc_C);

int clip_A = count_clipped_samples(samples, count, 'A');
int clip_B = count_clipped_samples(samples, count, 'B');
int clip_C = count_clipped_samples(samples, count, 'C');

printf("\nClipped samples Phase A: %d\n", clip_A);
printf("Clipped samples Phase B: %d\n", clip_B);
printf("Clipped samples Phase C: %d\n", clip_C);

int total_clip = count_total_clipped(samples, count);
printf("Total clipped samples: %d\n", total_clip);

int comp_A = check_compliance(rms_A);
int comp_B = check_compliance(rms_B);
int comp_C = check_compliance(rms_C);

write_results(
"results.txt",
rms_A, rms_B, rms_C,
vpp_A, vpp_B, vpp_C,
dc_A, dc_B, dc_C,
clip_A, clip_B, clip_C,
comp_A, comp_B, comp_C
);

printf("\nResults written to results.txt\n");
}

free(samples);

return 0;
}