/****************************************************************************
//   qwinwrap Copyright (C) 2012 yahia nouah <yahiaui@gmail.com>
//
//      This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
//      This is free software, and you are welcome to redistribute it
//      under certain conditions; type `show c' for details.
//
//  The hypothetical commands `show w' and `show c' should show the appropriate
//  parts of the General Public License.  Of course, your program's commands
//  might be different; for a GUI interface, you would use an "about box".
//
//    You should also get your employer (if you work as a programmer) or school,
//  if any, to sign a "copyright disclaimer" for the program, if necessary.
//  For more information on this, and how to apply and follow the GNU GPL, see
//  <http://www.gnu.org/licenses/>.
//
//    The GNU General Public License does not permit incorporating your program
//  into proprietary programs.  If your program is a subroutine library, you
//  may consider it more useful to permit linking proprietary applications with
//  the library.  If this is what you want to do, use the GNU Lesser General
//  Public License instead of this License.  But first, please read
//  <http://www.gnu.org/philosophy/why-not-lgpl.html>.
// ----------------------------------------------------------
** If you have questions regarding the use of this file, please contact
** yahia nouah (yahiaui@gmail.com)
** $qwinwrap_END_LICENSE$
**
****************************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QListWidgetItem>
#include <QProcess>
#include "objdesk.h"
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    ObjDesk *objDesktop;
void setVisible(bool visible);
protected:
    void changeEvent(QEvent *e);

    void closeEvent(QCloseEvent *event);
private:
    Ui::MainWindow *ui;
  QProcess processView;
   QProcess *processDesktop;
    QString m_xScreenSaverPath;
    QString m_vedioPath;
    QString m_sound;
   QString m_xwinwrap;
QStringList listVo;
   QSystemTrayIcon *trayIcon;
   QMenu *trayIconMenu;
   QAction *restoreAction;
   QAction *quitAction;
 QAction *stopAction;
  QAction *playAction;
    QAction *minimizeAction;
 QString   m_desktopId;
private slots:
    void on_actionAbout_triggered();
    void on_actionAboutQt_triggered();
    void on_actionSetScreenSaver_triggered();
    void on_toolButton_clicked();
    void on_pBtnKill_clicked();
   // void on_pBtnCancel_clicked();

    void on_pBtnApplique_clicked();
QString findDesktop();

    void saveLayou();
    void loadLayout();

void createActions();
    void createTrayIcon();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void on_listWidget_itemActivated(QListWidgetItem *item);
  //  void on_btnMinimize_clicked();
    void on_actionQuit_triggered();
    void on_pBtnCancel_clicked();


    void on_toolButtonPreview_toggled(bool checked);
    void on_listWidget_itemSelectionChanged();
    void on_widget_customContextMenuRequested(const QPoint &pos);
    void getid();
    void on_btnMinimize_clicked();
    void on_stackedWidget_currentChanged(int arg1);
};

#endif // MAINWINDOW_H
