#include <stdio.h>
#include <wiringPi.h>
#include <bcm2835.h>
 

#define PIN_A_I 	9//GPIO3
#define PIN_B_O 	7//GPIO4

#define PIN_A_O 	4//GPIO23
#define PIN_B_I 	5//GPIO24
/************************************************************
PIN_A_O rise --> PIN_B_I high --> 
PIN_B_O rise --> PIN_A_I high --> 
PIN_A_O fall  -->
*/

#define CNT_MAX 1000*100
uint32_t cnt;
uint8_t b_flag;

void pin_A_I_interrupt_cb(void){
	//delay(100);
	if(digitalRead(PIN_A_I)){ 
		// printf("pin A rising.\n");
		digitalWrite(PIN_A_O, LOW);
	}else{
		// printf("pin A falling.\n");
		digitalWrite(PIN_A_O, HIGH);
	}
	cnt++;
}

void pin_B_I_interrupt_cb(void){
	//delay(100);
	if(digitalRead(PIN_B_I)){ 
		// printf("pin B rising.\n");
		digitalWrite(PIN_B_O, HIGH);
		// b_flag = 1;
	}else{
		// printf("pin B falling.\n");
		digitalWrite(PIN_B_O, LOW);
		// b_flag = 2;
	}   
	cnt++;
}

int  main(int argc,  char* argv[]) {	
   // printf ("__FUNCTION__ = %s\n", __FUNCTION__);
   
   wiringPiSetup();
	cnt = 0;
	b_flag = 0;
   
   pinMode(PIN_A_I, INPUT);
   pinMode(PIN_A_O, OUTPUT);
   pinMode(PIN_B_I, INPUT);
   pinMode(PIN_B_O, OUTPUT);
   digitalWrite(PIN_A_O, LOW);	
   digitalWrite(PIN_B_O, LOW);	
   
   wiringPiISR (PIN_A_I, INT_EDGE_BOTH , pin_A_I_interrupt_cb);
   wiringPiISR (PIN_B_I, INT_EDGE_BOTH , pin_B_I_interrupt_cb);
   
	//delay(100);
   digitalWrite(PIN_A_O, HIGH);	
	
	//delay(100);
   
   while(cnt<CNT_MAX);
   
   return 0;
}


//void pinMode (int pin, int mode) ;
//void digitalWrite (int pin, int value) ;
//int digitalRead (int pin) ;