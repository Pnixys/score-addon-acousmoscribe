#pragma once
#include <Acousmoscribe/Process.hpp>
#include <Process/LayerView.hpp>

#include <QPainter>
#include <QPainterPath>

#include <Process/LayerView.hpp>

namespace Acousmoscribe
{
class SpectralKeyView;
class View final : public Process::LayerView
{
    W_OBJECT(View)
public:
  explicit View(QGraphicsItem* parent);
  ~View() override;
  int visibleCount() const;

private:
  struct SK spectralkey();
  bool canEdit() const;
  void paint_impl(QPainter*) const override;

  QPainterPath m_selectArea;
  double m_defaultW; // Covers the [ 0; 1 ] area
  int m_min{0}, m_max{127};

  QPixmap m_textCache;
  QPixmap m_bgCache;

  mutable std::vector<QPainter::PixmapFragment> m_fragmentCache;
};
}
