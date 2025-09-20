#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>
#include <singleLEDLibrary.h>
#include "Arduino.h"
#include "ADXL345.h"
#include "I2Cdev.h"
#include "Buzzer.h"
#include "LED.h"
#include "Button.h"


// Pin Definitions
#define BUZZER_PIN_SIG  2
#define LEDR_PIN_VIN  3
#define PUSHBUTTON_1_PIN_2  4
#define PUSHBUTTON_2_PIN_2  5
#define SIM800L_SOFTWARESERIAL_PIN_TX 10
#define SIM800L_SOFTWARESERIAL_PIN_RX 11



// Global variables and def
int16_t adxlAx, adxlAy, adxlAz;
// object initialization
ADXL345 adxl;
Buzzer buzzer(BUZZER_PIN_SIG);
LED ledR(LEDR_PIN_VIN);
Button pushButton_1(PUSHBUTTON_1_PIN_2);
Button pushButton_2(PUSHBUTTON_2_PIN_2);



const int timeout = 1000;       //define timeout of 1sec
char menuOption = 0;
long time0;


void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    adxl.init();
 pushButton_1.init();
    pushButton_2.init();
    menuOption = menu();
    
}


void loop() 
{
    
    
    if(menuOption == '1') {
          // read raw accel measurements from device
    adxl.getAcceleration(&adxlAx, &adxlAy, &adxlAz);
    // display tab-separated accel x/y/z values
    sensors_event_t event; 
    accel.getEvent(&event);
    Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("");
    Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("");
    Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("");
    Serial.println("m/s^2 ");
    delay(500);
    Serial.print(F("ADXL345 accel-\t")); 
    Serial.print(adxlAx); Serial.print(F("\t"));
    Serial.print(adxlAy); Serial.print(F("\t"));  
    Serial.println(adxlAz);

    }
    else if(menuOption == '2') {
    // The buzzer will turn on and off for 500ms (0.5 sec)
    buzzer.on();       // 1. turns on
    delay(500);             // 2. waits 500 milliseconds (0.5 sec)
    buzzer.off();      // 3. turns off.
    delay(500);             // 4. waits 500 milliseconds (0.5 sec)
    }
    else if(menuOption == '3') {
    // LED - Basic Red 5mm - Test Code
 // The LED will turn on and fade till it is off
    for(int i=255 ; i> 0 ; i -= 5)
    {
    ledR.dim(i);                      // 1. Dim Led 
    delay(15);                               // 2. waits 5 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }                                          
    ledR.off();                        // 3. turns off
    }
    else if(menuOption == '4')
    {
      {
  // join I2C bus (I2Cdev library doesn't do this automatically)
  Wire.begin();
 
  // initialize serial communication
  // (38400 chosen because it works as well at 8MHz as it does at 16MHz, but
  // it's really up to you depending on your project)
  Serial.begin(38400);
 
  // initialize device
  Serial.println("Initializing I2C devices...");
  accelgyro.initialize();
 
  // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU9250 connection successful" : "MPU9250 connection failed");
    delay(1000);
    Serial.println("     ");
 
 //Mxyz_init_calibrated ();
}
 
void loop()
{   
    getAccel_Data();
    getGyro_Data();
    getCompassDate_calibrated(); // compass data has been calibrated here
    getHeading();               //before we use this function we should run 'getCompassDate_calibrated()' frist, so that we can get calibrated data ,then we can get correct angle .                    
    getTiltHeading();           
 
    Serial.println("calibration parameter: ");
    Serial.print(mx_centre);
    Serial.print("         ");
    Serial.print(my_centre);
    Serial.print("         ");
    Serial.println(mz_centre);
    Serial.println("     ");
 
 
    Serial.println("Acceleration(g) of X,Y,Z:");
    Serial.print(Axyz[0]);
    Serial.print(",");
    Serial.print(Axyz[1]);
    Serial.print(",");
    Serial.println(Axyz[2]);
    Serial.println("Gyro(degress/s) of X,Y,Z:");
    Serial.print(Gxyz[0]);
    Serial.print(",");
    Serial.print(Gxyz[1]);
    Serial.print(",");
    Serial.println(Gxyz[2]);
    Serial.println("Compass Value of X,Y,Z:");
    Serial.print(Mxyz[0]);
    Serial.print(",");
    Serial.print(Mxyz[1]);
    Serial.print(",");
    Serial.println(Mxyz[2]);
    Serial.println("The clockwise angle between the magnetic north and X-Axis:");
    Serial.print(heading);
    Serial.println(" ");
    Serial.println("The clockwise angle between the magnetic north and the projection of the positive X-Axis in the horizontal plane:");
    Serial.println(tiltheading);
    Serial.println("   ");
    Serial.println("   ");
    Serial.println("   ");
    delay(300);
}
    }
    else if(menuOption == '5') {
   
    bool pushButton_1Val = pushButton_1.read();
    Serial.print(F("Val: ")); Serial.println(pushButton_1Val);

    }
    else if(menuOption == '6') {
   
    
    bool pushButton_2Val = pushButton_2.read();
    Serial.print(F("Val: ")); Serial.println(pushButton_2Val);

    }
    else if(menuOption == '7')
    {
    pinMode(button1, INPUT_PULLUP); //The button is always on HIGH level, when pressed it goes LOW
  sim800l.begin(9600);   //Module baude rate, this is on max, it depends on the version
  Serial.begin(9600);   
  delay(1000);
}
 
void loop()
{
  

  button_State = digitalRead(button1);   //We are constantly reading the button State
 
  if (button_State == LOW) {            //And if it's pressed
    Serial.println("Button pressed");   //Shows this message on the serial monitor
    delay(200);                         //Small delay to avoid detecting the button press many times
    
    SendSMS();                          //And this function is called

 }
 
  if (sim800l.available()){            //Displays on the serial monitor if there's a communication from the module
    Serial.write(sim800l.read()); 
  }
}
 
void SendSMS()
{
  Serial.println("Sending SMS...");              
  sim800l.print("AT+CMGF=1\r");                  
  delay(100);
  sim800l.print("AT+CMGS=\"+*********\"\r"); 
  delay(500);
  sim800l.print("HELP!!!!!!!!!!!!!");       
  delay(500);
  sim800l.print((char)26);// (required according to the datasheet)
  delay(500);
  sim800l.println();
  Serial.println("SEND HELP ASAP!!!!!!!!!!!!!.");
  delay(500);

}
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}




char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) SparkFun ADXL345 - Triple Axis Accelerometer Breakout"));
    Serial.println(F("(2) Buzzer"));
    Serial.println(F("(3) LED - Basic Red 5mm"));
    Serial.println(F("(4) SparkFun MPU-9250 - IMU Breakout"));
    Serial.println(F("(5) Mini Pushbutton Switch #1"));
    Serial.println(F("(6) Mini Pushbutton Switch #2"));
    Serial.println(F("(7) QuadBand GPRS-GSM SIM800L"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
      if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
          
        else if(c == '2') 
         
        else if(c == '3') 
         
        else if(c == '4') 
          
        else if(c == '5') 
          
        else if(c == '6') 
          
        else if(c == '7') 
          
            else
            {
            }
            time0 = millis();
            return c;
        }
    }
}
