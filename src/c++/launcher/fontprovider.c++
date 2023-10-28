//
// Created by whs31 on 28.10.2023.
//

#include "fontprovider.h"
#include <QtCore/QList>
#include <QtGui/QFont>
#include <QtGui/QFontDatabase>
#include <QtGui/QGuiApplication>

namespace QtEx
{
  void FontProvider::setApplicationFont(const Qt::String& font) noexcept
  {
    auto id = QFontDatabase::addApplicationFont(font);
    auto family = QFontDatabase::applicationFontFamilies(id)[0];
    QFont f(family);
    QGuiApplication::setFont(f);
  }
} // QtEx