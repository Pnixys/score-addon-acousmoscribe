#pragma once
#include <Acousmoscribe/View.hpp>
#include <QGraphicsItem>

namespace Acousmoscribe
{
class View;
class Presenter;
class SpectralKeyView final 
    : public QGraphicsItem
{
  Q_INTERFACES(QGraphicsItem)

public:
struct SK
{
  SK() = default;
};
  SpectralKeyView(QGraphicsItem* parent);
  SK SK() const noexcept;

private:
  void paint(QPainter*) const;
};
}
