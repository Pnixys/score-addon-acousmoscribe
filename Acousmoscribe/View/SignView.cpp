#include "SignView.hpp"

#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>
#include <QPainter>

#include <Acousmoscribe/Model/Sign.hpp>
#include <Acousmoscribe/Presenter/Presenter.hpp>
#include <Acousmoscribe/View/View.hpp>

namespace Acousmoscribe
{

SignView::SignView(const Sign& n, Presenter& presenter, View* parent)
    : QGraphicsItem{parent}, sign{n}, m_presenter{presenter}, m_action{None}
{
  this->setFlag(QGraphicsItem::ItemIsSelectable, true);
  this->setFlag(QGraphicsItem::ItemIsMovable, true);
  this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
  this->setAcceptHoverEvents(true);
}

void SignView::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{

  QPen p;
  p.setColor(Qt::black);
  p.setWidth(1);
  painter->setPen(p);

  float x_left = boundingRect().left();
  float x_right = boundingRect().right();
  float w = boundingRect().width();
  float h = boundingRect().height() * 0.99;

  Grain grain = sign.grain();
  Speed speed = sign.rhythmicProfile().speed();
  Acceleration acc = sign.rhythmicProfile().acceleration();

  double duration = sign.duration();
  float volumeStart = sign.dynamicProfile().volumeStart;
  float volumeEnd = sign.dynamicProfile().volumeEnd;
  float volumeUsed;

  Pitch pitch = sign.melodicProfile().pitch();
  Pitch pitchEnd = sign.melodicProfile().pitchEnd();

  QPointF a(0, h);
  QPointF b(0, h * (1 - volumeStart));
  QPointF c(w,  h * (1 - volumeEnd));
  QPointF d(w, h);

  double x_pitch; //x coordinate of the melodic profile on the sign
  volumeUsed = std::max(volumeStart, volumeEnd);
  if (volumeUsed == volumeStart)
  {
    x_pitch = x_right*0.015;;
  }
  else
  {
    x_pitch = x_right*0.95;
  }

  p.setStyle(Qt::DotLine);
  painter->setBrush(Qt::white);
  p.setWidth(0);
  painter->setPen(p);
  QPointF points[4] = {a, b, c, d};
  painter->drawPolygon(points, 4);

  p.setCapStyle(Qt::RoundCap);
  p.setWidth(1);
  painter->setPen(p);

  /* GRAIN */
  switch (grain)
  {
    case smooth:
      p.setStyle(Qt::DotLine);
      break;
    case fine:
      p.setStyle(Qt::DashDotLine);
      break;
    case sharp:
      p.setStyle(Qt::DashLine);
      break;
    case big:
      p.setStyle(Qt::SolidLine);
      break;
  }

  painter->setPen(p);
  painter->drawLine(b, c);

  /* RHYTHMIC */
  switch (speed)
  {
    case slow:
      p.setStyle(Qt::DashLine);
      break;
    case medium:
      p.setStyle(Qt::DashDotLine);
      break;
    case fast:
      p.setStyle(Qt::DotLine);
      break;
    default:
      p.setStyle(Qt::SolidLine);
      break;
  }

  painter->setPen(p);
  painter->drawLine(d, a);

  p.setStyle(Qt::SolidLine);
  painter->setPen(p);
  painter->drawLine(a, b);
  painter->drawLine(c, d);

  float h_acc = h - std::min(h * volumeStart / 3, h * volumeEnd / 3);

  /* ACCELERATION */
  switch (acc)
  {
    case decelerating:
      painter->drawLine(QPointF(x_right*0.15, h), QPointF(x_right*0.15, h_acc));
      break;
    case accelerating:
      painter->drawLine(QPointF(x_right*0.75, h), QPointF(x_right*0.75, h_acc));
      break;
    default:
      break;
  }

  /* MELODIC */

  float h_pitch = volumeUsed * 0.65;
  float y_pitch;

  float att_rel = 1;
  if (volumeStart < volumeEnd)
    att_rel = -1;

  float pitchY[7];

  for (int i = 1; i <= 7; i++)
  {
    y_pitch = h - volumeUsed * h + i * h_pitch * h / 5;
    pitchY[i - 1] = y_pitch;
    if (i == 4)
    {
      p.setWidth(5); // the 4th point is bigger
      painter->setPen(p);
      painter->drawPoint(QPoint(x_pitch, y_pitch));
      p.setWidth(1);
      painter->setPen(p);
    }
    else
    {
      painter->drawPoint(QPoint(x_pitch, y_pitch));
    }
  }
  p.setWidth(1);
  painter->setPen(p);

  QPoint firstP;
  QPoint secondP;

  painter->setPen(p);

  float use1, use2;
  if (volumeStart < volumeEnd)
  {
    use1 = w * (att_rel * (0.025 + 0.04));
    use2 = 0.05 * w * att_rel;
  }
  else
  {
    use1 = 0.05 * w * att_rel;
    use2 = w * (att_rel * (0.025 + 0.04));
  }

  switch (pitch)
  {
    case very_high:
      firstP = QPoint(x_pitch + use1, pitchY[0]);
      break;
    case high:
      firstP = QPoint(x_pitch + use1, pitchY[1]);
      break;

    case mid_high:
      firstP = QPoint(x_pitch + use1, pitchY[2]);
      break;
    case mid:
      firstP = QPoint(x_pitch + use1, pitchY[3]);
      break;
    case mid_low:
      firstP = QPoint(x_pitch + use1, pitchY[4]);
      break;

    case low:
      firstP = QPoint(x_pitch + use1, pitchY[5]);
      break;

    case very_low:
      firstP = QPoint(x_pitch + use1, pitchY[6]);
      break;
  }

  switch (pitchEnd)
  {
    case very_high:
      secondP = QPoint(x_pitch + use2, pitchY[0]);
      break;
    case high:
      secondP = QPoint(x_pitch + use2, pitchY[1]);
      break;
    case mid_high:
      secondP = QPoint(x_pitch + use2, pitchY[2]);
      break;
    case mid:
      secondP = QPoint(x_pitch + use2, pitchY[3]);
      break;
    case mid_low:
      secondP = QPoint(x_pitch + use2, pitchY[4]);
      break;
    case low:
      secondP = QPoint(x_pitch + use2, pitchY[5]);
      break;
    case very_low:
      secondP = QPoint(x_pitch + use2, pitchY[6]);
      break;
  }

  painter->drawLine(firstP, secondP);
}

QPointF SignView::closestPos(QPointF newPos) const noexcept
{
  auto& view = *(View*)parentItem();
  const QRectF rect = view.boundingRect();
  const auto height = rect.height();

  const auto w = view.defaultWidth();
  double offset = 80; // corresponds to the space of the 2 keys

  newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left() + offset)));
  newPos.setY(0);

  return newPos;
}

