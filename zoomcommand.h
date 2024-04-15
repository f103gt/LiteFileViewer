#ifndef ZOOMCOMMAND_H
#define ZOOMCOMMAND_H

class ZoomCommand {
public:
    virtual ~ZoomCommand() {}
    virtual double calculateZoomLevel(double currentZoomLevel, double factor) = 0;
};


class ZoomInCommand : public ZoomCommand {
public:
    double calculateZoomLevel(double currentZoomLevel, double factor) override {
        return currentZoomLevel * factor;
    }
};

class ZoomOutCommand : public ZoomCommand {
public:
    double calculateZoomLevel(double currentZoomLevel, double factor) override {
        return currentZoomLevel / factor;
    }
};


#endif // ZOOMCOMMAND_H
