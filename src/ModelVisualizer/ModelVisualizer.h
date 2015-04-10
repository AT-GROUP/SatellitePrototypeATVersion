#ifndef MODELVISUALIZER_H
#define MODELVISUALIZER_H

#include "QSatelliteItem.h"
#include "QStationItem.h"
#include <QWidget>
#include <QGraphicsView>
#include <QGridLayout>
#include <QListWidget>
#include <QXmlStreamReader>
#include <qmenubar.h>

#ifndef MODEL_VISUALIZER_API
	#define MODEL_VISUALIZER_API __declspec(dllexport)
#endif

class MODEL_VISUALIZER_API ModelVisualizer : public QWidget
{
    Q_OBJECT
	private:
		QGraphicsScene* p_Scene;
		QGraphicsView* p_View;
		QGraphicsPixmapItem* p_BackGroundPic;
		QGridLayout* p_GridLayout;
		QListWidget* p_EventList;
		QMenuBar* p_MainMenu;
		QMap<QString, QStationItem*> *p_StationList;
		QMap<QString, QSatelliteItem*> *p_SatelliteList;
	public:
		explicit ModelVisualizer(QWidget *parent = 0);
		~ModelVisualizer();
		QAction* action1;
		QAction* action2;
		QAction* action3;
		QAction* action4;
		QAction* action5;
		QAction* action6;
	public slots:
		void addMessageToEventsList(const QString& message);
		void updateFromModelFile();
		void showGraphsWindow();
	protected:
		virtual void wheelEvent(QWheelEvent* event);
	private:
		void mapZoom(qreal factor, QPointF centerPoint);
		void createMenu();
		void createView();
		void createWidgets();
		void createLayout();
		void addStations();
		std::tuple<QString, QString, QString> parseFacts(QXmlStreamReader& xml);
	signals:
		void pause();
};

#endif // MODELVISUALIZER_H
