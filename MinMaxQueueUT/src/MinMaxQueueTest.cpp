#include "MinMaxQueueTest.h"

#include <thread>
#include <optional>


template<class T>
void MinMaxQueueTestFixture<T>::PushTest(const T &value)
{
    m_queue.push(value);
    EXPECT_EQ(m_queue.size(), 1);
}


template<class T>
void MinMaxQueueTestFixture<T>::PopTest(const T &value)
{
    const auto testValue = value;
    m_queue.push(testValue);
    ASSERT_EQ(m_queue.size(), 1);
    EXPECT_EQ(m_queue.pop(), testValue);
    EXPECT_EQ(m_queue.size(), 0);
}


template<class T>
void MinMaxQueueTestFixture<T>::MinMaxTest(const T &value, const T &value2)
{
    const auto testValue = value;
    m_queue.push(testValue);

    const auto testValue2 = value2;
    m_queue.push(testValue2);

    ASSERT_EQ(m_queue.size(), 2);
    EXPECT_EQ(m_queue.min(), testValue);
    EXPECT_EQ(m_queue.max(), testValue2);
}


template<class T>
void MinMaxQueueTestFixture<T>::MinMaxComplexTest(std::vector<T> values)
{
    for (const auto &value: values)
    {
        std::optional<T> queueMin;
        std::optional<T> queueMax;

        if (m_queue.size() > 0)
        {
            queueMin = m_queue.min();
            queueMax = m_queue.max();
        }

        m_queue.push(value);

        auto expectedMin = queueMin && queueMin < value ? queueMin.value() : value;
        auto expectedMax = queueMax && queueMax > value ? queueMax.value() : value;

        EXPECT_EQ(m_queue.min(), expectedMin);
        EXPECT_EQ(m_queue.max(), expectedMax);
    }

    while (m_queue.size() > 1)
    {
        auto popValue = m_queue.pop();
        
        values.erase(values.begin());

        auto min = std::min_element(values.begin(), values.end());
        auto max = std::max_element(values.begin(), values.end());

        EXPECT_EQ(m_queue.min(), *min);
        EXPECT_EQ(m_queue.max(), *max);
    }
}


template<class T>
void MinMaxQueueTestFixture<T>::MultithreadPushTest(const T &value)
{
    const auto testValue = value;
    std::thread t1([this, testValue](){ m_queue.push(testValue); });
    std::thread t2([this, testValue](){ m_queue.push(testValue); });
    std::thread t3([this, testValue](){ m_queue.push(testValue); });

    t1.join();
    t2.join();
    t3.join();

    EXPECT_EQ(m_queue.size(), 3);
}


template<class T>
void MinMaxQueueTestFixture<T>::MultithreadPopTest(const T &value)
{
    const auto testValue = value;

    m_queue.push(testValue);
    m_queue.push(testValue);
    m_queue.push(testValue);

    ASSERT_EQ(m_queue.size(), 3);

    std::thread t1([this](){ m_queue.pop(); });
    std::thread t2([this](){ m_queue.pop(); });
    std::thread t3([this](){ m_queue.pop(); });

    t1.join();
    t2.join();
    t3.join();

    EXPECT_EQ(m_queue.size(), 0);
}


template<class T>
void MinMaxQueueTestFixture<T>::PopEmptyQueueTest()
{
    ASSERT_DEATH(m_queue.pop(), ".*");
}


template<class T>
void MinMaxQueueTestFixture<T>::MinEmptyQueueTest()
{
    ASSERT_DEATH(m_queue.min(), ".*");
}


template<class T>
void MinMaxQueueTestFixture<T>::MaxEmptyQueueTest()
{
    ASSERT_DEATH(m_queue.max(), ".*");
}


TEST_F(IntMinMaxQueueTestFixture, IntPushTest)
{
    PushTest(0);
}


TEST_F(StringMinMaxQueueTestFixture, StringPushTest)
{
    PushTest("a");
}


TEST_F(UserTypeMinMaxQueueTestFixture, UserTypePushTest)
{
    PushTest(A(0));
}


TEST_F(IntMinMaxQueueTestFixture, IntPopTest)
{
    PopTest(0);
}


TEST_F(StringMinMaxQueueTestFixture, StringPopTest)
{
    PopTest(std::string("a"));
}


TEST_F(UserTypeMinMaxQueueTestFixture, UserTypePopTest)
{
    PopTest(A(0));
}


