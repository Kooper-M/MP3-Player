#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QDir>

class AudioHandler {
    public: 
        AudioHandler(QString);
        void updateUrl(QUrl);
        void play();
        void pause();
        void next();
    private:
        QMediaPlayer *player_;
        QAudioOutput *audioOutput_;
        //QUrl url_;
        QDir dir_; 
        QStringList filePathList_;
        size_t playListPos_;
        size_t playListSize_;
};