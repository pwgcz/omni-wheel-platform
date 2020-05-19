/*
 * silnik.c
 *
 *  Created on: 25.08.2019
 *      Author: Pawe³
 */

#include "silnik.h"
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){// Wywo³ywanie przerwañ inicjalizowanych licznikiem
	if(htim->Instance == TIM2){		//przerwanie wywo³ywane co 100us
		Licznik_Impulsow(&silnik_a);//Obliczanie liczby impusów z 3 silników
		Licznik_Impulsow(&silnik_b);
		Licznik_Impulsow(&silnik_c);


	}
	if(htim->Instance == TIM3){		//przerwanie wywo³ywane co 10ms
		Obliczanie_Predkosci_Akt(&silnik_a);// obliczanie prêdkoœci 3 silników
		Obliczanie_Predkosci_Akt(&silnik_b);
		Obliczanie_Predkosci_Akt(&silnik_c);

		Regulator_PID(&silnik_a);// dzia³anie regulatorów 3 silik
		Regulator_PID(&silnik_b);
		Regulator_PID(&silnik_c);
	}
}

void Kierunek_Silnika(struct parametry_silnika *silnik, uint8_t kierunek){
	uint32_t pin_state_1;				//metoda odpowiadajaca za kierunek obrotow silnika
	uint32_t pin_state_2;				//wpisuje odpowiedni stan w dwa piny sterownika
	if(kierunek == left){				//stan wysoki na pierwszym pinie AIN1 i niski na drugim AIN2 to obrot w prawo
		pin_state_1 = GPIO_PIN_RESET;	//stan niski na pierwszym pinie AIN1 i wysoki na drugim AIN2 to obrut w lewo
		pin_state_2 = GPIO_PIN_SET;
	} else {
		pin_state_1 = GPIO_PIN_SET;
		pin_state_2 = GPIO_PIN_RESET;
	}
	if(silnik == &silnik_a) {
			HAL_GPIO_WritePin(S1_PORT_IN1,S1_PIN_IN1,pin_state_1);
			HAL_GPIO_WritePin(S1_PORT_IN2,S1_PIN_IN2,pin_state_2);
		} else if(silnik == &silnik_b) {
			HAL_GPIO_WritePin(S2_PORT_IN1,S2_PIN_IN1,pin_state_1);
			HAL_GPIO_WritePin(S2_PORT_IN2,S2_PIN_IN2,pin_state_2);
		} else if(silnik == &silnik_c){
			HAL_GPIO_WritePin(S3_PORT_IN1,S3_PIN_IN1,pin_state_1);
			HAL_GPIO_WritePin(S3_PORT_IN2,S3_PIN_IN2,pin_state_2);
		}

}

