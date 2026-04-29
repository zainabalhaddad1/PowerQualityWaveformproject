#pragma once
#ifndef IO_H
#define IO_H

#include "waveform.h"

int load_samples(const char* filename, WaveformSample** samples);
void write_results(
const char* filename,
double rms_A, double rms_B, double rms_C,
double vpp_A, double vpp_B, double vpp_C,
double dc_A, double dc_B, double dc_C,
int clip_A, int clip_B, int clip_C,
int comp_A, int comp_B, int comp_C
);
#endif