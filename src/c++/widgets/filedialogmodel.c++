//
// Created by whs31 on 27.10.2023.
//

#include "filedialogmodel.h"
#include <cmath>
#include <array>
#include <QtCore/QDir>
#include <QtCore/QCoreApplication>

using std::array;
using Qt::Directory;
using Qt::FileInfo;

namespace QtEx
{
  FileDialogModel::FileEntry::FileEntry()
    : is_dir(false)
    , name("invalid")
    , size("0 B")
    , last_changed(DateTime())
    , extension("file")
  {}

  FileDialogModel::FileEntry::FileEntry(bool is_dir, String name, String size, DateTime last_changed, String extension)
    : is_dir(is_dir)
    , name(std::move(name))
    , size(std::move(size))
    , last_changed(std::move(last_changed))
    , extension(std::move(extension))
  {}

  FileDialogModel::FileDialogModel(Qt::Object* parent)
    : Qt::AbstractListModel(parent)
  {
    this->setPath(QCoreApplication::applicationDirPath());
  }

  String FileDialogModel::path() const { return m_path; }
  void FileDialogModel::setPath(const String& x)
  {
    m_storage.clear();
    Directory dir(x, "*", QDir::DirsFirst | QDir::Name | QDir::IgnoreCase,
                          QDir::Files | QDir::Hidden | QDir::Dirs | QDir::NoDotAndDotDot);
    for(const FileInfo& item : dir.entryInfoList())
    {
      beginInsertRows(QModelIndex(), rowCount(), rowCount());
      bool is_hidden = item.completeBaseName().isEmpty();
      if(item.isDir())
      {
        m_storage.emplace_back(true, item.fileName(), QString::number(QDir(item.filePath()).count()) + " files",
                               item.lastModified(), "");
        continue;
      }
      m_storage.emplace_back(false, item.fileName(), parseSize(item.size()),
                             item.lastModified(), is_hidden ? "" : item.suffix());
      endInsertRows();
    }
  }

  int FileDialogModel::rowCount(const QModelIndex&) const { return static_cast<isize>(m_storage.size()); }
  QVariant FileDialogModel::data(const QModelIndex& index, int role) const
  {
    if(not index.isValid())
      return {};
    switch(role)
    {
      case Index: return index.row();
      case IsDirectory: return Variant::fromValue(m_storage[index.row()].is_dir);
      case Name: return Variant::fromValue(m_storage[index.row()].name);
      case Size: return Variant::fromValue(m_storage[index.row()].size);
      case LastChanged: return Variant::fromValue(m_storage[index.row()].last_changed);
      case Extension: return Variant::fromValue(m_storage[index.row()].extension);

      default: return "Error reading from model";
    }
  }

  QHash<int, QByteArray> FileDialogModel::roleNames() const
  {
    auto roles = QAbstractItemModel::roleNames();
    roles[Index] = "index";
    roles[IsDirectory] = "isDirectory";
    roles[Name] = "name";
    roles[Size] = "size";
    roles[LastChanged] = "lastChanged";
    roles[Extension] = "extension";
    return roles;
  }

  auto FileDialogModel::parseSize(u64 size) -> String
  {
    using std::pow;
    static array<String , 7> prefixes{ " bit", " B", " KB", " MB", " GB", " TB", " PB" };
    auto log1024 = [](auto &num) -> int{return static_cast<int>(std::log(num) / std::log(1024));};
    auto exp = log1024(size);
    return String::number(static_cast<f32>(size) / pow(1024, exp), 'f', 2) + prefixes[exp + 1];
  }
} // QtEx
