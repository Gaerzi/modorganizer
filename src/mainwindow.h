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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QDir>
#include <QTreeWidget>
#include <QListWidgetItem>
#include <QProcess>
#include <QThread>
#include <QProgressBar>
#include <QTranslator>
#include <directoryentry.h>
#include "executableslist.h"
#include "modlist.h"
#include "pluginlist.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <archive.h>
#include "directoryrefresher.h"
#include <imoinfo.h>
#include <iplugintool.h>
#include <iplugindiagnose.h>
#include "settings.h"
#include "nexusdialog.h"
#include "downloadmanager.h"
#include "installationmanager.h"
#include "selfupdater.h"
#include "savegamegamebyro.h"
#include "modlistsortproxy.h"
#include "pluginlistsortproxy.h"
#include "tutorialcontrol.h"
#include "savegameinfowidgetgamebryo.h"

namespace Ui {
    class MainWindow;
}

class QToolButton;

class MainWindow : public QMainWindow, public IOrganizer
{
  Q_OBJECT

public:
  explicit MainWindow(const QString &exeName, QSettings &initSettings, QWidget *parent = 0);
  ~MainWindow();

  void readSettings();

  bool addProfile();
  void refreshLists();
  void refreshESPList();
  void refreshBSAList();
  void refreshDataTree();
  void refreshSaveList();
  void refreshModList();

  void setExecutablesList(const ExecutablesList &executablesList);

  void setModListSorting(int index);
  void setESPListSorting(int index);
  void setCompactDownloads(bool compact);

  bool setCurrentProfile(int index);
  bool setCurrentProfile(const QString &name);

  void createFirstProfile();

  void spawnProgram(const QString &fileName, const QString &argumentsArg,
                    const QString &profileName, const QDir &currentDirectory);

  void loadPlugins();

  virtual IGameInfo &gameInfo() const;
  virtual QString profileName() const;
  virtual QString profilePath() const;
  virtual VersionInfo appVersion() const;
  virtual IModInterface *getMod(const QString &name);
  virtual IModInterface *createMod(const QString &name);
  virtual bool removeMod(IModInterface *mod);
  virtual void modDataChanged(IModInterface *mod);
  virtual QVariant pluginSetting(const QString &pluginName, const QString &key) const;

  void addPrimaryCategoryCandidates(QMenu *primaryCategoryMenu, ModInfo::Ptr info);

public slots:

  void displayColumnSelection(const QPoint &pos);

  void externalMessage(const QString &message);
  void modorder_changed();
  void esplist_changed();
  void refresher_progress(int percent);
  void directory_refreshed();

  void toolPluginInvoke();

signals:

  /**
   * @brief emitted after a mod has been installed
   * @node this is currently only used for tutorials
   */
  void modInstalled();

  /**
   * @brief emitted after the information dialog has been closed
   */
  void modInfoDisplayed();

  /**
   * @brief emitted when the selected style changes
   */
  void styleChanged(const QString &styleFile);

protected:

  virtual void showEvent(QShowEvent *event);
  virtual void closeEvent(QCloseEvent *event);
  virtual bool eventFilter(QObject *obj, QEvent *event);
  virtual void resizeEvent(QResizeEvent *event);

private:

  void actionToToolButton(QAction *&sourceAction);
  bool verifyPlugin(IPlugin *plugin);
  void registerPluginTool(IPluginTool *tool);
  bool registerPlugin(QObject *pluginObj);

  void updateToolBar();
  void activateSelectedProfile();

  void setBrowserGeometry(const QByteArray &geometry);
  void setExecutableIndex(int index);

  bool nexusLogin();

  void saveCurrentESPList();

  bool testForSteam();
  void startSteam();

  HANDLE spawnBinaryDirect(const QFileInfo &binary, const QString &arguments, const QString &profileName, const QDir &currentDirectory, const QString &steamAppID);
  void spawnBinary(const QFileInfo &binary, const QString &arguments = "", const QDir &currentDirectory = QDir(), bool closeAfterStart = true, const QString &steamAppID = "");

