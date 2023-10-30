//
// Created by whs31 on 27.10.2023.
//

#pragma once

#include <vector>
#include <QtCore/QDateTime>
#include <QtCore/QAbstractListModel>
#include <QtExtensions/QtExtensions>

namespace QtEx
{
  using std::vector;
  using Qt::String;
  using Qt::DateTime;
  using Qt::Variant;
  class FileDialogModel : public Qt::AbstractListModel
  {
    Q_OBJECT
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged FINAL)

    public:
      enum Roles
      {
        Index = Qt::UserRole + 1,
        IsDirectory,
        Name,
        Size,
        LastChanged,
        Extension
      };

      struct FileEntry
      {
        FileEntry();
        FileEntry(bool is_dir, String name, String size, DateTime last_changed, String extension);

        bool is_dir;
        String name;
        String size;
        DateTime last_changed;
        String extension;
      };

      explicit FileDialogModel(Qt::Object* parent = nullptr);

      [[nodiscard]] String path() const;
      virtual void setPath(const String&);

      [[nodiscard]] int rowCount(const QModelIndex& = QModelIndex()) const override;
      [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;

    signals:
      void pathChanged();

    protected:
      [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

      static auto parseSize(u64 size) -> String;

    private:
      vector<FileEntry> m_storage;
      String m_path;
  };
} // QtEx

