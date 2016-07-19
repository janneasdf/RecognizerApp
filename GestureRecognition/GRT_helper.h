#ifndef GRT_HELPER_H
#define GRT_HELPER_H

#include "Libraries/GRT/GRT.h"
#include "sensor_events.h"
#include "event_type_converter.h"

using namespace GRT;
using namespace std;

/*
 * This header includes helper functions related to using GRT
 *
 */

/* Helper function for printing amount of samples for different types of events */
void print_sample_distribution(TimeSeriesClassificationData& data, const event_type_converter& event_type_converter);

/* This function extracts training data from a vector<labeled_event_data> (read from file)
into GRT's TimeSeriesClassificationData object. */
TimeSeriesClassificationData extract_training_data(const vector<labeled_event_data>& labeled_training_data, 
    const event_type_converter& event_type_converter);

/* Create a Hidden Markov Model classifier and setup its parameters */
HMM setup_HMM(int downsample_factor, bool continuous);

DTW setup_DTW();

#endif
