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
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QProcess>
#include <QMessageBox>
#include <QFileDialog>
#include <QSettings>
#include <QtGui>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    ui->listWidgetType->setViewMode(QListView::IconMode);
        ui->listWidgetType->setIconSize(QSize(64, 64));
        ui->listWidgetType->setMovement(QListView::Static);
        ui->listWidgetType->setMaximumWidth(100);
        ui->listWidgetType->setSpacing(12);
processDesktop=new QProcess;

if(QFile::exists("/usr/bin/xwinwrap")){
    m_xwinwrap="/usr/bin/xwinwrap";
    ui->radioButtonXwin->setToolTip("xwinwrap found in : "+m_xwinwrap);
  //  ui->labelXwin->setText("xwinwrap found in : "+m_xwinwrap);
}else if(QFile::exists(qApp->applicationDirPath()+"/xwinwrap")){
    m_xwinwrap="\""+qApp->applicationDirPath()+"/xwinwrap\"";
    ui->radioButtonXwin->setToolTip("xwinwrap found in : "+m_xwinwrap);
}else{
    ui->radioButtonXwin->setToolTip("xwinwrap no found" );
    ui->radioButtonXwin->setEnabled(false);
    ui->radioButtonWidget->setChecked(true);
}

//ui->widget->setVisible(false);

   loadLayout();
   createActions();
createTrayIcon();
connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
        this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

QDesktopWidget *wid=new QDesktopWidget;
    wid->setAttribute(Qt::WA_NoChildEventsFromChildren,true);

  //


    objDesktop=new ObjDesk;

//objDesktop->show();
        trayIcon->setIcon(QIcon(":/qwinwrap.png"));

// ui->listWidget->addItem("glmatrix");
    QDir dirS(m_xScreenSaverPath);
    QString subfile;
    foreach ( subfile, dirS.entryList(QDir::AllEntries| QDir::NoDotAndDotDot )){
         ui->listWidget->addItem(subfile);

    }
    listVo<<""<<"-vo gl_nosw"<<"-vo gl"<<"-vo gl2"<<"-vo matrixview";
ui->widget->setVisible(false);
  trayIcon->show();

     m_desktopId=findDesktop();
}

MainWindow::~MainWindow()
{
    delete ui;
     saveLayou();
}
void MainWindow::setVisible(bool visible)
{
    minimizeAction->setEnabled(visible);
    restoreAction->setEnabled(isMaximized() || !visible);
    QMainWindow::setVisible(visible);
}
void MainWindow::closeEvent(QCloseEvent *event)
{
     on_pBtnKill_clicked();
}
void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    case QEvent::WindowStateChange:

        if(this->isMinimized()){

                 on_toolButtonPreview_toggled(false);
         }
          break;
    case QEvent::Hide:
      qDebug()<<this->isHidden();
        break;

    default:
        break;
    }
}



void MainWindow::on_pBtnApplique_clicked()
{

  on_pBtnKill_clicked();
    qreal i=ui->doubleSpinBox->value();
    QString opacity=QString::number(i);

    objDesktop->setWindowOpacity(i);
    if (ui->checkBoxSound->isChecked()){
        m_sound="-quiet";
    }else{
        m_sound="-nosound";
    }

    QString argument;
    if(ui->stackedWidget->currentIndex()==0){//xscreen saver
        if(!ui->listWidget->currentItem())return;
        QString pathScreenS=m_xScreenSaverPath+"/"+ui->listWidget->currentItem()->text();


        if(ui->radioButtonXwin->isChecked()){//xwinwrap
            argument=QString("%1 -ni -argb -o %2 -fs -s -st -sp  -b -nf  -- %3 -root -window-id WID "
                             ).arg(m_xwinwrap).arg(opacity).arg(pathScreenS);
        }else if(ui->radioButtonWidget->isChecked()){

            objDesktop->show();

            argument=QString("%1 -window-id  %2 "
                             ).arg(pathScreenS).arg(objDesktop->winId());
        }else if(ui->radioButtonDirect->isChecked()){
            argument=QString("%1 -root  -install -window-id  %2 "
                             ).arg(pathScreenS).arg(m_desktopId);
        }

    }else{ //mplayer
        m_vedioPath=ui->lineEdit->text().trimmed();
        int index=ui->comboBoxVo->currentIndex();
        QString strVo= listVo.at(index);

        if(ui->radioButtonXwin->isChecked()){//xwinwrap
                    if(ui->rBtnLoop->isChecked()){
                        QString loop=QString::number(ui->spinBoxLoop->value());
                        argument=QString("%1 -ni -o %2 -fs -s -st -sp -b -nf -- mplayer -wid WID %3  %4 -noconfig all -really-quiet -msglevel all=-1 -loop %5  1>/dev/null 2>/dev/null"
                                         ).arg(m_xwinwrap).arg(opacity).arg(m_sound).arg(strVo + " " +m_vedioPath).arg(loop);

                    }else{

                                argument=QString("%1 -ni -o %2 -fs -s -st -sp -b -nf -- mplayer -wid WID %3  %4 -noconfig all -really-quiet -msglevel all=-1 2>/dev/null"
                                                 ).arg(m_xwinwrap).arg(opacity).arg(m_sound).arg(strVo + " \"" +m_vedioPath+"\"");

                    }
        } else{
            objDesktop->setFileName(m_vedioPath,ui->checkBoxSound->checkState(),ui->rBtnLoop->checkState());
            objDesktop->show();
        }
    }
    qDebug()<<argument ;
    //   process.startDetached(argument);

    processDesktop->start(argument);


}


