#include "QSatelliteItem.h"
#include "InfoTableModel.h"
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QHeaderView>
#include <tuple>

QSatelliteItem::QSatelliteItem(qreal x, qreal y, QString n, QObject* parent, QGraphicsItemGroup* parent2)
	    :QObject(parent),QGraphicsItemGroup(parent2)
{
    name = n;
    icon = new QGraphicsPixmapItem(QPixmap(":/Pictures/Resources/satellite.png"));
	addToGroup(icon);
    setPos(x,y);
    icon->setVisible (true);
	p_InfoList = new QTableView();
    p_InfoList->setModel(new InfoTableModel(n));
    p_InfoList->setAutoScroll (false);
    p_InfoList->horizontalHeader()->hide();
    p_InfoList->verticalHeader()->hide();
	setAcceptHoverEvents(true);

	ipAddress = "10.50.0.1";
	maxBw = "1024";
	curBw = "0";
	avalBw = "0";
	stationCount = "0";
	status = "offline";

	updateFact(std::make_tuple(n, "name", n));
	updateFact(std::make_tuple(n, "maxBw", maxBw));
	updateFact(std::make_tuple(n, "avalBw", avalBw));
	//updateFact(std::make_tuple(n, "curBw", curBw));
	updateFact(std::make_tuple(n, "stationCount", stationCount));
	updateFact(std::make_tuple(n, "status", status));
}

QSatelliteItem::~QSatelliteItem()
{
	delete icon;
	delete p_InfoList;
}

void QSatelliteItem::hoverEnterEvent (QGraphicsSceneHoverEvent *event)
{
   // ToDo: Fix warning "QGraphicsProxyWidget::setWidget: cannot embed widget *XXXXX; already embedded"
   proxy = icon->scene()->addWidget(p_InfoList);
   proxy->setPos(event->scenePos());
   p_InfoList->show();
   event->accept();
}

void QSatelliteItem::hoverLeaveEvent (QGraphicsSceneHoverEvent *event)
{    
    p_InfoList->hide();
    event->accept();
}

void QSatelliteItem::updateFact(std::tuple<QString, QString, QString> info)
{
	QString satelliteName, attrName, attrValue;
	std::tie(satelliteName, attrName, attrValue) = info;
	if (satelliteName == name)
	{
		if (attrName == "ipAddress")
			ipAddress = attrValue;
		if (attrName == "name")
			name = attrValue;
		if (attrName == "maxBw")
		{
			if (maxBw != attrValue) emit valueChanged(name + " " + attrName + " changed to " + attrValue);
			maxBw = attrValue;
		}
		if (attrName == "avalBw")
			avalBw = attrValue;
		if (attrName == "stationCount")
		{
			if (stationCount != attrValue) emit valueChanged(name + " " + attrName + " changed to " + attrValue);
			stationCount = attrValue;
		}
		if (attrName == "status")
		{
			if (status != attrValue) emit valueChanged(name + " " + attrName + " changed to " + attrValue);
			status = attrValue;
		}
		InfoTableModel* tempModel = (InfoTableModel*) p_InfoList->model();
		tempModel->updateData(QPair<QString,QString>(attrName,attrValue));
		
	}
}