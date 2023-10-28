//
// Created by whs31 on 28.10.2023.
//

#pragma once

#include <QtExtensions/QtExtensions>

namespace QtEx
{
  class FontProvider
  {
    public:
      [[maybe_unused]] static void setApplicationFont(const Qt::String& font) noexcept;
  };
} // QtEx

