#ifndef PZEM_H
#define PZEM_H
#include <string.h>
#include <Arduino.h>
#include <PZEM004Tv30.h>
void readPZEM(PZEM004Tv30 &pzem, String name);
void turnOnPiority(PZEM004Tv30 &pzem1, PZEM004Tv30 &pzem2, PZEM004Tv30 &pzem3, int batteryPercentage);
void shutDownPiority(PZEM004Tv30 &pzem1, PZEM004Tv30 &pzem2, PZEM004Tv30 &pzem3, int batteryPercentage);
#endif