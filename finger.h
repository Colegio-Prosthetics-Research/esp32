#ifndef FINGER_H
#define FINGER_H

#include <iostream>
#include <string>
#include <ESP32Servo.h>
using std::string;

class Finger {
        public:
        // Constructor
        Finger(double maxAngle, int servoPin);
        // Variables
        double maxAngle;
        Servo servo;

        // Methods
        void setAngle(double angle);

        // Destructor
        ~Finger();
};
#endif // FINGER_H