//void MainWindow::on_pBtnCancel_clicked()
//{
//        qApp->exit();
//}

void MainWindow::on_pBtnKill_clicked()
{
    QProcess process;
    process.execute("killall xwinwrap");
    process.close();

    processDesktop->close();
    objDesktop->hide();
    objDesktop->stopMedia();
}

void MainWindow::on_toolButton_clicked()
{

    QString fn = QFileDialog::getOpenFileName(this, tr("Open File..."),
                 QString(), trUtf8("Video Files (*)"));
    if (!fn.isEmpty())
    {
        ui->lineEdit->setText(fn);

    }
     //   ui->comboBox->setCurrentIndex(1);
}

void MainWindow::saveLayou()//حفظ البيانات الى ملف
{
    QSettings settings(QDir::homePath()+"/.Qwinwrap/qwinwrap.ini",
                       QSettings::IniFormat);

    settings.beginGroup("MainWindow");
    settings.setValue("xScreenSaverPath", m_xScreenSaverPath);
  settings.setValue("vedioPath", m_vedioPath);
    settings.endGroup();

}

void MainWindow::loadLayout()//load layou
{
     QSettings settings(QDir::homePath()+"/.Qwinwrap/qwinwrap.ini",
                        QSettings::IniFormat);
QString xScreenSaverPath;
     settings.beginGroup("MainWindow");
     if(QFile::exists("/usr/lib/xscreensaver")){
     xScreenSaverPath=settings.value("xScreenSaverPath","/usr/lib/xscreensaver").toString();
     }else  if(QFile::exists("/usr/lib64/xscreensaver")){
         xScreenSaverPath=settings.value("xScreenSaverPath","/usr/lib64/xscreensaver").toString();
    }else{
           xScreenSaverPath=qApp->applicationDirPath()+"/xscreensaver";
     }
     m_xScreenSaverPath=settings.value("xScreenSaverPath",xScreenSaverPath).toString();
     m_vedioPath=settings.value("vedioPath","").toString();
     ui->lineEdit->setText(m_vedioPath);
    settings.endGroup();
}

void MainWindow::on_actionSetScreenSaver_triggered()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    QString(),
                                                    QFileDialog::ShowDirsOnly
                                                    |QFileDialog::DontResolveSymlinks);

    QDir dir;
    if(dir.exists(dirName)){
        m_xScreenSaverPath=dirName;
          ui->listWidget->clear();
                  QDir dirS(m_xScreenSaverPath);
        QString subfile;

        foreach ( subfile, dirS.entryList(QDir::AllEntries| QDir::NoDotAndDotDot )){
             ui->listWidget->addItem(subfile);
         //   filetemp.remove(tempDir+"/"+subfile);
        }
    }


}

void MainWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this,"");
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this,"","Qwinwrap application gui for xwinwrap \n"
                       "Author : abouzakaria\n"
                       "Version : " +QApplication::applicationVersion());
}
void MainWindow::createActions()
{
    playAction = new QAction(tr("play Animation"), this);
    connect(playAction, SIGNAL(triggered()), this, SLOT(on_pBtnApplique_clicked()));

    stopAction = new QAction(tr("Stop Animation"), this);
    connect(stopAction, SIGNAL(triggered()), this, SLOT(on_pBtnKill_clicked()));

    minimizeAction = new QAction(tr("Mi&nimize"), this);
    connect(minimizeAction, SIGNAL(triggered()), this, SLOT(showMinimized()));

    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), this, SLOT(on_pBtnCancel_clicked()) );

}
void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
 trayIconMenu->addAction(playAction);
    trayIconMenu->addAction(stopAction);
   trayIconMenu->addSeparator();
     trayIconMenu->addAction(minimizeAction);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}
