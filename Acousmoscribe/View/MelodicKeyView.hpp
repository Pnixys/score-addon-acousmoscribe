#pragma once
#include <QGraphicsItem>

#include <Acousmoscribe/Model/MelodicKey.hpp>
#include <Acousmoscribe/Presenter/Presenter.hpp>
#include <Acousmoscribe/View/View.hpp>

namespace Acousmoscribe
{
class Presenter;
class View;
class MelodicKeyView final
   : public QGraphicsItem
{
  Q_INTERFACES(QGraphicsItem)
public:
  const MelodicKey& melodicKey;

  MelodicKeyView(const MelodicKey& mk, Presenter& presenter, View* parent);

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

private:
  bool canEdit() const;
  void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

  Presenter& m_presenter;

  float m_width{};
  float m_height{};

  enum Action
  {
    None,
    ChangePitch,
    ChangeRange
  } m_action{};
};
}
