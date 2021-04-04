#include "View.hpp"

#include <Process/Style/ScenarioStyle.hpp>
#include <Acousmoscribe/SpectralKeyView.hpp>
#include <Acousmoscribe/MelodicKeyView.hpp>
#include <Acousmoscribe/Model/MelodicKey.hpp>

#include <score/graphics/GraphicsItem.hpp>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QPainter>
#include <wobjectimpl.h>
#include <QBrush>

W_OBJECT_IMPL(Acousmoscribe::View)
namespace Acousmoscribe
{
View::View(QGraphicsItem* parent) : Process::LayerView{parent}
{
  this->setAcceptHoverEvents(true);
  this->setAcceptDrops(true);
  this->setFlag(QGraphicsItem::ItemIsFocusable, true);
  this->setFlag(QGraphicsItem::ItemClipsToShape, true);

  m_fragmentCache.reserve(20);

  
}

View::~View()
{
}

bool View::canEdit() const
{
  const auto rect = boundingRect();
  const auto note_height = rect.height() / (visibleCount());
  return note_height > 5;
}

void View::paint_impl(QPainter* p) const
{
  /*p->setBrush(draw);
  p->drawRect( 40,30, width_fdp,100 );*/

}

void View::mousePressEvent(QGraphicsSceneMouseEvent* ev)
{
  /*
  width_fdp = 100;
  QColor cyan(Qt::cyan); 
  draw.setColor(cyan);*/
}

void View::mouseReleaseEvent(QGraphicsSceneMouseEvent* ev)
{
  /*
  width_fdp = 300;
  QColor green(Qt::green); 
  draw.setColor(green); */
  
}

void View::setDefaultWidth(double w)
{
  m_defaultW = w;
  update();
  const auto& children = childItems();
  for (auto cld : children)
    cld->update();
}

int View::visibleCount() const
{
  return m_max - m_min + 1;
}



}
