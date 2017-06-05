#include "layout_stack.h"
#include <cstdlib>
#include <cassert>
#include <QWidget>

using namespace gui_utils;

layout_stack::layout_stack (QWidget *parent)
{
  m_size = 0;
  m_parent = parent;
}

void layout_stack::push_back (qlayout_type type)
{
  layout_meta lm;
  lm.type = type;
  switch (type)
  {
    case qlayout_type::hbox:
      lm.layout = new QHBoxLayout;
      break;
    case qlayout_type::vbox:
      lm.layout = new QVBoxLayout;
      break;
    case qlayout_type::grid:
      lm.layout = new QGridLayout;
      break;
    case qlayout_type::stacked:
      lm.layout = new QStackedLayout;
      break;
    case qlayout_type::form:
      lm.layout = new QFormLayout;
      break;
    case qlayout_type::COUNT:
      std::abort ();
      break;
  }
  if (m_stack.size () <= m_size)
    m_stack.push_back (lm);
  else
    m_stack[m_size] = lm;

  size_t old_size = m_size;
  m_size++;

  if (old_size == 0)
    return;

  qlayout_type oldtype = m_stack[old_size - 1].type;
  assert (oldtype == qlayout_type::hbox
          || oldtype == qlayout_type::vbox);
  dynamic_cast<QBoxLayout*> (m_stack[old_size - 1].layout)->addLayout
      (m_stack[m_size - 1].layout);
}

void layout_stack::pop_back ()
{
  if (m_size == 0)
    return;

  if (m_size >= 1)
    m_size--;

  if (m_size == 0)
    {
      if (m_parent)
        m_parent->setLayout (m_stack[m_size].layout);
    }
}

QLayout *layout_stack::top ()
{
  if (m_size <= 0)
    return nullptr;
  return m_stack[m_size - 1].layout;
}

QHBoxLayout *layout_stack::as_hbox ()
{
  if (m_size <= 0)
    return nullptr;
  return dynamic_cast<QHBoxLayout *> (top ());
}

QVBoxLayout *layout_stack::as_vbox ()
{
  if (m_size <= 0)
    return nullptr;
  return dynamic_cast<QVBoxLayout *> (top ());
}

QGridLayout *layout_stack::as_grid ()
{
  if (m_size <= 0)
    return nullptr;
  return dynamic_cast<QGridLayout *> (top ());
}

QStackedLayout *layout_stack::as_stacked ()
{
  if (m_size <= 0)
    return nullptr;
  return dynamic_cast<QStackedLayout *> (top ());
}

QFormLayout *layout_stack::as_form ()
{
  if (m_size <= 0)
    return nullptr;
  return dynamic_cast<QFormLayout *> (top ());
}

void layout_stack::addWidget (QWidget *widget, int stretch, Qt::Alignment alignment)
{
  if (m_size <= 0)
    return;
  qlayout_type type = m_stack[m_size - 1].type;
  QLayout *layout = m_stack[m_size - 1].layout;
  assert (type == qlayout_type::hbox
          || type == qlayout_type::vbox);
  dynamic_cast<QBoxLayout*> (layout)->addWidget (widget, stretch, alignment);
}

void layout_stack::addLayout (QLayout *layout, int stretch)
{
  if (m_size <= 0)
    return;
  qlayout_type type = m_stack[m_size - 1].type;
  QLayout *l = m_stack[m_size - 1].layout;
  assert (type == qlayout_type::hbox
          || type == qlayout_type::vbox);
  dynamic_cast<QBoxLayout*> (l)->addLayout (layout, stretch);
}

void layout_stack::addStretch (int stretch)
{
  if (m_size <= 0)
    return;
  qlayout_type type = m_stack[m_size - 1].type;
  QLayout *l = m_stack[m_size - 1].layout;
  assert (type == qlayout_type::hbox
            || type == qlayout_type::vbox);
  dynamic_cast<QBoxLayout*> (l)->addStretch (stretch);
}

void layout_stack::addWidget (QWidget *widget, int row, int column, Qt::Alignment alignment)
{
  if (m_size <= 0)
    return;
  qlayout_type type = m_stack[m_size - 1].type;
  QLayout *l = m_stack[m_size - 1].layout;
  assert (type == qlayout_type::grid);
  dynamic_cast<QGridLayout*> (l)->addWidget (widget, row, column, alignment);
}

void layout_stack::addWidget (QWidget *widget, int fromRow, int fromColumn, int rowSpan,
                              int columnSpan, Qt::Alignment alignment)
{
  if (m_size <= 0)
    return;
  qlayout_type type = m_stack[m_size - 1].type;
  QLayout *l = m_stack[m_size - 1].layout;
  assert (type == qlayout_type::grid);
  dynamic_cast<QGridLayout*> (l)->addWidget (widget, fromRow, fromColumn, rowSpan, columnSpan,
                                             alignment);
}

void layout_stack::addLayout (QLayout *layout, int row, int column, Qt::Alignment alignment)
{
  if (m_size <= 0)
    return;
  qlayout_type type = m_stack[m_size - 1].type;
  QLayout *l = m_stack[m_size - 1].layout;
  assert (type == qlayout_type::grid);
  dynamic_cast<QGridLayout*> (l)->addLayout (layout, row, column, alignment);
}

void layout_stack::addLayout (QLayout *layout, int row, int column, int rowSpan, int columnSpan,
                              Qt::Alignment alignment)
{
  if (m_size <= 0)
    return;
  qlayout_type type = m_stack[m_size - 1].type;
  QLayout *l = m_stack[m_size - 1].layout;
  assert (type == qlayout_type::grid);
  dynamic_cast<QGridLayout*> (l)->addLayout (layout, row, column, rowSpan, columnSpan, alignment);
}



create_layout::create_layout (layout_stack &stack, qlayout_type type) :
  m_stack (stack)
{
  stack.push_back (type);
}

create_layout::~create_layout ()
{
  m_stack.pop_back ();
}
