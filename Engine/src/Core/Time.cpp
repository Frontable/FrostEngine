

#include "Core/Time.h"
#include <chrono>

namespace FrostEngine
{

    double Time::NowSeconds()
    {
        using clock = std::chrono::high_resolution_clock;
        return std::chrono::duration<double>(clock::now().time_since_epoch()).count();
    }

}


