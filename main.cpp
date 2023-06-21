#include <iostream>

#include <QtGui/QtGui>
#include <QApplication>

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QAudio>

#include <QVideoWidget>
#include <QtWidgets/QtWidgets>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QFileDialog>

int main(int argc, char** argv)
{
    QApplication app(argc,argv);

    QWidget playerWindow;
    QVBoxLayout vbox(&playerWindow);
    QHBoxLayout buttons;

    auto videoWidget = new QVideoWidget(&playerWindow);
    vbox.addWidget(videoWidget);
    QSlider *songSlider = new QSlider(&playerWindow);
    songSlider->setOrientation(Qt::Horizontal);
    vbox.addWidget(songSlider);

    auto *openFileButton = new QPushButton("Open", &playerWindow);
    auto *playMediaButton = new QPushButton("Play", &playerWindow);
    auto *pauseMediaButton = new QPushButton("Pause", &playerWindow);

    buttons.addWidget(openFileButton);
    buttons.addWidget(playMediaButton);
    buttons.addWidget(pauseMediaButton);

    vbox.addLayout(&buttons);

    QString filePath;

    auto *player = new QMediaPlayer(&playerWindow);
    auto *audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);


    player->setVideoOutput(videoWidget);
    bool isPlaying = false;

    QObject::connect(openFileButton, &QPushButton::clicked, [&filePath, player, &isPlaying]()
                     {
        player->stop();
        filePath = QFileDialog::getOpenFileName(nullptr, "Open media", "/home/", "mp3 files (*.mp3, *.mp4)");
        isPlaying = false;
    });

            QObject::connect(player, &QMediaPlayer::durationChanged,songSlider, &QSlider::setMaximum);

    QObject::connect(playMediaButton, &QPushButton::clicked, [&isPlaying, songSlider, player,&filePath, audioOutput]()
    {
        if(!isPlaying)
        {
            player->setSource(QUrl::fromLocalFile(filePath));
            audioOutput->setVolume(0.7);

            QObject::connect(player, &QMediaPlayer::positionChanged, [songSlider](qint64 position)
            {
                songSlider->setValue(position);
            });
            isPlaying = true;
        }
        player->play();
    });


    QObject::connect(songSlider, &QSlider::sliderMoved, player, &QMediaPlayer::setPosition);

    QObject::connect(pauseMediaButton, &QPushButton::clicked, player, &QMediaPlayer::pause);

    playerWindow.show();

    return app.exec();
}
