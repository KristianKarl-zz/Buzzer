#ifndef MAINWINDOWIMPL_H
#define MAINWINDOWIMPL_H

#include <QMainWindow>
#include <QTimer>
#include <Phonon/MediaObject>
#include <joystick.h>
#include "ui_mainwindow.h"

class MainWindowImpl : public QMainWindow, public Ui::MainWindow
{
Q_OBJECT
public:
	MainWindowImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
        QTimer *timer;
        Joystick *joystick;
        bool buttonIsHit;
        Phonon::MediaObject *buzz1;
        Phonon::MediaObject *buzz2;
        Phonon::MediaObject *buzz3;
        Phonon::MediaObject *buzz4;
private slots:
        void updateForm();
        void joyConnect();
        void resetConnect();
};
#endif




