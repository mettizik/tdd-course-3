/*
Timer
Implement a timer class that implements the interface ITimer which is defined below.
Follow this specification:

Timer allows to determine if specific period of time expired or not since Start was called last time
Timer allows to determine how much time left till period is expired
Timer can be (re-)started any time, no metter in what state it is
*/

#include <gtest/gtest.h>
#include <chrono>

using namespace std::chrono;
typedef high_resolution_clock Clock;
typedef Clock::duration Duration;
typedef time_point<Clock> TimePoint;
static const Duration s_zeroDuration(microseconds(0));

class Time
{
public:
    Time()
    {
        m_timePassed = s_zeroDuration;
    }

    Duration Now() const
    {
        return m_timePassed;
    }

    void Wait(const Duration& duration)
    {
        m_timePassed += duration;
    }

    Duration TimePassed() const
    {
        return m_timePassed;
    }

private:
    Duration m_timePassed;
};

class Timer {
public:
    Timer(const Duration& duration, const Time& time)
        : m_duration(duration)
        , m_time(time)
        , m_start(time.Now())
    {}

    virtual ~Timer() {}

    virtual void Start()
    {
        m_start = m_time.Now();
    }

    virtual bool IsExpired() const
    {
        return TimeLeft() == s_zeroDuration;
    }

    virtual Duration TimeLeft() const
    {
        return std::max(m_start + m_duration - m_time.TimePassed(), s_zeroDuration);
    }
private:
    const Duration m_duration;
    Duration m_start;
    const Time& m_time;
};


TEST(Timer, TimeLeftWithoutStartReturnsInitialTime)
{
    Timer timer(seconds(1), Time());
    EXPECT_EQ(seconds(1), timer.TimeLeft());
}

TEST(Timer, TimeLeftReturns0AfterInitialTimePassed)
{
    Time time;
    Timer timer(seconds(1), time);
    timer.Start();
    time.Wait(seconds(1));
    EXPECT_EQ(s_zeroDuration, timer.TimeLeft());
}

TEST(Timer, TimeExpiredReturnTrueOnFinish)
{
    Time time;
    Timer timer(seconds(1), time);
    timer.Start();
    time.Wait(seconds(1));
    EXPECT_TRUE(timer.IsExpired());
}

TEST(Timer, TimeExpiredReturnTrueIfPassed2Seconds)
{
    Time time;
    Timer timer(seconds(1), time);
    timer.Start();
    time.Wait(seconds(2));
    EXPECT_TRUE(timer.IsExpired());
}

TEST(Timer, TimerCanBeStartedAfterExpired)
{
    Time time;
    Timer timer(seconds(1), time);
    timer.Start();
    time.Wait(seconds(2));
    timer.Start();
    EXPECT_EQ(seconds(1), timer.TimeLeft());
}
