#ifndef LAYOUT_STACK_H
#define LAYOUT_STACK_H
#include <vector>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStackedLayout>
#include <QFormLayout>

#define INSERT_LAYOUT(stack, type) \
  create_layout layout_watcher__ (stack, type)

class QLayout;
namespace gui_utils
{
  enum class qlayout_type
  {
    hbox,
    vbox,
    grid,
    stacked,
    form,
    COUNT
  };

  struct layout_meta
  {
    QLayout *layout;
    qlayout_type type;
  };

  class layout_stack
  {
  private:
    std::vector<layout_meta> m_stack;
    size_t m_size;
    QWidget *m_parent;
  public:
    layout_stack (QWidget *parent = nullptr);
    void push_back (qlayout_type type);
    void pop_back ();
    QLayout *top ();
    QHBoxLayout *as_hbox ();
    QVBoxLayout *as_vbox ();
    QGridLayout *as_grid ();
    QStackedLayout *as_stacked ();
    QFormLayout *as_form ();
    //QBoxLayout
    void addWidget (QWidget *widget, int stretch = 0, Qt::Alignment alignment = Qt::Alignment ());
    void addLayout (QLayout *layout, int stretch = 0);
    void addStretch (int stretch = 0);
    //QGridLayout
    void addWidget (QWidget *widget, int row, int column, Qt::Alignment alignment = Qt::Alignment());
    void addWidget (QWidget *widget, int fromRow, int fromColumn, int rowSpan, int columnSpan,
                   Qt::Alignment alignment = Qt::Alignment());

    void addLayout (QLayout *layout, int row, int column, Qt::Alignment alignment = Qt::Alignment());
    void addLayout(QLayout *layout, int row, int column, int rowSpan, int columnSpan,
                   Qt::Alignment alignment = Qt::Alignment());

  };

  class create_layout //watcher class
  {
  private:
    layout_stack &m_stack;
  public:
    create_layout (layout_stack &stack, qlayout_type type);
    ~create_layout ();
  };

}
#endif // LAYOUT_STACK_H
