#include "playerwidget.h"

#include <QtAV/VideoOutput.h>
//#include <QSlider>
#include <slider.h>

#include <QVBoxLayout>
#include <QFileDialog>
#include <QPushButton>
#include <QDebug>

playerWidget::playerWidget(QWidget *parent) : QWidget(parent)
{
    resize(800, 600);

    m_unit = 1000;

    m_player = new AVPlayer(this);
    QVBoxLayout *vl = new QVBoxLayout();
    setLayout(vl);
    VideoOutput *m_vo = new VideoOutput(this);
    if (!m_vo->widget()) {
        //QMessageBox::warning(0, QString::fromLatin1("QtAV error"), tr("Can not create video renderer"));
        qDebug() << "QtAV error : Can not create video renderer";
        return;
    }
    m_player->setRenderer(m_vo);
    vl->addWidget(m_vo->widget());

    //slider
    m_slider = new Slider();
    m_slider->setOrientation(Qt::Horizontal);
    connect(m_slider, SIGNAL(sliderMoved(int)), SLOT(seekBySlider(int)));
    connect(m_slider, SIGNAL(sliderPressed()), SLOT(seekBySlider()));
    connect(m_player, SIGNAL(positionChanged(qint64)), SLOT(updateSlider(qint64)));
    connect(m_player, SIGNAL(started()), SLOT(updateSlider()));
    connect(m_player, SIGNAL(notifyIntervalChanged()), SLOT(updateSliderUnit()));
    vl->addWidget(m_slider);


    QHBoxLayout *hb = new QHBoxLayout();
    vl->addLayout(hb);
    QPushButton *m_openBtn = new QPushButton(tr("Open"));
    QPushButton *m_playBtn = new QPushButton(tr("Play/Pause"));
    QPushButton *m_stopBtn = new QPushButton(tr("Stop"));
    QPushButton *m_skipBtn = new QPushButton(tr("skip"));
    hb->addWidget(m_openBtn);
    hb->addWidget(m_playBtn);
    hb->addWidget(m_stopBtn);
    hb->addWidget(m_skipBtn);
    connect(m_openBtn, SIGNAL(clicked()), SLOT(openMedia()));
    connect(m_playBtn, SIGNAL(clicked()), SLOT(playPause()));
    connect(m_skipBtn, SIGNAL(clicked()), SLOT(playSkip()));
}

void playerWidget::seekBySlider(int value)
{
    if (!m_player->isPlaying())
        return;
    //qDebug()<<"m_player seek="<<value*m_unit;
    m_player->seek(qint64(value*m_unit));
}

void playerWidget::seekBySlider()
{
    //qDebug()<<"myslider="<<m_slider->value()<<"mslider_size="<<m_player->duration()/m_unit;
    seekBySlider(m_slider->value());
}

void playerWidget::updateSlider(qint64 value)
{
    m_slider->setRange(0, int(m_player->duration()/m_unit));
    m_slider->setValue(int(value/m_unit));
}

void playerWidget::updateSlider()
{
    updateSlider(m_player->position());
}

void playerWidget::updateSliderUnit()
{
    m_unit = m_player->notifyInterval();
    updateSlider();
}

void playerWidget::openMedia()
{
//    QString file = QFileDialog::getOpenFileName(0, tr("Open a video"));
//    if (file.isEmpty())
//        return;
    //m_player->play(file);
    //m_player->play("rtmp://192.168.1.9/vod/1.mp4");
    //m_player->play("/home/hyz/Downloads/testvideo3.mp4");
    m_player->play("rtmp://58.200.131.2:1935/livetv/dftv");
}
void playerWidget::playSkip()
{
    seekBySlider(m_player->duration()*0.5/m_unit);
}
void playerWidget::playPause()
{
    if (!m_player->isPlaying()) {
        m_player->play();
        return;
    }
    m_player->pause(!m_player->isPaused());
}
