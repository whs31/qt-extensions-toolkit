//
// Created by whs31 on 10.10.2023.
//

#pragma once

#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtExtensions/QMLRegistration>
#include <QtExtensions/Global>
#include <QtExtensionsToolkit/ISettingsProvider>

namespace QtEx
{
  class Settings : public Qt::Object
  {
    Q_OBJECT

    public:
      Settings(const Settings&) = delete;
      Settings(Settings&&) = delete;
      Settings& operator=(const Settings&) = delete;
      Settings& operator=(Settings&&) = delete;

      static auto get(ISettingsProvider* provider = nullptr) -> Settings*;

      [[nodiscard]] ISettingsProvider* io() const;      void setIo(ISettingsProvider*);

      [[nodiscard]] auto read(const String& key, const String& fid = String()) const noexcept -> Variant;

      template<typename T>
      [[nodiscard]] auto read(const String& key, const String& fid = String()) const noexcept -> T
      { return read(key, fid).value<T>(); }

      invokable void write(const QString& key, const QVariant& value, const QString& fid = QString()) noexcept;
      invokable void save() const noexcept;
      invokable void load() noexcept;
      invokable void revert() noexcept;

    signals:
      void ioChanged();
      void valueChanged(QString key, QString fid);

    private:
      explicit Settings(ISettingsProvider* provider, Qt::Object* parent = nullptr);

    private:
      ISettingsProvider* m_io;
  };
} // QtEx

