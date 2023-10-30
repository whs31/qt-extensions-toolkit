//
// Created by whs31 on 27.10.2023.
//

#include "toolkit.h"
#include <QtExtensions/QMLRegistration>
#include <QtExtensionsToolkit/FileDialogModel>
#include <QtExtensionsToolkit/QuickGlobalPointerHolder>
#include <QtExtensionsToolkit/Theme>
#include <QtExtensionsToolkit/CircularReveal>
#include <QtExtensionsToolkit/FluentIcons>

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
    qmlRegisterType<CircularReveal>(uri, major, minor, "QtxCircularReveal");
    qmlRegisterSingletonType<QuickGlobalPointerHolder>(uri, major, minor, "QtxGlobal", QuickGlobalPointerHolder::create);
    qmlRegisterSingletonType<Theme>(uri, major, minor, "Theme", Theme::create);

    qmlRegisterType(QUrl("qrc:/qtx/widgets/FileDialog.qml"), uri, major, minor, "QtxFileDialog");
    qmlRegisterType(QUrl("qrc:/qtx/utils/ThemeChanger.qml"), uri, major, minor, "QtxThemeChanger");
    qmlRegisterType(QUrl("qrc:/qtx/ui/QtxText.qml"), uri, major, minor, "FluentText");
    qmlRegisterType(QUrl("qrc:/qtx/ui/QtxFocusRectangle.qml"), uri, major, minor, "FluentFocusRectangle");
    qmlRegisterType(QUrl("qrc:/qtx/ui/QtxButton.qml"), uri, major, minor, "FluentButton");
    qmlRegisterType(QUrl("qrc:/qtx/ui/QtxSwitch.qml"), uri, major, minor, "FluentSwitch");
    qmlRegisterType(QUrl("qrc:/qtx/ui/QtxTTFIcon.qml"), uri, major, minor, "FluentTTFIcon");
    qmlRegisterType(QUrl("qrc:/qtx/ui/QtxCheckbox.qml"), uri, major, minor, "FluentCheckbox");
    qmlRegisterType(QUrl("qrc:/qtx/ui/QtxTooltip.qml"), uri, major, minor, "FluentTooltip");
    qmlRegisterType(QUrl("qrc:/qtx/ui/QtxUIShadow.qml"), uri, major, minor, "FluentShadow");
    qmlRegisterType(QUrl("qrc:/qtx/ui/QtxSlider.qml"), uri, major, minor, "FluentSlider");

    qmlRegisterUncreatableMetaObject(Fluent::staticMetaObject, uri, major, minor, "FluentIcons", "Access to enums & flags only");
  }
} // QtEx