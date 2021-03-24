#include "SignView.hpp"


namespace Acousmoscribe
{

SignView::SignView(QGraphicsItem* parent)
    : QGraphicsItem{parent}
{
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemIsMovable, false);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    this->setAcceptHoverEvents(true);
}

void SignView::paint(QPainter* p) const
{
}
}
