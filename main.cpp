#include "mbed.h" 
#include "DHT.h" 
#include "LED_Bar.h"
#include "TextLCD.h"

DHT sensor(D4, DHT11);
DigitalOut buzzer(D3);
DigitalOut led_green(LED_GREEN);
DigitalOut led_red(LED_RED);
DigitalOut led_blue(LED_BLUE);
InterruptIn sw2(SW2);
InterruptIn sw3(SW3);
InterruptIn motion(D2);
DigitalIn motionConfirm(D2);
DigitalIn button(D7);
LED_Bar bar(D6,D5);
Serial blue (PTC15,PTC14);
TextLCD lcd(D0,D1,D8,D9,D10,D11);
double h = 0.0f, c = 0.0f, f = 0.0f, k = 0.0f; 

//ISR: motion detected
void motionSensor(void)
{   lcd.cls();
    wait(1);
    lcd.printf("Motion Detected,  Alarm in 10s");
    wait(5);

    lcd.cls();
    wait(1);
    lcd.printf("Intruder Alert!");
    lcd.locate(0,1);
    lcd.printf("PB = Alarm Off");
    
    //print to terminal
    printf("MOTION DETECTED\n");
    
    //send msg via bluetooth
    blue.printf("Intruder Detected! Call 911 or press button on system to disarm.\n\n");
    
    buzzer = 1;
    led_red = 1;
    led_green = 1;
    led_blue = 0;
    
    while(button == 0)
    {
        wait(0.1);
    }
    
    //print to terminal
    printf("Buzzer off.\n");
    
    //send msg via bluetooth
    blue.printf("Alarm Disabled.\n\n");
    
    buzzer = 0;
    led_red = 1;
    led_blue = 1;
    led_green = 0;
    wait(0.7);

}
    
//ISR: sw2 pressed (display current temp/hum)
void tempDisplay(void)
{
    lcd.cls();
    led_blue = 0;
    led_green = 1;
    led_red = 1;
    wait(0.5);
    printf("Temperature in Kelvin: %4.2f, Celcius: %4.2f, Farenheit %4.2f\n", k, c, f); printf("Humidity is %4.2f\n", h); 
    wait(0.1);
    lcd.locate(4,0);
    lcd.printf("T=%4.2fF        H=%4.2f",f,h);
    wait(5);
}

//ISR: sw3 pressed (enable/disable system)
void disable(void)
{
    lcd.cls();
    led_red = 0;
    led_green = 1;
    led_blue = 1;
    
    //print to lcd
    wait(0.1);
    lcd.printf("System Disabled.");
    lcd.locate(2,1);
    lcd.printf("SW3 = Enable");
    
    //print to terminal
    printf("SYSTEM DISABLED\n");
    
    while(sw3==1)
    {
        //wait until sw3 pressed again
    }
    wait(0.7);
    
    //print to terminal
    printf("SYSTEM ENABLED\n");
    
    led_red = 1;
    led_blue = 1;
    led_green = 0;
}

int main() 
{
     lcd.cls();
     //Interrupts
     sw2.rise(&tempDisplay);
     motion.rise(&motionSensor);
     sw3.rise(&disable);
     
     //Variables
     int LED_const;
     int on = 1, off = 0;
     int error = 0;
     
     lcd.cls();
     wait(0.01);
     lcd.locate(4,0);
     lcd.printf("Welcome!");
     wait(2);
     
     //While loop
     while(1)
     { 
        lcd.cls();
        wait(0.01);
        lcd.locate(1,0);
        lcd.printf("System Enabled   SW3 = Disable");
        
        led_blue = 1;
        led_red = 1;
        led_green = 0;
        
        //monitor temperature for too high or too low
        error = sensor.readData(); 
        if (0 == error)     
        { 
            c = sensor.ReadTemperature(CELCIUS); 
            f = sensor.ReadTemperature(FARENHEIT); 
            k = sensor.ReadTemperature(KELVIN);
            h = sensor.ReadHumidity();
            
            //high temp check
            if(c >= 26.7 || f >= 80.0 || k >= 299.8)
            {
                //print to lcd
                lcd.cls();
                wait(0.1);
                lcd.locate(4,0);
                lcd.printf("WARNING!");
                lcd.locate(1,1);
                lcd.printf("Temp Too HIGH");
                
                //print to terminal
                printf("HIGH TEMP DETECTED\n");
 
                buzzer = on;
                wait(0.5);
                buzzer = off;
                wait(5.0);
            }
            
            //low temp check
            if(c < 12.8 || f < 55.0 || k < 285.9)
            {
                //print to lcd
                lcd.cls();
                wait(0.1);
                lcd.locate(4,0);
                lcd.printf("WARNING!");
                lcd.locate(2,1);
                lcd.printf("Temp Too LOW");
                
                //print to terminal
                printf("LOW TEMP DETECTED\n");
                
                buzzer = on;
                wait(0.5);
                buzzer = off;   
                wait(5.0);             
            }
  
            //LED bar check:
            //define constant to send to LED Bar for temp ranges:
            if(f<55.0)
                LED_const = 0;
            else if(f >= 55.0 && f < 57.5)
                LED_const = 0;
            else if(f >= 57.5 && f < 60.0)
                LED_const = 1;
            else if(f >= 60.0 && f < 62.5)
                LED_const = 2;
            else if(f >= 62.5 && f < 65.0)
                LED_const = 3;
            else if(f >= 65.0 && f < 67.5)
                LED_const = 4;
            else if(f >= 67.5 && f < 70.0)
                LED_const = 5;
            else if(f >= 70.0 && f < 72.5)
                LED_const = 6;
            else if(f >= 72.5 && f < 75.0)
                LED_const = 7;
            else if(f >= 75.0 && f < 80.0)
                LED_const = 8;
            else if(f >= 80.0)
                LED_const = 9;                           
                        
            bar.setLevel(LED_const);         
            
        }//if(0==error)
    }//while(1)
}//main