#ifndef GALLERY_H
#define GALLERY_H

#include <QDialog>
#include <QGridLayout>
#include <QMap>

class Thumbnail;


class Gallery:public QDialog
{
    Q_OBJECT
public:
    Gallery(bool rawVideo = true,QWidget* parent = 0);
    ~Gallery();

private slots:

    void addNewVideo();

    void removeThumbnail(QString name);

    void playVideo(QString name);

signals:
    void play(QString name);

private:

    void fetchData();

    bool addThumbnail(QString filename);

private:
    QGridLayout* m_pGLayout;
    QPushButton *m_pAddBtn;
    bool m_enableNewAdd;
    QMap<QString,Thumbnail*> m_VideoMap;

};

#endif // GALLERY_H
