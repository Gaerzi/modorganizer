/*
Copyright (C) 2012 Sebastian Herbord. All rights reserved.

This file is part of Mod Organizer.

Mod Organizer is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Mod Organizer is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Mod Organizer.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "downloadlistsortproxy.h"

DownloadListSortProxy::DownloadListSortProxy(const DownloadManager *manager, QObject *parent)
  : QSortFilterProxyModel(parent), m_Manager(manager), m_CurrentFilter()
{
}

void DownloadListSortProxy::updateFilter(const QString &filter)
{
  m_CurrentFilter = filter;
  invalidateFilter();
}

bool DownloadListSortProxy::lessThan(const QModelIndex &left,
                                     const QModelIndex &right) const
{
  int leftIndex  = sourceModel()->data(left).toInt();
  int rightIndex = sourceModel()->data(right).toInt();

  if (left.column() == 0) {
    return m_Manager->getFileName(leftIndex).compare(m_Manager->getFileName(rightIndex), Qt::CaseInsensitive) < 0;
  } else if (left.column() == 1) {
    return leftIndex < rightIndex;
  } else {
    return m_Manager->getState(leftIndex) < m_Manager->getState(rightIndex);
  }
}


bool DownloadListSortProxy::filterAcceptsRow(int source_row, const QModelIndex&) const
{
  if (m_CurrentFilter.length() == 0) {
    return true;
  }
  return m_Manager->getFileName(source_row).contains(m_CurrentFilter, Qt::CaseInsensitive);
}