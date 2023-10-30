//
// Created by whs31 on 10/30/2023.
//

#include "fluentrectangle.h"
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>

namespace Fluent
{
  Rectangle::Rectangle(QQuickItem* parent)
    : QQuickPaintedItem(parent)
    , m_color("white")
    , m_radius({0, 0, 0, 0})
  {}

  Qt::Color Rectangle::color() const { return m_color; }
  void Rectangle::setColor(const Qt::Color x) {
    m_color = x;
    emit colorChanged();
    this->update();
  }

  QList<int> Rectangle::radius() const { return m_radius; }
  void Rectangle::setRadius(const QList<int> x) {
    m_radius = x;
    emit radiusChanged();
    this->update();
  }

  void Rectangle::paint(QPainter* painter)
  {
    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    QRectF rect = boundingRect();
    path.moveTo(rect.bottomRight() - QPointF(0, radius()[2]));
    path.lineTo(rect.topRight() + QPointF(0, radius()[1]));
    path.arcTo(QRectF(QPointF(rect.topRight() - QPointF(radius()[1] * 2, 0)), QSize(radius()[1] * 2, radius()[1] * 2)), 0, 90);
    path.lineTo(rect.topLeft() + QPointF(radius()[0], 0));
    path.arcTo(QRectF(QPointF(rect.topLeft()), QSize(radius()[0] * 2, radius()[0] * 2)), 90, 90);
    path.lineTo(rect.bottomLeft() - QPointF(0, radius()[3]));
    path.arcTo(QRectF(QPointF(rect.bottomLeft() - QPointF(0, radius()[3] * 2)), QSize(radius()[3] * 2, radius()[3] * 2)), 180, 90);
    path.lineTo(rect.bottomRight() - QPointF(radius()[2], 0));
    path.arcTo(QRectF(QPointF(rect.bottomRight() - QPointF(radius()[2] * 2, radius()[2] * 2)), QSize(radius()[2] * 2, radius()[2] * 2)), 270, 90);
    painter->fillPath(path, color());
    painter->restore();
  }
} // Fluent