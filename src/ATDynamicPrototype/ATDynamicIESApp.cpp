#include "ATDynamicIESApp.h"
#include <QtCore/QTimer>
#include "src/TempSolverWrapper/SolverWrapper.h"
#include "src/ModelVisualizer/ModelVisualizer.h"
#include <qdebug.h>

ATDynamicIESApp::ATDynamicIESApp(int argc, char *argv[])
	:QApplication(argc, argv)
{	
	pWorld = new ModelVisualizer();
	pDLLWrapper = new SolverWrapper();
	pTickTimer = new QTimer(this);
	connect(pTickTimer, SIGNAL(timeout()), this, SLOT(reachNextState()));
	pDLLWrapper->configurate();
	pTickTimer->start(500);
	state = 0;
	connect(pWorld->action1, SIGNAL(triggered()), pTickTimer, SLOT(start()));
	connect(pWorld->action2, SIGNAL(triggered()), pTickTimer, SLOT(stop()));
}

ATDynamicIESApp::~ATDynamicIESApp()
{
	pTickTimer->stop();
	delete pTickTimer;
	//delete pDLLWrapper;
	delete pWorld;
}

ModelVisualizer* ATDynamicIESApp::getVisualazer()
{
	return pWorld;
}

void ATDynamicIESApp::reachNextState()
{
	switch (state)
	{
		case 0:
			pDLLWrapper->processModelTact();
			++state;
			break;
		case 1:
			pDLLWrapper->processSolversTact();
			++state;
			break;
		case 2:
			pWorld->updateFromModelFile();
			state = 0;
			break;
	}
}