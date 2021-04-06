#include "MelodicKeyView.hpp"

#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>
#include <Acousmoscribe/Presenter.hpp>
#include <Acousmoscribe/Model/MelodicKey.hpp>

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


QRectF MelodicKeyView::computeRect() const noexcept
{
  auto& view = *(View*)parentItem();
  const auto h = view.height();
  //const auto w = view.defaultWidth();
  const auto w = view.width();
  const auto [min, max] = view.range();
  const auto key_height = h / view.visibleCount();
  const QRectF rect{
      35 * w, //35 à changer (instant de départ)
      0,
      35 * w,
      key_height};

  return rect;
}

void MelodicKeyView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)

//void MelodicKeyView::paint(QPainter* painter)
{
  QPen p;
  p.setColor(Qt::black);
  p.setWidth(1);
  painter->setPen(p);
  painter->setBrush(Qt::white);
  painter->drawRect(QRect(35, 0, 35, 70));

  enum Pitch
  {
    very_high = 0,
    high,
    mid_high,
    mid,
    mid_low,
    low,
    very_low
  };

  enum Range
  {
    weak = 0,
    normal,
    strong
  };

  Range m_range = weak;
  Pitch m_pitch = mid_high;

  /* RANGE */
  p.setWidth(1);
  p.setStyle(Qt::SolidLine);
  painter->setPen(p);
  painter->drawPoint(QPoint(42, 8));
  painter->drawPoint(QPoint(42, 17));
  painter->drawPoint(QPoint(42, 25));
  p.setWidth(2);
  painter->setPen(p);
  painter->drawPoint(QPoint(42, 34));
  p.setWidth(1);
  painter->setPen(p);
  painter->drawPoint(QPoint(42, 43));
  painter->drawPoint(QPoint(42, 52));
  painter->drawPoint(QPoint(42, 61));

  /* VERY HIGH */
  if (m_pitch == very_high)
  {

    /* DIFFERENCES */
    if (m_range == weak)
    {
      p.setStyle(Qt::DotLine);
    }
    else if (m_range == normal)
    {
      p.setStyle(Qt::DashDotLine);
    }
    else if (m_range == strong)
      p.setStyle(Qt::SolidLine);

    painter->setPen(p);
    painter->drawLine(QPoint(42, 8), QPoint(63, 8));

    /* HIGH */
  }
  else if (m_pitch == high)
  {

    /* DIFFERENCES */
    if (m_range == weak)
    {
      p.setStyle(Qt::DotLine);
    }
    else if (m_range == normal)
    {
      p.setStyle(Qt::DashDotLine);
    }
    else if (m_range == strong)
      p.setStyle(Qt::SolidLine);

    painter->setPen(p);
    painter->drawLine(QPoint(42, 17), QPoint(63, 17));

    /* MID HIGH */
  }
  else if (m_pitch == mid_high)
  {

    /* DIFFERENCES */
    if (m_range == weak)
    {
      p.setStyle(Qt::DotLine);
    }
    else if (m_range == normal)
    {
      p.setStyle(Qt::DashDotLine);
    }
    else if (m_range == strong)
      p.setStyle(Qt::SolidLine);

    painter->setPen(p);
    painter->drawLine(QPoint(42, 25), QPoint(63, 25));

    /* MID */
  }
  else if (m_pitch == mid)
  {

    /* DIFFERENCES */
    if (m_range == weak)
    {
      p.setStyle(Qt::DotLine);
    }
    else if (m_range == normal)
    {
      p.setStyle(Qt::DashDotLine);
    }
    else if (m_range == strong)
      p.setStyle(Qt::SolidLine);

    painter->setPen(p);
    painter->drawLine(QPoint(42, 34), QPoint(63, 33));

    /* MID LOW */
  }
  else if (m_pitch == mid_low)
  {

    /* DIFFERENCES */
    if (m_range == weak)
    {
      p.setStyle(Qt::DotLine);
    }
    else if (m_range == normal)
    {
      p.setStyle(Qt::DashDotLine);
    }
    else if (m_range == strong)
      p.setStyle(Qt::SolidLine);

    painter->setPen(p);
    painter->drawLine(QPoint(42, 43), QPoint(63, 43));

    /* LOW */
  }
  else if (m_pitch == low)
  {

    /* DIFFERENCES */
    if (m_range == weak)
    {
      p.setStyle(Qt::DotLine);
    }
    else if (m_range == normal)
    {
      p.setStyle(Qt::DashDotLine);
    }
    else if (m_range == strong)
      p.setStyle(Qt::SolidLine);

    painter->setPen(p);
    painter->drawLine(QPoint(42, 52), QPoint(63, 52));

    /* VERY LOW */
  }
  else if (m_pitch == very_low)
  {

    /* DIFFERENCES */
    if (m_range == weak)
    {
      p.setStyle(Qt::DotLine);
    }
    else if (m_range == normal)
    {
      p.setStyle(Qt::DashDotLine);
    }
    else if (m_range == strong)
      p.setStyle(Qt::SolidLine);

    painter->setPen(p);
    painter->drawLine(QPoint(42, 61), QPoint(63, 61));
  }
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
      Pitch p;
      Range r;
      case ChangePitch:
        p = low;
        m_presenter.on_melodicKeyPitchChanged(melodicKey, p);
        std::cout << "on_melodicKeyPitchChanged\n";
        break;
      case ChangeRange:
        r = weak;
        m_presenter.on_melodicKeyRangeChanged(melodicKey, r);
        std::cout << "on_melodicKeyRangeChanged\n";
        break;
    }
  }
  event->accept();
  m_action = None;
}
}
