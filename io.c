#include <stdio.h>
#include <stdlib.h>
#include "io.h"

int load_samples(const char* filename, WaveformSample** samples)
{
FILE* file = fopen(filename, "r");

if (file == NULL)
{
printf("Error: Could not open file.\n");
return 0;
}

char line[256];
int count = 0;

// Skip header line
fgets(line, sizeof(line), file);

// Count data rows
while (fgets(line, sizeof(line), file))
{
count++;
}

*samples = (WaveformSample*)malloc(count * sizeof(WaveformSample));

if (*samples == NULL)
{
printf("Memory allocation failed.\n");
fclose(file);
return 0;
}

// Go back to beginning of file
rewind(file);

// Skip header line again
fgets(line, sizeof(line), file);

int i = 0;

while (fgets(line, sizeof(line), file))
{
sscanf(line, "%lf,%lf,%lf,%lf,%lf,%lf,%lf,%lf",
&((*samples)[i].timestamp),
&((*samples)[i].phase_A_voltage),
&((*samples)[i].phase_B_voltage),
&((*samples)[i].phase_C_voltage),
&((*samples)[i].line_current),
&((*samples)[i].frequency),
&((*samples)[i].power_factor),
&((*samples)[i].thd_percent));

i++;
}

fclose(file);

return count;
}
void write_results(
const char* filename,
double rms_A, double rms_B, double rms_C,
double vpp_A, double vpp_B, double vpp_C,
double dc_A, double dc_B, double dc_C,
int clip_A, int clip_B, int clip_C,
int comp_A, int comp_B, int comp_C
)
{
FILE* file = fopen(filename, "w");

if (file == NULL)
{
printf("Error: Could not create results file.\n");
return;
}

fprintf(file, "Power Quality Waveform Analysis Results\n");
fprintf(file, "*******************************\n\n");

fprintf(file, "RMS Voltage:\n");
fprintf(file, "Phase A: %.2f V\n", rms_A);
fprintf(file, "Phase B: %.2f V\n", rms_B);
fprintf(file, "Phase C: %.2f V\n\n", rms_C);
fprintf(file, "*******************************\n\n");
fprintf(file, "RMS Compliance:\n");
fprintf(file, "Phase A: %s\n", comp_A ? "COMPLIANT" : "NOT COMPLIANT");
fprintf(file, "Phase B: %s\n", comp_B ? "COMPLIANT" : "NOT COMPLIANT");
fprintf(file, "Phase C: %s\n\n", comp_C ? "COMPLIANT" : "NOT COMPLIANT");
fprintf(file, "*******************************\n\n");
fprintf(file, "Peak-to-Peak Voltage:\n");
fprintf(file, "Phase A: %.2f V\n", vpp_A);
fprintf(file, "Phase B: %.2f V\n", vpp_B);
fprintf(file, "Phase C: %.2f V\n\n", vpp_C);
fprintf(file, "*******************************\n\n");
fprintf(file, "DC Offset:\n");
fprintf(file, "Phase A: %.6f V\n", dc_A);
fprintf(file, "Phase B: %.6f V\n", dc_B);
fprintf(file, "Phase C: %.6f V\n\n", dc_C);

fprintf(file, "Clipping Detection:\n");
fprintf(file, "Phase A clipped samples: %d\n", clip_A);
fprintf(file, "Phase B clipped samples: %d\n", clip_B);
fprintf(file, "Phase C clipped samples: %d\n", clip_C);
fprintf(file, "Total clipped samples: %d\n", clip_A + clip_B + clip_C);

fclose(file);
}