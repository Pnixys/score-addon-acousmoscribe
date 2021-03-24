#pragma once
#include <Acousmoscribe/View.hpp>
#include <QGraphicsItem>

namespace Acousmoscribe
{
class View;
class Presenter;
class SignView final 
    : public QGraphicsItem
{
  Q_INTERFACES(QGraphicsItem)

public:
struct Sign
{
  Sign() = default;
};
  SignView(QGraphicsItem* parent);
  Sign Sign() const noexcept;

private:
  void paint(QPainter*) const;
};
}