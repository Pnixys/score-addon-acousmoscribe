// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <Acousmoscribe/View.hpp>
#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <Acousmoscribe/SpectralKeyView.hpp>
#include <QGuiApplication>
#include <QPainter>
#include <QPoint>
namespace Acousmoscribe
{
SpectralKeyView::SpectralKeyView(View* parent)
  : QGraphicsItem{parent}
  , m_action{None}
{
  this->setFlag(QGraphicsItem::ItemIsSelectable, true);
  this->setFlag(QGraphicsItem::ItemIsMovable, true);
  this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
  this->setAcceptHoverEvents(true);
}

void SpectralKeyView::paint(QPainter* painter)
{
    //TODO RENDRE RECT INVISIBLE
    /*static const MidiStyle s;

  painter->setRenderHint(QPainter::Antialiasing, false);
  if (m_width <= 1.2)
  {
    painter->setPen(this->isSelected() ? s.noteSelectedBasePen : s.noteBasePen);
    painter->drawLine(0, 0, 0, m_height - 1.5);
  }
  else
  {
    painter->setPen(this->isSelected() ? s.noteSelectedBasePen : Qt::NoPen);
    painter->setBrush(s.paintedNoteBrush[note.velocity()]);*/

    QPen p;
    p.setColor(Qt::black);
    p.setWidth(1);
    painter->setPen(p);
    painter->setBrush(Qt::white);
    painter->drawRect(QRect(0,0,35,70));
    

    enum Nature
    {
        null = 0,
        tonic,
        inharmonic,
        noise
    };

    Nature m_nature = noise;
    Nature m_nature2 = inharmonic;
    bool m_isRich = true;
    bool m_isRich2 = true;
    bool m_isHybrid = true;

    /* TONIC */
    if(m_nature == tonic){
        if(m_nature2 == noise){
            p.setStyle(Qt::DotLine);
            painter->setPen(p);
        }

        /* HYBRID */
        if(m_nature2 == inharmonic){
            p.setStyle(Qt::DashLine);
            painter->setPen(p);
            painter->drawArc(QRectF(3,5,25,30), 15000, 2000);
            if(m_isRich){
                p.setStyle(Qt::SolidLine);
                painter->setPen(p);
                painter->drawLine(QPoint(2, 28), QPoint(6, 28));
                painter->drawLine(QPoint(25, 23), QPoint(30, 23));
            }

        /* GROUP */
        }else if(m_nature2 == tonic){
            p.setStyle(Qt::SolidLine);
            painter->setPen(p);
            painter->drawLine(QPoint(12, 56), QPoint(28, 16));
            painter->drawLine(QPoint(10, 44), QPoint(18, 25));

            if(m_isRich2){
                painter->drawLine(QPoint(8, 43), QPoint(11, 46));
                painter->drawLine(QPoint(16, 23), QPoint(19, 26));
            }
            if(m_isRich){
                painter->drawLine(QPoint(10, 54), QPoint(14, 58));
                painter->drawLine(QPoint(26, 14), QPoint(30, 18));
            }

        }else{
            painter->drawLine(QPoint(9, 55), QPoint(25, 15));
            if(m_isRich == true)
                p.setStyle(Qt::SolidLine);
                painter->setPen(p);
                painter->drawLine(QPoint(6, 54), QPoint(10, 56));
                painter->drawLine(QPoint(22, 14), QPoint(26, 16));
        }

    /* INHARMONIC */
    }else if(m_nature == inharmonic){

        /* HYBRID TONIC */
        if(m_nature2 == tonic){
            p.setStyle(Qt::DashLine);
            painter->setPen(p);
        }

        /* HYBRID NOISE */
        if(m_nature2 == noise){
            p.setStyle(Qt::DotLine);
            p.setWidth(2);
            QVector<qreal> dashes;
            qreal space = 2;
            dashes << 1 << space << 1 << space << 1 << space << 1 << space << 1 << space << 1;
            p.setDashPattern(dashes);
            painter->setPen(p);
            painter->drawArc(QRectF(3,5,25,30), 15000, 2000);

        }else{
            painter->drawArc(QRectF(3,5,25,30), 15000, 2000);
        }
        if(m_isRich == true){
            p.setWidth(1);
            p.setStyle(Qt::SolidLine);
            painter->setPen(p);
            painter->drawLine(QPoint(2, 28), QPoint(6, 28));
            painter->drawLine(QPoint(25, 23), QPoint(30, 23));
        }

        /* GROUP */
        if(m_nature2 == inharmonic){
            painter->drawArc(QRectF(5,4,20,23), 15258, 1400);
            if(m_isRich2 == true){
                painter->drawLine(QPoint(6, 24), QPoint(12, 24));
                painter->drawLine(QPoint(19, 22), QPoint(24, 22));
            }
        }

    /* NOISE */
    }else if(m_nature == noise){
        p.setWidth(3);
        painter->setPen(p);

        /* GROUP */
        if(m_nature2 == noise){
            painter->drawPoint(QPoint(14, 30));
            painter->drawPoint(QPoint(20, 37));
            if(m_isRich){
                p.setWidth(1);
                painter->setPen(p);
                painter->drawLine(QPoint(8, 28), QPoint(14, 24));
                painter->drawLine(QPoint(14, 36), QPoint(20, 32));
            }
            if(m_isRich2){
                p.setWidth(1);
                painter->setPen(p);
                painter->drawLine(QPoint(14, 36), QPoint(20, 32));
                painter->drawLine(QPoint(20, 44), QPoint(26, 40));
            }
        }else{
            /* HYBRID INHARMONIC */
            if(m_nature2 == inharmonic){
                p.setStyle(Qt::DotLine);
                p.setWidth(2);
                QVector<qreal> dashes;
                qreal space = 2;
                dashes << 1 << space << 1 << space << 1 << space << 1 << space << 1 << space << 1;
                if(m_isRich == true){
                    p.setWidth(1);
                    p.setStyle(Qt::SolidLine);
                    painter->setPen(p);
                    painter->drawLine(QPoint(2, 28), QPoint(6, 28));
                    painter->drawLine(QPoint(25, 23), QPoint(30, 23));                p.setDashPattern(dashes);
                painter->setPen(p);
                painter->drawArc(QRectF(3,5,25,30), 15000, 2000);
                if(m_isRich2 == true){
                    p.setWidth(1);
                    p.setStyle(Qt::SolidLine);
                    painter->setPen(p);
                    painter->drawLine(QPoint(2, 28), QPoint(6, 28));
                    painter->drawLine(QPoint(25, 23), QPoint(30, 23));
            }else{
                painter->drawPoint(QPoint(17, 35));
                if(m_isRich == true){
                    p.setWidth(1);
                    painter->setPen(p);
                    painter->drawLine(QPoint(12, 38), QPoint(16, 40));
                    painter->drawLine(QPoint(18, 31), QPoint(22, 33));
                }
            }
            }
        }
   }
}
}




QVariant SpectralKeyView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
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
}

