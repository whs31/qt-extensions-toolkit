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

  template <typename T>
  using error_if_not_derived_from_qcoreapplication = std::enable_if_t<std::is_base_of<QCoreApplication, T>::value, bool>;

  template <typename T, error_if_not_derived_from_qcoreapplication<T> = true>
  class ApplicationLauncher
  {
    public:
      explicit ApplicationLauncher(int argc, char** argv, ApplicationBase* base)
        : m_argc(argc)
        , m_argv(argv)
        , m_base(base)
        , m_project_info(ProjectInfo())
        , m_quick_parameters(QuickParameters())
        , m_icon_path(Qt::String())
        , m_dump_platform_info(true)
        , m_free_console(false)
      {}

      [[nodiscard]] ApplicationBase* base() const { return m_base; }
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

      void launch() noexcept
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

        const QUrl qml_entry(quickParameters().entry);
        QQuickStyle::setStyle(quickParameters().style);

        base()->start();

        QQmlEngine engine;
        Qt::Object::connect(&engine, &QQmlEngine::quit, qApp, &QCoreApplication::quit);

        QQmlComponent component(&engine);
        QQuickWindow::setDefaultAlphaBuffer(true);
        component.loadUrl(qml_entry);
        if(component.isReady())
          component.create();
        else
          llog(Error) component.errorString();
      }

    private:
      ApplicationBase* m_base;
      int m_argc;
      char** m_argv;
      ProjectInfo m_project_info;
      QuickParameters m_quick_parameters;
      Qt::String m_icon_path;
      bool m_dump_platform_info;
      bool m_free_console;
      std::unique_ptr<T> m_app;
  };
} // QtEx

