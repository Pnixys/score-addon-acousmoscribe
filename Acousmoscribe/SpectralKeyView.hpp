#pragma once

#include <QGraphicsItem>
#include "Acousmoscribe/Model/SpectralKey.hpp"


namespace Acousmoscribe
{
class View;
class SpectralKey;
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

  QRectF boundingRect() const override { return {0, 0, 35, 70}; }
  void paint(QPainter* painter);


private:
  QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

  SpectralKey *m_spectralKey;


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
