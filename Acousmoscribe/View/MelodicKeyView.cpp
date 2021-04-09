#include "MelodicKeyView.hpp"

#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>

#include <Acousmoscribe/Model/MelodicKey.hpp>
#include <Acousmoscribe/Presenter/Presenter.hpp>

namespace Acousmoscribe
{

MelodicKeyView::MelodicKeyView(const MelodicKey& mk, Presenter& p, View* parent)
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
  float h = m_height*0.99;

  Pitch pitch = melodicKey.pitch();
  Range range = melodicKey.range();

  QPen pen;
  pen.setWidth(1);
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
      pen.setWidth(3); // the 4th point is bigger
      painter->setPen(pen);
      painter->drawPoint(QPoint(x_pitch, y_pitch));
      pen.setWidth(1);
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

  painter->setPen(pen);

  float y_range = (pitch+1)*h_pitch/7;;
  painter->drawLine(QPoint(x_pitch, y_range), QPoint(x_pitch + w/2, y_range));
  
}

QRectF MelodicKeyView::computeRect() const noexcept
{
  auto& view = *(View*)parentItem();
  const auto h = view.height();
  const auto w = view.defaultWidth();
  const QRectF rect{
      60, 
      0,
      60,
      h};

  return rect;
}


bool MelodicKeyView::canEdit() const
{
  return boundingRect().height() > 5;
}

void MelodicKeyView::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
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
  if (canEdit())
  {
    switch (m_action)
    {
      case ChangePitch:
      {
        Pitch p = (Pitch) (((int) melodicKey.pitch() + 1)%7);
        m_presenter.on_melodicKeyPitchChanged(melodicKey, p);
        std::cout << "done on_melodicKeyPitchChanged\n";
        break;
      }
      case ChangeRange:
      {
        Range r = (Range) (((int) melodicKey.range() + 1)%3);
        m_presenter.on_melodicKeyRangeChanged(melodicKey, r);
        std::cout << "done on_melodicKeyRangeChanged\n";
        break;
      }
    }
  }
  event->accept();
  m_action = None;
}
}
