#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include "sensor_events.h"

using namespace std;

/* 
This header declares helper functions for parsing files 
(for example, sensor data/events or configuration files).
*/

/* Reads one string value from the input string stream iss */
std::string read_field_string(std::istringstream& iss);

/* Reads one float value from the input string stream iss */
float read_field_float(std::istringstream& iss);

/* Reads the lines from a file. Each line is one element of the vector. */
std::vector<std::string> read_lines_from_file(std::string filename);

/* Extracts event marker data from a file */
std::vector<event_marker> read_event_markers_from_file(std::string event_data_filename);

/* Read training data (sensor event data) and put it into labeled */
std::vector<labeled_event_data> read_labeled_training_data(const string data_folder, const vector<string>& training_data_filenames);

/* Reads sensor data from file */
vector<sensor_frame> read_sensor_data(string sensor_data_filename);

/* Read labeled training data, with each event marker as a separate gesture,
 * where a gesture starts with the event marker and is window_size long
 * (therefore, there is no end marker).
*/
vector<labeled_event_data> read_labeled_training_data_separate(const string data_folder, const vector<string>& training_data_filenames, float window_size);