QRectF SignView::computeRect() const noexcept
{
  auto& view = *(View*)parentItem();
  const auto h = view.height();
  // const auto w = view.width();
  const auto w = view.defaultWidth(); // changé
  const QRectF rect{sign.start() * w, 0, sign.duration() * w, h};

  std::cout << "entré dans compute rect :\n"
            << "\n";
  std::cout << "largeur :" << sign.duration() * w << "\n";
  std::cout << "w :" << view.width() << "\n";

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
  float h = this->boundingRect().height();
  float w = this->boundingRect().width();

  const auto mods = QGuiApplication::keyboardModifiers();
  if (!(mods & Qt::ControlModifier) && !isSelected())
    m_presenter.on_deselectOtherSigns();

  if (event->pos().x() >= w - 10 && event->pos().y() <= h / 2)
  {
    auto& skin = score::Skin::instance(); // Scale
    this->setCursor(skin.CursorScaleH);
  }
  else if (event->pos().y() <= 10 && (2 <= event->pos().x() <= w - 2))
  {
    this->setCursor(Qt::PointingHandCursor); // Change grain
  }
  else if (event->pos().y() >= h - 10 && (2 <= event->pos().x() <= w - 2))
  {
    this->setCursor(Qt::PointingHandCursor); // Rhythmic speed
  }
  else if (event->pos().x() <= 10 && mods & Qt::NoModifier && event->pos().y() <= h / 2)
  {
    this->setCursor(Qt::PointingHandCursor); // Melo Variation
  }
  else if (event->pos().x() <= 10 && mods & Qt::ShiftModifier && event->pos().y() <= h / 2)
  {
    this->setCursor(Qt::UpArrowCursor); // Melo Pitch end
  }
  else if (event->pos().x() <= 10 && mods & Qt::ControlModifier && event->pos().y() <= h / 2)
  {
    this->setCursor(Qt::UpArrowCursor); // Melo Pitch
  }
  else if (event->pos().x() <= 10 && event->pos().y() >= h / 2)
  {
    this->setCursor(Qt::UpArrowCursor); // Vol start
  }
  else if (event->pos().x() >= w - 10 && event->pos().y() >= h / 2)
  {
    this->setCursor(Qt::UpArrowCursor); // Vol end
  }
  else
  {
    this->setCursor(Qt::ArrowCursor);
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

  float h = this->boundingRect().height();
  float w = this->boundingRect().width();

  m_action = None;

  if (canEdit())
  {
    std::cout << "x : " << event->pos().x() << ", y : " << event->pos().y() << "\n";
    std::cout << "w : " << w << ", h : " << h << "\n";

    if (event->pos().x() >= w - 10 && event->pos().y() <= h / 2)
    {
      m_action = Scale;
    }
    else if (event->pos().y() <= 10 && (2 <= event->pos().x() <= w - 2))
    {
      std::cout << "ChangeGrain \n";
      m_action = ChangeGrain;
    }
    else if (event->pos().y() >= h - 10 && (2 <= event->pos().x() <= w - 2))
    {
      std::cout << "ChangeRhythmicProfileSpeed \n";
      m_action = ChangeRhythmicProfileSpeed;
    }
    else if (event->pos().x() <= 10 && mods & Qt::NoModifier && event->pos().y() <= h / 2)
    {
      std::cout << "ChangeMelodicProfileVariation \n";
      m_action = ChangeMelodicProfileVariation;
    }
    else if (event->pos().x() <= 10 && mods & Qt::ShiftModifier && event->pos().y() <= h / 2)
    {
      std::cout << "ChangeMelodicProfilePitchEnd \n";
      m_action = ChangeMelodicProfilePitchEnd;
    }
    else if (event->pos().x() <= 10 && mods & Qt::ControlModifier && event->pos().y() <= h / 2)
    {
      std::cout << "ChangeMelodicProfilePitch \n";
      m_action = ChangeMelodicProfilePitch;
    }
    else if (event->pos().x() <= 10 && event->pos().y() >= h / 2)
    {
      std::cout << "ChangeSignVolumeStart \n";
      m_action = ChangeSignVolumeStart;
    }
    else if (event->pos().x() >= w - 10 && event->pos().y() >= h / 2)
    {
      std::cout << "ChangeSignVolumeEnd \n";
      m_action = ChangeSignVolumeEnd;
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
    switch (m_action)
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
    switch (m_action)
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
      case ChangeSignVolumeStart:
      {
        float v = sign.dynamicProfile().volumeStart + 0.2;
        v = v > 1. ? 0.2 : v;
        m_presenter.on_signVolumeStartChanged(sign, v);
        std::cout << "done on_signVolumeStartChanged\n";
        break;
      }
      case ChangeSignVolumeEnd:
      {
        float ve = sign.dynamicProfile().volumeEnd + 0.2;
        ve = ve > 1. ? 0.2 : ve;
        m_presenter.on_signVolumeEndChanged(sign, ve);
        std::cout << "done on_signVolumeEndChanged\n";
        break;
      }
      case ChangeMelodicProfilePitch:
      {
        Pitch p = (Pitch)(((int)sign.melodicProfile().pitch() + 1) % 7);
        m_presenter.on_signMelodicProfilePitchChanged(sign, p);
        std::cout << "done on_signPitchChanged\n";
        break;
      }
      case ChangeMelodicProfilePitchEnd:
      {
        Pitch pe = (Pitch)(((int)sign.melodicProfile().pitchEnd() + 1) % 7);
        m_presenter.on_signMelodicProfilePitchEndChanged(sign, pe);
        std::cout << "done on_signPitchEndChanged\n";
        break;
      }
      case ChangeMelodicProfileVariation:
      {
        Variation v = (Variation)(((int)sign.melodicProfile().variation() + 1) % 4);
        m_presenter.on_signMelodicProfileVariationChanged(sign, v);
        std::cout << "done on_signVariationChanged\n";
        break;
      }
      case ChangeRhythmicProfileSpeed:
      {
        Speed s = (Speed)(((int)sign.rhythmicProfile().speed() + 1) % 4);
        m_presenter.on_signRhythmicProfileSpeedChanged(sign, s);
        std::cout << "done on_signSpeedChanged\n";
        break;
      }
      case ChangeGrain:
      {
        Grain g = (Grain)(((int)sign.grain() + 1) % 4);
        m_presenter.on_signGrainChanged(sign, g);
        std::cout << "done on_signGrainChanged\n";
        break;
      }
      case ChangeRhythmicProfileAcceleration:
      {
        Acceleration a
            = (Acceleration)(((Acceleration)sign.rhythmicProfile().acceleration() + 1) % 3);
        m_presenter.on_signRhythmicProfileAccelerationChanged(sign, a);
        std::cout << "done on_signAccelerationChanged\n";
        break;
      }
      case None:
        break;
    }
  }
  event->accept();
  m_action = None;
}
}
