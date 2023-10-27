//
// Created by whs31 on 27.10.2023.
//

#pragma once

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtExtensions/QtExtensions>
#include <QtExtensions/QMLRegistration>

namespace QtEx
{
  class QuickGlobalPointerHolder : public Qt::Object
  {
    Q_OBJECT
    Q_PROPERTY(QObject* rootWindow READ rootWindow WRITE setRootWindow NOTIFY rootWindowChanged)
    Q_PROPERTY(QObject* root READ root WRITE setRoot NOTIFY rootChanged)
    Q_PROPERTY(QObject* map READ map WRITE setMap NOTIFY mapChanged)

    public:
      static auto get() -> QuickGlobalPointerHolder*;
      static auto create(QQmlEngine* qml_engine, QJSEngine* js_engine) -> QuickGlobalPointerHolder*;

      QuickGlobalPointerHolder(const QuickGlobalPointerHolder&) = delete;
      QuickGlobalPointerHolder(QuickGlobalPointerHolder&&) = delete;
      QuickGlobalPointerHolder& operator=(const QuickGlobalPointerHolder&) = delete;
      QuickGlobalPointerHolder& operator=(QuickGlobalPointerHolder&&) = delete;

      [[nodiscard]] QObject* rootWindow() const;   void setRootWindow(QObject*);
      [[nodiscard]] QObject* root() const;         void setRoot(QObject*);
      [[nodiscard]] QObject* map() const;          void setMap(QObject*);

    signals:
      void rootWindowChanged();
      void rootChanged();
      void mapChanged();

    private:
      explicit QuickGlobalPointerHolder(Qt::Object* parent = nullptr);

    private:
      Qt::Object* m_root_window;
      Qt::Object* m_root;
      Qt::Object* m_map;

      // lists...
  };
} // QtEx

