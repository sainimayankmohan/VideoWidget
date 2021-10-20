#include "gallery.h"
#include "thumbnail.h"
#include <QFileDialog>
#include <QDebug>
#include <QSettings>
#include <QDir>

Gallery::Gallery(bool rawVideo, QWidget *parent):QDialog(parent),m_pAddBtn(NULL),m_enableNewAdd(rawVideo)
{
    m_pGLayout = new QGridLayout(this);

    if(rawVideo)
    {
        m_pAddBtn = new QPushButton();
        m_pAddBtn->setIcon(QIcon(":/add.png"));
        m_pAddBtn->setIconSize(QSize(80,80));
        m_pAddBtn->setMaximumSize(200,200);

        connect(m_pAddBtn,SIGNAL(clicked(bool)),this,SLOT(addNewVideo()));
        m_pGLayout->addWidget(m_pAddBtn);
    }

    setLayout(m_pGLayout);

    fetchData();
}

Gallery::~Gallery()
{
    if(m_pAddBtn!= NULL)
        delete m_pAddBtn;
    m_pAddBtn = NULL;
    delete m_pGLayout;
}

void Gallery::addNewVideo()
{
    QString fileName = QFileDialog::getOpenFileName(this, ("Open File"),
                                                     "/home",
                                                     ("Videos (*.mp4 )"));

    if(!fileName.isEmpty())
    {
        QStringList lList = fileName.split("/");

        QSettings settings(QDir::currentPath() + "/videowidgetsettings.ini",QSettings::IniFormat);
        settings.beginGroup(RAW_VIDEOS);
        settings.setValue(lList.last(),fileName);
        addThumbnail(fileName);
        settings.sync();
    }
}

void Gallery::removeThumbnail(QString name)
{
    if(m_VideoMap.contains(name))
    {
        Thumbnail* thumbnail = m_VideoMap.value(name);
        m_pGLayout->removeWidget(thumbnail);
        m_VideoMap.remove(name);
        thumbnail->hide();
        delete thumbnail;
        thumbnail = NULL;
    }

    QSettings settings(QDir::currentPath() + "/videowidgetsettings.ini",QSettings::IniFormat);
    if(m_enableNewAdd)
        settings.beginGroup(RAW_VIDEOS);
    else
        settings.beginGroup(EDITED_VIDEOS);

    for(QString key:settings.allKeys())
    {
        if(key == name.split("/").last())
        {
            if(settings.value(key).toString() == name)
                settings.remove(key);
        }
    }
}

void Gallery::playVideo(QString name)
{
    accept();
    emit play(name);
}

void Gallery::fetchData()
{
    QSettings settings(QDir::currentPath() + "/videowidgetsettings.ini",QSettings::IniFormat);
    if(m_enableNewAdd)
        settings.beginGroup(RAW_VIDEOS);
    else
        settings.beginGroup(EDITED_VIDEOS);

    QStringList keys = settings.allKeys();


    for(QString key : keys)
    {
        addThumbnail(settings.value(key).toString());
    }
}

bool Gallery::addThumbnail(QString filename)
{
    if(!m_VideoMap.contains(filename))
    {
        Thumbnail* thumbnail = new Thumbnail(filename,m_enableNewAdd,this);
        connect(thumbnail,SIGNAL(remove(QString)),this,SLOT(removeThumbnail(QString)));
        connect(thumbnail,SIGNAL(play(QString)),this,SLOT(playVideo(QString)));

        m_VideoMap.insert(filename,thumbnail);

        int count = m_pGLayout->count();

        int col = count%4;

        int row = count/4;

        m_pGLayout->addWidget(thumbnail,row,col);

        return true;
    }

    return false;
}



