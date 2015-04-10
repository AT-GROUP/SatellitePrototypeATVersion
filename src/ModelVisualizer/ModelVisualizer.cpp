#include "ModelVisualizer.h"
#include <QWheelEvent>
#include <QMenuBar>
#include <QToolButton>
#include <tuple>
#include <qlist.h>
#include <qdebug.h>
#include <GraphsWindow.h>
#include <qsignalmapper.h>

ModelVisualizer::ModelVisualizer(QWidget *parent):
    QWidget(parent)
{
    createWidgets();
    createView();
    createMenu();
    createLayout();
    addStations();
}

ModelVisualizer::~ModelVisualizer()
{
    delete p_Scene;
    delete p_View;
    delete p_GridLayout;
    delete p_EventList;
//    delete p_MainMenu;
    delete action1;
}

void ModelVisualizer::createWidgets()
{
    p_Scene = new QGraphicsScene();
    p_EventList = new QListWidget();
    p_EventList->setFixedWidth (180);
    p_EventList->autoScrollMargin();
    p_BackGroundPic = new QGraphicsPixmapItem(QPixmap(":/Pictures/Resources/back.png"));
	//setStyleSheet("background-image: url(:/Pictures/Resources/back.png);");
    p_Scene->addItem(p_BackGroundPic);
}

void ModelVisualizer::createView()
{
    p_View = new QGraphicsView();
    p_View->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    p_View->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    p_View->setMouseTracking(true);
    p_View->setScene(p_Scene);
}

void ModelVisualizer::createMenu()
{
	QSignalMapper* m_sigmapper = new QSignalMapper(this);
    p_MainMenu = new QMenuBar();
    action1 = new QAction("Continue simulation", this);
    action1->setData(QString("Simulation continued"));
    connect(action1, SIGNAL(triggered()), m_sigmapper, SLOT(map()));
    p_MainMenu->addAction(action1);
	m_sigmapper->setMapping(action1, action1->data().toString());
	action2 = new QAction("Pause simulation", this);
    action2->setData(QString("Simulation paused"));
	connect(action2, SIGNAL(triggered()), m_sigmapper, SLOT(map()));
    m_sigmapper->setMapping(action2, action2->data().toString());
    p_MainMenu->addAction(action2);
	action3 = new QAction("Configure model", this);
    action3->setData(QString("Not done yet"));
	connect(action3, SIGNAL(triggered()), m_sigmapper, SLOT(map()));
	p_MainMenu->addAction(action3);
    m_sigmapper->setMapping(action3, action3->data().toString());
	action4 = new QAction("Show graphics", this);
	connect(action4, SIGNAL(triggered()), this, SLOT(showGraphsWindow()));
	p_MainMenu->addAction(action4);
	connect(m_sigmapper, SIGNAL(mapped(QString)), this, SLOT(addMessageToEventsList(const QString&)));
}

void ModelVisualizer::createLayout()
{
    p_GridLayout = new QGridLayout();
    p_GridLayout->addWidget(p_View, 1, 0);
    p_GridLayout->addWidget(p_EventList, 1, 1);
    p_GridLayout->addWidget (p_MainMenu, 0, 0, 1, 0);
    setLayout(p_GridLayout);
}

void ModelVisualizer::addStations()
{
	p_StationList = new QMap<QString, QStationItem*>();
	p_SatelliteList = new QMap<QString, QSatelliteItem*>();
	p_StationList->insert("Station1", new QStationItem(800,200, "Station1"));
    p_StationList->insert("Station2", new QStationItem(840,250, "Station2"));
    p_StationList->insert("Station3", new QStationItem(370,250, "Station3"));
    p_StationList->insert("Station4", new QStationItem(400,277, "Station4"));
    p_StationList->insert("Station5", new QStationItem(450,250, "Station5"));
	p_StationList->insert("Station6", new QStationItem(200,400, "Station6"));
	p_StationList->insert("Station7", new QStationItem(700,240, "Station7"));
	p_StationList->insert("Station8", new QStationItem(1000,250, "Station8"));
	p_StationList->insert("Station9", new QStationItem(905,470, "Station9"));
	p_SatelliteList->insert("Intelsat", new QSatelliteItem(200,100, "Intelsat"));
	p_SatelliteList->insert("Yamal", new QSatelliteItem(600,0, "Yamal"));
	p_SatelliteList->insert("AM3", new QSatelliteItem(1000,100, "AM3"));
	for (QMap<QString, QStationItem*>::iterator it = p_StationList->begin(); it != p_StationList->end(); it++)
	{
		 p_Scene->addItem((*it));
		 connect((*it), SIGNAL(valueChanged(const QString&)), this, SLOT(addMessageToEventsList(const QString&)));
	}
	for (QMap<QString, QSatelliteItem*>::iterator it = p_SatelliteList->begin(); it != p_SatelliteList->end(); it++)
	{
		 p_Scene->addItem((*it));
		 connect((*it), SIGNAL(valueChanged(const QString&)), this, SLOT(addMessageToEventsList(const QString&)));
	}
}

void ModelVisualizer::addMessageToEventsList(const QString& message)
{
    p_EventList->addItem(message);
    p_EventList->scrollToBottom();
}

void ModelVisualizer::wheelEvent(QWheelEvent * event)
{
    // ToDo: Fix max zoom and zoom position
    if (event->modifiers().testFlag(Qt::ControlModifier))
    {
        int numSteps = event->delta() / 15 / 8;
        if (numSteps == 0)
        {
            event->ignore();
            return;
        }
        qreal sc = pow(1.25, numSteps);
        this->mapZoom(sc, p_View->mapToScene(event->pos()));
        event->accept();
    }
}

void ModelVisualizer::mapZoom(qreal factor, QPointF centerPoint)
{
    p_View->scale(factor, factor);
    p_View->centerOn(centerPoint);
}

void ModelVisualizer::updateFromModelFile()
{
    QFile* file = new QFile("BB2.xml");
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }
    QXmlStreamReader xml(file);
	while ((!xml.atEnd()) && (!xml.hasError()))
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            if (xml.name() != "fact")
                continue;
			std::tuple<QString, QString, QString> attr = (parseFacts(xml));
			if (p_StationList->contains(std::get<0>(attr)))
			{
				p_StationList->value(std::get<0>(attr))->updateFact(attr);
			}
			if (p_SatelliteList->contains(std::get<0>(attr)))
			{
				p_SatelliteList->value(std::get<0>(attr))->updateFact(attr);
			}
        }
    }
	p_EventList->addItem("Model updated");
	p_EventList->scrollToBottom();
}

std::tuple<QString, QString, QString> ModelVisualizer::parseFacts(QXmlStreamReader& xml)
{
    QXmlStreamAttributes attributes = xml.attributes();
    if ((attributes.hasAttribute("AttrPath"))&&(attributes.hasAttribute("Value")))
    {
        return std::make_tuple(attributes.value("AttrPath").toString().split('.').at(0), attributes.value("AttrPath").toString().split('.').at(1), attributes.value("Value").toString());
    }
}

void ModelVisualizer::showGraphsWindow()
{
	GraphsWindow* g1 = new GraphsWindow();
	g1->show();
}