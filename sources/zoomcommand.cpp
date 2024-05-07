#include "../headers/zoomcommand.h"
double ZoomOutCommand::calculateZoomLevel(double currentZoomLevel, double factor){
    return currentZoomLevel / factor;
}


double ZoomInCommand::calculateZoomLevel(double currentZoomLevel, double factor){
    return currentZoomLevel * factor;
}
