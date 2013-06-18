#include "gui/formsettings.h"
#include "gui/themefactory.h"
#include "gui/systemtrayicon.h"
#include "core/settings.h"
#include "core/defs.h"


FormSettings::FormSettings(QWidget *parent) : QDialog(parent), m_ui(new Ui::FormSettings) {
  m_ui->setupUi(this);

  // Set flags.
  setWindowFlags(Qt::MSWindowsFixedSizeDialogHint | Qt::Dialog);

  // Establish needed connections.
  connect(this, &FormSettings::accepted, this, &FormSettings::saveSettings);

  // Load all settings.
  loadInterface();
}

FormSettings::~FormSettings() {
  delete m_ui;
}

void FormSettings::saveSettings() {
  // Save all categories.
  //saveGeneral();
  saveInterface();
  //saveLanguages();

  // Make sure that settings is synced.
  Settings::getInstance()->checkSettings();
}

void FormSettings::loadInterface() {
  // Load settings of tray icon.
  if (SystemTrayIcon::isSystemTrayAvailable()) {
    // načti
    m_ui->m_radioTrayOff->setChecked(!Settings::getInstance()->value(APP_CFG_GUI,
                                                                     "use_tray_icon",
                                                                     true).toBool());
    m_ui->m_cmbTrayClose->setCurrentIndex(Settings::getInstance()->value(APP_CFG_GUI,
                                                                         "close_win_action",
                                                                         0).toInt());
  }
  else {
    m_ui->m_radioTrayOff->setText(tr("disable (Tray icon is not available.)"));
    m_ui->m_radioTrayOff->setChecked(true);
    m_ui->m_grpTray->setDisabled(true);
  }

  // Load settings of icon theme.
  QString current_theme = ThemeFactory::getCurrentIconTheme();
#if defined(Q_OS_LINUX)
  QString system_theme = ThemeFactory::getSystemIconTheme();
#endif

  foreach (QString icon_theme_name, ThemeFactory::getInstalledIconThemes()) {
#if defined(Q_OS_LINUX)
    if (icon_theme_name == system_theme) {
      m_ui->m_cmbIconTheme->addItem(tr("system icon theme (default)"),
                                    icon_theme_name);
    }
    else {
#endif
      m_ui->m_cmbIconTheme->addItem(icon_theme_name,
                                    icon_theme_name);
#if defined(Q_OS_LINUX)
    }
    if (current_theme == system_theme) {
      // Because system icon theme lies at the index 0.
      // See ThemeFactory::getInstalledIconThemes() for more info.
      m_ui->m_cmbIconTheme->setCurrentIndex(0);
    }
    else {
#endif
      // TODO: Display correct theme on linux.
      m_ui->m_cmbIconTheme->setCurrentText(current_theme);
#if defined(Q_OS_LINUX)
    }
#endif
  }
}

void FormSettings::saveInterface() {
  // Save tray icon.
  if (SystemTrayIcon::isSystemTrayAvailable()) {
    Settings::getInstance()->setValue(APP_CFG_GUI, "use_tray_icon",
                                      m_ui->m_radioTrayOn->isChecked());
    Settings::getInstance()->setValue(APP_CFG_GUI, "close_win_action",
                                      m_ui->m_cmbTrayClose->currentIndex());
    // TODO: Switch tray icon here (destroy it/create it) and
    // if icon is should be destroyed and no main window is visible,
    // then show main window and then destroy tray icon.
  }

  // Save selected icon theme.
  ThemeFactory::setCurrentIconTheme(m_ui->m_cmbIconTheme->itemData(m_ui->m_cmbIconTheme->currentIndex()).toString());
}