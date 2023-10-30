//
// Created by whs31 on 10/30/2023.
//

#pragma once

#include <QtCore/QList>
#include <QtGui/QColor>
#include <QtQuick/QQuickPaintedItem>
#include <QtExtensions/QtExtensions>

namespace Fluent
{
  class Rectangle : public QQuickPaintedItem
  {
    Q_OBJECT
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged FINAL)
    Q_PROPERTY(QList<int> radius READ radius WRITE setRadius NOTIFY radiusChanged FINAL)
    QML_NAMED_ELEMENT(FluentRectangle)

    public:
      explicit Rectangle(QQuickItem* parent = nullptr);

      [[nodiscard]] Qt::Color color() const;        void setColor(const Qt::Color);
      [[nodiscard]] QList<int> radius() const;      void setRadius(const QList<int>);

      void paint(QPainter* painter) override;

    signals:
      void colorChanged();
      void radiusChanged();

    private:
      Qt::Color m_color;
      QList<int> m_radius;
  };
} // Fluent


