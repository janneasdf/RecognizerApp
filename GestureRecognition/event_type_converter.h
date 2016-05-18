#pragma once
#include <string>
#include <map>
#include <vector>
#include "sensor_events.h"
using namespace std;

/* Since GRT handles classes as int, this class assigns integers 
	to event types for converting between them easily. */
class event_type_converter
{
public:
	/* Initializes the integer-event_type mapping */
	void initialize(vector<labeled_event_data> event_data);

	string int_to_event_type(int event_class) const;
	int event_type_to_int(string event_type) const;

private:
	map<int, string> map_int_to_event;
	map<string, int> map_event_to_int;
};