// This is an open source non-commercial project. Dear PVS-Studio, please check
// it. PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <QCursor>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>
#include <QPainter>
#include <QPoint>

#include <Acousmoscribe/Presenter/Presenter.hpp>
#include <Acousmoscribe/View/SpectralKeyView.hpp>
#include <Acousmoscribe/View/View.hpp>

namespace Acousmoscribe
{
SpectralKeyView::SpectralKeyView(const SpectralKey& sk, Presenter& p, View* parent)
    : QGraphicsItem{parent}, spectralKey{sk}, m_presenter{p}, m_action{None}
{
  this->setFlag(QGraphicsItem::ItemIsSelectable, true);
  this->setFlag(QGraphicsItem::ItemIsMovable, false);
  this->setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
  this->setAcceptHoverEvents(true);
}

void SpectralKeyView::paint(
    QPainter* painter,
    const QStyleOptionGraphicsItem* option,
    QWidget* widget)
{
  float w = m_width;
  float h = m_height*0.99;

  Nature nature = spectralKey.nature();
  Nature nature2 = spectralKey.nature2();
  bool rich = spectralKey.isRich();
  bool rich2 = spectralKey.isRich2();
  bool hybrid = spectralKey.isHybrid();
  bool hybrid2 = spectralKey.isHybrid2();
  bool warped = spectralKey.isWarped();
  bool warped2 = spectralKey.isWarped2();

  QPen p;
  p.setColor(Qt::black);
  p.setWidth(1);
  painter->setPen(p);

  /* Background Rect */

  painter->setBrush(Qt::white);
  painter->drawRect(boundingRect().adjusted(0., 0., 0., 0));

  if (hybrid)
  {
    switch (nature)
    {

      case tonic_inharmonic:
        p.setStyle(Qt::DashLine);
        nature = inharmonic;
        break;

      case noisy_tonic:
        p.setStyle(Qt::DotLine);
        nature = tonic;
        break;

      case noisy_inharmonic:
        p.setStyle(Qt::DotLine);
        nature = inharmonic;
        break;

      default:
        break;
    }
  }

  painter->setPen(p);

  switch (nature)
  {
    case tonic:
      if (warped)
      {
        painter->drawLine(QPoint(w / 5, h / 1.05), QPoint(w / 1.5, h / 1.5));
        painter->drawLine(QPoint(w / 1.5, h / 1.5), QPoint(w / 1.05, h / 5));
      }
      else
      {
        painter->drawLine(QPoint(w / 5, h / 1.05), QPoint(w / 1.05, h / 5));
      }
      break;

    case inharmonic:
      painter->drawArc(QRectF(w / 11, h / 30, w / 3, h / 3), 9900, 2000);
      break;

    case noise:
      p.setWidth(4);
      painter->setPen(p);
      painter->drawPoint(w / 2.5, h / 2.5);
      p.setWidth(1);
      painter->setPen(p);
      break;

    default:
      break;
  }

  if (hybrid2)
  {
    switch (nature2)
    {

      case tonic_inharmonic:
        p.setStyle(Qt::DashLine);
        nature2 = inharmonic;
        break;

      case noisy_tonic:
        p.setStyle(Qt::DotLine);
        nature2 = tonic;
        break;

      case noisy_inharmonic:
        p.setStyle(Qt::DotLine);
        nature2 = inharmonic;
        break;

      default:
        break;
    }
  }
  painter->setPen(p);

  switch (nature2)
  {
    case tonic:
      if (warped2)
      {
        painter->drawLine(QPoint(w / 10, h / 1.2), QPoint(w / 1.7, h / 2.1));
        painter->drawLine(QPoint(w / 1.7, h / 2.1), QPoint(w / 1.2, h / 10));
      }
      else
      {
        painter->drawLine(QPoint(w / 10, h / 1.2), QPoint(w / 1.2, h / 10));
      }
      break;

    case inharmonic:
      painter->drawArc(QRectF(w / 11, h / 30, w / 2, h / 2), 9900, 2000);
      break;

    case noise:
      p.setWidth(4);
      painter->setPen(p);
      painter->drawPoint(w / 1.3, h / 1.3);
      p.setWidth(1);
      painter->setPen(p);
      break;

    default:
      break;
  }

  p.setStyle(Qt::SolidLine);
  painter->setPen(p);

  switch (rich)
  {
    case true:
      if (nature == tonic)
      {
        painter->drawLine(QPoint(w / 1.08, h / 6), QPoint(w / 1.015, h / 4.25));
        painter->drawLine(QPoint(w / 6, h / 1.1), QPoint(w / 4.5, h / 1.02));
      }
      else if (nature == inharmonic)
      {
        painter->drawLine(QPoint(w / 2.3, h / 9.6), QPoint(w / 2.6, h / 6.2));
        painter->drawLine(QPoint(w / 4.15, h / 2.85), QPoint(w / 4.9, h / 2.6));
      }
      else if (nature == noise)
      {
        painter->drawLine(QPoint(w / 2.6, h / 4.2), QPoint(w / 3.7, h / 2.8));
        if (nature2 != noise)
          painter->drawLine(QPoint(w / 2.45, h / 2), QPoint(w / 1.85, h / 2.7));
      }
      break;

    default:
      break;
  }

  switch (rich2)
  {
    case true:
      if (nature2 == tonic)
      {
        painter->drawLine(QPoint(w / 1.15, h / 7.2), QPoint(w / 1.25, h / 14.8));
        painter->drawLine(QPoint(w / 14.8, h / 1.25), QPoint(w / 6.8, h / 1.12));
      }
      else if (nature2 == inharmonic)
      {
        painter->drawLine(QPoint(w / 1.9, h / 4.2), QPoint(w / 1.7, h / 6.4));
        painter->drawLine(QPoint(w / 3.1, h / 2), QPoint(w / 3.9, h / 1.8));
      }
      else if (nature2 == noise)
      {
        painter->drawLine(QPoint(w / 1.2, h / 1.1), QPoint(w / 1.05, h / 1.3));
        if (nature == noise)
        {
          painter->drawLine(QPoint(w / 2, h / 1.65), QPoint(w / 1.5, h / 2.3));
        }
        else
        {
          painter->drawLine(QPoint(w / 1.55, h / 1.3), QPoint(w / 1.3, h / 1.6));
        }
      }
      break;

    default:
      break;
  }
}

QRectF SpectralKeyView::computeRect() const noexcept
{
  auto& view = *(View*)parentItem();
  const auto h = view.height();
  const auto w = view.defaultWidth();
  const QRectF rect{
      0, // 35 à changer (instant de départ)
      0,
      60,
      h};

  return rect;
}

bool SpectralKeyView::canEdit() const
{
  return boundingRect().height() > 5;
}

void SpectralKeyView::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
  std::cout << "in SPECTRAL mousePressEvent\n";

