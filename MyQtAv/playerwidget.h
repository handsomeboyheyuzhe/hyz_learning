#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QtAV/AVPlayer.h>

using namespace QtAV;

class Slider;

class playerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit playerWidget(QWidget *parent = 0);

private:
    AVPlayer *m_player;
    Slider *m_slider;
    int m_unit;

signals:

public slots:
    void seekBySlider(int value);
    void seekBySlider();
    void updateSlider(qint64 value);
    void updateSlider();
    void updateSliderUnit();

    void openMedia();
    void playPause();
    void playSkip();
};

#endif // PLAYERWIDGET_H
