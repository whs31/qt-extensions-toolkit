//
// Created by whs31 on 28.10.2023.
//

#pragma once

#include <map>
#include <QtCore/QObject>
#include <QtGui/QColor>
#include <QtExtensions/QtExtensions>
#include <QtExtensions/QMLRegistration>

using std::map;

namespace QtEx
{
  class ThemeImpl : public Qt::Object
  {
    Q_OBJECT

    public:
      enum ThemePalette
      {
        Rosewater,
        Flamingo,
        Pink,
        Mauve,
        Red,
        Maroon,
        Peach,
        Yellow,
        Green,
        Teal,
        Sky,
        Sapphire,
        Blue,
        Lavender,
        Text,
        Subtext1,
        Subtext0,
        Overlay2,
        Overlay1,
        Overlay0,
        Surface2,
        Surface1,
        Surface0,
        Base,
        Mantle,
        Crust
      };

      enum ThemeMode
      {
        Dark,
        Light
      };

      explicit ThemeImpl(Qt::Object* parent = nullptr);

      [[nodiscard]] invokable QColor color(ThemePalette) const noexcept;

      friend class Theme;

    private:
      static void emplace(const Qt::String& folder, const Qt::String& fallback_path, const Qt::String& fallback_name) noexcept;
      static auto isSystemInDarkMode() noexcept -> bool;

      void load(const Qt::String& folder, const Qt::String& name) noexcept;

    private:
      ThemeMode m_dark_mode;
      map <ThemePalette, Qt::Color> m_dict_light;
      map <ThemePalette, Qt::Color> m_dict_dark;
      Qt::String m_folder;
      Qt::String m_name;
      Qt::String m_fallback;

      map <Qt::String, ThemePalette> EnumerationDictionary;
  };
} // QtEx
Q_DECLARE_METATYPE(QtEx::ThemeImpl*)

namespace QtEx
{
  class Theme : public Qt::Object
  {
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString folder READ folder WRITE setFolder NOTIFY folderChanged FINAL)
    Q_PROPERTY(QString fallback READ fallback WRITE setFallback NOTIFY fallbackChanged FINAL)
    Q_PROPERTY(int darkMode READ darkMode WRITE setDarkMode NOTIFY darkModeChanged FINAL)
    Q_PROPERTY(ThemeImpl* io READ io NOTIFY ioChanged FINAL)

    public:
      enum ThemePalette
      {
        Rosewater,
        Flamingo,
        Pink,
        Mauve,
        Red,
        Maroon,
        Peach,
        Yellow,
        Green,
        Teal,
        Sky,
        Sapphire,
        Blue,
        Lavender,
        Text,
        Subtext1,
        Subtext0,
        Overlay2,
        Overlay1,
        Overlay0,
        Surface2,
        Surface1,
        Surface0,
        Base,
        Mantle,
        Crust
      };

      enum ThemeMode
      {
        Dark,
        Light
      };

      Q_ENUM(ThemePalette)
      Q_ENUM(ThemeMode)

      static auto get() -> Theme*;
      static auto create(QQmlEngine* qml_engine, QJSEngine* js_engine) -> Theme*;

      Theme(const Theme&) = delete;
      Theme(Theme&&) = delete;
      Theme& operator=(const Theme&) = delete;
      Theme& operator=(Theme&&) = delete;

      [[nodiscard]] Qt::String name() const;      void setName(const Qt::String&);
      [[nodiscard]] Qt::String folder() const;    void setFolder(const Qt::String&);
      [[nodiscard]] Qt::String fallback() const;  void setFallback(const Qt::String&);
      [[nodiscard]] int darkMode() const;         void setDarkMode(int);
      [[nodiscard]] ThemeImpl* io() const;

    signals:
      void nameChanged();
      void folderChanged();
      void fallbackChanged();
      void darkModeChanged();
      void ioChanged();

    private:
      explicit Theme(Qt::Object* parent = nullptr);
      bool eventFilter(Qt::Object* object, QEvent* event) override;

    private:
      ThemeImpl* m_io;
  };
} // QtEx

Q_DECLARE_METATYPE(QtEx::Theme*)

