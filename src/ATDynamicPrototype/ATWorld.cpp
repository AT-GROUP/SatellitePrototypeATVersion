
#include "ATWorld.h"
#include <QtWidgets/QGraphicsRectItem>

ATWorld::ATWorld()
{
	auto rect = new QGraphicsRectItem(0, 0, 300, 400);
	addItem(rect);

	m_pBall = new QGraphicsEllipseItem(-10, -10, 20, 20);
	m_pBall->setBrush(QBrush(QColor(0, 255, 0)));
	addItem(m_pBall);
	m_pBall->setPos(100, 60);
}

void ATWorld::testUpdate()
{
	auto old_pos = m_pBall->pos();
	m_pBall->setPos(old_pos.x() + 0.3, old_pos.y() + 0.9);
}
