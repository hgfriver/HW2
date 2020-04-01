#include "mbed.h"

Serial pc( USBTX, USBRX );
AnalogIn Ain(A0);
AnalogOut Aout(DAC0_OUT);


float previousMillis = 0;        
float interval = 1; //if 2 ,means 2 seconds.

float currentMillis = t.read();

float seconds;

DigitalIn  Switch(SW3);
DigitalOut redLED(LED1);

DigitalOut greenLED(LED2);
int counter = 0;
int sine_state = 0;
int freq = 0;
BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);

Timer t;

char table[11] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x0};

float ADCdata[512];


float sine;

int sample = 512;

int ledState = 0;


int n1 = 0;
int n2 = 0; 
int n3 = 0;

int main(){

    /*t.start();

    
        currentMillis = t.read();

        if(currentMillis - previousMillis > interval) { //go into every 2 seconds
            previousMillis = currentMillis; 
            
            freq = counter; //update every 1 second !!!!!!!!!!
            
            counter = 0;
        }*/

    for(int i = 0; i < sample; i++){
        ADCdata[i] = Ain;
        
        if((ADCdata[i] > 0.3) && (sine_state == 0)){
            freq++;
            sine_state = 1;
        }
        
        if(ADCdata[i] < 0.2)
            sine_state = 0;
        
        wait(1./sample);
    }  






    for(int j = 0; j < sample; j++){
        pc.printf("%1.3f\r\n", ADCdata[j]);
        wait(0.01);
    }
        

        n1 = freq / 100;
        n2 = freq / 10 % 10;
        n3 = freq % 10;
        

    while(1){
        redLED = 1;
        greenLED = 0;

        while(Switch == 0){
            redLED = 0;
            greenLED = 1;

            display = table[n1];
            wait(1);
            display = table[n2];
            wait(1);
            display = table[n3] + 128;
            wait(1);
            display = table[10];
        }

        /*seconds = t.read();
        sine =  0.5+0.5*sin(2*3.14159*freq*seconds);
        Aout = sine;*/

        for(float k = 0; k < 2; k += 0.05 ){
          Aout = 0.5 + 0.5 * sin(k * 2 * 3.14159 * freq);
          wait(0.001);
        }


    }
}