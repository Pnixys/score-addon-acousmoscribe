#pragma once

#include <QGraphicsItem>
#include "Acousmoscribe/Model/SpectralKey.hpp"
#include <Acousmoscribe/Presenter/Presenter.hpp>
#include <Acousmoscribe/View/View.hpp>

namespace Acousmoscribe
{
class View;
class Presenter;
class SpectralKey;
class SpectralKeyView final
    : public QGraphicsItem
{
  Q_INTERFACES(QGraphicsItem)
public:
  const SpectralKey& spectralKey;

  SpectralKeyView(const SpectralKey& sp, Presenter& presenter, View* parent);

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

  //QRectF boundingRect() const override { return {0, 0, 35, 70}; }
  QRectF boundingRect() const override { return {0, 0, m_width, m_height}; }
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

  QRectF computeRect() const noexcept;

private:
  bool canEdit() const;
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
  
  QVariant itemChange(GraphicsItemChange change, const QVariant& value) override;

  Presenter& m_presenter;

  float m_width{};
  float m_height{};

  enum Action {
    None,
    ChangeNature,
    ChangeNature2,
    ChangeRich2,
    ChangeRich,
    ChangeHybrid,
    ChangeHybrid2,
    ChangeWarped,
    ChangeWarped2
  } m_action{};
};
}
