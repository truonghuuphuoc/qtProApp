#ifndef PHNSOUNDPLAYER_H
#define PHNSOUNDPLAYER_H

#include <QtCore>
#include <QThread>
#include <QString>
#include <QtMultimedia/QSound>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>

#include "phnevent.h"


class phnSoundPlayer: public QThread
{
    Q_OBJECT
public:
    explicit phnSoundPlayer(QObject *parent = nullptr);
    ~phnSoundPlayer();

    void run() Q_DECL_OVERRIDE;

private:
    QString mSoundPath;
    QMediaPlayer *mPlayer;
    QMediaPlaylist *mPlayList;
    QQueue<phnEvent> *mEvent;

public:
    void setInformation(QString _soundPath, QQueue<phnEvent> *_event);

};

#endif // PHNSOUNDPLAYER_H
