#include "GRT_helper.h"

void print_sample_distribution(TimeSeriesClassificationData& data, const event_type_converter& event_type_converter) {
    cout << "Samples: " << data.getNumSamples() << endl;
    vector<UINT> class_samples_histogram(data.getNumClasses() + 1, 0); // probably null class (0) is excluded, therefore +1
    for (UINT i = 0; i < data.getNumSamples(); ++i) {
        auto& sample = data[i];
        class_samples_histogram[sample.getClassLabel()]++;
    }
    for (UINT i = 0; i < data.getNumClasses() + 1; ++i) {
        cout << event_type_converter.int_to_event_type(i) << " samples: " << class_samples_histogram[i] << "\t";
    }
    cout << endl;
}

TimeSeriesClassificationData extract_training_data(const vector<labeled_event_data>& labeled_training_data,
    const event_type_converter& event_type_converter) {
    TimeSeriesClassificationData training_data;
    training_data.setNumDimensions(2); // Accelerometer, gyroscope
    for (const labeled_event_data& event : labeled_training_data) {
        /* Don't add data if it's empty */
        if (event.sensor_data.empty())
            continue;
        MatrixDouble training_sample;
        for (size_t i = 0; i < event.sensor_data.size(); ++i) {
            const sensor_frame& frame = event.sensor_data[i];
            VectorDouble sensor_data_row;
            sensor_data_row.push_back(frame.acceleration);
            sensor_data_row.push_back(frame.gyro);
            training_sample.push_back(sensor_data_row);
        }
        if (!training_data.addSample(event_type_converter.event_type_to_int(event.type), training_sample)) {
            cout << "Error while adding sample. " << endl;
        }
    }
    return training_data;
}

HMM setup_HMM(int downsample_factor) {
    HMM hmm = HMM();
    hmm.setHMMType(HMMTypes::HMM_CONTINUOUS);
    hmm.setDownsampleFactor(downsample_factor);
    hmm.setCommitteeSize(10);
    hmm.setAutoEstimateSigma(true);
    hmm.setModelType(HMMModelTypes::HMM_LEFTRIGHT);
    hmm.setDelta(1);
    hmm.enableNullRejection(true);
    return hmm;
}

DTW setup_DTW() {
   DTW dtw = DTW();
   //dtw.enableTrimTrainingData(true, 0.1, 90);
   return dtw;
}
