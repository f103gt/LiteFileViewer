#include "../headers/viewerfactory.h"
#include "../headers/txtviewer.h"
#include "../headers/pdfviewer.h"
#include "../headers/csvviewer.h"
#include "../headers/imageviewer.h"
#include <QRegularExpression>

ViewerFactory::ViewerFactory() {
    creators["txt"] =creators["sql"] = creators["xml"] = creators["html"] = creators["json"]
        =[]() { return new TxtViewer; };
    creators["pdf"] =  [](){ return new PdfViewer; };
    creators["csv"] =  [](){ return &CsvViewer::getInstance(); };
    creators["jpg"] = creators["png"] = []() { return new ImageViewer; };
}

FileViewer* ViewerFactory::createViewer(const QString &fileType) {
    auto it = creators.find(fileType);
    if (it != creators.end()) {
        FileViewer* viewer = SingletonManager::getInstance().getViewer(it->first);
        if (!viewer) {
            viewer = it->second();
            SingletonManager::getInstance().registerSingleton(it->first, viewer);
        }
        return viewer;
    } else {
        return nullptr;
    }
}

FileViewer* SingletonManager::getViewer(const QString &className) {
    auto it = singletons.find(className);
    if (it != singletons.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

void SingletonManager::registerSingleton(const QString &className, FileViewer* singleton) {
    singletons[className] = singleton;
}

SingletonManager& SingletonManager::getInstance() {
    static SingletonManager instance;
    return instance;
}

ViewerFactory& ViewerFactory::getInstance() {
    static ViewerFactory instance;
    return instance;
}