void Licznik_Impulsow(struct parametry_silnika *silnik){
	uint32_t nowy_stan1;				//Licznik impusow dodaje lub odejmuje wartosci od zmiennej impulsy
	uint32_t stary_stan1;				//w zaleznosci od kierunkow obrotow silnika, sa one rozpoznawane za pomoca
	uint32_t nowy_stan2;				//2 kanalowego enkodera z sygnalem kwadraturowym ktory jeden jjest przesuniety
	uint32_t stary_stan2;				//o 90stopni , rozpoznaje 4 stany i na podstawie ich kolejnosci wykonuje obliczenia
	uint32_t nowy_stan3;				//metoda jest wykonywana w przerwaniu co 100us poniewa¿ rozdzielczosc nie pozwala
	uint32_t stary_stan3;				// na leprzy pomiar nawet przy dzialaniu ciaglym, oraz dzailanie w przerwaniu zmiejsza
										//moc obliczeniowa mikrokontrolera
	if(silnik == &silnik_a){
		if(HAL_GPIO_ReadPin(S1_PORT_EN1, S1_PIN_EN1)==1 && HAL_GPIO_ReadPin(S1_PORT_EN2, S1_PIN_EN2)==0){
				nowy_stan1 = 0;
			}
			else if(HAL_GPIO_ReadPin(S1_PORT_EN1, S1_PIN_EN1)==1 && HAL_GPIO_ReadPin(S1_PORT_EN2, S1_PIN_EN2)==1){
				nowy_stan1 = 1;
			}
			else if(HAL_GPIO_ReadPin(S1_PORT_EN1, S1_PIN_EN1)==0 && HAL_GPIO_ReadPin(S1_PORT_EN2, S1_PIN_EN2)==1){
					nowy_stan1=2;
				}
			else if(HAL_GPIO_ReadPin(S1_PORT_EN1, S1_PIN_EN1)==0 && HAL_GPIO_ReadPin(S1_PORT_EN2, S1_PIN_EN2)==0){
					nowy_stan1=3;
				}
			if(nowy_stan1 == 3 && stary_stan1 == 0){
				silnik_a.impulsy_abs--;
				silnik_a.impulsy--;
			}
			else if(nowy_stan1 == 0 && stary_stan1 == 3){
				silnik_a.impulsy_abs++;
				silnik_a.impulsy--;
			}
			else if(nowy_stan1 > stary_stan1){
				silnik_a.impulsy_abs++;
				silnik_a.impulsy--;
			}
			else if(nowy_stan1 < stary_stan1){
				silnik_a.impulsy_abs--;
				silnik_a.impulsy--;
			}
		stary_stan1 = nowy_stan1;
	}
	if(silnik == &silnik_b){
			if(HAL_GPIO_ReadPin(S2_PORT_EN1, S2_PIN_EN1)==1 && HAL_GPIO_ReadPin(S2_PORT_EN2, S2_PIN_EN2)==0){
					nowy_stan2 = 0;
				}
				else if(HAL_GPIO_ReadPin(S2_PORT_EN1, S2_PIN_EN1)==1 && HAL_GPIO_ReadPin(S2_PORT_EN2, S2_PIN_EN2)==1){
					nowy_stan2 = 1;
				}
				else if(HAL_GPIO_ReadPin(S2_PORT_EN1, S2_PIN_EN1)==0 && HAL_GPIO_ReadPin(S2_PORT_EN2, S2_PIN_EN2)==1){
						nowy_stan2 = 2;
					}
				else if(HAL_GPIO_ReadPin(S2_PORT_EN1, S2_PIN_EN1)==0 && HAL_GPIO_ReadPin(S2_PORT_EN2, S2_PIN_EN2)==0){
						nowy_stan2 = 3;
					}
				if(nowy_stan2 == 3 && stary_stan2 == 0){
					silnik_b.impulsy_abs--;
					silnik_b.impulsy--;
				}
				else if(nowy_stan2 == 0 && stary_stan2 == 3){
					silnik_b.impulsy_abs++;
					silnik_b.impulsy--;
				}
				else if(nowy_stan2 > stary_stan2){
					silnik_b.impulsy_abs++;
					silnik_b.impulsy--;
				}
				else if(nowy_stan2 < stary_stan2){
					silnik_b.impulsy_abs--;
					silnik_b.impulsy--;
				}
			stary_stan2 = nowy_stan2;
		}
	if(silnik == &silnik_c){
			if(HAL_GPIO_ReadPin(S3_PORT_EN1, S3_PIN_EN1)==1 && HAL_GPIO_ReadPin(S3_PORT_EN2, S3_PIN_EN2)==0){
					nowy_stan3 = 0;
				}
				else if(HAL_GPIO_ReadPin(S3_PORT_EN1, S3_PIN_EN1)==1 && HAL_GPIO_ReadPin(S3_PORT_EN2, S3_PIN_EN2)==1){
					nowy_stan3 = 1;
				}
				else if(HAL_GPIO_ReadPin(S3_PORT_EN1, S3_PIN_EN1)==0 && HAL_GPIO_ReadPin(S3_PORT_EN2, S3_PIN_EN2)==1){
						nowy_stan3 = 2;
					}
				else if(HAL_GPIO_ReadPin(S3_PORT_EN1, S3_PIN_EN1)==0 && HAL_GPIO_ReadPin(S3_PORT_EN2, S3_PIN_EN2)==0){
						nowy_stan3 = 3;
					}
				if(nowy_stan1 == 3 && stary_stan1 == 0){
					silnik_c.impulsy_abs--;
					silnik_c.impulsy--;
				}
				else if(nowy_stan3 == 0 && stary_stan3 == 3){
					silnik_c.impulsy_abs++;
					silnik_c.impulsy--;
				}
				else if(nowy_stan3 > stary_stan3){
					silnik_c.impulsy_abs++;
					silnik_c.impulsy--;
				}
				else if(nowy_stan3 < stary_stan3){
					silnik_c.impulsy_abs--;
					silnik_c.impulsy--;
				}
			stary_stan3 = nowy_stan3;
		}
}
void Obliczanie_Predkosci_Akt(struct parametry_silnika *silnik){

		silnik->aktualna_predkosc = silnik->impulsy;			//predkos jest obliczana bezwzglednie i dziala w przerwaniu 100ms
		if(silnik->impulsy < 0){								//przepisuje wartosc licznika impulsow do zmiennej predkoc po czym licznik impulsow
			silnik->aktualna_predkosc = -(silnik->impulsy);		// zostaje zerowany dzieki takiemu doborowi przerwan mozna obliczyc predkosc obrotowa silnikow
		}else{
			silnik->aktualna_predkosc = silnik->impulsy;
		}
		silnik->impulsy = 0;


}
void Regulator_PID(struct parametry_silnika *silnik){
	uint32_t e, e_last, I_count, regg_out, D, I;

		e = silnik -> predkosc_zadana - silnik -> aktualna_predkosc;
		if(silnik ->aktualna_predkosc  > 0){							//dzialanie calkujace zrelizowane jest za pomoca definicji
			I_count = I_count + e;										//calki, kolejne wartosci e sa do siebie sumowane
		}
		I = I_count*Ti;
		D = Td*(e-e_last)*d_part;										//rozniczkowanie jest rowniez wykonane z definicji
		regg_out =  P*e+I+D;											//wartosc regulacji  po dzialaniu algorymu PID
		e_last = e;
		if(regg_out > 10000){
			regg_out = 10000;
		}else if(regg_out <=0){
			regg_out = 0;
		}
		silnik ->wypelnienie = regg_out * 0.04;							// skalowanie wartosci z obliczeniowej na wartosc wypelnienia PWM
																		// ktora przyjmuje wartosci od 0 do 800(0%-100%), ograniczylem wartosc
																		//przyjmowana od 0 do 400 by zmiejszyc pobor pradu na silnik i zapobiec
}																		//przepaleniu sterownikow


