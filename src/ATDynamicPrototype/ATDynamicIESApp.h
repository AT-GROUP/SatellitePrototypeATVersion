
#ifndef ATDYNAMICPROTOTYPE_ATDynamicIESApp_H
#define ATDYNAMICPROTOTYPE_ATDynamicIESApp_H

#include <QtWidgets/QApplication>

#define MODEL_VISUALIZER_API __declspec(dllimport)
#define TEMP_SOLVER_API __declspec(dllimport)

class SolverWrapper;
class QTimer;
class ModelVisualizer;

class ATDynamicIESApp: public QApplication
{
	Q_OBJECT
	public:
		ATDynamicIESApp(int argc, char *argv[]);
		~ATDynamicIESApp();
		ModelVisualizer* getVisualazer();
	private:
		QTimer *pTickTimer;
		SolverWrapper *pDLLWrapper;
		ModelVisualizer *pWorld;
		int state;

	public slots:
		virtual void reachNextState();
};
	
#endif
