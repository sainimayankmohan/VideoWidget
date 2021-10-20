#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

#include <QMediaPlayer>
#include <QVideoWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void onRawButtonClicked();
    void onEditedButtonClicked();
    void onVideoWidgetClose();
    void playVideo(QString name);

private:
    QHBoxLayout *m_pMainLayout;
    QPushButton *m_pRawButton;
    QPushButton *m_pEditedButton;
    QMediaPlayer *m_pMediaPlayer;
    QVideoWidget *m_pVideoWidget;
};

#endif // WIDGET_H
