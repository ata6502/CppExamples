/*
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
*/

#include <string>
#include <iostream>
#include <ppl.h>

// Concurrency::parallel_for_each - the first argument is a lambda expression that should be run in parallel
// Concurrency::combinable, local(), combine_each()

int main()
{
}
