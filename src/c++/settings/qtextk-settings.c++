//
// Created by whs31 on 10.10.2023.
//

#include "qtextk-settings.h"
#include <stdexcept>
#include <QtExCore/Logging>

namespace QtEx
{
  auto Settings::get(ISettingsProvider* provider) -> Settings* { static Settings instance(provider); return &instance; }
  Settings::Settings(ISettingsProvider* provider, Qt::Object* parent)
    : Qt::Object(parent)
    , m_io(provider)
  {
    if(provider == nullptr)
      throw std::invalid_argument(scope_information_str + " Null provider was passed to constructor");
    this->load();
    qRegisterMetaType<ISettingsProvider*>("ISettingsProvider*");
  }

  ISettingsProvider* Settings::io() const { return m_io; }
  void Settings::setIo(ISettingsProvider* x) { m_io = x; emit ioChanged(); }
  auto Settings::read(const String& key, const String& fid) const noexcept -> Variant { return io()->read(key, fid); }
  void Settings::write(const QString& key, const QVariant& value, const QString& fid) noexcept
  {
    io()->write(key, value, fid);
    emit valueChanged(key, fid);
  }

  void Settings::save() const noexcept { io()->save(); }
  void Settings::load() noexcept
  {
    io()->load();
    emit ioChanged();
  }

  void Settings::revert() noexcept { this->load(); }
} // QtEx