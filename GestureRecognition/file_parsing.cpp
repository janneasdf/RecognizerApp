#include "file_parsing.h"

#include <iostream>

using namespace std;

string read_field_string(istringstream& iss) {
	string value;
	if (!getline(iss, value, ',')) {
		throw exception("Error: Not enough values to read from stream. ");
	}
	return value;
}

float read_field_float(istringstream& iss) {
	string value = read_field_string(iss);
	return (float)atof(value.c_str());
}

vector<sensor_frame> read_sensor_data(string sensor_data_filename) {
	/* Open sensor data file */
	ifstream sensor_data_file(sensor_data_filename);
	if (!sensor_data_file.good()) {
		throw exception("Error opening sensor data file. ");
	}
	/* Loop through lines in file */
	vector<sensor_frame> sensor_data;
	for (string line; getline(sensor_data_file, line);) {
		/* Skip line if it is a comment */
		if (line.length() > 0 && line[0] == '#') continue;
		/* Extract values from the line */
		istringstream iss(line);
		float time = read_field_float(iss);
		float acceleration = read_field_float(iss);
		float compass = read_field_float(iss);
		float gyro = read_field_float(iss);
		/* Store values into a frame struct and push it to the vector */
		sensor_frame frame(time, acceleration, compass, gyro);
		sensor_data.push_back(frame);
	}
	return sensor_data;
}

vector<string> read_lines_from_file(string filename) {
	vector<string> filenames;
	ifstream file(filename);
	if (!file.good()) {
		throw std::invalid_argument(string("Error opening ") + filename);
	}
	for (string line; getline(file, line);) {
		filenames.push_back(line);
	}
	file.close();
	return filenames;
}

vector<event_marker> read_event_markers_from_file(string event_data_filename) {
	ifstream event_data_file(event_data_filename);
	vector<event_marker> event_markers;
	for (string line; getline(event_data_file, line);) {
		/* Extract event time and type from the line */
		istringstream iss(line);
		float time = read_field_float(iss);
		string event_type = read_field_string(iss);
		event_markers.push_back(event_marker(time, event_type));
	}
	return event_markers;
}

vector<labeled_event_data> read_labeled_training_data(const string data_folder, const vector<string>& training_data_filenames) {
	vector<labeled_event_data> labeled_training_data;
	for (string filename : training_data_filenames) {
		cout << "Extracting training data from file: " << filename << endl;
		/* Format of data files is data_folder + filename + .dat, format of event files is data_folder + filename + _events + .dat */
		string sensor_data_filename = data_folder + filename + ".dat";
		string event_data_filename = data_folder + filename + "_events.dat";
		/* Read sensor frames (time, acceleration, compass, gyro) */
		vector<sensor_frame> sensor_frames;
		sensor_frames = read_sensor_data(sensor_data_filename);
		/* Open event data file and extract event data */
		vector<event_marker> event_markers = read_event_markers_from_file(event_data_filename);
		/* Extract event data (current version expects events to consist of a start and an end marker) */
		if (event_markers.size() % 2 != 0) {
			throw exception("Event markers amount is not divisible by two (all events should consist of two markers (currently)). ");
		}
        size_t num_events = event_markers.size() / 2;
		/* Loop through events */
		int frame_index = 0;
		for (int event_index = 0; event_index < num_events; ++event_index) {
			event_marker event_begin_marker = event_markers[event_index * 2];
			event_marker event_end_marker = event_markers[event_index * 2 + 1];
			labeled_event_data labeled_event_data;
			labeled_event_data.type = event_begin_marker.type + "," + event_end_marker.type;
			while (sensor_frames[frame_index].time < event_begin_marker.time) ++frame_index;
			while (sensor_frames[frame_index].time < event_end_marker.time) {
				labeled_event_data.sensor_data.push_back(sensor_frames[frame_index]);
				++frame_index;
			}
			labeled_training_data.push_back(labeled_event_data);
		}
        cout << "Finished reading training data from file: " << filename << endl;
	}
	return labeled_training_data;
}

vector<labeled_event_data> read_labeled_training_data_separate(const string data_folder, const vector<string>& training_data_filenames, float window_size)
{
    vector<labeled_event_data> labeled_training_data;
    for (string filename : training_data_filenames) {
        cout << "Extracting training data from file: " << filename << endl;
        /* Format of data files is data_folder + filename + .dat, format of event files is data_folder + filename + _events + .dat */
        string sensor_data_filename = data_folder + filename + ".dat";
        string event_data_filename = data_folder + filename + "_events.dat";
        /* Read sensor frames (time, acceleration, compass, gyro) */
        vector<sensor_frame> sensor_frames;
        sensor_frames = read_sensor_data(sensor_data_filename);
        /* Open event data file and extract event data */
        vector<event_marker> event_markers = read_event_markers_from_file(event_data_filename);
        /* Read window_size sized window of data after each event marker as an event */
        int frame_index = 0;
        for (int event_index = 0; event_index < event_markers.size(); ++event_index)
        {
            auto& event = event_markers[event_index];
            labeled_event_data event_data;
            event_data.type = event.type;
            /* Skip frames before start of event */
            while (sensor_frames[frame_index].time < event.time) frame_index++;
            /* Read data window_size long data */
            while (sensor_frames[frame_index].time < event.time + window_size)
            {
                event_data.sensor_data.push_back(sensor_frames[frame_index]);
                frame_index++;
            }
            labeled_training_data.push_back(event_data);
        }
        cout << "Finished reading training data from file: " << filename << endl;
    }
    return labeled_training_data;
}
