#include "moduletracking.h"

ModuleTracking::ModuleTracking(QObject *parent) :
    Module(parent)
{
    init();
    setVideo(true);
}

void ModuleTracking::process(cv::Mat &mat)
{

}
