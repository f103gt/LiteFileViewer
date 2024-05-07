#ifndef ZOOMCOMMAND_H
#define ZOOMCOMMAND_H

/*!
\\module ZoomCommand
\\class ZoomCommand
\\brief The ZoomCommand class is an abstract class that defines the interface for zoom commands.

This class provides a virtual destructor and a pure virtual method to calculate the zoom level.
Subclasses must implement the calculateZoomLevel method to provide specific zooming behavior.

\\sa ZoomInCommand, ZoomOutCommand
*/

class ZoomCommand {
public:
    /*!
    \\brief Virtual destructor.
    */
    virtual ~ZoomCommand() {}

    /*!
    \\brief Calculates the new zoom level based on the current zoom level and a factor.
    \\param currentZoomLevel The current zoom level.
    \\param factor The factor by which to zoom.
    \\return The new zoom level.
    */
    virtual double calculateZoomLevel(double currentZoomLevel, double factor) = 0;
};

/*!
\\class ZoomInCommand
\\brief The ZoomInCommand class provides the functionality to increase the zoom level.

This class inherits from ZoomCommand and implements the calculateZoomLevel method to increase the zoom level by a given factor.

\\sa ZoomCommand
*/

class ZoomInCommand : public ZoomCommand {
public:
    /*!
    \\brief Calculates the increased zoom level.
    \\param currentZoomLevel The current zoom level.
    \\param factor The factor by which to increase the zoom.
    \\return The increased zoom level.
    */
    double calculateZoomLevel(double currentZoomLevel, double factor) override;
};

/*!
\\class ZoomOutCommand
\\brief The ZoomOutCommand class provides the functionality to decrease the zoom level.

This class inherits from ZoomCommand and implements the calculateZoomLevel method to decrease the zoom level by a given factor.

\\sa ZoomCommand
*/

class ZoomOutCommand : public ZoomCommand {
public:
    /*!
    \\brief Calculates the decreased zoom level.
    \\param currentZoomLevel The current zoom level.
    \\param factor The factor by which to decrease the zoom.
    \\return The decreased zoom level.
    */
    double calculateZoomLevel(double currentZoomLevel, double factor) override ;
};

#endif // ZOOMCOMMAND_H
