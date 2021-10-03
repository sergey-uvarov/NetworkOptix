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


#define PushPopMinMaxTest(val, val2, val3, val4) \
    auto testValue = val;                          \
    auto testValue2 = val2;                         \
    auto testValue3 = val3;                         \
    auto testValue4 = val4;                         \
                                                 \
    m_queue.push(testValue);                     \
    m_queue.push(testValue2);                    \
    m_queue.push(testValue3);                    \
    m_queue.push(testValue4);                    \
                                                 \
    EXPECT_EQ(m_queue.min(), testValue);         \
    EXPECT_EQ(m_queue.max(), testValue2);        \
                                                 \
    m_queue.pop();                               \
                                                 \
    EXPECT_EQ(m_queue.min(), testValue4);        \
    EXPECT_EQ(m_queue.max(), testValue2);        \
                                                 \
    m_queue.pop();                               \
                                                 \
    EXPECT_EQ(m_queue.min(), testValue4);        \
    EXPECT_EQ(m_queue.max(), testValue3);        \


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

TEST_F(IntMinMaxQueueTestFixture, IntPushPopMinMaxTest)
{
    PushPopMinMaxTest(0, 3, 2, 1)
}

TEST_F(StringMinMaxQueueTestFixture, StringPushPopMinMaxTest)
{
    PushPopMinMaxTest(std::string("a"), std::string("d"), std::string("c"), std::string("b"))
}

TEST_F(UserTypeMinMaxQueueTestFixture, UserTypePushPopMinMaxTest)
{
    PushPopMinMaxTest(A(0), A(3), A(2), A(1))
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
    ASSERT_DEATH(m_queue.pop(), ".*");
}

TEST_F(StringMinMaxQueueTestFixture, StringPopEmptyQueue)
{
    ASSERT_DEATH(m_queue.pop(), ".*");
}

TEST_F(UserTypeMinMaxQueueTestFixture, UserTypePopEmptyQueue)
{
    ASSERT_DEATH(m_queue.pop(), ".*");
}

TEST_F(IntMinMaxQueueTestFixture, IntMinEmptyQueue)
{
    ASSERT_DEATH(m_queue.min(), ".*");
}

TEST_F(IntMinMaxQueueTestFixture, IntMaxEmptyQueue)
{
    ASSERT_DEATH(m_queue.max(), ".*");
}

TEST_F(StringMinMaxQueueTestFixture, StringMinEmptyQueue)
{
    ASSERT_DEATH(m_queue.min(), ".*");
}

TEST_F(StringMinMaxQueueTestFixture, StringMaxEmptyQueue)
{
    ASSERT_DEATH(m_queue.max(), ".*");
}

TEST_F(UserTypeMinMaxQueueTestFixture, UserTypeMinEmptyQueue)
{
    ASSERT_DEATH(m_queue.min(), ".*");
}

TEST_F(UserTypeMinMaxQueueTestFixture, UserTypeMaxEmptyQueue)
{
    ASSERT_DEATH(m_queue.max(), ".*");
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

TEST_F(IntMinMaxQueueTestFixture, IntMinMaxComplexTest)
{
    m_queue.push(2);

    EXPECT_EQ(m_queue.min(), 2);
    EXPECT_EQ(m_queue.max(), 2);

    m_queue.push(4);

    EXPECT_EQ(m_queue.min(), 2);
    EXPECT_EQ(m_queue.max(), 4);

    m_queue.push(4);

    EXPECT_EQ(m_queue.min(), 2);
    EXPECT_EQ(m_queue.max(), 4);

    m_queue.push(3);

    EXPECT_EQ(m_queue.min(), 2);
    EXPECT_EQ(m_queue.max(), 4);

    m_queue.push(5);

    EXPECT_EQ(m_queue.min(), 2);
    EXPECT_EQ(m_queue.max(), 5);

    m_queue.push(0);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 5);

    m_queue.push(1);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 5);

    m_queue.push(2);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 5);

    EXPECT_EQ(m_queue.pop(), 2);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 5);

    EXPECT_EQ(m_queue.pop(), 4);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 5);

    EXPECT_EQ(m_queue.pop(), 4);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 5);

    EXPECT_EQ(m_queue.pop(), 3);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 5);

    EXPECT_EQ(m_queue.pop(), 5);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 2);

    EXPECT_EQ(m_queue.pop(), 0);

    EXPECT_EQ(m_queue.min(), 1);
    EXPECT_EQ(m_queue.max(), 2);

    EXPECT_EQ(m_queue.pop(), 1);

    EXPECT_EQ(m_queue.min(), 2);
    EXPECT_EQ(m_queue.max(), 2);

    EXPECT_EQ(m_queue.pop(), 2);
}

TEST_F(IntMinMaxQueueTestFixture, IntMinMaxAscendingTest)
{
    m_queue.push(0);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 0);

    m_queue.push(1);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 1);

    m_queue.push(2);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 2);

    m_queue.push(3);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 3);

    m_queue.push(4);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 4);

    m_queue.push(5);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 5);

    EXPECT_EQ(m_queue.pop(), 0);

    EXPECT_EQ(m_queue.min(), 1);
    EXPECT_EQ(m_queue.max(), 5);

    EXPECT_EQ(m_queue.pop(), 1);

    EXPECT_EQ(m_queue.min(), 2);
    EXPECT_EQ(m_queue.max(), 5);

    EXPECT_EQ(m_queue.pop(), 2);

    EXPECT_EQ(m_queue.min(), 3);
    EXPECT_EQ(m_queue.max(), 5);

    EXPECT_EQ(m_queue.pop(), 3);

    EXPECT_EQ(m_queue.min(), 4);
    EXPECT_EQ(m_queue.max(), 5);

    EXPECT_EQ(m_queue.pop(), 4);

    EXPECT_EQ(m_queue.min(), 5);
    EXPECT_EQ(m_queue.max(), 5);

    EXPECT_EQ(m_queue.pop(), 5);
}

TEST_F(IntMinMaxQueueTestFixture, IntMinMaxDescendingTest)
{
    m_queue.push(5);

    EXPECT_EQ(m_queue.min(), 5);
    EXPECT_EQ(m_queue.max(), 5);

    m_queue.push(4);

    EXPECT_EQ(m_queue.min(), 4);
    EXPECT_EQ(m_queue.max(), 5);

    m_queue.push(3);

    EXPECT_EQ(m_queue.min(), 3);
    EXPECT_EQ(m_queue.max(), 5);

    m_queue.push(2);

    EXPECT_EQ(m_queue.min(), 2);
    EXPECT_EQ(m_queue.max(), 5);

    m_queue.push(1);

    EXPECT_EQ(m_queue.min(), 1);
    EXPECT_EQ(m_queue.max(), 5);

    m_queue.push(0);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 5);

    EXPECT_EQ(m_queue.pop(), 5);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 4);

    EXPECT_EQ(m_queue.pop(), 4);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 3);

    EXPECT_EQ(m_queue.pop(), 3);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 2);

    EXPECT_EQ(m_queue.pop(), 2);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 1);

    EXPECT_EQ(m_queue.pop(), 1);

    EXPECT_EQ(m_queue.min(), 0);
    EXPECT_EQ(m_queue.max(), 0);

    EXPECT_EQ(m_queue.pop(), 0);
}