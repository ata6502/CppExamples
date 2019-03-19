/*
    Parallelism
    ===========
    - Many cores doing the same thing in parallel
    - Foot race or swimming race with lanes
    - Getting a task done faster

    Concurrency
    ===========
    - Many different things being done at the same time, co-ordinated
    - Basketball or hockey game
    - Responsiveness and efficiency

    PPL (Parallel Patterns Library):
    - Lets you use multi-core machines without having to write threads and locks.
    - Provides task parallelism. Rather than setting up a thread, you can work with a task.

      // foo() returns a task that will be executed on another thread. When the task is done, the lambda that was passed into then() is executed.
      x = foo().then([&](Result r){ ... });

      // wait() waits for an asynchronous method to finish.
      x = foo().wait();

    - Provides threadsafe parallel containers.
    - Provides parallel algorithms that act on parallel containers or as parallelized loops.

    To use PPL #include <ppl.h> and use the concurrency namespace.

    Concurrency::parallel_for_each - the first argument is a lambda expression that should be run in parallel
    Concurrency::combinable, local(), combine_each()

*/

#include <iostream>
#include <chrono>
#include <thread>       // std::this_thread
#include <ppltasks.h>   // concurrency::create_task
#include <future>       // std::future

using namespace std::chrono_literals; // ms, s, m, h suffixes

using std::cout;

class SlowCounter
{
public:
    SlowCounter() : m_counter(1) {}

    void Count()
    {
        for (int i = 1; i <= 3; ++i)
        {
            // A platform-independent way to access the current thread.
            // Pause the current thread for 1 sec.
            std::this_thread::sleep_for(1s);

            cout << m_counter;
            ++m_counter;
        }

        cout << " ";
    }
private:
    int m_counter;
};

class FutureCounter
{
public:
    FutureCounter() : m_counter(1) {}

    std::future<void> Count()
    {
        // std::async returns std::future.
        // The lambda passed as a parameter to async runs on a separate
        // thread and it does not block i.e., the Count method returns
        // immediately.
        return std::async([this]
        {
            // The following loop is exactly the same as in SlowCounter.
            for (int i = 1; i <= 3; ++i)
            {
                std::this_thread::sleep_for(1s);

                cout << m_counter;
                ++m_counter;
            }

            cout << " ";
        });
    }
private:
    int m_counter;
};

// TODO: Error C2314: keyword '__await' is deprecated: use 'co_await' instead
//std::future<void> CountWrapperAwait(FutureCounter& fc)
//{
//    // await returns immediately, it does not block.
//    __await fc.Count();
//    cout << "await ";
//}

int main()
{
    SlowCounter sc;
    sc.Count();

    // Create a task using PPL.
    concurrency::create_task([&]() { sc.Count(); })
        .then([]() { cout << "end "; })
        .wait(); // wait until counting is finished

    // Call get (or wait) to wait until the future is completed.
    // The get method blocks i.e., it does not provide any benefits
    // of concurrency.
    FutureCounter fc;
    fc.Count().get();

    // CountWrapperAwait does not block. Evaluation continues and is 
    // reachable through a promise such as std::future
    // If you want to wait until the future is finished, write result.wait()

    // FutureCounter fc2;
    // auto result = CountWrapperAwait(fc2); // returns a future

    return 0;
}
