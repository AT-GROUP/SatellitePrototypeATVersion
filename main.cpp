#include "src/ATDynamicPrototype/ATDynamicIESApp.h"
#include "src/ModelVisualizer/ModelVisualizer.h"

int main(int argc, char *argv[])
{
	ATDynamicIESApp a(argc, argv);
	a.getVisualazer()->show();
	return a.exec();
}
