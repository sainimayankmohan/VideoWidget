#include "thumbnail.h"
#include <QSettings>
#include <QDir>
#include <QFile>
#include <QTimer>
#include <QDebug>

Thumbnail::Thumbnail(QString name, bool israw, QWidget *parent) : QFrame(parent),m_Name(name)
{
    m_pNameLbl = new QLabel(name.split("/").last());
    m_pNameLbl->setMaximumHeight(40);

    m_pRemoveButton = new QPushButton;
    m_pRemoveButton->setIcon(QIcon(":/remove.png"));
    m_pRemoveButton->setMaximumHeight(40);
    connect(m_pRemoveButton,SIGNAL(clicked(bool)),this,SLOT(onRemoveButtonClicked()));

    m_pVideoWidget = new QVideoWidget();
    m_pVideoWidget->setMaximumHeight(120);

    m_pPlayButton =  new QPushButton();
    m_pPlayButton->setIcon(QIcon(":/play.png"));
    m_pPlayButton->setMaximumHeight(40);
    connect(m_pPlayButton,SIGNAL(clicked(bool)),this,SLOT(onPlayButtonClicked()));

    m_pEditButton =  new QPushButton();
    m_pEditButton->setIcon(QIcon(":/edit.png"));
    m_pEditButton->setMaximumHeight(40);
    connect(m_pEditButton,SIGNAL(clicked(bool)),this,SLOT(onEditButtonClicked()));

    m_pGLayout = new QGridLayout();

    m_pGLayout->addWidget(m_pNameLbl,0,0,Qt::AlignLeft);
    m_pGLayout->addWidget(m_pRemoveButton,0,1,Qt::AlignRight);
    m_pGLayout->addWidget(m_pVideoWidget,1,0,Qt::AlignCenter);
    m_pGLayout->addWidget(m_pPlayButton,2,0,Qt::AlignLeft);
    m_pGLayout->addWidget(m_pEditButton,2,1,Qt::AlignRight);

    m_pMediaPlayer = new QMediaPlayer;
    m_pMediaPlayer->setMedia(QUrl::fromLocalFile(m_Name));
    m_pMediaPlayer->setVideoOutput(m_pVideoWidget);
    m_pMediaPlayer->play();

    QTimer::singleShot(1000,m_pMediaPlayer,SLOT(stop()));

    if(!israw)
        m_pEditButton->hide();

    setLayout(m_pGLayout);

    setFrameShape(QFrame::Box);

    setWindowFlags(Qt::FramelessWindowHint);

    setMaximumSize(200,200);
}

Thumbnail::~Thumbnail()
{
    delete m_pNameLbl;
    delete m_pRemoveButton;
    delete m_pVideoWidget;
    delete m_pEditButton;
    delete m_pPlayButton;
    delete m_pGLayout;
    delete m_pMediaPlayer;
}

void Thumbnail::onRemoveButtonClicked()
{
    emit remove(m_Name);
}

void Thumbnail::onPlayButtonClicked()
{
    emit play(m_Name);
    //Play Video

//    QMediaPlayer* player = new QMediaPlayer;
//    player->setMedia(QUrl::fromLocalFile(m_Name));

//    QVideoWidget *videoWidget = new QVideoWidget();
//    player->setVideoOutput(videoWidget);
//    videoWidget->showMaximized();
//    videoWidget->raise();

//    player->play();

}

void Thumbnail::onEditButtonClicked()
{
    //Show Edit option

    QStringList lList = m_Name.split("/");

//    QString path = m_Name.remove(lList.last());

//    QString editPath = path + "edited_" +lList.last();

    QSettings settings(QDir::currentPath() + "/videowidgetsettings.ini",QSettings::IniFormat);
    settings.beginGroup(EDITED_VIDEOS);

//    if(QFile::copy(m_Name, editPath))
//    {

//        settings.setValue("edited_" +lList.last(),editPath);
//    }
//    else
//    {
        settings.setValue(lList.last(),m_Name);
//    }
    settings.sync();
}

