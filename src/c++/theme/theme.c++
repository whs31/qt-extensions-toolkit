//
// Created by whs31 on 28.10.2023.
//

#include "theme.h"
#include <QtCore/QCoreApplication>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtExtensions/Logging>

namespace QtEx
{
  using Qt::Directory;
  using Qt::File;
  using Qt::String;

  ThemeImpl::ThemeImpl(Qt::Object* parent)
    : Qt::Object(parent)
    , m_dark_mode(Dark)
    , EnumerationDictionary({
      { "rosewater", Rosewater },
      { "flamingo", Flamingo },
      { "pink", Pink },
      { "mauve", Mauve },
      { "red", Red },
      { "maroon", Maroon },
      { "peach", Peach },
      { "yellow", Yellow },
      { "green", Green },
      { "teal", Teal },
      { "sky", Sky },
      { "sapphire", Sapphire },
      { "blue", Blue },
      { "lavender", Lavender },
      { "text", Text },
      { "subtext1", Subtext1 },
      { "subtext0", Subtext0 },
      { "overlay2", Overlay2 },
      { "overlay1", Overlay1 },
      { "overlay0", Overlay0 },
      { "surface2", Surface2 },
      { "surface1", Surface1 },
      { "surface0", Surface0 },
      { "base", Base },
      { "mantle", Mantle },
      { "crust", Crust },
    })
    , m_folder(QCoreApplication::applicationDirPath() + "/theme")
    , m_name("Catpuccin")
    , m_fallback(":/qtx/themes/catpuccin.json")
  {
    qRegisterMetaType<ThemeImpl*>("ThemeImpl*");
    ThemeImpl::emplace(m_folder, m_fallback, "catpuccin.json");
  }



  QColor ThemeImpl::color(ThemeImpl::ThemePalette key) const noexcept
  {
    switch(m_dark_mode)
    {
      case Light: return m_dict_light.at(key);
      case Dark: [[fallthrough]];
      default: return m_dict_dark.at(key);
    }
  }

  void ThemeImpl::emplace(const Qt::String& folder, const Qt::String& fallback_path, const Qt::String& fallback_name) noexcept
  {
    const String target = String("%1/%2").arg(folder, fallback_name);
    llog(Debug) "Looking for" << target;
    Directory directory(folder);
    if(not directory.exists())
    {
      directory.mkpath(folder);
      llog(Debug) "Created directory" << folder;
    }

    File file(target);
    if(not file.exists())
    {
      File::copy(fallback_path, target);
      llog(Debug) "Placed fallback file" << fallback_name << "into folder";
    }
  }

  void ThemeImpl::load(const String& folder, const String& name) noexcept
  {
    Directory directory(folder, "*.json", QDir::Name | QDir::IgnoreCase, QDir::Files | QDir::Hidden);
    for(const auto& entry : directory.entryList())
    {
      File file(folder + "/" + entry);
      file.setPermissions(QFileDevice::ReadUser | QFileDevice::WriteUser);
      if(not file.open(QIODevice::ReadOnly | QIODevice::Text))
      {
        llog(Error) "Failed to open file for read" << entry;
        continue;
      }

      auto doc = QJsonDocument::fromJson(file.readAll());
      file.close();

      if(doc.isNull() or not doc.isObject())
      {
        llog(Error) "Invalid JSON";
        continue;
      }
      auto json = doc.object();
      if(not json.contains("name"))
      {
        llog(Error) "Name is required for theme .json file";
        continue;
      }
      if(json["name"] != name)
      {
        llog(Warning) "Name" << json["name"] << "doesn't match" << name;
        continue;
      }

      {
        auto light = json["light"].toObject();
        for(auto it = light.begin(); it != light.end(); ++it)
          m_dict_light.insert({
            EnumerationDictionary[it.key()],
            Qt::Color(it.value().toString())
          });
      }

      {
        auto dark = json["dark"].toObject();
        for(auto it = dark.begin(); it != dark.end(); ++it)
          m_dict_dark.insert({
            EnumerationDictionary[it.key()],
            Qt::Color(it.value().toString())
          });
      }
    }
  }

  auto Theme::get() -> Theme* { static Theme instance; return &instance; }
  auto Theme::create(QQmlEngine* qml_engine, QJSEngine* js_engine) -> Theme* { return get(); }

  Qt::String Theme::name() const { return io()->m_name; }
  void Theme::setName(const Qt::String& x)
  {
    io()->m_name = x;
    emit nameChanged();
    io()->load(folder(), name());
    emit ioChanged();
  }

  Qt::String Theme::folder() const { return io()->m_folder; }
  void Theme::setFolder(const Qt::String& x)
  {
    io()->m_folder = x;
    emit folderChanged();
    io()->load(folder(), name());
    emit ioChanged();
  }

  Qt::String Theme::fallback() const { return io()->m_fallback; }
  void Theme::setFallback(const Qt::String& x)
  {
    io()->m_fallback = x;
    emit fallbackChanged();
    ThemeImpl::emplace(folder(), fallback(), "fallback.json");
  }

  int Theme::darkMode() const { return static_cast<int>(io()->m_dark_mode); }
  void Theme::setDarkMode(int x)
  {
    if(x == io()->m_dark_mode)
      return;
    io()->m_dark_mode = static_cast<ThemeImpl::ThemeMode>(static_cast<ThemeMode>(x));
    emit darkModeChanged();
    emit ioChanged();
  }

  ThemeImpl* Theme::io() const { return m_io; }

  Theme::Theme(Qt::Object* parent)
    : Qt::Object(parent)
    , m_io(new ThemeImpl(this))
  {
    io()->load(io()->m_folder, io()->m_name);
  }
} // QtEx