#include "signal_base.h"
#include "enable_slots.h"

misc::signal_base::signal_base ()
{

}

misc::signal_base::~signal_base ()
{
  for (auto slot_addr : m_enabled_slots)
    reinterpret_cast<enable_slots *> (slot_addr)->disconnect_full (this);
}

void misc::signal_base::unregister_slot (enable_slots *slot_handle)
{
  this->m_enabled_slots.erase (reinterpret_cast<intptr_t> (slot_handle));
}
