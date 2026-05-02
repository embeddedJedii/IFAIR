#ifndef PZEM_H
#define PZEM_H
#include <string.h>
#include <Arduino.h>
#include <PZEM004Tv30.h>
extern uint8_t percentage;
extern uint8_t lastPercentage;
void readPZEM(PZEM004Tv30 &pzem, String name);
void turnOnPiority( int batteryPercentage);
void shutDownPiority(PZEM004Tv30 &pzem1, PZEM004Tv30 &pzem2, PZEM004Tv30 &pzem3, float batteryPercentage);
void updateSystemStatus();
extern bool status_75;
extern bool status_45;
#endif