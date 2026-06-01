#pragma once
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>
#include <queue>
#include <type_traits>
#include <future>
#include <memory>


class ThreadPool
{
    public:
    ThreadPool()
    :m_shouldEnd{false}
    {
        unsigned int threads = std::thread::hardware_concurrency();
        for(unsigned int i = 0; i < threads; ++i)
        {
            m_threads.emplace_back([this](){ Work(); });
        }

    }

    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(m_queueLock);
            m_shouldEnd = true;
        }

        m_condition.notify_all();
        for(auto &thread : m_threads)
        {
            if(thread.joinable()) { thread.join(); };
        }
    }


    void AddTask(std::function<void()> _task)
    {
        {
            std::unique_lock<std::mutex> lock(m_queueLock);
            m_tasks.push(_task);            
        }
        m_condition.notify_one();
    }

    template<typename Func, typename... Args >
    auto Enqueue(Func&& _func, Args... _args) -> std::future<std::invoke_result_t<Func, Args...>>
    {
        using ReturnType = std::invode_result_t<Func, Args...>;

        auto task = std::make_shader<ReturnType>

    }

    private:
    void Work()
    {
        while(true)
        {
            std::function<void()> task;
            {
                std::unique_lock<std::mutex> lock(m_queueLock);
                m_condition.wait(lock, [this](){ return m_shouldEnd || !m_tasks.empty(); });
                if(m_shouldEnd && m_tasks.empty())
                {
                    return;
                }
                task = m_tasks.front();
                m_tasks.pop();
            }
            task();
        }
    }
    bool m_shouldEnd;
    std::vector<std::thread> m_threads;
    std::queue<std::function<void()>> m_tasks;
    std::mutex m_queueLock;
    std::condition_variable m_condition;
};