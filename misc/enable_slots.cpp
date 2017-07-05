#include "enable_slots.h"

misc::enable_slots::enable_slots ()
{

}

misc::enable_slots::~enable_slots ()
{
  for (auto sig_addr : m_signals)
    {
      reinterpret_cast<signal_base *> (sig_addr)->unregister_slot (this);
    }
}

void misc::enable_slots::disconnect_full (misc::signal_base *sig)
{
  m_signals.erase (m_signals.find (reinterpret_cast<intptr_t> (sig)));
}


