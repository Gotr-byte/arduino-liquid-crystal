#include<LiquidCrystal.h>

const int analogInputPin = A0;  // Analog input pin that the voltage is connected to
const int pwmOutputPin = 9;
int outputValue = 0;
float inputVoltage = 0.0;       // Variable to hold the input voltage
int receivedInt = 0;    // variable to hold the received data

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
void setup()
{
  Serial.begin(9600);
 lcd.begin(16, 2);
}

void loop()
{
  // Read the input on analog pin 0:
  int sensorValue = analogRead(analogInputPin);
  // Generate output value to analog output with sensor
  String inputString = ""; // String to hold input

  // Check if data is available to read
  while (Serial.available()) {
    // Delay to allow buffer to fill:
    delay(5);

    // Read incoming characters
    char inChar = Serial.read();
    inputString += inChar;
  }

  // If the input string is not empty, convert to integer:
  if (inputString != "") {
    outputValue = inputString.toInt();
    Serial.print("OutputVal=");
                 Serial.print(outputValue);
    Serial.print("\n");
  }

  
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  inputVoltage = sensorValue * (5.0 / 1023.0);

  // Print out the value in volts:
  lcd.setCursor(0,0);
  lcd.print("Voltage = " );
  lcd.print(outputValue);
  lcd.println(" V");
  analogWrite(pwmOutputPin, outputValue);
  
  // Delay for a bit to make the output easier to read:
  delay(500);   
}