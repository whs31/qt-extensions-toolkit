//
// Created by whs31 on 27.10.2023.
//

#include "toolkit.h"
#include <QtExtensions/QMLRegistration>
#include <QtExtensionsToolkit/FileDialogModel>
#include <QtExtensionsToolkit/QuickGlobalPointerHolder>
#include <QtExtensionsToolkit/Theme>

inline void initResources()
{
  #if (QT_VERSION < QT_VERSION_CHECK(6, 2, 0))
  Q_INIT_RESOURCE(toolkit_js);
  Q_INIT_RESOURCE(toolkit_qml);
  Q_INIT_RESOURCE(toolkit_rc);
  #endif
}

namespace QtEx
{
  void Toolkit::registerTypes(const char* uri, int major, int minor) noexcept
  {
    qmlRegisterModule(uri, major, minor);
    qmlRegisterType<FileDialogModel>(uri, major, minor, "QtxFileDialogModel");
    qmlRegisterSingletonType<QuickGlobalPointerHolder>(uri, major, minor, "QtxGlobal", QuickGlobalPointerHolder::create);
    qmlRegisterSingletonType<Theme>(uri, major, minor, "Theme", Theme::create);

    qmlRegisterType(QUrl("qrc:/qtx/widgets/FileDialog.qml"), uri, major, minor, "QtxFileDialog");
  }
} // QtEx