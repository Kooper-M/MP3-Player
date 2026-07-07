#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

class AudioHandler {
    public: 
        AudioHandler(QUrl);
        //void updateUrl(QUrl);
        void play();
    private:
        QMediaPlayer *player_;
        QAudioOutput *audioOutput_;
        QUrl url_;
};