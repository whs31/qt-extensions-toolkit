//
// Created by whs31 on 27.10.2023.
//

#pragma once

#include <QtCore/QCoreApplication>

#if defined(QT_GUI_LIB)
#include <QtGui/QGuiApplication>
#endif

#if defined(QT_WIDGETS_LIB)
#include <QtWidgets/QApplication>
#endif
