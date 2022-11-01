#include "deltaTime.hpp"
#include <chrono>
#include <ctime>

using namespace std;
using namespace chrono;

void deltaTime::calculateDTime(){
    currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = currentTime - previousTime;
    dTime = elapsed_seconds.count();
    previousTime = currentTime;
}

double deltaTime::getDTime(){
    return dTime;
}
