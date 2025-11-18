#ifndef FINGER_H
#define FINGER_H

#include <iostream>
#include <string>
#include <ESP32Servo.h>
using std::string;

class Finger {
        private:
        void logEvent(const String& level, const String& message, const String& component = "Finger", const String& details = "");

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