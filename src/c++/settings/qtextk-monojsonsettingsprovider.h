//
// Created by whs31 on 11.10.2023.
//

#pragma once

#include <map>
#include <QtExtensionsToolkit/ISettingsProvider>

using std::map;

namespace QtEx
{
  class MonoJsonSettingsProvider : public ISettingsProvider
  {
    Q_OBJECT

    constexpr static const char* DEFAULT_FILEPATH = "/cfg/settings.json";
    constexpr static const char* DEFAULT_FALLBACK_RC_FILE = ":/json/settings.json";

    public:
      explicit MonoJsonSettingsProvider(Qt::Object* parent = nullptr) noexcept;
      MonoJsonSettingsProvider(String filepath, String fallback_file, Qt::Object* parent = nullptr) noexcept;

      [[nodiscard]] invokable QVariant read(const QString& key, const QString& fid = QString()) const noexcept override;
      void write(const String& key, const Variant& value, const String& fid = String()) noexcept override;

      void load() noexcept override;
      void save() const noexcept override;

    protected:
      String m_filepath;
      String m_fallback_file;
      map<String, Variant> m_json;
  };
} // QtEx

Q_DECLARE_METATYPE(QtEx::MonoJsonSettingsProvider*)