  const auto mods = QGuiApplication::keyboardModifiers();
  if (!(mods & Qt::ControlModifier) && !isSelected())
    m_presenter.on_deselectOtherSigns();

  float h = this->boundingRect().height();
  float w = this->boundingRect().width();

  m_action = None;

  if (canEdit())
  {
    if (event->pos().x() <= w/2 && event->pos().y() >= h / 2 && mods & Qt::NoModifier)
    {
      m_action = ChangeNature;
    }
    else if (event->pos().x() <= w/2 && event->pos().y() <= h / 2 && mods & Qt::NoModifier)
    {
      m_action = ChangeRich;
    }
    else if (event->pos().x() >= w/2 && event->pos().y() <= h / 2 && mods & Qt::NoModifier)
    {
      m_action = ChangeHybrid;
    }
    else if (event->pos().x() >= w/2 && event->pos().y() >= h / 2 && mods & Qt::NoModifier)
    {
      m_action = ChangeWarped;
    }
    else if (event->pos().x() <= w/2 && event->pos().y() >= h / 2 && mods & Qt::AltModifier)
    {
      m_action = ChangeNature2;
    }
    else if (event->pos().x() <= w/2 && event->pos().y() <= h / 2 && mods & Qt::AltModifier)
    {
      m_action = ChangeRich2;
    }
    else if (event->pos().x() >= w/2 && event->pos().y() <= h / 2 && mods & Qt::AltModifier)
    {
      m_action = ChangeHybrid2;
    }
    else if (event->pos().x() >= w/2 && event->pos().y() >= h / 2 && mods & Qt::AltModifier)
    {
      m_action = ChangeWarped2;
    }
    else
    {
      m_action = None;
    }
  }
  event->accept();
}

void SpectralKeyView::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
  std::cout << "in  SPECTRAL mouseReleaseEvent\n";

  if (canEdit())
  {
    switch (m_action)
    {
      case ChangeNature:{
        Nature n = (Nature) (((int) spectralKey.nature() + 1)%7);
        m_presenter.on_spectralKeyNatureChanged(spectralKey, n);
        std::cout << "in changeNature\n";
        break;
      }
      case ChangeNature2:{
        Nature n = (Nature) (((int) spectralKey.nature2() + 1)%7);
        m_presenter.on_spectralKeyNature2Changed(spectralKey, n);
        std::cout << "in changeNature2\n";
        break;
      }
      case ChangeRich:{
        bool b = !(spectralKey.isRich());
        m_presenter.on_spectralKeyIsRichChanged(spectralKey, b);
        break;
      }
      case ChangeRich2:{
        bool b = !(spectralKey.isRich2());
        m_presenter.on_spectralKeyIsRich2Changed(spectralKey, b);
        break;
      }
      case ChangeHybrid:{
        bool b = !(spectralKey.isHybrid());
        m_presenter.on_spectralKeyIsHybridChanged(spectralKey, b);
        break;
      }
      case ChangeHybrid2:{
        bool b = !(spectralKey.isHybrid2());
        m_presenter.on_spectralKeyIsHybrid2Changed(spectralKey, b);
        break;
      }
      case ChangeWarped:{
        bool b = !(spectralKey.isWarped());
        m_presenter.on_spectralKeyIsWarpedChanged(spectralKey, b);
        break;
      }
      case ChangeWarped2:{
        bool b = !(spectralKey.isWarped2());
        m_presenter.on_spectralKeyIsWarped2Changed(spectralKey, b);
        break;
      }
    }
  }
  event->accept();
  m_action = None;
}

QVariant
SpectralKeyView::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
  switch (change)
  {
    case QGraphicsItem::ItemSelectedChange:
    {
      this->setZValue(10 * (int)value.toBool());
      break;
    }
    default:
      break;
  }

  return QGraphicsItem::itemChange(change, value);
}
}
