#-------------------------------------------------
#
# Project created by QtCreator 2016-05-13T15:33:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = RecognizerApp
TEMPLATE = app

CONFIG += qt debug

INCLUDEPATH += BallCommunication/Libraries/

# Tell the qcustomplot header that it will be used as library:
DEFINES += QCUSTOMPLOT_USE_LIBRARY

# Link with debug version of qcustomplot if compiling in debug mode, else with release library:
CONFIG(debug, release|debug) {
  win32:QCPLIB = qcustomplotd1
  else: QCPLIB = qcustomplotd
} else {
  win32:QCPLIB = qcustomplot1
  else: QCPLIB = qcustomplot
}
LIBS += "-L../RecognizerApp/Libraries/" -l$$QCPLIB

contains(QT_ARCH, i386) {
    LIBS += "-LE:/Research/Sensorball/New stuff/RecognizerApp/BallCommunication/Libraries/SDL/x86/lib" -lSDL
    LIBS += "-LE:/Research/Sensorball/New stuff/RecognizerApp/BallCommunication/Libraries/SDL/x86/lib" -lSDL_net
} else {
    LIBS += "-LE:/Research/Sensorball/New stuff/RecognizerApp/BallCommunication/Libraries/SDL/x64/lib" -lSDL
    LIBS += "-LE:/Research/Sensorball/New stuff/RecognizerApp/BallCommunication/Libraries/SDL/x64/lib" -lSDL_net
}

