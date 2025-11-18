#include "finger.h"
#include <ArduinoJson.h>

void Finger::logEvent(const String& level, const String& message, const String& component = "Finger", DynamicJsonDocument* details = nullptr) {
    DynamicJsonDocument doc(512);
    doc["timestamp"] = millis();
    doc["level"] = level;
    doc["component"] = component;
    doc["message"] = message;
    
    if (details) {
        doc["details"] = *details;  
    }
    
    String jsonString;
    serializeJson(doc, jsonString);
    Serial.println(jsonString);
}


Finger::Finger(double maxAngle = 180, double minAngle = 0, int servoPin = 15)  {
    this->maxAngle = maxAngle;
    this->minAngle = minAngle;
    servo.setPeriodHertz(50);           // standard 50 hz servo
    servo.attach(servoPin, 500, 2500);  // attaches the servo on servoPin to the servo object

    if (servo.attached()) {
        DynamicJsonDocument details(200);
        details["pin"] = servoPin;
        details["maxAngle"] = maxAngle;
        details["minAngle"] = minAngle;
        
        String detailsStr;
        serializeJson(details, detailsStr);
        logEvent("INFO", "Finger servo attached successfully", "Finger", detailsStr);
    } else {
        DynamicJsonDocument details(200);
        details["pin"] = servoPin;
        details["error"] = "Servo attachment failed";
        
        String detailsStr;
        serializeJson(details, detailsStr);
        logEvent("ERROR", "Failed to attach finger servo", "Finger", detailsStr);
    }
}

Finger::~Finger() {
    servo.detach();
    DynamicJsonDocument details(200);
    details["pin"] = servoPin;
    
    String detailsStr;
    serializeJson(details, detailsStr);
    logEvent("INFO", "Finger servo detached", "Finger", detailsStr);
}

void Finger::CalculateAngle(double percentage) {
    DynamicJsonDocument debugDetails(200);
        debugDetails["input_percentage"] = percentage;
        debugDetails["minAngle"] = minAngle;
        debugDetails["maxAngle"] = maxAngle;
        
        String debugStr;
        serializeJson(debugDetails, debugStr);
        logEvent("DEBUG", "CalculateAngle method called", "Finger::CalculateAngle", debugStr);

        if (percentage < 0) {
            percentage = 0;
            logEvent("WARNING", "Percentage clamped to minimum 0", "Finger::CalculateAngle");
        } else if (percentage > 100) {
            percentage = 100;
            logEvent("WARNING", "Percentage clamped to maximum 100", "Finger::CalculateAngle");
        }
        
        double angle = minAngle + (maxAngle - minAngle) * (percentage / 100.0);
        
        // This is for logging the calculate angle result
        DynamicJsonDocument infoDetails(200);
        infoDetails["percentage"] = percentage;
        infoDetails["calculated_angle"] = angle;
        
        String infoStr;
        serializeJson(infoDetails, infoStr);
        logEvent("INFO", "Angle calculated successfully", "Finger::CalculateAngle", infoStr);
        
        setAngle(angle);
}

void Finger::setAngle(double angle) {
    // Implementation of finger movement logic
    DynamicJsonDocument debugDetails(200);
    debugDetails["requested_angle"] = angle;
    debugDetails["max_allowed_angle"] = maxAngle;
    
    String debugStr;
    serializeJson(debugDetails, debugStr);
    logEvent("DEBUG", "setAngle method called", "Finger::setAngle", debugStr);

    double originalAngle = angle;
    
    if (angle < 0) {
        angle = 0;
        logEvent("WARNING", "Angle clamped to minimum 0", "Finger::setAngle");
    } else if (angle > maxAngle) {
        angle = maxAngle;
        logEvent("WARNING", "Angle clamped to maximum", "Finger::setAngle");
    }

    servo.write(angle);
    
    // Info level: successful operation
    DynamicJsonDocument infoDetails(200);
    infoDetails["final_angle"] = angle;
    infoDetails["original_requested_angle"] = originalAngle;
    infoDetails["pin"] = servoPin;
    
    String infoStr;
    serializeJson(infoDetails, infoStr);
    logEvent("INFO", "Servo angle set successfully", "Finger::setAngle", infoStr);
}
