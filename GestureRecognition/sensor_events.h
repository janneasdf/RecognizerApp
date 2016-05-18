#pragma once

#include <string>
#include <vector>
#include <sstream>
using namespace std;

/* 
This header includes types and helper functions related to sensor data
and sensor events.
*/

/* Struct that holds sensor values from one frame of data */
struct sensor_frame {
	float time;
	float acceleration;
	float compass; // ...why?
	float gyro;
	sensor_frame(float time, float acceleration, float compass, float gyro) :
		time(time), acceleration(acceleration), compass(compass), gyro(gyro) {}
};

/* Represents a marked event in the data */
struct event_marker {
	float time;
	string type;
	event_marker(float time, string event_type) : time(time), type(event_type) {}
};

/* Struct that represents one piece of labeled training data */
struct labeled_event_data {
	string type;
	vector<sensor_frame> sensor_data;	// todo decide if sensor data should be made to start from t=0 for these
	labeled_event_data() {}
	labeled_event_data(string event_type, vector<sensor_frame> sensor_data) : type(event_type), sensor_data(sensor_data) {}
};

