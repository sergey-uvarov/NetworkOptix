#include <gtest/gtest.h>

#include "MinMaxQueue.h"

template<class T>
class MinMaxQueueTestFixture : public ::testing::Test
{
public:

    void PushTest(const T &value);
    void PushTimeTest();
    void PopTest(const T &value);
    void MinMaxTest(const T &value, const T &value2);
    void MinMaxComplexTest(std::list<T> values);
    void MultithreadPushTest(const T &value);
    void MultithreadPopTest(const T &value);
    void PopEmptyQueueTest();
    void MinEmptyQueueTest();
    void MaxEmptyQueueTest();

protected:
    MinMaxQueue<T> m_queue;
};

class IntMinMaxQueueTestFixture : public MinMaxQueueTestFixture<int>
{};

class StringMinMaxQueueTestFixture : public MinMaxQueueTestFixture<std::string>
{};

struct A
{
    A(const int value) : m_value(value) {}

    bool operator< (const A &other) const
    {
        return m_value < other.m_value;
    }

    bool operator> (const A &other) const
    {
        return m_value > other.m_value;
    }

    bool operator== (const A &other) const
    {
        return m_value == other.m_value;
    }

    int m_value = 0;
};

class UserTypeMinMaxQueueTestFixture : public MinMaxQueueTestFixture<A>
{};