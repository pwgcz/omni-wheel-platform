/*
 * silnik.h
 *
 *  Created on: 25.08.2019
 *      Author: Pawe³
 */







#ifndef SILNIK_H_
#define SILNIK_H_

#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx_it.h"
#include <stdbool.h>
#include <math.h>


#define P				52  	 //wzmocnienie regulatora PID
#define d_part			7412
#define Td				0.01	 //czas wyprzedzenia
#define Ti				15		//czas zdwojenia




typedef struct parametry_silnika {
	int32_t aktualna_predkosc;
	int32_t predkosc_zadana;
	int32_t impulsy_abs;
	int32_t impulsy;
	int32_t wypelnienie;


} parametry_silnika;
parametry_silnika silnik_a;
parametry_silnika silnik_b;
parametry_silnika silnik_c;

enum kierunek {
	left,
	right
};


void Kierunek_Silnika(struct parametry_silnika *silnik, uint8_t kierunek);
void Licznik_Impulsow(struct parametry_silnika *silnik);
void Obliczanie_Predkosci_Akt(struct parametry_silnika *silnik);
void Regulator_PID(struct parametry_silnika *silnik);


#endif
