#include "SignView.hpp"

#include <Acousmoscribe/View.hpp>
#include <Acousmoscribe/Presenter.hpp>

#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>
#include <QPainter>

namespace Acousmoscribe
{

SignView::SignView(const Sign& n, Presenter& presenter, View* parent)
    : QGraphicsItem{parent}
    , sign{n}
    , m_presenter{presenter}
    , m_action{None}
{
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemIsMovable, false);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    this->setAcceptHoverEvents(true);
}

void SignView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{/*
  static const MidiStyle s;

  painter->setRenderHint(QPainter::Antialiasing, false);

  if (m_width <= 1.2)
  {
    painter->setPen(this->isSelected() ? s.signSelectedBasePen : s.signBasePen);
    painter->drawLine(0, 0, 0, m_height - 1.5);
  }
  else
  {
    painter->setPen(this->isSelected() ? s.signSelectedBasePen : Qt::NoPen);
    painter->setBrush(s.paintedSignBrush[sign.velocity()]);

    painter->drawRect(boundingRect().adjusted(0., 0., 0., 0));
  }*/
}

QPointF SignView::closestPos(QPointF newPos) const noexcept
{
  auto& view = *(View*)parentItem();
  const auto [min, max] = view.range();
  const double count = view.visibleCount();
  const QRectF rect = view.boundingRect();
  const auto height = rect.height();
  const auto sign_height = height / count;

  newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
  auto bounded = (qBound(rect.top(), newPos.y() - sign_height * 0.45, rect.bottom())) / height;
  int sign = qBound(min, int(max - bounded * count), max);

  newPos.setY(height - (sign - min + 1) * sign_height);
  return newPos;
}

QRectF SignView::computeRect() const noexcept
{
  auto& view = *(View*)parentItem();
  const auto h = view.height();
  const auto w = view.defaultWidth();
  const auto [min, max] = view.range();
  const auto sign_height = h / view.visibleCount();
  const QRectF rect{
      sign.start() * w,
      h - std::ceil(min * sign_height),
      sign.duration() * w,
      sign_height};

  return rect;
}

QVariant SignView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
  switch (change)
  {
    case QGraphicsItem::ItemSelectedChange:
    {
      this->setZValue(10 * (int)value.toBool());
      break;
    }
    default:
      break;
  }

  return QGraphicsItem::itemChange(change, value);
}

void SignView::hoverEnterEvent(QGraphicsSceneHoverEvent* event)
{
  if (event->pos().x() >= this->boundingRect().width() - 2)
  {
    auto& skin = score::Skin::instance();
    this->setCursor(skin.CursorScaleH);
  }
  else
  {
    this->setCursor(Qt::ArrowCursor);
  }

  QGraphicsItem::hoverEnterEvent(event);
}

void SignView::hoverMoveEvent(QGraphicsSceneHoverEvent* event)
{
  if (event->pos().x() >= this->boundingRect().width() - 2)
  {
    auto& skin = score::Skin::instance();
    this->setCursor(skin.CursorScaleH);
  }
  else
  {
    if(qApp->keyboardModifiers() == Qt::ShiftModifier)
    {
      auto& skin = score::Skin::instance();
      this->setCursor(skin.CursorSpin);
    }
    else
    {
      this->setCursor(Qt::ArrowCursor);
    }
  }

  QGraphicsItem::hoverMoveEvent(event);
}

void SignView::hoverLeaveEvent(QGraphicsSceneHoverEvent* event)
{
  this->setCursor(Qt::ArrowCursor);

  QGraphicsItem::hoverEnterEvent(event);
}

bool SignView::canEdit() const
{
  return boundingRect().height() > 5;
}

static QPointF signview_origpoint;
void SignView::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  const auto mods = QGuiApplication::keyboardModifiers();
  if (!(mods & Qt::ControlModifier) && !isSelected())
    m_presenter.on_deselectOtherSigns();

  setSelected(true);

  m_action = None;
  if (canEdit())
  {
    if (event->pos().x() >= this->boundingRect().width() - 2)
    {
      m_action = Scale;
    }
    /*else if (mods & Qt::ShiftModifier)
    {
      m_action = ChangeVelocity;
    }*/
    else if (mods & Qt::AltModifier)
    {
      m_action = Duplicate;
    }
    else
    {
      m_action = Move;
      signview_origpoint = this->pos();
    }
  }
  event->accept();
}

void SignView::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  if (canEdit())
  {
    switch(m_action)
    {
      case Move:
        this->setPos(closestPos(
            signview_origpoint + event->scenePos() - event->buttonDownScenePos(Qt::LeftButton)));
         m_presenter.on_signMoved(*this);
        break;
      case Scale:
        this->setWidth(std::max(2., event->pos().x()));
        break;
      case Duplicate:
        m_presenter.on_signDuplicate();
        break;
      /*case ChangeVelocity:
        m_presenter.on_requestVelocityChange(sign, event->buttonDownScenePos(Qt::LeftButton).y() - event->scenePos().y());
        break;*/
      case None:
        break;
    }
  }
  event->accept();
}

void SignView::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
  if (canEdit())
  {
    switch(m_action)
    {
      case Move:
        this->setPos(closestPos(
            signview_origpoint + event->scenePos() - event->buttonDownScenePos(Qt::LeftButton)));
         m_presenter.on_signMoved(*this);
         m_presenter.on_signMoveFinished(*this);
        break;
      case Scale:
        this->setWidth(std::max(2., event->pos().x()));
        m_presenter.on_signScaled(sign, m_width / ((View*)parentItem())->defaultWidth());
        break;
      case Duplicate:
        m_presenter.on_signDuplicate();
        break;
      /*case ChangeVelocity:
        m_presenter.on_requestVelocityChange(sign, event->buttonDownScenePos(Qt::LeftButton).y() - event->scenePos().y());
        m_presenter.on_velocityChangeFinished();
        break;*/
      case None:
        break;
    }
  }
  event->accept();
  m_action = None;
}
}
