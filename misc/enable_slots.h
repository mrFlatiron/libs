#ifndef ENABLE_SLOTS_H
#define ENABLE_SLOTS_H

#include "misc_signal.h"
#include <unordered_set>
#include <list>

namespace misc
{
  class enable_slots
  {
  private:
    std::unordered_set<intptr_t> m_signals;
  public:
    enable_slots ();
    ~enable_slots ();
    template<class Func, class... Args>
    void connect_to (signal<Args...> &sig, Func slot);
    void disconnect_full (signal_base *sig);
  };
}

template<class Func, class... Args>
void misc::enable_slots::connect_to (misc::signal<Args...> &sig, Func slot)
{

  m_signals.insert (reinterpret_cast<intptr_t> ((misc::signal_base *)(&sig)));
  sig.register_slot (this, std::function<void(Args...)> (slot));
}


#endif // ENABLE_SLOTS_H
