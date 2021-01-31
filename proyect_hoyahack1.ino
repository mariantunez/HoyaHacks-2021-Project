

int triggerPin = 12;       // input pin of the Trigger of the Ultrasound
int echoPin = 11;         // input pin of the Echo of the Ultrasound
long durationTime;		 // variable that holds the length of the ultrasound wave in microseconds
float distance, feet;   // variable that holds how far away the object is

int inputPIR = 2;               //  input pin for the PIR sensor
int pirState = LOW;            // set to low assuming no motion detected at first
int valPIR = 0;               // variable for reading the pin PIR status 
int pinMotor = 4; 			 // pin to send a voltage to the vibrating motor

void setup() {
  pinMode(triggerPin, OUTPUT);       // declare trigger pin of Ultrasound as an output
  pinMode(echoPin, INPUT);       // declare echo pin of Ultrasound as an input
  pinMode(inputPIR, INPUT);     // declare PIR sensor as an input
  pinMode(pinMotor, OUTPUT);   // declare microvibrating motor as an input
  Serial.begin(9600);         //begin Serial Port
}

void loop(){
  //ULTRAOSUND SENSOR
  //Set trigPin in LOW for 5 microseconds.
  //The trigPin in LOW pulse beforehand ensures a clean HIGH pulse.
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(5);
  //Set the trigPin Trigger in HIGH for 15 or more microseconds.
  //The trigPin in HIGH tells the sensor to send Ultrasound waves for 15 or more microseconds.
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(15);
  digitalWrite(triggerPin, LOW);
  //Read the echoPin, with the funtion pulseIn() 
  //The pulseIn()returns the duration time(length of the wave) in microseconds
  durationTime = pulseIn(echoPin, HIGH);
 
  // Calculate the distance 
  // Distance= (Time x SpeedSound in Air)/2
  //The speed of the air is 0.034cm/s
  distance = durationTime * 0.034 / 2;    //In centimeters
  feet = distance*0.0328084;             //convert distance from cm to ft
  
  //PIR SENSOR & MICROVIBRATING MOTOR
  //The PIR sensor is activated until distance is <= 60 feet
  if (feet <= 6) {
    Serial.println("Ultrasound Sensor detected something");
    valPIR = digitalRead(inputPIR);  // read input value of PIR sensor
    
    if (valPIR == HIGH) {            // check if the input PIR value is HIGH
      	//We print the distance of the bject detected only ofr reference
      	Serial.print("Person detected at "); 
		Serial.print(feet);
		Serial.println(" ft away");
		
      	//Now the we detectect a person we can activate the vibrating motor
    	digitalWrite(pinMotor, HIGH);
      	if (pirState == LOW) {
        // We print a message for reference that the motor is anouncing the user of the detection 
      	Serial.println("Motion detected!");
        delayMicroseconds(6000000);
      	// the state of pinState is HIGH because is detecting movement
      	pirState = HIGH;
    	}
 	 } else {
      	digitalWrite(pinMotor, LOW);
    	if (pirState == HIGH){
      	// No thata there is no movement the PIR sensor nd the motot are off
        //We print for reference that no motion is detected anymore
      	Serial.println("Motion ended!");
      	pirState = LOW;
    	}
  	}
  }
  else{
  	digitalWrite(pinMotor, LOW);
	Serial.println("Nothing in the proximity");  
  }
  
}