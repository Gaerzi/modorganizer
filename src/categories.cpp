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

#include "categories.h"
#include <utility.h>
#include "report.h"
#include <gameinfo.h>
#include <QObject>
#include <QFile>
#include <QDir>
#include <QList>


CategoryFactory* CategoryFactory::s_Instance = NULL;


CategoryFactory::CategoryFactory()
{
  reset();

  QFile categoryFile(QDir::fromNativeSeparators(ToQString(GameInfo::instance().getOrganizerDirectory())).append("/categories.dat"));

  if (!categoryFile.open(QIODevice::ReadOnly)) {
    loadDefaultCategories();
  } else {
    int lineNum = 0;
    while (!categoryFile.atEnd()) {
      QByteArray line = categoryFile.readLine();
      ++lineNum;
      QList<QByteArray> cells = line.split('|');
      if (cells.count() != 4) {
        qCritical("invalid category line %d: %s (%d cells)",
                  lineNum, line.constData(), cells.count());
      } else {
        std::vector<int> nexusIDs;
        if (cells[2].length() > 0) {
          QList<QByteArray> nexusIDStrings = cells[2].split(',');
          for (QList<QByteArray>::iterator iter = nexusIDStrings.begin();
               iter != nexusIDStrings.end(); ++iter) {
            bool ok = false;
            int temp = iter->toInt(&ok);
            if (!ok) {
              qCritical("invalid id %s", iter->constData());
            }
            nexusIDs.push_back(temp);
          }
        }
        bool cell0Ok = true;
        bool cell3Ok = true;
        int id = cells[0].toInt(&cell0Ok);
        int parentID = cells[3].trimmed().toInt(&cell3Ok);
        if (!cell0Ok || !cell3Ok) {
          qCritical("invalid category line %d: %s",
                    lineNum, line.constData());
        }
        addCategory(id, QString::fromUtf8(cells[1].constData()), nexusIDs, parentID);
      }
    }
    categoryFile.close();
  }
  std::sort(m_Categories.begin(), m_Categories.end());
  setParents();
}


CategoryFactory &CategoryFactory::instance()
{
  if (s_Instance == NULL) {
    s_Instance = new CategoryFactory;
  }
  return *s_Instance;
}


void CategoryFactory::reset()
{
  m_Categories.clear();
  addCategory(0, "None", MakeVector<int>(2, 28, 87), 0);
}


void CategoryFactory::setParents()
{
  for (std::vector<Category>::iterator iter = m_Categories.begin();
       iter != m_Categories.end(); ++iter) {
    iter->m_HasChildren = false;
  }

  for (std::vector<Category>::const_iterator categoryIter = m_Categories.begin();
       categoryIter != m_Categories.end(); ++categoryIter) {
    if (categoryIter->m_ParentID != 0) {
      std::map<int, unsigned int>::const_iterator iter = m_IDMap.find(categoryIter->m_ParentID);
      if (iter != m_IDMap.end()) {
        m_Categories[iter->second].m_HasChildren = true;
      }
    }
  }
}


void CategoryFactory::saveCategories()
{
  QFile categoryFile(QDir::fromNativeSeparators(ToQString(GameInfo::instance().getOrganizerDirectory())).append("/categories.dat"));

  if (!categoryFile.open(QIODevice::WriteOnly)) {
    reportError(QObject::tr("Failed to save custom categories"));
    return;
  }

  categoryFile.resize(0);
  for (std::vector<Category>::const_iterator iter = m_Categories.begin();
       iter != m_Categories.end(); ++iter) {
    if (iter->m_ID == 0) {
      continue;
    }
    QByteArray line;
    line.append(QByteArray::number(iter->m_ID)).append("|")
        .append(iter->m_Name.toUtf8()).append("|")
        .append(VectorJoin(iter->m_NexusIDs, ",")).append("|")
        .append(QByteArray::number(iter->m_ParentID)).append("\n");
    categoryFile.write(line);
  }
  categoryFile.close();
}


void CategoryFactory::addCategory(int id, const QString &name, const std::vector<int> &nexusIDs, int parentID)
{
  int index = m_Categories.size();
  m_Categories.push_back(Category(index, id, name, nexusIDs, parentID));
  for (std::vector<int>::const_iterator iter = nexusIDs.begin();
       iter != nexusIDs.end(); ++iter) {
    m_NexusMap[*iter] = index;
  }
  m_IDMap[id] = index;
}


