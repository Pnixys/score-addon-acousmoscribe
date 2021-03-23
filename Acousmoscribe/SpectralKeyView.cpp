#include "SpectralKeyView.hpp"


namespace Acousmoscribe
{

SpectralKeyView::SpectralKeyView(QGraphicsItem* parent)
    : QGraphicsItem{parent}
{
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemIsMovable, false);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    this->setAcceptHoverEvents(true);
}

void SpectralKeyView::paint(QPainter* p) const
{
}
}
