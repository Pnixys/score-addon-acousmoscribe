#include "SignView.hpp"

#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>
#include <QPainter>

#include <Acousmoscribe/Model/Sign.hpp>
#include <Acousmoscribe/Presenter.hpp>
#include <Acousmoscribe/View.hpp>

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
  float h = boundingRect().height()*0.99;

  Grain grain = sign.grain();
  Speed speed = sign.rhythmicProfile().speed();
  Acceleration acc = sign.rhythmicProfile().acceleration();

  double duration = sign.duration();
  double attack = sign.dynamicProfile().attack;
  double release = sign.dynamicProfile().release;
  float volumeStart = sign.dynamicProfile().volumeStart;
  float volumeEnd = sign.dynamicProfile().volumeEnd;
  float volumeUsed;

  Pitch pitch = sign.melodicProfile().pitch();
  Pitch pitchEnd = sign.melodicProfile().pitchEnd();

  float x_pitch;
    if(attack+volumeStart > 1)
           attack = 1-volumeStart;
       if(release > volumeStart)
           release = volumeStart;

        QPointF a(x_left, h);
        QPointF b(x_left, h*(1-volumeStart));
        QPointF c;
        QPointF d(x_right, h);

        /* DYNAMIC */
       if(attack > 0.0){
           c = QPointF(x_right, h*(1-volumeStart-attack));
           volumeEnd = volumeStart+attack;

        }else if (release > 0.0){
           c = QPointF(x_right, h*(1-volumeStart+release));
           volumeEnd = volumeStart-release;

       }else{
           c = QPointF(x_right, h*(1-volumeEnd));
       }

       volumeUsed = std::max(volumeStart, volumeEnd);
       if(volumeUsed == volumeStart){
           x_pitch = w*(duration*0.05);
       }else{
           x_pitch = w*(duration*0.95);
       }

       p.setStyle(Qt::DotLine);
       painter->setBrush(Qt::white);
       painter->setPen(p);
       QPointF points[4] = {a,b,c,d};
       painter->drawPolygon(points, 4);
       p.setCapStyle(Qt::RoundCap);
       painter->setPen(p);

       /* RHYTHMIC */
       switch (grain) {
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

       switch (speed) {
        case slow:
           p.setStyle(Qt::DashLine);
           break;
        case medium:
           p.setStyle(Qt::DashDotLine);
           break;
        case fast:
           p.setStyle(Qt::DotLine);
           break;
        default :
           break;
       }

       painter->setPen(p);
       painter->drawLine(d, a);

       p.setStyle(Qt::SolidLine);
       painter->setPen(p);
       painter->drawLine(a, b);
       painter->drawLine(c, d);

       float h_acc = h - std::min(h*volumeStart/3, h*volumeEnd/3);


       /* ACCELERATION */
       switch (acc) {
       case decelerating:
           painter->drawLine(QPointF(x_left+w/10, h), QPointF(x_left+w/10, h_acc));
           break;
       case accelerating:
           painter->drawLine(QPointF(x_right-w/10, h), QPointF(x_right-w/10, h_acc));
           break;
       default:
           break;
       }

       /* MELODIC */
       p.setWidth(2);
       painter->setPen(p);

         float h_pitch = volumeUsed*0.65;
         float y_pitch;

         float att_rel = 1;
         if(attack > 0)
            att_rel = -1;

         float pitchY[7];

         for (int i = 1; i <= 7; i++)
         {
             y_pitch = h-volumeUsed*h + i*h_pitch*h/5;
           pitchY[i-1] = y_pitch;
           if (i == 4)
           {
             p.setWidth(4); // the 4th point is bigger
             painter->setPen(p);
             painter->drawPoint(QPoint(x_pitch, y_pitch));
             p.setWidth(2);
             painter->setPen(p);
           }
           else{
            painter->drawPoint(QPoint(x_pitch, y_pitch));
           }

         }
         p.setWidth(1);
         painter->setPen(p);


     QPoint firstP;
     QPoint secondP;

     painter->setPen(p);

     float use1, use2;
     if(attack > 0){
         use1 = w*(att_rel*(0.025+0.04));
         use2 = 0.05*w*att_rel;
     }else{
         use1 = 0.05*w*att_rel;
         use2 = w*(att_rel*(0.025+0.04));
     }


     switch(pitch){
        case very_high :
         firstP = QPoint(x_pitch+use1, pitchY[0]);
         break;
        case high:
            firstP = QPoint(x_pitch+use1, pitchY[1]);
            break;

     case mid_high :
         firstP = QPoint(x_pitch+use1, pitchY[2]);
         break;
     case mid:
         firstP = QPoint(x_pitch+use1, pitchY[3]);
         break;
     case mid_low:
      firstP = QPoint(x_pitch+use1, pitchY[4]);
      break;

        case low:
         firstP = QPoint(x_pitch+use1, pitchY[5]);
         break;

        case very_low:
         firstP = QPoint(x_pitch+use1, pitchY[6]);
         break;

    }

     switch (pitchEnd){
     case very_high:
         secondP =  QPoint(x_pitch+use2, pitchY[0]);
         break;
     case high:
         secondP =  QPoint(x_pitch+use2, pitchY[1]);
         break;
     case mid_high:
         secondP =  QPoint(x_pitch+use2, pitchY[2]);
         break;
     case mid:
         secondP =  QPoint(x_pitch+use2, pitchY[3]);
         break;
     case mid_low:
         secondP =  QPoint(x_pitch+use2, pitchY[4]);
         break;
     case low:
         secondP =  QPoint(x_pitch+use2, pitchY[5]);
         break;
     case very_low:
         secondP =  QPoint(x_pitch+use2, pitchY[6]);
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
  const QRectF rect{
    sign.start() * w, 
    0, 
    sign.duration() * w, 
    h};

  std::cout << "entré dans compute rect :\n" << "\n";
  std::cout << "largeur :" << sign.duration()*w << "\n";
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
  if (event->pos().x() >= this->boundingRect().width() - 2)
  {
    auto& skin = score::Skin::instance();
    this->setCursor(skin.CursorScaleH);
  }
  else
  {
    if (qApp->keyboardModifiers() == Qt::ShiftModifier)
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
      /*case ChangeVelocity:
        m_presenter.on_requestVelocityChange(sign, event->buttonDownScenePos(Qt::LeftButton).y() -
        event->scenePos().y()); break;*/
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
        //this->setWidth(std::max(2., event->pos().x()));
        //m_presenter.on_signScaled(sign, m_width / ((View*)parentItem())->defaultWidth());
        break;
      case Duplicate:
        m_presenter.on_signDuplicate();
        break;
      case ChangeSignVolumeIn:
        // m_presenter.on_signVolumeInChanged(sign, (sign.dynamicProfile().volumeStart+0.1)%1);
        break;
      case ChangeSignVolumeOut:
        // m_presenter.on_signVolumeOutChanged(sign, (sign.dynamicProfile().volumeEnd+0.1)%1.0);
        break;
      case ChangeMelodicProfilePitch:
        // m_presenter.on_signMelodicProfilePitchChanged(sign,
        // (sign.melodicProfile().pitch()+1)%7.0);
        break;
      case ChangeMelodicProfilePitchEnd:
        // m_presenter.on_signMelodicProfilePitchEndChanged(sign,
        // (sign.melodicProfile().pitchEnd()+1)%7.0);
        break;
      case ChangeMelodicProfileVariation:
        m_presenter.on_signMelodicProfileVariationChanged(sign, none);
        break;
      case ChangeRhythmicProfileSpeed:
        m_presenter.on_signRhythmicProfileSpeedChanged(sign, continuous);
        break;
      case ChangeGrain:
        // TODO recup le grain voulu
        m_presenter.on_signGrainChanged(sign, smooth);
        break;
      /*case ChangeVelocity:
        m_presenter.on_requestVelocityChange(note, event->buttonDownScenePos(Qt::LeftButton).y() -
        event->scenePos().y()); m_presenter.on_velocityChangeFinished(); break;*/
      case None:
        break;

        // TODO START ?
    }
  }
  event->accept();
  m_action = None;
}
}
