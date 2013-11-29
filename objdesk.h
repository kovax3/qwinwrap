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
#ifndef OBJDESK_H
#define OBJDESK_H

#include <QWidget>
#include <phonon/audiooutput.h>

#include <phonon/videowidget.h>
#include <phonon/mediaobject.h>

class ObjDesk : public QWidget
{
    Q_OBJECT
public:
    explicit ObjDesk(QWidget *parent= 0);


signals:

public slots:
    void setFileName(const QString &fileName,bool mute ,bool loop);
void stopMedia();
private slots:
    void hasVideoChanged(bool bHasVideo);
    void stateChanged(Phonon::State newstate, Phonon::State );
void mediaFinished();
private :
    Phonon::MediaObject m_MediaObject;

  Phonon::AudioOutput m_AudioOutput;

   Phonon::VideoWidget *m_videoWidget;
   bool m_loop;
};

#endif // OBJDESK_H
