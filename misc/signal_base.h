#ifndef SIGNAL_BASE_H
#define SIGNAL_BASE_H

#include <unordered_set>

namespace misc
{
  class enable_slots;

  class signal_base
  {
  protected:
    std::unordered_set<intptr_t> m_enabled_slots;
  public:
    signal_base ();
    virtual ~signal_base ();
    void unregister_slot (enable_slots *slot_handle);
  };
}
#endif // SIGNAL_BASE_H
