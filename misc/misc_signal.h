#ifndef MISC_SIGNAL_H
#define MISC_SIGNAL_H


#include "signal_base.h"
#include "enable_slots.h"


#include <unordered_map>
#include <functional>
#include <unordered_set>
#include <vector>


namespace misc
{

  template<class... Args>
  class signal : public signal_base
  {
  private:
    std::unordered_map<intptr_t, std::vector<std::function<void(Args...)> > > m_slots;
  public:
    void register_slot (enable_slots *slot_handle, const std::function<void(Args...)> &slot);
    void operator () (Args&&... args);
  };

  template<class... Args>
  void misc::signal<Args...>::register_slot (enable_slots *slot_handle,
                                        const std::function<void(Args...)> &slot)
  {
    intptr_t slot_handle_addr = reinterpret_cast<intptr_t> (slot_handle);

    auto register_res = m_enabled_slots.find (slot_handle_addr);
    auto slot_map_res = m_slots.find (slot_handle_addr);

    if (register_res == m_enabled_slots.end ())
      {
        std::vector<std::function<void(Args...)> > new_vector;
        new_vector.push_back (slot);
        m_enabled_slots.insert (slot_handle_addr);
        m_slots.insert ({slot_handle_addr, std::move (new_vector)});
      }
    else
      slot_map_res->second.push_back (slot);
  }


  template<class... Args>
  void misc::signal<Args...>::operator () (Args&&... args)
  {
    for (auto map_iter : m_slots)
      {
        if (m_enabled_slots.find (map_iter.first) != m_enabled_slots.end ())
          for (auto slot : map_iter.second)
            slot (std::forward<Args>(args)...);
      }
  }
}

#endif // MISC_SIGNAL_H
