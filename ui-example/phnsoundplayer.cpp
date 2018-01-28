#include "phnsoundplayer.h"

QT_USE_NAMESPACE

phnSoundPlayer::phnSoundPlayer(QObject *parent)
    : QThread(parent)
{
    this->mSoundPath = "";
    this->mEvent = NULL;

    mPlayer = new QMediaPlayer(this);
    mPlayList = new QMediaPlaylist(mPlayer);
    mPlayer->setPlaylist(mPlayList);
}

phnSoundPlayer::~phnSoundPlayer()
{
}

void phnSoundPlayer::setInformation(QString _soundPath, QQueue<phnEvent> *_event)
{
    this->mSoundPath = _soundPath;
    this->mEvent = _event;
}

void phnSoundPlayer::run()
{
    QString _zone;
    QString _target;
    QString _score;
    QString _index;

    while(true)
    {
        if(mEvent != NULL && !mEvent->isEmpty() && mPlayer->state() == QMediaPlayer::StoppedState)
        {
            phnEvent event = mEvent->dequeue();

            _zone   = mSoundPath + "zone_" + QString("%1").arg(event.Zone, 0, 10, QChar('0')) + ".mp3";
            _target = mSoundPath + "bia_" + QString("%1").arg(event.Target, 0, 10, QChar('0')) + ".mp3";
            _index  = mSoundPath + "lan_" + QString("%1").arg(event.Sequence + 1, 0, 10, QChar('0')) + ".mp3";
            _score  = mSoundPath + QString("%1").arg(event.Value, 0, 10, QChar('0')) + ".mp3";

            if(!mPlayList->isEmpty())
            {
                mPlayList->clear();
            }

            mPlayList->addMedia(QUrl::fromLocalFile(_zone));
            mPlayList->addMedia(QUrl::fromLocalFile(_target));
            mPlayList->addMedia(QUrl::fromLocalFile(_index));
            mPlayList->addMedia(QUrl::fromLocalFile(_score));
            // ...
            mPlayList->setCurrentIndex(0);

            mPlayer->setVolume(60);
            mPlayer->play();
        }
        else
        {
            QThread::msleep(300);
        }
    }
}
