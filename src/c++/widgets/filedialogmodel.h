//
// Created by whs31 on 27.10.2023.
//

#pragma once

#include <vector>
#include <QtCore/QDateTime>
#include <QtCore/QAbstractListModel>
#include <QtCore/QDir>
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
    Q_PROPERTY(QString mask READ mask WRITE setMask NOTIFY maskChanged FINAL)

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

      [[nodiscard]] String path() const;                          void setPath(const String&);
      [[nodiscard]] Qt::Directory::SortFlags sortFlags() const;   void setSortFlags(Qt::Directory::SortFlags);
      [[nodiscard]] Qt::Directory::Filters filters() const;       void setFilters(Qt::Directory::Filters);
      [[nodiscard]] Qt::String mask() const;                      void setMask(const Qt::String);

      [[nodiscard]] int rowCount(const QModelIndex& = QModelIndex()) const override;
      [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;

    signals:
      void pathChanged();
      void sortFlagsChanged();
      void filtersChanged();
      void maskChanged();

    protected:
      [[nodiscard]] QHash<int, QByteArray> roleNames() const override;
      virtual void scan() noexcept;

      static auto parseSize(u64 size) -> String;

    protected:
      vector<FileEntry> m_storage;
      String m_path;
      Qt::Directory::SortFlags m_sort_flags;
      Qt::Directory::Filters m_filters;
      Qt::String m_mask;
  };
} // QtEx