void CategoryFactory::loadDefaultCategories()
{
  // the order here is relevant as it defines the order in which the
  // mods appear in the combo box
  addCategory(1, "Animations", MakeVector<int>(1, 51), 0);
  addCategory(2, "Armour", MakeVector<int>(1, 54), 0);
  addCategory(3, "Audio", MakeVector<int>(1, 61), 0);
  addCategory(5, "Clothing", MakeVector<int>(1, 60), 0);
  addCategory(6, "Collectables", MakeVector<int>(1, 92), 0);
  addCategory(7, "Creatures", MakeVector<int>(2, 83, 65), 0);
  addCategory(8, "Factions", MakeVector<int>(1, 25), 0);
  addCategory(9, "Gameplay", MakeVector<int>(1, 24), 0);
  addCategory(10, "Hair", MakeVector<int>(1, 26), 0);
  addCategory(11, "Items", MakeVector<int>(2, 27, 85), 0);
  addCategory(19, "Weapons", MakeVector<int>(2, 36, 55), 11);
  addCategory(12, "Locations", MakeVector<int>(7, 22, 30, 70, 88, 89, 90, 91), 0);
  addCategory(4, "Cities", MakeVector<int>(1, 53), 12);
  addCategory(20, "Magic", MakeVector<int>(3, 75, 93, 94), 0);
  addCategory(21, "Models & Textures", MakeVector<int>(1, 29), 0);
  addCategory(13, "NPCs", MakeVector<int>(1, 33), 0);
  addCategory(14, "Patches", MakeVector<int>(2, 79, 84), 0);
  addCategory(15, "Quests", MakeVector<int>(1, 35), 0);
  addCategory(16, "Races & Classes", MakeVector<int>(1, 34), 0);
  addCategory(22, "Skills", MakeVector<int>(1, 73), 0);
  addCategory(17, "UI", MakeVector<int>(1, 42), 0);
  addCategory(18, "Visuals", MakeVector<int>(1, 62), 0);
}


int CategoryFactory::getParentID(unsigned int index) const
{
  if ((index < 0) || (index >= m_Categories.size())) {
    throw MyException(QObject::tr("invalid index %1").arg(index));
  }

  return m_Categories[index].m_ParentID;
}


bool CategoryFactory::categoryExists(int id) const
{
  return m_IDMap.find(id) != m_IDMap.end();
}


bool CategoryFactory::isDecendantOf(int id, int parentID) const
{
  std::map<int, unsigned int>::const_iterator iter = m_IDMap.find(id);
  if (iter != m_IDMap.end()) {
    unsigned int index = iter->second;
    if (m_Categories[index].m_ParentID == 0) {
      return false;
    } else if (m_Categories[index].m_ParentID == parentID) {
      return true;
    } else {
      return isDecendantOf(m_Categories[index].m_ParentID, parentID);
    }
  } else {
    qWarning("%d is no valid category id", id);
    return false;
  }
}


bool CategoryFactory::hasChildren(unsigned int index) const
{
  if ((index < 0) || (index >= m_Categories.size())) {
    throw MyException(QObject::tr("invalid index %1").arg(index));
  }

  return m_Categories[index].m_HasChildren;
}


QString CategoryFactory::getCategoryName(unsigned int index) const
{
  if ((index < 0) || (index >= m_Categories.size())) {
    throw MyException(QObject::tr("invalid index %1").arg(index));
  }

  return m_Categories[index].m_Name;
}


int CategoryFactory::getCategoryID(unsigned int index) const
{
  if ((index < 0) || (index >= m_Categories.size())) {
    throw MyException(QObject::tr("invalid index %1").arg(index));
  }

  return m_Categories[index].m_ID;
}


int CategoryFactory::getCategoryIndex(int ID) const
{
  std::map<int, unsigned int>::const_iterator iter = m_IDMap.find(ID);
  if (iter == m_IDMap.end()) {
    throw MyException(QObject::tr("invalid category id %1").arg(ID));
  }
  return iter->second;
}



unsigned int CategoryFactory::resolveNexusID(int nexusID) const
{
  std::map<int, unsigned int>::const_iterator iter = m_NexusMap.find(nexusID);
  if (iter != m_NexusMap.end()) {
    qDebug("nexus category id %d maps to internal %d", nexusID, iter->second);
    return iter->second;
  } else {
    qDebug("nexus category id %d not mapped", nexusID);
    return 0U;
  }
}