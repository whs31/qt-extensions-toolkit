//
// Created by whs31 on 27.10.2023.
//

#include "toolkit.h"
#include <QtExtensions/QMLRegistration>
#include <QtExtensionsToolkit/FileDialogModel>
#include <QtExtensionsToolkit/QuickGlobalPointerHolder>

namespace QtEx
{
  void Toolkit::registerTypes(const char* uri, int major, int minor) noexcept
  {
    qmlRegisterModule(uri, major, minor);
    qmlRegisterType<FileDialogModel>(uri, major, minor, "XFileDialogModel");
    qmlRegisterSingletonType<QuickGlobalPointerHolder>(uri, major, minor, "XGlobal", QuickGlobalPointerHolder::create);
  }
} // QtEx