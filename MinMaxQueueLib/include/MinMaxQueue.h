#include <mutex>
#include <deque>
#include <atomic>

#include <iostream>

template<class T>
class MinMaxQueue
{
    struct Node
    {
        Node(const T &val)
        : value(val)
        , localMin(val)
        , localMax(val)
        {}

        T value;
        T localMin;
        T localMax;

        bool operator< (const Node &other) const
        {
            return value < other.value;
        }
        bool operator> (const Node &other) const
        {
            return value > other.value;
        }

        bool operator== (const Node &other) const
        {
            return value == other.value;
        }
    };

public:
    void push(const T &value)
    {
        std::lock_guard<std::mutex> lg(m_mutex);

        auto node = Node(value);

        m_queue.push_back(node);

        auto minUpdated = false;
        auto maxUpdated = false;

        if (!m_max || m_queue.back().value > *m_max)
        {
            m_max = &m_queue.back().value;
            maxUpdated = true;
        }
        if (!m_min || m_queue.back().value < *m_min)
        {
            m_min = &m_queue.back().value;
            minUpdated = true;
        }

        if (!minUpdated && !maxUpdated)
        {
            auto it = m_queue.end() - 2;

            while (node.value > it->localMax)
            {
                it->localMax = node.value;
                --it;
            }

            it = m_queue.end() - 2;

            while (node.value < it->localMin)
            {
                it->localMin = node.value;
                --it;
            }
        }
    }

    T pop()
    {
        std::lock_guard<std::mutex> lg(m_mutex);

        if (m_queue.empty())
            m_queue.pop_front(); // Cause segmentation fault as an expected behavior of STL container

        auto minValue = min();
        auto maxValue = max();

        auto result = std::move(m_queue.front().value);

        m_queue.pop_front();

        if (result == minValue)
            m_min = !m_queue.empty() ? &m_queue.front().localMin : nullptr;

        if (result == maxValue)
            m_max = !m_queue.empty() ? &m_queue.front().localMax : nullptr;

        return result;
    }

    T min() const
    {
        return *m_min; // Will cause segmentation fault in case of an empty queue as we have no value to return
    }

    T max() const
    {
        return *m_max; // Will cause segmentation fault in case of an empty queue as we have no value to return
    }

    int size() const
    {
        std::lock_guard<std::mutex> lg(m_mutex);
        return m_queue.size();
    }

private:
    std::atomic<T *> m_min = nullptr;
    std::atomic<T *> m_max = nullptr;

    std::deque<Node> m_queue;
    mutable std::mutex m_mutex;
};