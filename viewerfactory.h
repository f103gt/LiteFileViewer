#ifndef VIEWERFACTORY_H
#define VIEWERFACTORY_H

#include "txtviewer.h"
#include "pdfviewer.h"
#include "csvviewer.h"
#include "imageviewer.h"
#include <map>
#include <functional>
#include <txtviewer.h>


class SingletonManager {
public:
    static SingletonManager& getInstance() {
        static SingletonManager instance;
        return instance;
    }

    FileViewer* getViewer(const QString &className) {
        auto it = singletons.find(className);
        if (it != singletons.end()) {
            return it->second;
        } else {
            return nullptr;
        }
    }

    void registerSingleton(const QString &className, FileViewer* singleton) {
        singletons[className] = singleton;
    }

private:
    std::map<QString, FileViewer*> singletons;
};


class ViewerFactory {
public:
    static ViewerFactory& getInstance() {
        static ViewerFactory instance;
        return instance;
    }

    FileViewer* createViewer(const QString &fileType) {
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

private:
    ViewerFactory() {
        creators["txt"] = []() { return new TxtViewer; };
        creators["pdf"] =  [](){ return new PdfViewer; };
        creators["csv"] =  [](){ return &CsvViewer::getInstance(); };
        creators["jpg"] = creators["png"] = []() { return new ImageViewer; };
    }

    std::map<QString, std::function<FileViewer*()>> creators;

    // prevent these functions
    ViewerFactory(ViewerFactory const&) = delete;
    void operator=(ViewerFactory const&) = delete;
};

#endif // VIEWERFACTORY_H
