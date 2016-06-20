#include <unordered_set>
#include <iterator>
#include "event_type_converter.h"

void event_type_converter::initialize(vector<labeled_event_data> event_data)
{
	/* Clear the maps */
	map_int_to_event.clear();
	map_event_to_int.clear();

	/* Find all distinct event names in event data and put them into vector "event_types" */
	unordered_set<string> set_event_types;
	for (const labeled_event_data& data : event_data)
	{
		set_event_types.insert(data.type);
	}
	vector<string> event_types;
	copy(set_event_types.begin(), set_event_types.end(), back_inserter(event_types));

	/* Create int<->event relations */
    map_int_to_event[0] = "No gesture";
    map_event_to_int["No gesture"] = 0;
	int current_class = 1;
	for (string event_type : event_types)
	{
		map_int_to_event[current_class] = event_type;
		map_event_to_int[event_type] = current_class;
		++current_class;
	}
}

string event_type_converter::int_to_event_type(int event_class) const
{
	return map_int_to_event.at(event_class);
}

int event_type_converter::event_type_to_int(string event_type) const
{
	return map_event_to_int.at(event_type);
}