  void updateTo(QTreeWidgetItem *subTree, const std::wstring &directorySoFar, const DirectoryEntry &directoryEntry, bool conflictsOnly);
  void refreshDirectoryStructure();
  bool refreshProfiles(bool selectProfile = true);
  void refreshExecutablesList();
  void installMod(const QString &fileName);
  void installMod();
  bool modifyExecutablesDialog();
  void displayModInformation(ModInfo::Ptr modInfo, unsigned int index, int tab);
  void displayModInformation(int row, int tab = 0);
  void testExtractBSA(int modIndex);

  void writeDataToFile(QFile &file, const QString &directory, const DirectoryEntry &directoryEntry);

  void renameModInList(QFile &modList, const QString &oldName, const QString &newName);

  void refreshFilters();

  void saveCategoriesFromMenu(QMenu *menu, int modRow);

  bool addCategories(QMenu *menu, int targetID);

  void updateDownloadListDelegate();

  // remove invalid category-references from mods
  void fixCategories();

  void storeSettings();

  bool queryLogin(QString &username, QString &password);

  void createHelpWidget();

  bool extractProgress(QProgressDialog &extractProgress, int percentage, std::string fileName);

  void checkBSAList();

  bool checkForProblems(QString &problemDescription);

  int getBinaryExecuteInfo(const QFileInfo &targetInfo, QFileInfo &binaryInfo, QString &arguments);
  void addFilterItem(const QString &name, int categoryID);

  void setCategoryListVisible(bool visible);

  void updateProblemsButton();

  SaveGameGamebryo *getSaveGame(const QString &name);
  SaveGameGamebryo *getSaveGame(QListWidgetItem *item);

  void displaySaveGameInfo(const SaveGameGamebryo *save, QPoint pos);

  HANDLE nextChildProcess();

  bool errorReported(QString &logFile);

private:

  Ui::MainWindow *ui;

  TutorialControl m_Tutorial;

  QString m_ExeName;

  int m_OldProfileIndex;

  QThread m_RefresherThread;
  DirectoryRefresher m_DirectoryRefresher;
  DirectoryEntry *m_DirectoryStructure;
  std::vector<QString> m_ModNameList; // the mod-list to go with the directory structure
  QProgressBar *m_RefreshProgress;
  bool m_Refreshing;

  ModList m_ModList;
  ModListSortProxy *m_ModListSortProxy;
  PluginList m_PluginList;
  PluginListSortProxy *m_PluginListSortProxy;

  ExecutablesList m_ExecutablesList;
  int m_OldExecutableIndex;

  QString m_GamePath;

  int m_ContextRow;
  QTreeWidgetItem *m_ContextItem;
  int m_SelectedSaveGame;

  Settings m_Settings;

  NexusDialog m_NexusDialog;
  DownloadManager m_DownloadManager;
  InstallationManager m_InstallationManager;

  QTranslator *m_Translator;
  QTranslator *m_TranslatorQt;

  SelfUpdater m_Updater;

  CategoryFactory &m_CategoryFactory;

  Profile *m_CurrentProfile;

  int m_ModsToUpdate;

  QStringList m_PendingDownloads;
  QList<boost::function<void (MainWindow*)> > m_PostLoginTasks;
  bool m_AskForNexusPW;
  bool m_LoginAttempted;

  QStringList m_DefaultArchives;
  QStringList m_ActiveArchives;
  bool m_DirectoryUpdate;
  bool m_ArchivesInit;

  QTime m_StartTime;
  SaveGameInfoWidget *m_CurrentSaveView;

  IGameInfo *m_GameInfo;

  std::vector<IPluginDiagnose*> m_DiagnosisPlugins;

private slots:

  void showMessage(const QString &message);
  void showError(const QString &message);

  // main window actions
  void helpTriggered();
  void issueTriggered();
  void wikiTriggered();
  void tutorialTriggered();
  void extractBSATriggered();

