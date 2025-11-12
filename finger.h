#ifndef FINGER_H
#define FINGER_H

#include <iostream>
#include <string>
#include <ESP32Servo.h>
using std::string;

class Finger {
        public:
        // Constructor
        Finger(double maxAngle,double minAngle, int servoPin);
        // Variables
        double maxAngle;
        double minAngle;
        Servo servo;

        // Methods
        void setAngle(double angle);

        // Destructor
        ~Finger();
};
#endif // FINGER_H