void MainWindow::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        if(this->isHidden()){
                this->showNormal();
        }else{
            this->hide();
             on_toolButtonPreview_toggled(false);
        }

    case QSystemTrayIcon::DoubleClick:

    case QSystemTrayIcon::MiddleClick:

    default:
        ;
    }
}

void MainWindow::on_listWidget_itemActivated(QListWidgetItem *item)
{

    on_pBtnApplique_clicked();

}

//void MainWindow::on_btnMinimize_clicked()
//{
//    hide();
//}

void MainWindow::on_actionQuit_triggered()
{
      on_pBtnKill_clicked();
qApp->quit();
}

void MainWindow::on_pBtnCancel_clicked()
{
     on_pBtnKill_clicked();
  qApp->quit();
     //  findDesktop();

}




void MainWindow::on_toolButtonPreview_toggled(bool checked)
{
    if(checked==false){
          processView.close();
           ui->widget->setVisible(false);
      //    ui->toolButtonPreview->setArrowType(Qt::LeftArrow);
ui->toolButtonPreview->setChecked(false);
    }else{
           ui->widget->setVisible(true);
         //    ui->toolButtonPreview->setArrowType(Qt::RightArrow);
             processView.close();
             if(!ui->listWidget->currentItem())
                 return;
             QString pathScreenS=m_xScreenSaverPath+"/"+ui->listWidget->currentItem()->text();

               QString    argument=QString("%1 -window-id %2 "
                                     ).arg(pathScreenS).arg(ui->widget->winId());

         qDebug( )<<argument;

         processView.start(argument);
    }
}

void MainWindow::on_listWidget_itemSelectionChanged()
{
    if(!ui->widget->isVisible())
        return;
    processView.close();


QString pathScreenS=m_xScreenSaverPath+"/"+ui->listWidget->currentItem()->text();
//process.startDetached(m_xScreenSaverPath+"/"+item->text());
      QString    argument=QString("%1 -window-id  %2 "
                            ).arg(pathScreenS).arg(ui->widget->winId());

qDebug( )<<argument;

processView.start(argument);
}

void MainWindow::on_widget_customContextMenuRequested(const QPoint &pos)
{
    ui->menuFile->exec(this->cursor().pos());
}

QString MainWindow::findDesktop()
{
    int W=QApplication::desktop()->geometry().width();
    int Y=QApplication::desktop()->geometry().height();
    QString G=QString::number(W)+"x"+QString::number(Y)+"+0+0";
    qDebug()<<"this geometry= "+G;
    QProcess p;

    p.start("xwininfo -root -tree");
    p.waitForFinished();
     QByteArray result = p.readAll();
     QTextCodec *codec = QTextCodec::codecForName("UTF-8");
       QString string = codec->toUnicode(result);
       QTextStream inw(&string);

       QString thisLine;
       bool isFirsChild=false;
       bool asChild=true;
       bool asdesktop=false;
       while ( !inw.atEnd() )
       {
          QString widthline = inw.readLine();
          if(widthline.contains("child")){
            isFirsChild=true;
              asChild=true;
          }else{

                asChild=false;
          }

          if(widthline.contains(G)){
                if(widthline.contains("desktop"))
                 asdesktop=true;

                if(isFirsChild==true&&asChild==false&&asdesktop==true)
                       thisLine=widthline.trimmed();
}
         //  qDebug()<<"isFirsChild : "<<isFirsChild <<" asChild : "<<asChild <<"   asdesktop : "<<asdesktop<<  "  : "<<widthline;
           if(!widthline.contains("child"))
                isFirsChild=false;

       }
      //   QMessageBox::information(0,"",thisLine);
         QString id=thisLine.section(" ",0,0);

return id;

}

void MainWindow::getid()
{
    bool ok;
        QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                                             tr("User name:"), QLineEdit::Normal,
                                             m_desktopId, &ok);
        if (ok && !text.isEmpty())
          m_desktopId=text;
  //    QMessageBox::information(0,"",findDesktop());
}

void MainWindow::on_btnMinimize_clicked()
{
    this->hide();
    on_toolButtonPreview_toggled(false);
}

void MainWindow::on_stackedWidget_currentChanged(int arg1)
{
    if(arg1==1)
           on_toolButtonPreview_toggled(false);
}
