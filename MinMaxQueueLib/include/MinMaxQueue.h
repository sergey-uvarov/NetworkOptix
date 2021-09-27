#include <mutex>
#include <deque>
#include <atomic>

#include <iostream>

template<class T>
class MinMaxQueue
{
public:
    void push(const T &value)
    {
        std::lock_guard<std::mutex> lg(m_mutex);

        m_queue.push_back(value);

        if (!m_max || m_queue.back() > *m_max)
            m_max = &m_queue.back();
        if (!m_min || m_queue.back() < *m_min)
            m_min = &m_queue.back();
    }

    T pop()
    {
        std::lock_guard<std::mutex> lg(m_mutex);

        if (m_queue.empty())
        {
            m_min = nullptr;
            m_max = nullptr;
            m_queue.pop_front(); // Cause segmentation fault as an expected behavior of STL container
        }

        auto minValue = min();
        auto maxValue = max();

        auto result = std::move(m_queue.front());

        m_queue.pop_front();

        if (result == minValue)
        {
            auto it = std::min_element(m_queue.begin(), m_queue.end());
            m_min = it != m_queue.end() ? &(*it) : nullptr;
        }

        if (result == maxValue)
        {
            auto it = std::max_element(m_queue.begin(), m_queue.end());
            m_max = it != m_queue.end() ? &(*it) : nullptr;
        }

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

private:
    std::atomic<T *> m_min = nullptr;
    std::atomic<T *> m_max = nullptr;

    std::deque<T> m_queue;
    std::mutex m_mutex;

    friend class IntMinMaxQueueTestFixture;
    friend class StringMinMaxQueueTestFixture;
    friend class UserTypeMinMaxQueueTestFixture;
};