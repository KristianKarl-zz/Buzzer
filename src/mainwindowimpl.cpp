#include "mainwindowimpl.h"
#include <Phonon/AudioOutput>
#include <QKeyEvent>
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/extensions/XTest.h>
#include <unistd.h>


/* Send Fake Key Event */
static void SendKey (Display * disp, KeySym keysym, KeySym modsym)
{
  KeyCode keycode = 0, modcode = 0;

  keycode = XKeysymToKeycode (disp, keysym);
  if (keycode == 0) return;

  XTestGrabControl (disp, True);

  /* Generate modkey press */
  if (modsym != 0)
  {
     modcode = XKeysymToKeycode(disp, modsym);
     XTestFakeKeyEvent (disp, modcode, True, 0);
  }

  /* Generate regular key press and release */
  XTestFakeKeyEvent (disp, keycode, True, 0);
  XTestFakeKeyEvent (disp, keycode, False, 0);

  /* Generate modkey release */
  if (modsym != 0)
    XTestFakeKeyEvent (disp, modcode, False, 0);

  XSync (disp, False);
  XTestGrabControl (disp, False);
}

MainWindowImpl::MainWindowImpl( QWidget * parent, Qt::WFlags f)
        : QMainWindow(parent, f)
{
	setupUi(this);
        timer = new QTimer(this);


        joystick = new Joystick();
        joyDevBox->setText("/dev/input/js0");
        connect( timer, SIGNAL(timeout()), this, SLOT(updateForm()));
        connect( btnConnect, SIGNAL(clicked()), this, SLOT(joyConnect()));
        connect( resetBtn, SIGNAL(clicked()), this, SLOT(resetConnect()));

        buzz1 =
                 Phonon::createPlayer(Phonon::MusicCategory,
                                      Phonon::MediaSource("buzz1.wav"));
        buzz2 =
                 Phonon::createPlayer(Phonon::MusicCategory,
                                      Phonon::MediaSource("buzz2.wav"));
        buzz3 =
                 Phonon::createPlayer(Phonon::MusicCategory,
                                      Phonon::MediaSource("buzz3.wav"));
        buzz4 =
                 Phonon::createPlayer(Phonon::MusicCategory,
                                      Phonon::MediaSource("buzz4.wav"));
}

void MainWindowImpl::resetConnect() {
    if ( btnConnect->text()!="Connected!") return;
    for ( int i=0; i<=19; i++) {
        while( joystick->getButton(i)>0);
    }
    buttonIsHit = false;
    label->setText("");
    label->setStyleSheet("QLabel { background-color : lightgrey; color : black; }");
    buzz1->stop();
    buzz2->stop();
    buzz3->stop();
    buzz4->stop();
}

void MainWindowImpl::joyConnect() {
        if( joystick->init( joyDevBox->text().toAscii() ) > -1 ) {
                btnConnect->setText("Connected!");
                resetConnect();
                timer->start();
        }
}

void MainWindowImpl::updateForm() {
        if ( buttonIsHit) return;
        if(joystick->getButton(0) > 0) {
            SendKey (XOpenDisplay (NULL), XK_space, 0);
            label->setText("Nord");
            label->setStyleSheet("QLabel { background-color : red; color : black; }");
            buttonIsHit = true;
            buzz1->play();
            QMainWindow::activateWindow();
        } else if(joystick->getButton(5) > 0) {
            SendKey (XOpenDisplay (NULL), XK_space, 0);
            label->setText("Second");
            label->setStyleSheet("QLabel { background-color : blue; color : black; }");
            buttonIsHit = true;
            buzz2->play();
        } else if(joystick->getButton(10) > 0) {
            SendKey (XOpenDisplay (NULL), XK_space, 0);
            label->setText("Third");
            label->setStyleSheet("QLabel { background-color : yellow; color : black; }");
            buttonIsHit = true;
            buzz3->play();
        } else if(joystick->getButton(15) > 0) {
            SendKey (XOpenDisplay (NULL), XK_space, 0);
            label->setText("Forth");
            label->setStyleSheet("QLabel { background-color : green; color : black; }");
            buttonIsHit = true;
            buzz4->play();
        }

}
