#include "MelodicKeyView.hpp"

//W_OBJECT_IMPL(Midi::Note)

namespace Acousmoscribe
{

MelodicKeyView::MelodicKeyView(QGraphicsItem* parent)
    : QGraphicsItem{parent}
{
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemIsMovable, false);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    this->setAcceptHoverEvents(true);
}

void MelodicKeyView::paint(QPainter* painter)
{
    QPen p;
    p.setColor(Qt::black);
    p.setWidth(1);
    painter->setPen(p);
    painter->setBrush(Qt::white);
    painter->drawRect(QRect(35,0,35,70));
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

    Pitch m_pitch = very_high;

    /* MELODIQUE */
    p.setWidth(3);
    p.setStyle(Qt::SolidLine);
    painter->setPen(p);
    painter->drawPoint(QPoint(42, 8));
    painter->drawPoint(QPoint(42, 17));
    painter->drawPoint(QPoint(42, 25));
    painter->drawPoint(QPoint(42, 33));
    painter->drawPoint(QPoint(42, 41));
    painter->drawPoint(QPoint(42, 49));
    painter->drawPoint(QPoint(42, 58));

    if(m_pitch == very_high){
        painter->drawPoint(QPoint(53, 8)); //1st point
        painter->drawPoint(QPoint(63, 8));
    }else if(m_pitch == high){
        painter->drawPoint(QPoint(53, 17)); //2nd point
        painter->drawPoint(QPoint(63, 17));
    }else if(m_pitch == mid_high){
        painter->drawPoint(QPoint(53, 25)); //3d point
        painter->drawPoint(QPoint(63, 25));
    }else if(m_pitch == mid){
        painter->drawPoint(QPoint(53, 33)); //4th point
        painter->drawPoint(QPoint(63, 33));
    }else if(m_pitch == mid_low){
        painter->drawPoint(QPoint(53, 41)); //5th point
        painter->drawPoint(QPoint(63, 41));
    }else if(m_pitch == low){
        painter->drawPoint(QPoint(53, 49)); //6th point
        painter->drawPoint(QPoint(63, 49));
    }else if(m_pitch == very_low){
    painter->drawPoint(QPoint(53, 58)); //7th point
    painter->drawPoint(QPoint(63, 58));
    }
}

}