SOURCES += main.cpp\
        mainwindow.cpp \
    BallCommunication/Networking/BallCommunicator/BallCommunicator.cpp \
    BallCommunication/Networking/BallCommunicator/BallCommunicator_UDP.cpp \
    BallCommunication/Networking/Network/Network.cpp \
    BallCommunication/Networking/Network/UDPClientSession.cpp \
    BallCommunication/Networking/Network/UDPServerSession.cpp \
    BallCommunication/Networking/RS232C/rs232c.cpp \
    BallCommunication/Networking/Timer/Timer.cpp \
    BallCommunication/Utilities/AccelerometerCalibrator/AccelerometerCalibrator.cpp \
    BallCommunication/Utilities/GyroCalibrator/GyroCalibrator.cpp \
    BallCommunication/ballcommunication.cpp \
    GestureRecognition/gesturerecognition.cpp \
    mainlogic.cpp \
    monitorview.cpp \
    training.cpp \
    trainingview.cpp \
    GestureRecognition/event_type_converter.cpp \
    GestureRecognition/file_parsing.cpp \
    GestureRecognition/sensor_events.cpp \
    GestureRecognition/recognizer.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/AdaBoost/WeakClassifiers/DecisionStump.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/AdaBoost/WeakClassifiers/RadialBasisFunction.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/AdaBoost/WeakClassifiers/WeakClassifier.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/AdaBoost/AdaBoost.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/ANBC/ANBC.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/ANBC/ANBC_Model.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/BAG/BAG.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/DecisionTree/DecisionTree.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/DecisionTree/DecisionTreeClusterNode.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/DecisionTree/DecisionTreeNode.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/DecisionTree/DecisionTreeThresholdNode.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/DecisionTree/DecisionTreeTripleFeatureNode.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/DTW/DTW.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/FiniteStateMachine/FiniteStateMachine.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/GMM/GMM.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/HMM/ContinuousHiddenMarkovModel.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/HMM/DiscreteHiddenMarkovModel.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/HMM/HMM.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/KNN/KNN.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/LDA/LDA.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/MinDist/MinDist.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/MinDist/MinDistModel.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/ParticleClassifier/ParticleClassifier.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/RandomForests/RandomForests.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/Softmax/Softmax.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/SVM/LIBSVM/libsvm.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/SVM/SVM.cpp \
    GestureRecognition/Libraries/GRT/ClassificationModules/SwipeDetector/SwipeDetector.cpp \
    GestureRecognition/Libraries/GRT/ClusteringModules/ClusterTree/ClusterTree.cpp \
    GestureRecognition/Libraries/GRT/ClusteringModules/GaussianMixtureModels/GaussianMixtureModels.cpp \
    GestureRecognition/Libraries/GRT/ClusteringModules/HierarchicalClustering/HierarchicalClustering.cpp \
    GestureRecognition/Libraries/GRT/ClusteringModules/KMeans/KMeans.cpp \
    GestureRecognition/Libraries/GRT/ClusteringModules/SelfOrganizingMap/SelfOrganizingMap.cpp \
    GestureRecognition/Libraries/GRT/ContextModules/Gate.cpp \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/BernoulliRBM/BernoulliRBM.cpp \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/MovementDetector/MovementDetector.cpp \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/PrincipalComponentAnalysis/PrincipalComponentAnalysis.cpp \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/Tree/Node.cpp \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/Tree/Tree.cpp \
    GestureRecognition/Libraries/GRT/CoreModules/Classifier.cpp \
    GestureRecognition/Libraries/GRT/CoreModules/Clusterer.cpp \
    GestureRecognition/Libraries/GRT/CoreModules/Context.cpp \
    GestureRecognition/Libraries/GRT/CoreModules/FeatureExtraction.cpp \
    GestureRecognition/Libraries/GRT/CoreModules/GestureRecognitionPipeline.cpp \
    GestureRecognition/Libraries/GRT/CoreModules/GRTBase.cpp \
    GestureRecognition/Libraries/GRT/CoreModules/MLBase.cpp \
    GestureRecognition/Libraries/GRT/CoreModules/PostProcessing.cpp \
    GestureRecognition/Libraries/GRT/CoreModules/PreProcessing.cpp \
    GestureRecognition/Libraries/GRT/CoreModules/Regressifier.cpp \
    GestureRecognition/Libraries/GRT/DataStructures/ClassificationData.cpp \
    GestureRecognition/Libraries/GRT/DataStructures/ClassificationSample.cpp \
    GestureRecognition/Libraries/GRT/DataStructures/RegressionData.cpp \
    GestureRecognition/Libraries/GRT/DataStructures/RegressionSample.cpp \
    GestureRecognition/Libraries/GRT/DataStructures/TimeSeriesClassificationData.cpp \
    GestureRecognition/Libraries/GRT/DataStructures/TimeSeriesClassificationDataStream.cpp \
    GestureRecognition/Libraries/GRT/DataStructures/TimeSeriesClassificationSample.cpp \
    GestureRecognition/Libraries/GRT/DataStructures/UnlabelledData.cpp \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/FFT/FastFourierTransform.cpp \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/FFT/FFT.cpp \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/FFT/FFTFeatures.cpp \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/KMeansFeatures/KMeansFeatures.cpp \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/KMeansQuantizer/KMeansQuantizer.cpp \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/MovementIndex/MovementIndex.cpp \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/MovementTrajectoryFeatures/MovementTrajectoryFeatures.cpp \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/RBMQuantizer/RBMQuantizer.cpp \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/SOMQuantizer/SOMQuantizer.cpp \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/TimeDomainFeatures/TimeDomainFeatures.cpp \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/TimeseriesBuffer/TimeseriesBuffer.cpp \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/ZeroCrossingCounter/ZeroCrossingCounter.cpp \
    GestureRecognition/Libraries/GRT/PostProcessingModules/ClassLabelChangeFilter.cpp \
    GestureRecognition/Libraries/GRT/PostProcessingModules/ClassLabelFilter.cpp \
    GestureRecognition/Libraries/GRT/PostProcessingModules/ClassLabelTimeoutFilter.cpp \
    GestureRecognition/Libraries/GRT/PreProcessingModules/DeadZone.cpp \
    GestureRecognition/Libraries/GRT/PreProcessingModules/Derivative.cpp \
    GestureRecognition/Libraries/GRT/PreProcessingModules/DoubleMovingAverageFilter.cpp \
    GestureRecognition/Libraries/GRT/PreProcessingModules/FIRFilter.cpp \
    GestureRecognition/Libraries/GRT/PreProcessingModules/HighPassFilter.cpp \
    GestureRecognition/Libraries/GRT/PreProcessingModules/LeakyIntegrator.cpp \
    GestureRecognition/Libraries/GRT/PreProcessingModules/LowPassFilter.cpp \
    GestureRecognition/Libraries/GRT/PreProcessingModules/MedianFilter.cpp \
    GestureRecognition/Libraries/GRT/PreProcessingModules/MovingAverageFilter.cpp \
    GestureRecognition/Libraries/GRT/PreProcessingModules/SavitzkyGolayFilter.cpp \
    GestureRecognition/Libraries/GRT/RegressionModules/ArtificialNeuralNetworks/MLP/MLP.cpp \
    GestureRecognition/Libraries/GRT/RegressionModules/ArtificialNeuralNetworks/MLP/Neuron.cpp \
    GestureRecognition/Libraries/GRT/RegressionModules/LinearRegression/LinearRegression.cpp \
    GestureRecognition/Libraries/GRT/RegressionModules/LogisticRegression/LogisticRegression.cpp \
    GestureRecognition/Libraries/GRT/RegressionModules/MultidimensionalRegression/MultidimensionalRegression.cpp \
    GestureRecognition/Libraries/GRT/RegressionModules/RegressionTree/RegressionTree.cpp \
    GestureRecognition/Libraries/GRT/Util/Cholesky.cpp \
    GestureRecognition/Libraries/GRT/Util/DebugLog.cpp \
    GestureRecognition/Libraries/GRT/Util/EigenvalueDecomposition.cpp \
    GestureRecognition/Libraries/GRT/Util/ErrorLog.cpp \
    GestureRecognition/Libraries/GRT/Util/InfoLog.cpp \
    GestureRecognition/Libraries/GRT/Util/LUDecomposition.cpp \
    GestureRecognition/Libraries/GRT/Util/MatrixDouble.cpp \
    GestureRecognition/Libraries/GRT/Util/PeakDetection.cpp \
    GestureRecognition/Libraries/GRT/Util/RangeTracker.cpp \
    GestureRecognition/Libraries/GRT/Util/SVD.cpp \
    GestureRecognition/Libraries/GRT/Util/TestingLog.cpp \
    GestureRecognition/Libraries/GRT/Util/ThreadPool.cpp \
    GestureRecognition/Libraries/GRT/Util/ThresholdCrossingDetector.cpp \
    GestureRecognition/Libraries/GRT/Util/TimeSeriesClassificationSampleTrimmer.cpp \
    GestureRecognition/Libraries/GRT/Util/TrainingDataRecordingTimer.cpp \
    GestureRecognition/Libraries/GRT/Util/TrainingLog.cpp \
    GestureRecognition/Libraries/GRT/Util/Util.cpp \
    GestureRecognition/Libraries/GRT/Util/WarningLog.cpp \
    GestureRecognition/grthelper.cpp \
    recognitionview.cpp \
    BallCommunication/ballcommunicationbase.cpp \
    BallCommunication/ballcommunicationfake.cpp

