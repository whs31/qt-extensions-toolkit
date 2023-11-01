//
// Created by whs31 on 27.10.2023.
//

#include "toolkit.h"
#include <QtExtensions/QMLRegistration>
#include <QtExtensionsToolkit/FileDialogModel>
#include <QtExtensionsToolkit/QuickGlobalPointerHolder>
#include <QtExtensionsToolkit/Theme>
#include <QtExtensionsToolkit/CircularReveal>

#if defined QTEXTENSIONS_TOOLKIT_FLUENT
#include <QtExtensionsToolkit/FluentIcons>
#include <QtExtensionsToolkit/FluentRectangle>
#endif

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
    initResources();
    qmlRegisterModule(uri, major, minor);
    qmlRegisterType<FileDialogModel>(uri, major, minor, "XFileDialogModel");
    qmlRegisterType<CircularReveal>(uri, major, minor, "XCircularReveal");
    qmlRegisterSingletonType<QuickGlobalPointerHolder>(uri, major, minor, "XGlobal", QuickGlobalPointerHolder::create);
    qmlRegisterSingletonType<Theme>(uri, major, minor, "Theme", Theme::create);

    qmlRegisterType(QUrl("qrc:/qtx/widgets/FileDialog.qml"), uri, major, minor, "XFileDialog");
    qmlRegisterType(QUrl("qrc:/qtx/utils/ThemeChanger.qml"), uri, major, minor, "XThemeChanger");

    #if defined QTEXTENSIONS_TOOLKIT_FLUENT
    qmlRegisterType<Fluent::Rectangle>(uri, major, minor, "FluentRectangle");]\

    qmlRegisterUncreatableMetaObject(Fluent::staticMetaObject, uri, major, minor, "FluentIcons", "Access to enums & flags only");
    #endif
  }
} // QtEx
