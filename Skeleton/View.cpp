#include "View.hpp"

#include <Process/Style/ScenarioStyle.hpp>

#include <score/graphics/GraphicsItem.hpp>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QPainter>

namespace Skeleton
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
  if (auto v = getView(*this))
  {
    if (canEdit())
    {
      const double dpi = p->device()->devicePixelRatioF();
      const auto view_left = v->mapToScene(0, 0);
      const auto left = std::max(0., this->mapFromScene(view_left).x());
      double x = left;
      const double text_w = 30. * dpi;
      const double next_w = m_bgCache.width() - text_w;
      const double proc_w = width();
      const double h = std::round(m_bgCache.height() / 2.);

      if (p->device()->devicePixelRatioF() == 1.)
      {
        m_fragmentCache.clear();
        while(x - next_w < proc_w)
        {
          m_fragmentCache.push_back(QPainter::PixmapFragment{
              x,
              h,
              text_w,
              0.,
              next_w,
              (double)m_bgCache.height(),
              1.,
              1.,
              0.,
              1.});
          x += next_w;
        }

        p->drawPixmapFragments(
            m_fragmentCache.data(),
            m_fragmentCache.size(),
            m_bgCache);
      }
      else
      {
        while(x - next_w < proc_w)
        {
          p->drawPixmap(QPointF{x, 0}, m_bgCache, QRectF{text_w, 0., next_w, (double)m_bgCache.height()});
          x += next_w / dpi;
        }
      }

      if(left < 30 && !m_textCache.isNull())
      {
        p->drawPixmap(QPointF{}, m_textCache);
      }
    }
  }
  if (!m_selectArea.isEmpty())
  {
    /*p->setBrush(style.transparentBrush);
    p->setPen(style.selectionPen);*/
    p->drawPath(m_selectArea);
  }
  p->drawRect(30, 50, 30, 50);

  /* rectangle/triangle */
  static const QPointF points[4] = {
     QPointF(10.0, 80.0), //bas gauche
     QPointF(10.0, 10.0), //haut gauche
     QPointF(50.0, 10.0), //haut droite
     QPointF(90.0, 80.0)  //bas droite
 };
 
 p->drawPolygon(points, 4);
}

int View::visibleCount() const
{
  return m_max - m_min + 1;
}
}
