#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QSystemTrayIcon>
#include <QPointer>


class SystemTrayIcon : public QSystemTrayIcon {
    Q_OBJECT
  public:
    explicit SystemTrayIcon(const QString &normal_icon,
                            const QString &plain_icon,
                            QObject *parent = 0);
    ~SystemTrayIcon();

    // Returns true if tray icon CAN be constructed on this machine.
    static bool isSystemTrayAvailable();

    // Returns true if tray icon CAN be costructed and IS enabled in
    // application settings.
    static bool isSystemTrayActivated();

    // Creates new tray icon if necessary and returns it.
    // WARNING: Use this in cooperation with SystemTrayIcon::isSystemTrayActivated().
    static SystemTrayIcon *getInstance();
    
    // Sets the number to be visible in the tray icon, -1 removes it.
    void setNumber(int number = -1);

    // TODO: Implement method for manual clearing of the tray icon. Creating of tray icon
    // handled by getInstance().
  signals:
    
  public slots:

  private:
    QString m_normalIcon;
    QString m_plainIcon;

    static QPointer<SystemTrayIcon> m_trayIcon;
};

#endif // SYSTEMTRAYICON_H