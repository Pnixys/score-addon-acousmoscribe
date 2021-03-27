#pragma once
#include <Acousmoscribe/View.hpp>
#include <QGraphicsItem>

namespace Acousmoscribe
{
/*struct MelodicKey
{
};*/

class MelodicKeyView final : public QGraphicsItem
{
public:
  MelodicKeyView(QGraphicsItem* parent);
};
}
