#include <AccelStepper.h>
 
#define pul 7
#define dir 6

AccelStepper stepper(1, pul, dir); // 1 specificies that a stepper driver is being used
 
void setup(){  
  // --- Velocity ---
  stepper.setMaxSpeed(4000); // 4000 steps/second is the maximum reliable limit for an arduino driving a stepper
  // corrosponds to max rotation of 20 RPS = 1,200 RPM
  // assume a radius of 11.94 cm
  // corrosponds to max speed of 15 m/s
  
  // --- Acceleration ---
  // max acceleration is 9.803 m/s^2
  // 9.803 m/s = 13.071 rev/s = 2614 steps/second
  stepper.setAcceleration(2614);

  stepper.setCurrentPosition(0);


  // wait until arduino makes serial contact with computer
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial.println("Serial connected! Ready to accept commands");
}

// User defined physics parameters:
float starting_height = 30; // meters
float winch_radius = 0.11936; // meters
float increment_distance = 0.25; // meters

// Derived physical parameters
float winch_circumnference = 0.75;

// Launch parameters
float desired_launch_speed = 15; // m/s
int launch_flag = 0;

int incoming_byte = 0;
 
void loop(){
    // Commands:
    // " ": emergency stop (space bar)

    // --- Operation ---
    // Step 0: Winch begins fully retracted
    // Step 1.1: Winch slowly lowers the basket all the way to the floor
    // Step 1.2: Operator manually adjusts the height of the winch by large and small increments
    // Step 2: Operator triggers default launch
    //    Accelerates upward until reaching 15 m/s
    //    Decelerates at 9.8 m/s^2, past apogee, and continues to decelerate until {} height is achieved
    //    Softly brings payload to a stop
    //    Lowers payload back to initial height
    
  stepper.run();

  if (Serial.available() > 0){
      incoming_byte = Serial.read();
      
      if (incoming_byte == 32){ //  (space bar)
        // emergency stop
        launch_flag = 0;
        stepper.stop();
        Serial.println("Stopping...");
      } else if (incoming_byte == 46){ // .
        // raise stepper by increment
        stepper.move(increment_distance/winch_circumnference * 200);
        Serial.print("Moving up by ");
        Serial.println(increment_distance);
      } else if (incoming_byte == 44){ // .
        // raise stepper by increment
        stepper.move(-increment_distance/winch_circumnference * 200);
        Serial.print("Moving down by ");
        Serial.println(increment_distance);
      } else if (incoming_byte == 97) { // a
        // slowly lower stepper by starting_height
        stepper.move(-starting_height/winch_circumnference * 200);
        Serial.print("Moving down by ");
        Serial.print(starting_height);
        Serial.println(" meters");
      } else if (incoming_byte == 113) { // q
        // launch stepper
        launch_flag = 1;
        stepper.move(25000);

        Serial.println("Launch triggered!");
        Serial.print("Accelerating to ");
        Serial.print(desired_launch_speed);
        Serial.println(" m/s");
      } else if (incoming_byte == 115){ // s
        // Check current speed of the stepper
        
        Serial.print("Current speed is: ");
        Serial.print(stepper.speed());
      }
      else if (incoming_byte != 10){
        Serial.print("Recieved ");
        Serial.print(incoming_byte, DEC);
        Serial.println(" which is not a command :(");
      }
  }

  // Launch parameter
  
  if (launch_flag != 0){
    if (stepper.speed() >= 4000){
      Serial.println("Hit max upward speed. Decelerating...");
      stepper.move(-25000);
    } else if (stepper.speed() <= -4000){
      Serial.println("Hit downward speed. Stopping...");
      stepper.stop();
    }
  }
}