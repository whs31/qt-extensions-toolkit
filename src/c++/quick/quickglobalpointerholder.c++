//
// Created by whs31 on 27.10.2023.
//

#include "quickglobalpointerholder.h"

namespace QtEx
{
  auto QuickGlobalPointerHolder::get() -> QuickGlobalPointerHolder* { static QuickGlobalPointerHolder instance; return &instance; }
  auto QuickGlobalPointerHolder::create(QQmlEngine* qml_engine, QJSEngine* js_engine) -> QuickGlobalPointerHolder* { return get(); }

  QuickGlobalPointerHolder::QuickGlobalPointerHolder(Qt::Object* parent)
    : Qt::Object(parent)
  {}

  Qt::Object* QuickGlobalPointerHolder::rootWindow() const { return m_root_window; }
  void QuickGlobalPointerHolder::setRootWindow(Qt::Object* x) {
    m_root_window = x;
    emit rootWindowChanged();
  }

  Qt::Object* QuickGlobalPointerHolder::root() const { return m_root; }
  void QuickGlobalPointerHolder::setRoot(Qt::Object* x) {
    m_root = x;
    emit rootChanged();
  }

  Qt::Object* QuickGlobalPointerHolder::map() const { return m_map; }
  void QuickGlobalPointerHolder::setMap(Qt::Object* x) {
    m_map = x;
    emit mapChanged();
  }
} // QtEx