#include <chrono>

class deltaTime{
private:
    inline static double dTime = 0.0f;
    inline static auto previousTime = std::chrono::system_clock::now();
    inline static auto currentTime = std::chrono::system_clock::now();
public:
    static void calculateDTime();
    static double getDTime();
};
