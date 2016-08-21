#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <cassert>
#include <chrono>
#include <random>
#include <sstream>

class Random
{
    public:
        Random()
        {
            std::ostringstream oss;
            oss << std::chrono::system_clock::now().time_since_epoch().count();
            setSeed(oss.str());
        }

        Random(std::string const& seed)
        {
            setSeed(seed);
        }

        int operator()(int min, int max)
        {
            assert(min <= max);
            std::uniform_int_distribution<int> distribution(min, max);
            return distribution(mGenerator);
        }

        unsigned int operator()(unsigned int min, unsigned int max)
        {
            assert(min <= max);
            std::uniform_int_distribution<unsigned int> distribution(min, max);
            return distribution(mGenerator);
        }

        float operator()(float min, float max)
        {
            assert(min <= max);
            std::uniform_real_distribution<float> distribution(min, max);
            return distribution(mGenerator);
        }

        void setSeed(std::string const& seed)
        {
            mSeed = seed;
            std::seed_seq s(mSeed.begin(), mSeed.end());
            mGenerator.seed(s);
        }

        std::string getSeed() const
        {
            return mSeed;
        }

        static Random& instance()
        {
            return mRandom;
        }

    private:
        static Random mRandom;
        std::mt19937 mGenerator;
        std::string mSeed;
};

int random(int min, int max);

unsigned int random(unsigned int min, unsigned int max);

bool randomBool();

float random(float min, float max);

float randomDev(float middle, float deviation);

void setRandomSeed(std::string const& seed);

std::string getRandomSeed();

#endif // RANDOM_HPP
