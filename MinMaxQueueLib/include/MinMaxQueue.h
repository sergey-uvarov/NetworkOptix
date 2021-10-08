#include <atomic>
#include <deque>
#include <iostream>
#include <list>
#include <mutex>

template<class T>
class MinMaxQueue
{
public:
    void push(const T &value)
    {
        std::lock_guard<std::mutex> lg(m_mutex);

        m_queue.push_back(value);

        updateMaxExtrs(value);
        updateMinExtrs(value);
    }

    T pop()
    {
        std::lock_guard<std::mutex> lg(m_mutex);

        if (m_queue.empty())
            m_queue.pop_front(); // Cause segmentation fault as an expected behavior of STL container

        auto result = std::move(m_queue.front());

        m_queue.pop_front();

        if (m_queue.empty())
        {
            m_minExtrs.clear();
            m_maxExtrs.clear();

            return result;
        }

        if (result == min())
            m_minExtrs.pop_front();

        if (result == max())
            m_maxExtrs.pop_front();

        return result;
    }

    T min() const
    {
        return m_minExtrs.front(); // Undefined behavior in case of an empty list
    }

    T max() const
    {
        return m_maxExtrs.front(); // Undefined behavior in case of an empty list
    }

    int size() const
    {
        std::lock_guard<std::mutex> lg(m_mutex);
        return m_queue.size();
    }

private:
    void updateMaxExtrs(const T &value)
    {
        if (m_maxExtrs.empty())
        {
            m_maxExtrs.push_back(value);
            return;
        }
            
        if (value > m_maxExtrs.front())
        {
            m_maxExtrs.clear();
            m_maxExtrs.push_back(value);
            return;
        }

        if (value < m_maxExtrs.back())
        {
            m_maxExtrs.push_back(value);
        }
        else
        {
            auto it = m_maxExtrs.end();
            while (it != m_maxExtrs.begin() && *(--it) < value)
                m_maxExtrs.erase(it);
            m_maxExtrs.push_back(value);
        }
    }

    void updateMinExtrs(const T &value)
    {
        if (m_minExtrs.empty())
        {
            m_minExtrs.push_back(value);
            return;
        }
            
        if (value < m_minExtrs.front())
        {
            m_minExtrs.clear();
            m_minExtrs.push_back(value);
            return;
        }

        if (value > m_minExtrs.back())
        {
            m_minExtrs.push_back(value);
        }
        else
        {
            auto it = m_minExtrs.end();
            while (it != m_minExtrs.begin() && *(--it) > value)
                m_minExtrs.erase(it);
            m_minExtrs.push_back(value);
        }        
    }

private:
    std::list<T> m_maxExtrs;
    std::list<T> m_minExtrs;

    std::deque<T> m_queue;
    mutable std::mutex m_mutex;
};