//
// Created by whs31 on 11.10.2023.
//

#include "qtextk-monojsonsettingsprovider.h"
#include <utility>
#include <QtCore/QFile>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QCoreApplication>
#include <QtExtensions/Logging>

namespace QtEx
{
  MonoJsonSettingsProvider::MonoJsonSettingsProvider(Qt::Object* parent) noexcept
    : ISettingsProvider(parent)
    , m_filepath(QCoreApplication::applicationDirPath() + DEFAULT_FILEPATH)
    , m_fallback_file(DEFAULT_FALLBACK_RC_FILE)
  {
    qRegisterMetaType<MonoJsonSettingsProvider*>("MonoJsonSettingsProvider*");
  }

  MonoJsonSettingsProvider::MonoJsonSettingsProvider(String filepath, String fallback_file, Qt::Object* parent) noexcept
    : ISettingsProvider(parent)
    , m_filepath(std::move(filepath))
    , m_fallback_file(std::move(fallback_file))
  {
    qRegisterMetaType<MonoJsonSettingsProvider*>("MonoJsonSettingsProvider*");
  }

  QVariant MonoJsonSettingsProvider::read(const QString& key, const QString& fid) const noexcept
  {
    (void)fid;
    if(not m_json.count(key))
      return {};
    return m_json.at(key);
  }

  void MonoJsonSettingsProvider::write(const String& key, const Variant& value, const String& fid) noexcept
  {
    (void)fid;
    m_json[key] = value;
  }

  void MonoJsonSettingsProvider::load() noexcept
  {
    llog(Debug) "Loading settings";
    Qt::File file(m_filepath);
    if(not file.exists())
      Qt::File::copy(m_fallback_file, m_filepath);
    file.setPermissions(QFileDevice::ReadUser | QFileDevice::WriteUser);
    if(not file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      llog(Error) "Failed to open file for read:" << m_filepath;
      return;
    }

    auto doc = Qt::JsonDocument::fromJson(file.readAll());
    file.close();

    if(not doc.isNull() and doc.isObject())
    {
      auto json = doc.object();
      for(auto it = json.begin(); it != json.end(); ++it)
        m_json.insert({it.key(), it.value().toVariant()});
    }
  }

  void MonoJsonSettingsProvider::save() const noexcept
  {
    llog(Debug) "Saving settings";
    auto data = Qt::JsonDocument(Qt::JsonObject::fromVariantMap(QMap<String, Variant>(m_json)))
                              .toJson(Qt::JsonDocument::JsonFormat::Indented);
    Qt::File::remove(m_filepath);
    Qt::File file(m_filepath);
    if(not file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
      llog(Error) "Failed to open file for write:" << m_filepath;
      return;
    }
    file.write(data);
    file.close();
  }
} // QtEx