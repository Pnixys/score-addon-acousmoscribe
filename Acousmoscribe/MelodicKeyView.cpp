#include "MelodicKeyView.hpp"

#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>

#include <Acousmoscribe/Model/MelodicKey.hpp>
#include <Acousmoscribe/Presenter.hpp>

namespace Acousmoscribe
{

MelodicKeyView::MelodicKeyView(MelodicKey& mk, Presenter& p, View* parent)
    : QGraphicsItem{parent}
    , melodicKey{mk}
    , m_presenter{p}
    , m_action{None}
{
  this->setFlag(QGraphicsItem::ItemIsSelectable, true);
  this->setFlag(QGraphicsItem::ItemIsMovable, false);
  this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
  this->setAcceptHoverEvents(true);
}



void MelodicKeyView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)

{
  float w = m_width;
  float h = m_height;

  Pitch pitch = melodicKey.pitch();
  Range range = melodicKey.range();

  QPen pen;
  pen.setWidth((w + h) / 100);
  pen.setColor(Qt::black);
  pen.setStyle(Qt::SolidLine);
  painter->setPen(pen);

  /* Background Rect */

  painter->setBrush(Qt::white);
  painter->drawRect(boundingRect().adjusted(0., 0., 0., 0));

  float h_pitch = h*4/5;
  float x_pitch = w * 1/4;
  float y_pitch;
  for (int i = 1; i <= 7; i++)
  {
    y_pitch = i * h_pitch / 7;
    if (i == 4)
    {
      pen.setWidth((w + h) / 50); // the 4th point is bigger
      painter->setPen(pen);
      painter->drawPoint(QPoint(x_pitch, y_pitch));
      pen.setWidth((w + h) / 100);
      painter->setPen(pen);
    }
    else{
     painter->drawPoint(QPoint(x_pitch, y_pitch));
    }
  }

  switch(range)
  {
    case weak:
      pen.setStyle(Qt::DotLine); 
      break;

    case normal:
      pen.setStyle(Qt::DashDotLine); 
      break;

    case strong:
      pen.setStyle(Qt::SolidLine); 
      break;

    default:
      pen.setStyle(Qt::SolidLine); 
      break;
  }

  float y_range = (pitch+1)*h_pitch/7;;
  painter->drawLine(QPoint(x_pitch, y_range), QPoint(x_pitch + w/2, y_range));
  
}

QRectF MelodicKeyView::computeRect() const noexcept
{
  auto& view = *(View*)parentItem();
  const auto h = view.height();
  const auto w = view.defaultWidth();
  const auto [min, max] = view.range();
  const auto key_height = h / view.visibleCount();
  const QRectF rect{
      w/10, 
      0,
      0.1 * w,
      h};

  return rect;
}


bool MelodicKeyView::canEdit() const
{
  return boundingRect().height() > 5;
}

void MelodicKeyView::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
      std::cout << "in mousePressEvent\n";

  const auto mods = QGuiApplication::keyboardModifiers();
  setSelected(true);

  m_action = None;

  if (canEdit())
  {
    if (mods & Qt::ShiftModifier)
    {
      m_action = ChangeRange;
    }
    else
    {
      m_action = ChangePitch;
    }
  }
  event->accept();
}

void MelodicKeyView::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
          std::cout << "in mouseReleaseEvent\n";

  if (canEdit())
  {
    switch (m_action)
    {
      case ChangePitch:
        m_presenter.on_melodicKeyChanged(*this);
        std::cout << "in changePitch\n";
        break;
      case ChangeRange:
        /*m_presenter->on_melodicKeyChanged(this);
        QPainter *p;
        paint(p);
        std::cout << "in mouseReleaseEvent\n";*/
        break;
    }
  }
  event->accept();
  m_action = None;
}
}
