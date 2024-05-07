#ifndef VIEWERFACTORY_H
#define VIEWERFACTORY_H

#include "fileviewer.h"
#include <map>
#include <functional>

/*!
\\class SingletonManager
\\brief The SingletonManager class is a singleton that manages instances of FileViewer singletons.

This class ensures that there is only one instance of each type of FileViewer throughout the application.
It provides methods to access and register FileViewer singletons.

\\sa FileViewer
*/

class SingletonManager {
public:
    /*!
    \\brief Retrieves the SingletonManager instance.
    \\return Reference to the SingletonManager instance.
    */
    static SingletonManager& getInstance();

    /*!
    \\brief Retrieves a viewer singleton based on the class name.
    \\param className The class name of the viewer.
    \\return Pointer to the FileViewer singleton, or nullptr if not found.
    */
    FileViewer* getViewer(const QString &className);

    /*!
    \\brief Registers a viewer singleton with the given class name.
    \\param className The class name of the viewer.
    \\param singleton Pointer to the FileViewer singleton to register.
    */
    void registerSingleton(const QString &className, FileViewer* singleton);

private:
    std::map<QString, FileViewer*> singletons; /*!< Map of class names to FileViewer singletons. */
};

/*!
\\class ViewerFactory
\\brief The ViewerFactory class is a singleton that creates FileViewer objects based on file types.

This factory class uses a map of file extensions to functions that instantiate FileViewer objects.
It ensures that only one instance of each viewer type is created by using the SingletonManager.

\\sa FileViewer, SingletonManager
*/

class ViewerFactory {
public:
    /*!
    \\brief Retrieves the ViewerFactory instance.
    \\return Reference to the ViewerFactory instance.
    */
    static ViewerFactory& getInstance();

    /*!
    \\brief Creates a FileViewer based on the file type.
    \\param fileType The file type to create a viewer for.
    \\return Pointer to the created FileViewer, or nullptr if the file type is not supported.
    */
    FileViewer* createViewer(const QString &fileType);

private:
    ViewerFactory();
    std::map<QString, std::function<FileViewer*()>> creators; /*!< Map of file types to creator functions. */

    ViewerFactory(ViewerFactory const&) = delete;
    void operator=(ViewerFactory const&) = delete;
};

#endif // VIEWERFACTORY_H
