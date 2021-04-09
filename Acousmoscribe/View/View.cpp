#include "View.hpp"

#include <Process/Style/ScenarioStyle.hpp>
#include <Acousmoscribe/View/SpectralKeyView.hpp>
#include <Acousmoscribe/View/MelodicKeyView.hpp>
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

void View::paint_impl(QPainter* p) const
{

}

void View::mousePressEvent(QGraphicsSceneMouseEvent* ev)
{
}

void View::mouseReleaseEvent(QGraphicsSceneMouseEvent* ev)
{

}

void View::setDefaultWidth(double w)
{
  m_defaultW = w;
  update();
  const auto& children = childItems();
  for (auto cld : children)
    cld->update();
}

void View::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* ev)
{
  std::cout << "mouseDoubleClickEvent\n";
  doubleClicked(ev->pos());
  ev->accept();
}

void View::keyPressEvent(QKeyEvent* ev)
{
  if (ev->key() == Qt::Key_Backspace || ev->key() == Qt::Key_Delete)
  {
    deleteRequested();
  }

  ev->accept();
}

SignData View::signAtPos(QPointF point) const
{

  SignData s;
  s.m_start = std::max(0., point.x() / m_defaultW);
  s.m_duration = 0.5;
  DynamicProfile dyn = {1,1};
  s.setDynamicProfile(dyn);

  return s;
}

}
