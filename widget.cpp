#include "widget.h"
#include "gallery.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_pMainLayout = new QHBoxLayout(this);

    m_pRawButton = new QPushButton("Raw Videos",this);
    m_pRawButton->setFixedSize(300,200);

    m_pEditedButton = new QPushButton("Edited Videos",this);
    m_pEditedButton->setFixedSize(300,200);

    m_pMainLayout->addWidget(m_pRawButton,0,Qt::AlignHCenter);
    m_pMainLayout->addWidget(m_pEditedButton,0,Qt::AlignCenter);

    connect(m_pRawButton,SIGNAL(clicked(bool)),this,SLOT(onRawButtonClicked()));
    connect(m_pEditedButton,SIGNAL(clicked(bool)),this,SLOT(onEditedButtonClicked()));

    m_pMediaPlayer = new QMediaPlayer;
    m_pVideoWidget = new QVideoWidget();
    m_pMediaPlayer->setVideoOutput(m_pVideoWidget);

    setMinimumSize(800,600);

    setLayout(m_pMainLayout);
}

Widget::~Widget()
{
    delete m_pRawButton;
    delete m_pEditedButton;

    delete m_pMainLayout;

    delete m_pVideoWidget;
    delete m_pMediaPlayer;
}


void Widget::onRawButtonClicked()
{
    //Open Raw Videos widget
    Gallery g(true,this);
    connect(&g,SIGNAL(play(QString)),this,SLOT(playVideo(QString)));
    g.setFixedSize(this->size());
    g.setWindowTitle("Raw Videos");
    g.exec();
}

void Widget::onEditedButtonClicked()
{
    //open edited video widget
    Gallery g(false,this);
    g.setFixedSize(this->size());
    g.setWindowTitle("Edited Videos");
    g.exec();
}

void Widget::onVideoWidgetClose()
{
    m_pRawButton->setDisabled(false);
    m_pEditedButton->setDisabled(false);
}

void Widget::playVideo(QString name)
{
    m_pMediaPlayer->stop();
    m_pMediaPlayer->setMedia(QUrl::fromLocalFile(name));
    m_pVideoWidget->setWindowTitle(name);
    m_pVideoWidget->setFixedSize(this->size());
    m_pVideoWidget->show();
    m_pMediaPlayer->play();
}
