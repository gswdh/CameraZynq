#pragma once

#include <stdio.h>
#include <stdint.h>

void printBMCR(uint16_t reg);
void printBMSR(uint16_t reg);
void printPHYID1(uint16_t reg);
void printPHYID2(uint16_t reg);
void printANAR(uint16_t reg);
void printANLPAR(uint16_t reg);
void printANER(uint16_t reg);
void printANNPTR(uint16_t reg);
void printANNPRR(uint16_t reg);
void printINSR(uint16_t reg);