#include "MinMaxQueueTest.h"

#include <chrono>
#include <thread>


#define PushTest(val)           \
    m_queue.push(val);          \
    EXPECT_EQ(queueSize(), 1);  \


#define PopTest(val)                      \
    const auto testValue = val;           \
    m_queue.push(testValue);              \
    ASSERT_EQ(queueSize(), 1);            \
    EXPECT_EQ(m_queue.pop(), testValue);  \
    EXPECT_EQ(queueSize(), 0);            \


#define MinMaxTest(val, val2)              \
    const auto testValue = val;            \
    m_queue.push(testValue);               \
                                           \
    const auto testValue2 = val2;          \
    m_queue.push(testValue2);              \
                                           \
    ASSERT_EQ(queueSize(), 2);             \
    EXPECT_EQ(m_queue.min(), testValue);   \
    EXPECT_EQ(m_queue.max(), testValue2);  \


#define MultithreadPush(val)                                          \
    const auto testValue = val;                                       \
    std::thread t1([this, testValue](){ m_queue.push(testValue); });  \
    std::thread t2([this, testValue](){ m_queue.push(testValue); });  \
    std::thread t3([this, testValue](){ m_queue.push(testValue); });  \
                                                                      \
    t1.join();                                                        \
    t2.join();                                                        \
    t3.join();                                                        \
                                                                      \
    EXPECT_EQ(queueSize(), 3);                                        \


#define MultithreadPop(val)                      \
    const auto testValue = val;                  \
                                                 \
    m_queue.push(testValue);                     \
    m_queue.push(testValue);                     \
    m_queue.push(testValue);                     \
                                                 \
    ASSERT_EQ(queueSize(), 3);                   \
                                                 \
    std::thread t1([this](){ m_queue.pop(); });  \
    std::thread t2([this](){ m_queue.pop(); });  \
    std::thread t3([this](){ m_queue.pop(); });  \
                                                 \
    t1.join();                                   \
    t2.join();                                   \
    t3.join();                                   \
                                                 \
    EXPECT_EQ(queueSize(), 0);                   \


#define PushTimeComplexity(val)                                                                             \
    auto startTime = std::chrono::system_clock::now();                                                      \
    m_queue.push(val);                                                                                      \
    auto endTime = std::chrono::system_clock::now();                                                        \
                                                                                                            \
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();  \
                                                                                                            \
    int64_t accumTime = 0;                                                                                  \
    for (size_t i = 0; i < 1000000; ++i)                                                                    \
    {                                                                                                       \
        startTime = std::chrono::system_clock::now();                                                       \
        m_queue.push(val);                                                                                  \
        endTime = std::chrono::system_clock::now();                                                         \
                                                                                                            \
        accumTime += std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();    \
    }                                                                                                       \
                                                                                                            \
    EXPECT_EQ(elapsedTime, accumTime);                                                                      \


#define PopTimeComplexity(val)                                                                              \
    m_queue.push(val);                                                                                      \
    auto startTime = std::chrono::system_clock::now();                                                      \
    m_queue.pop();                                                                                          \
    auto endTime = std::chrono::system_clock::now();                                                        \
                                                                                                            \
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();  \
                                                                                                            \
    int64_t accumTime = 0;                                                                                  \
    for (size_t i = 0; i < 1000000; ++i)                                                                    \
    {                                                                                                       \
        m_queue.push(val);                                                                                  \
        startTime = std::chrono::system_clock::now();                                                       \
        m_queue.pop();                                                                                      \
        endTime = std::chrono::system_clock::now();                                                         \
                                                                                                            \
        accumTime += std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();    \
    }                                                                                                       \
                                                                                                            \
    EXPECT_EQ(elapsedTime, accumTime);                                                                      \


#define MinTimeComplexity(val)                                                                              \
    m_queue.push(val);                                                                                      \
    auto startTime = std::chrono::system_clock::now();                                                      \
    m_queue.min();                                                                                          \
    auto endTime = std::chrono::system_clock::now();                                                        \
                                                                                                            \
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();  \
                                                                                                            \
    int64_t accumTime = 0;                                                                                  \
    for (size_t i = 0; i < 1000000; ++i)                                                                    \
    {                                                                                                       \
        m_queue.push(val);                                                                                  \
        startTime = std::chrono::system_clock::now();                                                       \
        m_queue.min();                                                                                      \
        endTime = std::chrono::system_clock::now();                                                         \
                                                                                                            \
        accumTime += std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();    \
    }                                                                                                       \
                                                                                                            \
    EXPECT_EQ(elapsedTime, accumTime);                                                                      \


#define MaxTimeComplexity(val)                                                                              \
    m_queue.push(val);                                                                                      \
    auto startTime = std::chrono::system_clock::now();                                                      \
    m_queue.max();                                                                                          \
    auto endTime = std::chrono::system_clock::now();                                                        \
                                                                                                            \
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();  \
                                                                                                            \
    int64_t accumTime = 0;                                                                                  \
    for (size_t i = 0; i < 1000000; ++i)                                                                    \
    {                                                                                                       \
        m_queue.push(val);                                                                                  \
        startTime = std::chrono::system_clock::now();                                                       \
        m_queue.max();                                                                                      \
        endTime = std::chrono::system_clock::now();                                                         \
                                                                                                            \
        accumTime += std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();    \
    }                                                                                                       \
                                                                                                            \
    EXPECT_EQ(elapsedTime, accumTime);                                                                      \
    

