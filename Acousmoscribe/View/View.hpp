#pragma once
#include <Acousmoscribe/Model/Process.hpp>
#include <Process/LayerView.hpp>

#include <QPainter>
#include <QPainterPath>

#include <Process/LayerView.hpp>

namespace Acousmoscribe
{
class SpectralKeyView;
class MelodicKeyView;
class View final : public Process::LayerView
{
    W_OBJECT(View)
public:
  explicit View(QGraphicsItem* parent);
  ~View() override;
  double defaultWidth() const noexcept { return m_defaultW; }
  void setDefaultWidth(double w);
  void deleteRequested() W_SIGNAL(deleteRequested);

  
  SignData signAtPos(QPointF point) const;

private:
  QBrush draw;

  struct SK spectralKey();
  void paint_impl(QPainter*) const override;

  void mousePressEvent(QGraphicsSceneMouseEvent*) override;
  void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent*) override;
  void keyPressEvent(QKeyEvent*) override;

  SpectralKeyView *m_spectralKey;
  MelodicKeyView *m_melodickey;

  QPainterPath m_selectArea;
  double m_defaultW; // Covers the [ 0; 1 ] area

  QPixmap m_textCache;
  QPixmap m_bgCache;

  mutable std::vector<QPainter::PixmapFragment> m_fragmentCache;
};
}
