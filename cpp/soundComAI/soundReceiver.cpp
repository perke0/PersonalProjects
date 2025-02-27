#include <SFML/Audio.hpp>
#include <fftw3.h>
#include <iostream>
#include <map>
#include <cmath>
#include <thread>

const int SAMPLE_RATE = 44100;
const int BUFFER_SIZE = 1024; // Reduced for faster updates

// Map frequencies back to words/letters
std::map<int, std::string> frequencyToWord = {
    {1000, "Hello"},
    {1050, "World"},
    {1100, "AI"},
    {1150, "Fast"},
    {1200, "Chat"}
};

class SoundReceiver : public sf::SoundRecorder {
protected:
    bool onProcessSamples(const sf::Int16* samples, std::size_t sampleCount) override {
        // Convert samples to double for FFT
        double in[BUFFER_SIZE];
        fftw_complex out[BUFFER_SIZE];
        fftw_plan plan = fftw_plan_dft_r2c_1d(BUFFER_SIZE, in, out, FFTW_ESTIMATE);
        
        for (size_t i = 0; i < BUFFER_SIZE; i++) {
            in[i] = samples[i] / 32768.0; // Normalize samples
        }

        fftw_execute(plan);
        fftw_destroy_plan(plan);

        // Find the dominant frequency quickly
        int maxIndex = 0;
        double maxValue = 0;
        for (size_t i = 10; i < BUFFER_SIZE / 4; i++) { // Ignore very low frequencies
            double magnitude = out[i][0] * out[i][0] + out[i][1] * out[i][1];
            if (magnitude > maxValue) {
                maxValue = magnitude;
                maxIndex = i;
            }
        }

        double dominantFreq = (maxIndex * SAMPLE_RATE) / BUFFER_SIZE;
        std::cout << "Detected Frequency: " << dominantFreq << " Hz\n";

        // Find the closest matching word
        int closestFreq = 0;
        double minDiff = 1e9;
        for (const auto& pair : frequencyToWord) {
            double diff = std::abs(pair.first - dominantFreq);
            if (diff < minDiff) {
                minDiff = diff;
                closestFreq = pair.first;
            }
        }
        
        if (minDiff < 10) { // Allow small error margin
            std::cout << "Recognized: " << frequencyToWord[closestFreq] << "\n";
        }

        return true;
    }
};

int main() {
    if (!sf::SoundRecorder::isAvailable()) {
        std::cerr << "Error: Audio recording not supported!\n";
        return -1;
    }

    SoundReceiver receiver;
    receiver.start(SAMPLE_RATE);
    std::cout << "Listening for AI sounds...\n";

    std::thread inputThread([](){ std::cin.get(); }); // Runs input wait in parallel
    inputThread.join();
    
    receiver.stop();
    return 0;
}

