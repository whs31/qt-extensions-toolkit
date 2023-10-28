cmake_minimum_required(VERSION 3.15)

project(QtExtensionsToolkit
  VERSION 0.0.1
  DESCRIPTION "Qt Extensions App Toolkit Library"
  HOMEPAGE_URL "io.github.whs31"
  LANGUAGES C CXX
)

if(NOT CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD 17)
    set(CMAKE_C_STANDARD_REQUIRED OFF)
    set(CMAKE_C_EXTENSIONS OFF)
endif(NOT CMAKE_C_STANDARD)

if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif(NOT CMAKE_CXX_STANDARD)

if(TARGET ${PROJECT_NAME})
    return()
endif()

if(NOT TARGET QtExtensions)
    message(FATAL_ERROR "[Qt Extensions Toolkit] No Qt Extensions library found.")
endif()

set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOMOC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED
  COMPONENTS
    Core
    Quick
    Widgets
)

enable_testing()
include_directories(src/c++ include)

add_library(${PROJECT_NAME} STATIC)
target_sources(${PROJECT_NAME}
  PUBLIC
    include/QtExtensionsToolkit/ApplicationBase
    include/QtExtensionsToolkit/FileDialogModel
    include/QtExtensionsToolkit/FontProvider
    include/QtExtensionsToolkit/ISettingsProvider
    include/QtExtensionsToolkit/Launcher
    include/QtExtensionsToolkit/MonoJsonSettingsProvider
    include/QtExtensionsToolkit/QApplicationSelector
    include/QtExtensionsToolkit/QuickGlobalPointerHolder
    include/QtExtensionsToolkit/Register
    include/QtExtensionsToolkit/Settings

    resources/toolkit_rc.qrc
    src/js/toolkit_js.qrc
    src/qml/toolkit_qml.qrc
  PRIVATE
    src/c++/launcher/applicationbase.h
    src/c++/launcher/launcherbase.h
    src/c++/launcher/qapplication_selector.h
    src/c++/launcher/fontprovider.h
    src/c++/launcher/fontprovider.c++
    src/c++/quick/quickglobalpointerholder.c++
    src/c++/quick/quickglobalpointerholder.h
    src/c++/settings/qtextk-isettingsprovider.h
    src/c++/settings/qtextk-monojsonsettingsprovider.c++
    src/c++/settings/qtextk-monojsonsettingsprovider.h
    src/c++/settings/qtextk-settings.c++
    src/c++/settings/qtextk-settings.h
    src/c++/widgets/filedialogmodel.c++
    src/c++/widgets/filedialogmodel.h
    src/c++/toolkit.c++
    src/c++/toolkit.h
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Widgets
    QtExtensions
)

target_include_directories(${PROJECT_NAME} PUBLIC include src/c++)