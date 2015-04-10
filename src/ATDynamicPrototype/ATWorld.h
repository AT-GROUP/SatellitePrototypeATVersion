
#ifndef ATDYNAMICPROTOTYPE_ATWorld_H
#define ATDYNAMICPROTOTYPE_ATWorld_H

#include <QtWidgets/QGraphicsScene>

class ATWorld : public QGraphicsScene
{
	Q_OBJECT

public:
	ATWorld();
public slots:
	void testUpdate();
private:
	QGraphicsEllipseItem * m_pBall;
};

#endif
