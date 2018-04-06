#include <stdio.h>
#include <wiringPi.h>
#include <bcm2835.h>
 

#define PIN_A 9//GPIO3
#define PIN_B 7//GPIO4
// #define PIN_A 4//GPIO23
// #define PIN_B 5//GPIO24


void pin_A_interrupt_cb(void){
	if(digitalRead(PIN_A)){
		printf("pin A rising.\n");
	}else{
		printf("pin A falling.\n");
	}
}

void pin_B_interrupt_cb(void){
   
}

int  main(int argc,  char* argv[]) {	
   printf ("__FUNCTION__ = %s\n", __FUNCTION__);
   printf ("__PRETTY_FUNCTION__ = %s\n", __PRETTY_FUNCTION__);
   
   wiringPiSetup();
   
   pinMode(PIN_A, INPUT);
   pinMode(PIN_B, OUTPUT);
   
   wiringPiISR (PIN_A, INT_EDGE_BOTH , pin_A_interrupt_cb) ;
   
   delay (500) ;
   digitalWrite(PIN_B, HIGH);
   delay (500) ;
   digitalWrite(PIN_B, LOW);
   
   
   //while(1);
   
   return 0;
}


//void pinMode (int pin, int mode) ;
//void digitalWrite (int pin, int value) ;
//int digitalRead (int pin) ;