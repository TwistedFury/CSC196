#pragma once
#include "Time.h"

void swaws::Time::Tick()
{
    auto now = clock::now();
    m_deltaTime = std::chrono::duration<float>(now - m_frameTime).count();
    m_time = std::chrono::duration<float>(now - m_startTime).count();
    m_frameTime = now;
}
