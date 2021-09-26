#include <gtest/gtest.h>

#include "MinMaxQueue.h"

class IntMinMaxQueueTestFixture : public ::testing::Test
{
public:
    void SetUp() final {}
    void TearDown() final {}

    int queueSize() { return m_queue.m_queue.size(); }

protected:
    MinMaxQueue<int> m_queue;
};

class StringMinMaxQueueTestFixture : public ::testing::Test
{
public:
    void SetUp() final {}
    void TearDown() final {}

    int queueSize() { return m_queue.m_queue.size(); }

protected:
    MinMaxQueue<std::string> m_queue;
};

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

class UserTypeMinMaxQueueTestFixture : public ::testing::Test
{
public:
    void SetUp() final {}
    void TearDown() final {}

    int queueSize() { return m_queue.m_queue.size(); }

protected:
    MinMaxQueue<A> m_queue;
};