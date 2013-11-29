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
#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QDir>
#include <QMessageBox>
#include <QTranslator>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDir dir;
    QString h=dir.homePath();
    a.setApplicationName("Qwinwrap");
    a.setApplicationVersion("1.0");
    a.setOrganizationName("Abouzakaria");
    a.setWindowIcon(QIcon(":/qwinwrap.png"));
    if (!dir.exists(h+"/.Qwinwrap")) //التاكد من وجود مجلد المكتبة
    {
        dir.mkdir( h+"/.Qwinwrap");
    }
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        QMessageBox::critical(0, QObject::tr("Systray"),
                              QObject::tr("I couldn't detect any system tray "
                                          "on this system."));

    }
    QTranslator translator;
      QString locale = QLocale::system().name();

    translator.load(QString(":/Qwinwrap_") + locale);
    qDebug()<<locale;


    a.installTranslator(&translator);
    MainWindow w;
    if (locale.contains("ar_"))
        w.setLayoutDirection(Qt::RightToLeft);
    w.show();
    return a.exec();
}
