#pragma once

#include <QGraphicsItem>
#include "Acousmoscribe/Model/SpectralKey.hpp"


namespace Acousmoscribe
{
class View;
class SpectralKeyView final
    : public QGraphicsItem
{
  Q_INTERFACES(QGraphicsItem)
public:
  SpectralKeyView(View* parent);

  void setWidth(qreal w) noexcept
  {
    if (m_width != w)
    {
      prepareGeometryChange();
      m_width = w;
    }
  }

  void setHeight(qreal h) noexcept
  {
    if (m_height != h)
    {
      prepareGeometryChange();
      m_height = h;
    }
  }

  QRectF boundingRect() const override { return {0, 0, m_width, m_height}; }
  void paint(QPainter* painter);


private:
  QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;



  float m_width{};
  float m_height{};

  enum Action {
    None,
    Move,
    Scale,
    ChangeVelocity,
    Duplicate
  } m_action{};
};
}
