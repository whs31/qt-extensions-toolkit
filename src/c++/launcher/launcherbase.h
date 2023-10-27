//
// Created by whs31 on 27.10.2023.
//

#pragma once

#include <memory>
#include <type_traits>
#include <QtQml/QQmlEngine>
#include <QtQml/QQmlComponent>
#include <QtQml/QQmlContext>
#include <QtQuick/QQuickWindow>
#include <QtQuickControls2/QQuickStyle>
#include <Libra/Windows>
#include <Libra/WinAPI>
#include <QtExtensions/QtExtensions>
#include <QtExtensions/Logging>
#include <QtExtensionsToolkit/ApplicationBase>
#include <QtExtensionsToolkit/QApplicationSelector>

namespace QtEx
{
  struct ProjectInfo
  {
    ProjectInfo()
      : name("Unnamed")
      , version("0.0.0")
      , organization("Unspecified")
      , url("example.com")
    {}

    ProjectInfo(Qt::String name, Qt::String version, Qt::String organization, Qt::String url)
      : name(std::move(name))
      , version(std::move(version))
      , organization(std::move(organization))
      , url(std::move(url))
    {}

    Qt::String name;
    Qt::String version;
    Qt::String organization;
    Qt::String url;
  };

  struct QuickParameters
  {
    QuickParameters()
      : entry(Qt::String())
      , style("Default")
    {}

    QuickParameters(Qt::String entry, Qt::String style)
      : entry(std::move(entry))
      , style(std::move(style))
    {}

    Qt::String entry;
    Qt::String style;
  };

  template <typename T, typename U,
            std::enable_if_t<std::is_base_of<QCoreApplication, T>::value, bool> = true,
            std::enable_if_t<std::is_base_of<ApplicationBase, U>::value, bool> = true>
  class ApplicationLauncher
  {
    public:
      explicit ApplicationLauncher(int argc, char** argv)
        : m_argc(argc)
        , m_argv(argv)
        , m_base(std::make_unique<U>())
        , m_project_info(ProjectInfo())
        , m_quick_parameters(QuickParameters())
        , m_icon_path(Qt::String())
        , m_dump_platform_info(true)
        , m_free_console(false)
      {}

      [[nodiscard]] ApplicationBase* base() const { return m_base.get(); }
      [[nodiscard]] int argc() const { return m_argc; }
      [[nodiscard]] char** argv() const { return m_argv; }

      [[nodiscard]] ProjectInfo projectInfo() const { return m_project_info; }
      void setProjectInfo(const ProjectInfo& x) { m_project_info = x; }

      [[nodiscard]] QuickParameters quickParameters() const { return m_quick_parameters; }
      void setQuickParameters(const QuickParameters& x) { m_quick_parameters = x; }

      [[nodiscard]] Qt::String iconPath() const { return m_icon_path; }
      void setIconPath(const Qt::String& x) { m_icon_path = x; }

      [[nodiscard]] bool dumpPlatformInfo() const { return m_dump_platform_info; }
      void setDumpPlatformInfo(bool x) { m_dump_platform_info = x; }

      [[nodiscard]] bool freeConsole() const { return m_free_console; }
      void setFreeConsole(bool x) { m_free_console = x; }

      int launch() noexcept
      {
        using Qtx::Log;

        if(freeConsole())
          Libra::Windows::releaseConsole();

        m_app = std::make_unique<T>(m_argc, m_argv);
        T::setApplicationName(projectInfo().name);
        T::setApplicationVersion(projectInfo().version);
        T::setOrganizationName(projectInfo().organization);
        T::setOrganizationDomain(projectInfo().url);

        #ifndef Q_OS_WINDOWS
        T::setWindowIcon(QIcon(iconPath() + ".png"));
        #else
        T::setWindowIcon(QIcon(iconPath() + ".ico"));
        #endif

        Log::setLoggingPattern();

        if(dumpPlatformInfo())
        {
          Log::printPlatformInfo();
          Log::linebreak();
          Log::printQtInfo();
          Log::linebreak();
          Log::printApplicationInfo(m_app.get());
          Log::linebreak();
        }

        const QUrl QML_ENTRY(quickParameters().entry);
        if(quickParameters().style == "Material")
          qputenv("QT_QUICK_CONTROLS_MATERIAL_VARIANT", "Dense");
        QQuickStyle::setStyle(quickParameters().style);

        base()->start();

        m_engine = std::make_unique<QQmlEngine>();
        Qt::Object::connect(m_engine.get(), &QQmlEngine::quit, qApp, &QCoreApplication::quit);
        m_component = std::make_unique<QQmlComponent>(m_engine.get());
        QQuickWindow::setDefaultAlphaBuffer(true);
        m_component->loadUrl(QML_ENTRY);
        if(m_component->isReady())
          m_component->create();
        else
          llog(Error) m_component->errorString();

        return T::exec();
      }

    private:
      std::unique_ptr<ApplicationBase> m_base;
      int m_argc;
      char** m_argv;
      ProjectInfo m_project_info;
      QuickParameters m_quick_parameters;
      Qt::String m_icon_path;
      bool m_dump_platform_info;
      bool m_free_console;
      std::unique_ptr<T> m_app;
      std::unique_ptr<QQmlEngine> m_engine;
      std::unique_ptr<QQmlComponent> m_component;
  };
} // QtEx

