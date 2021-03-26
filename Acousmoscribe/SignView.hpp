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
  SignView(const Sign& n, Presenter& presenter, QGraphicsItem* parent);
  Sign Sign() const noexcept;

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
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

  QRectF computeRect() const noexcept;
  QPointF closestPos(QPointF sign) const noexcept;

private:
  bool canEdit() const;
  QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;
  void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
  void hoverMoveEvent(QGraphicsSceneHoverEvent* event) override;
  void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

  Presenter& m_presenter;

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