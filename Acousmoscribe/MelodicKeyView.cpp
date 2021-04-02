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

    enum Range{
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
    if(m_pitch == very_high){

        /* DIFFERENCES */
        if(m_range == weak){
            p.setStyle(Qt::DotLine);

        }else if(m_range == normal){
            p.setStyle(Qt::DashDotLine);

        }else if(m_range == strong)
            p.setStyle(Qt::SolidLine);

        painter->setPen(p);
        painter->drawLine(QPoint(42, 8), QPoint(63, 8));

    /* HIGH */
    }else if(m_pitch == high){

        /* DIFFERENCES */
        if(m_range == weak){
            p.setStyle(Qt::DotLine);

        }else if(m_range == normal){
            p.setStyle(Qt::DashDotLine);

        }else if(m_range == strong)
            p.setStyle(Qt::SolidLine);

        painter->setPen(p);
        painter->drawLine(QPoint(42, 17), QPoint(63, 17));

    /* MID HIGH */
    }else if(m_pitch == mid_high){

        /* DIFFERENCES */
        if(m_range == weak){
            p.setStyle(Qt::DotLine);

        }else if(m_range == normal){
            p.setStyle(Qt::DashDotLine);

        }else if(m_range == strong)
            p.setStyle(Qt::SolidLine);

        painter->setPen(p);
        painter->drawLine(QPoint(42, 25), QPoint(63, 25));

    /* MID */
    }else if(m_pitch == mid){

        /* DIFFERENCES */
        if(m_range == weak){
            p.setStyle(Qt::DotLine);

        }else if(m_range == normal){
            p.setStyle(Qt::DashDotLine);

        }else if(m_range == strong)
            p.setStyle(Qt::SolidLine);

        painter->setPen(p);
        painter->drawLine(QPoint(42, 34), QPoint(63, 33));

    /* MID LOW */
    }else if(m_pitch == mid_low){

        /* DIFFERENCES */
        if(m_range == weak){
            p.setStyle(Qt::DotLine);

        }else if(m_range == normal){
            p.setStyle(Qt::DashDotLine);

        }else if(m_range == strong)
            p.setStyle(Qt::SolidLine);

        painter->setPen(p);
        painter->drawLine(QPoint(42, 43), QPoint(63, 43));

    /* LOW */
    }else if(m_pitch == low){

        /* DIFFERENCES */
        if(m_range == weak){
            p.setStyle(Qt::DotLine);

        }else if(m_range == normal){
            p.setStyle(Qt::DashDotLine);

        }else if(m_range == strong)
            p.setStyle(Qt::SolidLine);

        painter->setPen(p);
        painter->drawLine(QPoint(42, 52), QPoint(63, 52));

    /* VERY LOW */
    }else if(m_pitch == very_low){

        /* DIFFERENCE */
        if(m_range == weak){
            p.setStyle(Qt::DotLine);

        }else if(m_range == normal){
            p.setStyle(Qt::DashDotLine);

        }else if(m_range == strong)
            p.setStyle(Qt::SolidLine);

        painter->setPen(p);
        painter->drawLine(QPoint(42, 61), QPoint(63, 61));
    }

}

}
