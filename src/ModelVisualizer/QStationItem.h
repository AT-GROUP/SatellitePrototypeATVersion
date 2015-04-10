#ifndef QSTATIONITEM_H
#define QSTATIONITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QTableWidget>

class QStationItem: public QObject, public QGraphicsItemGroup
{
	Q_OBJECT
    private:
        QGraphicsEllipseItem *p_Ellipse;
		QGraphicsProxyWidget *proxy;
		QTableView *p_InfoList;
		
		QString name;
		QString status;
		QString bwNeeded;
		QString bwInUse;
		QString ipAddress;
		QString satellite;

		void updateColor();
		void setColor(QColor qColor);
    public:
        QStationItem(qreal x, qreal y, QString n, QObject* parent = 0, QGraphicsItemGroup* parent2 = 0);
        ~QStationItem();
		void updateFact(std::tuple<QString, QString, QString> info);
    protected:
        virtual void hoverEnterEvent (QGraphicsSceneHoverEvent *event);
        virtual void hoverLeaveEvent (QGraphicsSceneHoverEvent *event);
	signals:
		void valueChanged(const QString& mess);
};

#endif // QSTATIONITEM_H
