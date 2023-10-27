//
// Created by whs31 on 27.10.2023.
//

#pragma once

#include <QtCore/QObject>
#include <QtExtensions/QtExtensions>

namespace QtEx
{
  class ApplicationBase : public Qt::Object
  {
    Q_OBJECT

    public:
      explicit ApplicationBase(Qt::Object* parent = nullptr);
      virtual void start() = 0;
  };
} // QtEx

namespace QtEx
{
  inline ApplicationBase::ApplicationBase(Qt::Object* parent)
    : Qt::Object(parent)
  {}
} // QtEx