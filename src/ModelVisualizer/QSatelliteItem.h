#ifndef QSATELLITEITEM_H
#define QSATELLITEITEM_H

#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QTableWidget>

class QSatelliteItem: public QObject, public QGraphicsItemGroup
{
	Q_OBJECT
    private:
        QGraphicsPixmapItem *icon;
		QGraphicsProxyWidget *proxy;
		QTableView *p_InfoList;

		QString name;
		QString ipAddress;
		QString maxBw;
		QString curBw;
		QString avalBw;
		QString stationCount;
		QString status;
    public:
        QSatelliteItem(qreal x, qreal y, QString n, QObject* parent = 0, QGraphicsItemGroup* parent2 = 0);
        ~QSatelliteItem();
		void updateFact(std::tuple<QString, QString, QString> info);
	protected:
		virtual void hoverEnterEvent (QGraphicsSceneHoverEvent *event);
        virtual void hoverLeaveEvent (QGraphicsSceneHoverEvent *event);
	signals:
		void valueChanged(const QString& mess);
};

#endif // QSATELLITEITEM_H