HEADERS  += mainwindow.h \
    BallCommunication/Libraries/SDL/include/begin_code.h \
    BallCommunication/Libraries/SDL/include/close_code.h \
    BallCommunication/Libraries/SDL/include/SDL.h \
    BallCommunication/Libraries/SDL/include/SDL_active.h \
    BallCommunication/Libraries/SDL/include/SDL_audio.h \
    BallCommunication/Libraries/SDL/include/SDL_byteorder.h \
    BallCommunication/Libraries/SDL/include/SDL_cdrom.h \
    BallCommunication/Libraries/SDL/include/SDL_config.h \
    BallCommunication/Libraries/SDL/include/SDL_config.h.default \
    BallCommunication/Libraries/SDL/include/SDL_config.h.in \
    BallCommunication/Libraries/SDL/include/SDL_config_dreamcast.h \
    BallCommunication/Libraries/SDL/include/SDL_config_macos.h \
    BallCommunication/Libraries/SDL/include/SDL_config_macosx.h \
    BallCommunication/Libraries/SDL/include/SDL_config_minimal.h \
    BallCommunication/Libraries/SDL/include/SDL_config_nds.h \
    BallCommunication/Libraries/SDL/include/SDL_config_os2.h \
    BallCommunication/Libraries/SDL/include/SDL_config_symbian.h \
    BallCommunication/Libraries/SDL/include/SDL_config_win32.h \
    BallCommunication/Libraries/SDL/include/SDL_copying.h \
    BallCommunication/Libraries/SDL/include/SDL_cpuinfo.h \
    BallCommunication/Libraries/SDL/include/SDL_endian.h \
    BallCommunication/Libraries/SDL/include/SDL_error.h \
    BallCommunication/Libraries/SDL/include/SDL_events.h \
    BallCommunication/Libraries/SDL/include/SDL_getenv.h \
    BallCommunication/Libraries/SDL/include/SDL_image.h \
    BallCommunication/Libraries/SDL/include/SDL_joystick.h \
    BallCommunication/Libraries/SDL/include/SDL_keyboard.h \
    BallCommunication/Libraries/SDL/include/SDL_keysym.h \
    BallCommunication/Libraries/SDL/include/SDL_loadso.h \
    BallCommunication/Libraries/SDL/include/SDL_main.h \
    BallCommunication/Libraries/SDL/include/SDL_mixer.h \
    BallCommunication/Libraries/SDL/include/SDL_mouse.h \
    BallCommunication/Libraries/SDL/include/SDL_mutex.h \
    BallCommunication/Libraries/SDL/include/SDL_name.h \
    BallCommunication/Libraries/SDL/include/SDL_net.h \
    BallCommunication/Libraries/SDL/include/SDL_opengl.h \
    BallCommunication/Libraries/SDL/include/SDL_platform.h \
    BallCommunication/Libraries/SDL/include/SDL_quit.h \
    BallCommunication/Libraries/SDL/include/SDL_rwops.h \
    BallCommunication/Libraries/SDL/include/SDL_stdinc.h \
    BallCommunication/Libraries/SDL/include/SDL_syswm.h \
    BallCommunication/Libraries/SDL/include/SDL_thread.h \
    BallCommunication/Libraries/SDL/include/SDL_timer.h \
    BallCommunication/Libraries/SDL/include/SDL_ttf.h \
    BallCommunication/Libraries/SDL/include/SDL_types.h \
    BallCommunication/Libraries/SDL/include/SDL_version.h \
    BallCommunication/Libraries/SDL/include/SDL_video.h \
    BallCommunication/Networking/BallCommunicator/BallCommunicator.h \
    BallCommunication/Networking/BallCommunicator/BallCommunicator_UDP.h \
    BallCommunication/Networking/Network/Network.h \
    BallCommunication/Networking/Network/UDPClientSession.h \
    BallCommunication/Networking/Network/UDPServerSession.h \
    BallCommunication/Networking/RS232C/rs232c.h \
    BallCommunication/Networking/Timer/Timer.h \
    BallCommunication/Utilities/AccelerometerCalibrator/AccelerometerCalibrator.h \
    BallCommunication/Utilities/GyroCalibrator/GyroCalibrator.h \
    BallCommunication/ballcommunication.h \
    BallCommunication/declaration.h \
    GestureRecognition/gesturerecognition.h \
    mainlogic.h \
    monitorview.h \
    training.h \
    trainingview.h \
    GestureRecognition/event_type_converter.h \
    GestureRecognition/file_parsing.h \
    GestureRecognition/GRT_helper.h \
    GestureRecognition/sensor_events.h \
    GestureRecognition/recognizer.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/AdaBoost/WeakClassifiers/DecisionStump.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/AdaBoost/WeakClassifiers/RadialBasisFunction.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/AdaBoost/WeakClassifiers/WeakClassifier.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/AdaBoost/AdaBoost.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/AdaBoost/AdaBoostClassModel.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/ANBC/ANBC.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/ANBC/ANBC_Model.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/BAG/BAG.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/DecisionTree/DecisionTree.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/DecisionTree/DecisionTreeClusterNode.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/DecisionTree/DecisionTreeNode.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/DecisionTree/DecisionTreeThresholdNode.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/DecisionTree/DecisionTreeTripleFeatureNode.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/DTW/DTW.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/FiniteStateMachine/FiniteStateMachine.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/FiniteStateMachine/FSMParticle.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/FiniteStateMachine/FSMParticleFilter.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/GMM/GMM.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/GMM/MixtureModel.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/HMM/ContinuousHiddenMarkovModel.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/HMM/DiscreteHiddenMarkovModel.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/HMM/HMM.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/HMM/HMMEnums.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/KNN/KNN.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/LDA/LDA.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/MinDist/MinDist.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/MinDist/MinDistModel.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/ParticleClassifier/ParticleClassifier.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/ParticleClassifier/ParticleClassifierParticleFilter.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/RandomForests/RandomForests.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/Softmax/Softmax.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/Softmax/SoftmaxModel.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/SVM/LIBSVM/libsvm.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/SVM/SVM.h \
    GestureRecognition/Libraries/GRT/ClassificationModules/SwipeDetector/SwipeDetector.h \
    GestureRecognition/Libraries/GRT/ClusteringModules/ClusterTree/ClusterTree.h \
    GestureRecognition/Libraries/GRT/ClusteringModules/ClusterTree/ClusterTreeNode.h \
    GestureRecognition/Libraries/GRT/ClusteringModules/GaussianMixtureModels/GaussianMixtureModels.h \
    GestureRecognition/Libraries/GRT/ClusteringModules/HierarchicalClustering/HierarchicalClustering.h \
    GestureRecognition/Libraries/GRT/ClusteringModules/KMeans/KMeans.h \
    GestureRecognition/Libraries/GRT/ClusteringModules/SelfOrganizingMap/SelfOrganizingMap.h \
    GestureRecognition/Libraries/GRT/ContextModules/Gate.h \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/BernoulliRBM/BernoulliRBM.h \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/EvolutionaryAlgorithm/EvolutionaryAlgorithm.h \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/EvolutionaryAlgorithm/Individual.h \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/GridSearch/GridSearch.h \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/LeastSquares/LinearLeastSquares.h \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/MeanShift/MeanShift.h \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/MovementDetector/MovementDetector.h \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/ParticleFilter/Particle.h \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/ParticleFilter/ParticleFilter.h \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/ParticleSwarmOptimization/ParticleSwarmOptimization.h \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/ParticleSwarmOptimization/PSOParticle.h \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/PrincipalComponentAnalysis/PrincipalComponentAnalysis.h \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/Tree/Node.h \
    GestureRecognition/Libraries/GRT/CoreAlgorithms/Tree/Tree.h \
    GestureRecognition/Libraries/GRT/CoreModules/Classifier.h \
    GestureRecognition/Libraries/GRT/CoreModules/Clusterer.h \
    GestureRecognition/Libraries/GRT/CoreModules/Context.h \
    GestureRecognition/Libraries/GRT/CoreModules/FeatureExtraction.h \
    GestureRecognition/Libraries/GRT/CoreModules/GestureRecognitionPipeline.h \
    GestureRecognition/Libraries/GRT/CoreModules/GRTBase.h \
    GestureRecognition/Libraries/GRT/CoreModules/MLBase.h \
    GestureRecognition/Libraries/GRT/CoreModules/PostProcessing.h \
    GestureRecognition/Libraries/GRT/CoreModules/PreProcessing.h \
    GestureRecognition/Libraries/GRT/CoreModules/Regressifier.h \
    GestureRecognition/Libraries/GRT/DataStructures/ClassificationData.h \
    GestureRecognition/Libraries/GRT/DataStructures/ClassificationSample.h \
    GestureRecognition/Libraries/GRT/DataStructures/RegressionData.h \
    GestureRecognition/Libraries/GRT/DataStructures/RegressionSample.h \
    GestureRecognition/Libraries/GRT/DataStructures/TimeSeriesClassificationData.h \
    GestureRecognition/Libraries/GRT/DataStructures/TimeSeriesClassificationDataStream.h \
    GestureRecognition/Libraries/GRT/DataStructures/TimeSeriesClassificationSample.h \
    GestureRecognition/Libraries/GRT/DataStructures/TimeSeriesPositionTracker.h \
    GestureRecognition/Libraries/GRT/DataStructures/UnlabelledData.h \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/FFT/FastFourierTransform.h \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/FFT/FFT.h \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/FFT/FFTFeatures.h \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/KMeansFeatures/KMeansFeatures.h \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/KMeansQuantizer/KMeansQuantizer.h \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/MovementIndex/MovementIndex.h \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/MovementTrajectoryFeatures/MovementTrajectoryFeatures.h \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/RBMQuantizer/RBMQuantizer.h \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/SOMQuantizer/SOMQuantizer.h \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/TimeDomainFeatures/TimeDomainFeatures.h \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/TimeseriesBuffer/TimeseriesBuffer.h \
    GestureRecognition/Libraries/GRT/FeatureExtractionModules/ZeroCrossingCounter/ZeroCrossingCounter.h \
    GestureRecognition/Libraries/GRT/PostProcessingModules/ClassLabelChangeFilter.h \
    GestureRecognition/Libraries/GRT/PostProcessingModules/ClassLabelFilter.h \
    GestureRecognition/Libraries/GRT/PostProcessingModules/ClassLabelTimeoutFilter.h \
    GestureRecognition/Libraries/GRT/PreProcessingModules/DeadZone.h \
    GestureRecognition/Libraries/GRT/PreProcessingModules/Derivative.h \
    GestureRecognition/Libraries/GRT/PreProcessingModules/DoubleMovingAverageFilter.h \
    GestureRecognition/Libraries/GRT/PreProcessingModules/FIRFilter.h \
    GestureRecognition/Libraries/GRT/PreProcessingModules/HighPassFilter.h \
    GestureRecognition/Libraries/GRT/PreProcessingModules/LeakyIntegrator.h \
    GestureRecognition/Libraries/GRT/PreProcessingModules/LowPassFilter.h \
    GestureRecognition/Libraries/GRT/PreProcessingModules/MedianFilter.h \
    GestureRecognition/Libraries/GRT/PreProcessingModules/MovingAverageFilter.h \
    GestureRecognition/Libraries/GRT/PreProcessingModules/SavitzkyGolayFilter.h \
    GestureRecognition/Libraries/GRT/RegressionModules/ArtificialNeuralNetworks/MLP/MLP.h \
    GestureRecognition/Libraries/GRT/RegressionModules/ArtificialNeuralNetworks/MLP/Neuron.h \
    GestureRecognition/Libraries/GRT/RegressionModules/LinearRegression/LinearRegression.h \
    GestureRecognition/Libraries/GRT/RegressionModules/LogisticRegression/LogisticRegression.h \
    GestureRecognition/Libraries/GRT/RegressionModules/MultidimensionalRegression/MultidimensionalRegression.h \
    GestureRecognition/Libraries/GRT/RegressionModules/RegressionTree/RegressionTree.h \
    GestureRecognition/Libraries/GRT/RegressionModules/RegressionTree/RegressionTreeNode.h \
    GestureRecognition/Libraries/GRT/Util/Cholesky.h \
    GestureRecognition/Libraries/GRT/Util/CircularBuffer.h \
    GestureRecognition/Libraries/GRT/Util/ClassificationResult.h \
    GestureRecognition/Libraries/GRT/Util/ClassTracker.h \
    GestureRecognition/Libraries/GRT/Util/CommandLineParser.h \
    GestureRecognition/Libraries/GRT/Util/DebugLog.h \
    GestureRecognition/Libraries/GRT/Util/EigenvalueDecomposition.h \
    GestureRecognition/Libraries/GRT/Util/ErrorLog.h \
    GestureRecognition/Libraries/GRT/Util/FileParser.h \
    GestureRecognition/Libraries/GRT/Util/GRTCommon.h \
    GestureRecognition/Libraries/GRT/Util/GRTException.h \
    GestureRecognition/Libraries/GRT/Util/GRTTypedefs.h \
    GestureRecognition/Libraries/GRT/Util/GRTVersionInfo.h \
    GestureRecognition/Libraries/GRT/Util/IndexedDouble.h \
    GestureRecognition/Libraries/GRT/Util/InfoLog.h \
    GestureRecognition/Libraries/GRT/Util/Log.h \
    GestureRecognition/Libraries/GRT/Util/LUDecomposition.h \
    GestureRecognition/Libraries/GRT/Util/Matrix.h \
    GestureRecognition/Libraries/GRT/Util/MatrixDouble.h \
    GestureRecognition/Libraries/GRT/Util/MinMax.h \
    GestureRecognition/Libraries/GRT/Util/Observer.h \
    GestureRecognition/Libraries/GRT/Util/ObserverManager.h \
    GestureRecognition/Libraries/GRT/Util/PeakDetection.h \
    GestureRecognition/Libraries/GRT/Util/Random.h \
    GestureRecognition/Libraries/GRT/Util/RangeTracker.h \
    GestureRecognition/Libraries/GRT/Util/SVD.h \
    GestureRecognition/Libraries/GRT/Util/TestingLog.h \
    GestureRecognition/Libraries/GRT/Util/TestInstanceResult.h \
    GestureRecognition/Libraries/GRT/Util/TestResult.h \
    GestureRecognition/Libraries/GRT/Util/ThreadPool.h \
    GestureRecognition/Libraries/GRT/Util/ThresholdCrossingDetector.h \
    GestureRecognition/Libraries/GRT/Util/Timer.h \
    GestureRecognition/Libraries/GRT/Util/TimeSeriesClassificationSampleTrimmer.h \
    GestureRecognition/Libraries/GRT/Util/TimeStamp.h \
    GestureRecognition/Libraries/GRT/Util/TrainingDataRecordingTimer.h \
    GestureRecognition/Libraries/GRT/Util/TrainingLog.h \
    GestureRecognition/Libraries/GRT/Util/TrainingResult.h \
    GestureRecognition/Libraries/GRT/Util/util.h \
    GestureRecognition/Libraries/GRT/Util/WarningLog.h \
    GestureRecognition/Libraries/GRT/GRT.h \
    recognitionview.h \
    BallCommunication/ballcommunicationbase.h \
    BallCommunication/ballcommunicationfake.h