TEST_F(IntMinMaxQueueTestFixture, IntPushTest)
{
    PushTest(0)
}

TEST_F(StringMinMaxQueueTestFixture, StringPushTest)
{
    PushTest("a")
}

TEST_F(UserTypeMinMaxQueueTestFixture, UserTypePushTest)
{
    PushTest(A(0))
}

TEST_F(IntMinMaxQueueTestFixture, IntPopTest)
{
    PopTest(0)
}

TEST_F(StringMinMaxQueueTestFixture, StringPopTest)
{
    PopTest(std::string("a"))
}

TEST_F(UserTypeMinMaxQueueTestFixture, UserTypePopTest)
{
    PopTest(A(0))
}

TEST_F(IntMinMaxQueueTestFixture, IntMinMaxTest)
{
    MinMaxTest(0, 1)
}

TEST_F(StringMinMaxQueueTestFixture, StringMinMaxTest)
{
    MinMaxTest(std::string("a"), std::string("b"))
}

TEST_F(UserTypeMinMaxQueueTestFixture, UserTypeMinMaxTest)
{
    MinMaxTest(A(0), A(1))
}

TEST_F(IntMinMaxQueueTestFixture, IntMultithreadPush)
{
    MultithreadPush(0)
}

TEST_F(StringMinMaxQueueTestFixture, StringMultithreadPush)
{
    MultithreadPush(std::string("a"))
}

TEST_F(UserTypeMinMaxQueueTestFixture, UserTypeMultithreadPush)
{
    MultithreadPush(A(0))
}

TEST_F(IntMinMaxQueueTestFixture, IntMultithreadPop)
{
    MultithreadPop(0)
}

TEST_F(StringMinMaxQueueTestFixture, StringMultithreadPop)
{
    MultithreadPop(std::string("a"))
}

TEST_F(UserTypeMinMaxQueueTestFixture, UserTypeMultithreadPop)
{
    MultithreadPop(A(0))
}

TEST_F(IntMinMaxQueueTestFixture, IntPopEmptyQueue)
{
    EXPECT_DEATH(m_queue.pop(), ".*");
}

TEST_F(StringMinMaxQueueTestFixture, StringPopEmptyQueue)
{
    EXPECT_DEATH(m_queue.pop(), ".*");
}

TEST_F(UserTypeMinMaxQueueTestFixture, UserTypePopEmptyQueue)
{
    EXPECT_DEATH(m_queue.pop(), ".*");
}

TEST_F(IntMinMaxQueueTestFixture, IntMinMaxEmptyQueue)
{
    EXPECT_DEATH(m_queue.min(), ".*");
    EXPECT_DEATH(m_queue.max(), ".*");
}

TEST_F(StringMinMaxQueueTestFixture, StringMinMaxEmptyQueue)
{
    EXPECT_DEATH(m_queue.min(), ".*");
    EXPECT_DEATH(m_queue.max(), ".*");
}

TEST_F(UserTypeMinMaxQueueTestFixture, UserTypeMinMaxEmptyQueue)
{
    EXPECT_DEATH(m_queue.min(), ".*");
    EXPECT_DEATH(m_queue.max(), ".*");
}

TEST_F(IntMinMaxQueueTestFixture, IntPushTimeComplexity)
{
    PushTimeComplexity(0)
}

TEST_F(StringMinMaxQueueTestFixture, StringPushTimeComplexity)
{
    PushTimeComplexity("a")
}

TEST_F(UserTypeMinMaxQueueTestFixture, UserTypePushTimeComplexity)
{
    PushTimeComplexity(A(0))
}

TEST_F(IntMinMaxQueueTestFixture, IntPopTimeComplexity)
{
    PopTimeComplexity(0)
}

TEST_F(StringMinMaxQueueTestFixture, StringPopTimeComplexity)
{
    PopTimeComplexity("a")
}

TEST_F(UserTypeMinMaxQueueTestFixture, UserTypePopTimeComplexity)
{
    PopTimeComplexity(A(0))
}

TEST_F(IntMinMaxQueueTestFixture, IntMinTimeComplexity)
{
    MinTimeComplexity(0)
}

TEST_F(StringMinMaxQueueTestFixture, StringMinTimeComplexity)
{
    MinTimeComplexity("a")
}

TEST_F(UserTypeMinMaxQueueTestFixture, UserTypeMinTimeComplexity)
{
    MinTimeComplexity(A(0))
}

TEST_F(IntMinMaxQueueTestFixture, IntMaxTimeComplexity)
{
    MaxTimeComplexity(0)
}

TEST_F(StringMinMaxQueueTestFixture, StringMaxTimeComplexity)
{
    MaxTimeComplexity("a")
}

TEST_F(UserTypeMinMaxQueueTestFixture, UserTypeMaxTimeComplexity)
{
    MaxTimeComplexity(A(0))
}