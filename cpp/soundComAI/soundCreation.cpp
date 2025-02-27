#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>
#include <iostream>

const int SAMPLE_RATE = 44100;
const int AMPLITUDE = 30000;
const float DURATION = 0.02f; // Duration of each letter's sound

// Function to generate a sine wave buffer for a given frequency
sf::SoundBuffer generateSineWave(float frequency) {
    int sampleCount = static_cast<int>(SAMPLE_RATE * DURATION);
    std::vector<sf::Int16> samples(sampleCount);

    for (int i = 0; i < sampleCount; i++) {
        float t = static_cast<float>(i) / SAMPLE_RATE;
        samples[i] = static_cast<sf::Int16>(AMPLITUDE * sin(2 * M_PI * frequency * t));
    }

    sf::SoundBuffer buffer;
    buffer.loadFromSamples(samples.data(), samples.size(), 1, SAMPLE_RATE);
    return buffer;
}

// Assigning a unique frequency to each letter (A-Z)
float getLetterFrequency(char letter) {
    if (letter >= 'A' && letter <= 'Z') {
        return 440.0f + (letter - 'A') * 20.0f; // Base frequency: 440Hz, step: 20Hz
    }
    return 0.0f; // No sound for unsupported characters
}

int main() {
    std::string message;
    std::cout << "Enter a message (A-Z only): ";
    std::cin >> message;
    
    sf::Sound sound;
    std::vector<sf::SoundBuffer> buffers;

    for (char &c : message) {
        c = toupper(c);
        float frequency = getLetterFrequency(c);
        if (frequency > 0.0f) {
            buffers.push_back(generateSineWave(frequency));
            sound.setBuffer(buffers.back());
            sound.play();
            sf::sleep(sf::seconds(DURATION + 0.01f)); // Play duration + small pause
        }
    }
    return 0;
}

