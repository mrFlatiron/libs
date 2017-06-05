#include "parallel.h"
#include <thread>
#include <vector>

void parallel::loop (const int t_count, std::function<void(const int)> worker)
{
  std::vector<std::thread> threads;

  for (int i = 0; i < t_count; i++)
    {
      threads.push_back (std::thread (worker, i));
    }

  for (int i = 0; i < t_count; i++)
    {
      threads[i].join ();
    }
}
