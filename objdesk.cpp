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
#include "objdesk.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>
ObjDesk::ObjDesk(QWidget *parent) :
    QWidget(parent)
{
this->setPalette(Qt::black);
//    this->setEnabled(false);
     this->setWindowFlags(Qt::WindowStaysOnBottomHint|Qt::FramelessWindowHint|Qt::BypassGraphicsProxyWidget);
  this->setAttribute(Qt::WA_DeleteOnClose,true);
this->setAttribute(Qt::WA_TransparentForMouseEvents,true);
this->setAttribute(Qt::WA_X11NetWmWindowTypeDesktop);
//this->setAttribute(Qt::WA_WindowPropagation,true);

  this->setAttribute(Qt::WA_PaintUnclipped,true);
//this->setAttribute(Qt::WA_PaintUnclipped,false);
this->setAttribute(Qt::WA_TranslucentBackground,true);

// this->setAttribute(Qt::WA_NoChildEventsFromChildren,true);
// this->setAttribute(Qt::WA_NoSystemBackground,true);
this->setFocusPolicy(Qt::NoFocus);
   QDesktopWidget *wid=new QDesktopWidget;
// this->setParent(wid);
  this->setGeometry(0,0,wid->geometry().width(),wid->geometry().height());
//    this->setMask(QRegion(50,50,200,200));
  this->setEnabled(false);
  //  this->setFocus(Qt::NoFocus);
         //   this->clearFocus();
//-------------------------------------------Phonon-------------------------------------------------------------------------------------
   m_videoWidget=new  Phonon::VideoWidget;
   connect(&m_MediaObject, SIGNAL(stateChanged(Phonon::State,Phonon::State)), this, SLOT(stateChanged(Phonon::State,Phonon::State)));
//   connect(&m_MediaObject, SIGNAL(totalTimeChanged(qint64)), this, SLOT(updateTime()));
 //  connect(&m_MediaObject, SIGNAL(tick(qint64)), this, SLOT(updateTime()));
 //  connect(&m_MediaObject, SIGNAL(metaDataChanged()), this, SLOT(updateInfo()));
    connect(&m_MediaObject, SIGNAL(hasVideoChanged(bool)), this, SLOT(hasVideoChanged(bool)));
       connect(&m_MediaObject, SIGNAL(finished()), this, SLOT(mediaFinished()));
   //connect(m_videoWidget, SIGNAL(customContextMenuRequested(const QPoint &)), SLOT(showContextMenu(const QPoint &)));
  Phonon::createPath(&m_MediaObject, &m_AudioOutput);
  Phonon::createPath(&m_MediaObject, m_videoWidget);
  QVBoxLayout *vLayoutInfo = new QVBoxLayout(this);
  vLayoutInfo->setSpacing(6);
  vLayoutInfo->setContentsMargins(11, 11, 11, 11);
  vLayoutInfo->setObjectName(QString::fromUtf8("vLayoutInfo"));
  vLayoutInfo->setContentsMargins(0, 0, 0, 0);
 vLayoutInfo->addWidget(m_videoWidget);
  m_videoWidget->setScaleMode(Phonon::VideoWidget::FitInView);
  m_videoWidget->setVisible(false);
}
void ObjDesk::hasVideoChanged(bool bHasVideo)
{

    m_videoWidget->setVisible(bHasVideo);

}
void ObjDesk::stateChanged(Phonon::State newstate, Phonon::State )
{

    switch (newstate) {
        case Phonon::ErrorState:
            if (m_MediaObject.errorType() == Phonon::FatalError) {


            } else {
              //  m_MediaObject.pause();
            }
   QMessageBox::warning(this, "Phonon Mediaplayer", m_MediaObject.errorString(), QMessageBox::Close);
         this->hide();
        break;

        case Phonon::StoppedState:
          //  m_videoWidget->setFullScreen(false);
            // Fall through
        case Phonon::PausedState:

            break;
        case Phonon::PlayingState:
        if (!m_MediaObject.hasVideo()){
           stopMedia();
            QMessageBox::warning(0, "Phonon Mediaplayer","this is no video valid", QMessageBox::Close);
         this->hide();
        }
     //   m_videoWidget->setVisible(false);
            // Fall through
        case Phonon::BufferingState:
            //rewindButton->setEnabled(true);
            break;
        case Phonon::LoadingState:
          // rewindButton->setEnabled(false);
            break;
    }
}
void ObjDesk::setFileName(const QString &fileName,bool mute ,bool loop)
{
m_videoWidget->showFullScreen();
     m_videoWidget->setVisible(true);
     m_MediaObject.setCurrentSource(Phonon::MediaSource(fileName));
    m_MediaObject.play();
m_loop=loop;
m_AudioOutput.setMuted(mute);

}
void ObjDesk::stopMedia()
{
      m_MediaObject.stop();
       m_videoWidget->setVisible(false);

}
void ObjDesk::mediaFinished()
{
    if(m_loop==false)
        return;
        m_MediaObject.setCurrentSource(m_MediaObject.currentSource());
//     if (m_MediaObject.currentTime() == m_MediaObject.totalTime())
//        m_MediaObject.seek(1);

     m_MediaObject.play();
      //
}
