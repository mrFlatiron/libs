#ifndef PARALLEL_H
#define PARALLEL_H

#include <functional>

namespace parallel
{
  void loop (const int t_count, std::function<void(const int t_num)> worker);
}

#endif // PARALLEL_H