FORMS    += mainwindow.ui \
    monitorview.ui \
    trainingview.ui \
    recognitionview.ui

SUBDIRS += \
    BallCommunication/BallCommunication.pro \
    GestureRecognition/GestureRecognition.pro

DISTFILES += \
    BallCommunication/Libraries/SDL/x64/lib/libfreetype-6.lib \
    BallCommunication/Libraries/SDL/x64/lib/SDL.lib \
    BallCommunication/Libraries/SDL/x64/lib/SDL_image.lib \
    BallCommunication/Libraries/SDL/x64/lib/SDL_mixer.lib \
    BallCommunication/Libraries/SDL/x64/lib/SDL_net.lib \
    BallCommunication/Libraries/SDL/x64/lib/SDL_ttf.lib \
    BallCommunication/Libraries/SDL/x64/lib/SDLmain.lib \
    BallCommunication/Libraries/SDL/x86/lib/libfreetype-6.lib \
    BallCommunication/Libraries/SDL/x86/lib/SDL.lib \
    BallCommunication/Libraries/SDL/x86/lib/SDL_image.lib \
    BallCommunication/Libraries/SDL/x86/lib/SDL_mixer.lib \
    BallCommunication/Libraries/SDL/x86/lib/SDL_net.lib \
    BallCommunication/Libraries/SDL/x86/lib/SDL_ttf.lib \
    BallCommunication/Libraries/SDL/x86/lib/SDLmain.lib \
    BallCommunication/Libraries/bin86/jpeg.dll \
    BallCommunication/Libraries/bin86/libfreetype-6.dll \
    BallCommunication/Libraries/bin86/libjpeg-8.dll \
    BallCommunication/Libraries/bin86/libogg-0.dll \
    BallCommunication/Libraries/bin86/libpng12-0.dll \
    BallCommunication/Libraries/bin86/libpng15-15.dll \
    BallCommunication/Libraries/bin86/libtiff-3.dll \
    BallCommunication/Libraries/bin86/libtiff-5.dll \
    BallCommunication/Libraries/bin86/libvorbis-0.dll \
    BallCommunication/Libraries/bin86/libvorbisfile-3.dll \
    BallCommunication/Libraries/bin86/libwebp-2.dll \
    BallCommunication/Libraries/bin86/mikmod.dll \
    BallCommunication/Libraries/bin86/SDL.dll \
    BallCommunication/Libraries/bin86/SDL_image.dll \
    BallCommunication/Libraries/bin86/SDL_mixer.dll \
    BallCommunication/Libraries/bin86/SDL_net.dll \
    BallCommunication/Libraries/bin86/SDL_ttf.dll \
    BallCommunication/Libraries/bin86/smpeg.dll \
    BallCommunication/Libraries/bin86/tbb.dll \
    BallCommunication/Libraries/bin86/tbb_debug.dll \
    BallCommunication/Libraries/bin86/zlib1.dll \
    BallCommunication/Data/Config/acceleration345Offset0.dat \
    BallCommunication/Data/Config/accelerationOffset0.dat \
    BallCommunication/Data/Config/communicator.conf \
    BallCommunication/Data/Config/gyroOffset0.dat \
    BallCommunication/Libraries/SDL/include/doxyfile \
    BallCommunication/.gitignore \
    data/conf/acceleration345Offset0.dat \
    data/conf/accelerationOffset0.dat \
    data/conf/communicator.conf \
    data/conf/gyroOffset0.dat \
    data/training_files/ground.dat \
    data/training_files/ground_events.dat \
    data/training_files/tableself.dat \
    data/training_files/tableself_events.dat \
    GestureRecognition/.gitignore \
    .gitignore