TEST_F(IntMinMaxQueueTestFixture, IntMinMaxTest)
{
    MinMaxTest(0, 1);
}


TEST_F(StringMinMaxQueueTestFixture, StringMinMaxTest)
{
    MinMaxTest(std::string("a"), std::string("b"));
}


TEST_F(UserTypeMinMaxQueueTestFixture, UserTypeMinMaxTest)
{
    MinMaxTest(A(0), A(1));
}


TEST_F(IntMinMaxQueueTestFixture, IntMultithreadPushTest)
{
    MultithreadPushTest(0);
}


TEST_F(StringMinMaxQueueTestFixture, StringMultithreadPushTest)
{
    MultithreadPushTest(std::string("a"));
}


TEST_F(UserTypeMinMaxQueueTestFixture, UserTypeMultithreadPushTest)
{
    MultithreadPushTest(A(0));
}


TEST_F(IntMinMaxQueueTestFixture, IntMultithreadPopTest)
{
    MultithreadPopTest(0);
}


TEST_F(StringMinMaxQueueTestFixture, StringMultithreadPopTest)
{
    MultithreadPopTest(std::string("a"));
}


TEST_F(UserTypeMinMaxQueueTestFixture, UserTypeMultithreadPopTest)
{
    MultithreadPopTest(A(0));
}


TEST_F(IntMinMaxQueueTestFixture, IntPopEmptyQueueTest)
{
    PopEmptyQueueTest();
}


TEST_F(StringMinMaxQueueTestFixture, StringPopEmptyQueueTest)
{
    PopEmptyQueueTest();
}


TEST_F(UserTypeMinMaxQueueTestFixture, UserTypePopEmptyQueueTest)
{
    PopEmptyQueueTest();
}


TEST_F(IntMinMaxQueueTestFixture, IntMinEmptyQueue)
{
    MinEmptyQueueTest();
}


TEST_F(IntMinMaxQueueTestFixture, IntMaxEmptyQueue)
{
    MinEmptyQueueTest();
}


TEST_F(StringMinMaxQueueTestFixture, StringMinEmptyQueue)
{
    MinEmptyQueueTest();
}


TEST_F(StringMinMaxQueueTestFixture, StringMaxEmptyQueue)
{
    MaxEmptyQueueTest();
}


TEST_F(UserTypeMinMaxQueueTestFixture, UserTypeMinEmptyQueue)
{
    MaxEmptyQueueTest();
}


TEST_F(UserTypeMinMaxQueueTestFixture, UserTypeMaxEmptyQueue)
{
    MaxEmptyQueueTest();
}


TEST_F(IntMinMaxQueueTestFixture, IntMinMaxComplexTest)
{
    MinMaxComplexTest({ 2, 4, 4, 3, 5, 0, 1, 2 });
}


TEST_F(StringMinMaxQueueTestFixture, StringMinMaxComplexTest)
{
    MinMaxComplexTest({ "c", "e", "e", "d", "f", "a", "b", "c" });
}


TEST_F(UserTypeMinMaxQueueTestFixture, UserTypeMinMaxComplexTest)
{
    MinMaxComplexTest({ A(2), A(4), A(4), A(3), A(5), A(0), A(1), A(2) });
}


TEST_F(IntMinMaxQueueTestFixture, IntMinMaxAscendingTest)
{
    MinMaxComplexTest({ 0, 1, 2, 3, 4, 5 });
}


TEST_F(StringMinMaxQueueTestFixture, StringMinMaxAscendingTest)
{
    MinMaxComplexTest({ "a", "b", "c", "d", "e", "f" });
}


TEST_F(UserTypeMinMaxQueueTestFixture, UserTypeMinMaxAscendingTest)
{
    MinMaxComplexTest({ A(0), A(1), A(2), A(3), A(4), A(5) });
}


TEST_F(IntMinMaxQueueTestFixture, IntMinMaxDescendingTest)
{
    MinMaxComplexTest({ 5, 4, 3, 2, 1, 0 });
}


TEST_F(StringMinMaxQueueTestFixture, StringMinMaxDescendingTest)
{
    MinMaxComplexTest({ "f", "e", "d", "c", "b", "a" });
}


TEST_F(UserTypeMinMaxQueueTestFixture, UserTypeMinMaxDescendingTest)
{
    MinMaxComplexTest({ A(5), A(4), A(3), A(2), A(1), A(0) });
}