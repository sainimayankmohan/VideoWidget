#ifndef THUMBNAIL_H
#define THUMBNAIL_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QMediaPlayer>
#include <QVideoWidget>

#define RAW_VIDEOS "Raw_Videos"
#define EDITED_VIDEOS "Edited_Videos"

class Thumbnail : public QFrame
{
    Q_OBJECT
public:
    Thumbnail(QString name,bool israw,QWidget *parent = 0);
    ~Thumbnail();

signals:

    void remove(QString name);
    void play(QString name);

private slots:

    void onRemoveButtonClicked();
    void onPlayButtonClicked();
    void onEditButtonClicked();

private:
    QString m_Name;
    QLabel *m_pNameLbl;
    QPushButton *m_pRemoveButton;
    QVideoWidget *m_pVideoWidget;
    QPushButton *m_pEditButton;
    QPushButton *m_pPlayButton;
    QGridLayout *m_pGLayout;
    QMediaPlayer *m_pMediaPlayer;
};

#endif // THUMBNAIL_H
