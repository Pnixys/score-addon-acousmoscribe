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

}
