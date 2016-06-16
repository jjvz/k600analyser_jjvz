#ifndef HAGARSORT_h
#define HAGARSORT_h 1

/* Header file for the 'HAGAR' sort - channel mapping needs to be defined somewhere else... probably the Parameters.c file */

#include <TCutG.h>
#include <vector>
#include <TFile.h>
#include <TTree.h>
#include <vector>
#include <TROOT.h>
#include <cmath>
#include "multiTDC.h"

void   HagarSort(float *ADC_import, int ntdc, int *TDC_channel_import, float *TDC_value_import, GammaData *gammy);
double HagarEnergyCalc(int Channel, double ADCValue);
bool   HagarADCTDCChannelCheck(int ADCChannel, int TDCChannel);
//int    HagarDetHitNumber(int ADCChannel);
//bool   HagarTDCTest(int TDCChannel);
//int    HagarTDCIdentifyDetector(int TDCChannel);

#endif