  // modlist context menu
  void installMod_clicked();
  void restoreBackup_clicked();
  void renameMod_clicked();
  void removeMod_clicked();
  void reinstallMod_clicked();
  void endorse_clicked();
  void unendorse_clicked();
  void visitOnNexus_clicked();
  void openExplorer_clicked();
  void information_clicked();
  // savegame context menu
  void fixMods_clicked();
  // data-tree context menu
  void writeDataToFile();
  void openDataFile();
  void addAsExecutable();
  void hideFile();
  void unhideFile();

  void linkDesktop();
  void linkMenu();

  void languageChange(const QString &newLanguage);
  void modStatusChanged(unsigned int index);
  void saveSelectionChanged(QListWidgetItem *newItem);

  bool saveCurrentLists();

  void windowTutorialFinished(const QString &windowName);

  BSA::EErrorCode extractBSA(BSA::Archive &archive, BSA::Folder::Ptr folder, const QString &destination, QProgressDialog &extractProgress);

  void syncOverwrite();

  void removeOrigin(const QString &name);

  void setPriorityMax();
  void setPriorityManually();
  void setPriorityMin();

  void procError(QProcess::ProcessError error);
  void procFinished(int exitCode, QProcess::ExitStatus exitStatus);

  // nexus related
  void checkModsForUpdates();
  void nexusLinkActivated(const QString &link);

  void loginSuccessful(bool necessary);
  void loginSuccessfulUpdate(bool necessary);
  void loginFailed(const QString &message);
  void loginFailedUpdate(const QString &message);

  void downloadRequestedNXM(const QString &url);
  void downloadRequested(QNetworkReply *reply, int modID, const QString &fileName);

  void installDownload(int index);
  void updateAvailable();

  void motdReceived(const QString &motd);
  void notEndorsedYet();

  void originModified(int originID);

  void saveCategories();
  void savePrimaryCategory();
  void addPrimaryCategoryCandidates();

  void modDetailsUpdated(bool success);

  void nxmUpdatesAvailable(const std::vector<int> &modIDs, QVariant userData, QVariant resultData, int requestID);
  void nxmEndorsementToggled(int, QVariant, QVariant resultData, int);
  void nxmRequestFailed(int modID, QVariant userData, int requestID, const QString &errorString);

  void editCategories();

  void displayModInformation(const QString &modName, int tab);

  void modRenamed(const QString &oldName, const QString &newName);

  void hideSaveGameInfo();

  void hookUpWindowTutorials();

  void endorseMod(ModInfo::Ptr mod);
  void cancelModListEditor();

  void lockESPIndex();
  void unlockESPIndex();

  void enableVisibleMods();
  void disableVisibleMods();

private slots: // ui slots
  // actions
  void on_actionAdd_Profile_triggered();
  void on_actionInstallMod_triggered();
  void on_actionModify_Executables_triggered();
  void on_actionNexus_triggered();
  void on_actionProblems_triggered();
  void on_actionSettings_triggered();
  void on_actionUpdate_triggered();
  void on_actionEndorseMO_triggered();

  void on_bsaList_customContextMenuRequested(const QPoint &pos);
  void on_bsaList_itemChanged(QTreeWidgetItem *item, int column);
  void on_btnRefreshData_clicked();
  void on_btnSave_clicked();
  void on_categoriesList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
  void on_categoriesList_customContextMenuRequested(const QPoint &pos);
  void on_compactBox_toggled(bool checked);
  void on_conflictsCheckBox_toggled(bool checked);
  void on_dataTree_customContextMenuRequested(const QPoint &pos);
  void on_executablesListBox_currentIndexChanged(int index);
  void on_modList_customContextMenuRequested(const QPoint &pos);
  void on_modList_doubleClicked(const QModelIndex &index);
  void on_profileBox_currentIndexChanged(int index);
  void on_profileRefreshBtn_clicked();
  void on_savegameList_customContextMenuRequested(const QPoint &pos);
  void on_startButton_clicked();
  void on_tabWidget_currentChanged(int index);

  void on_espList_customContextMenuRequested(const QPoint &pos);
  void on_displayCategoriesBtn_toggled(bool checked);
};

#endif // MAINWINDOW_H