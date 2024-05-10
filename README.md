# Lab 1
Unit tests are located in ./tests. To find the uml diagrams, follow to ./diagrams. There implemented 4 of them -
Use Case, Class, Activity.

Also I made a great use of one of my previous pojects located in this repository https://github.com/f103gt/bookstore.git.
This project implements books microservice using instead of rest controllers, gRpc services to establish inter process
communication IPC with other micorservices.

The implemented UML diagrams are the Deployment and Communication diagrams.

Diagrams are located here https://drive.google.com/drive/folders/1KudP0vzsYcxcYmotsXiF9jE9RAXunRnB?usp=sharing

# Lab 2 (7 Patterns)

## Lite File Viewer

### Tempalate(FileViewer) - used to define the skeleton of the zoom operation. 
This pattern allows to define the invariant parts of the algorithm once and let subclasses provide 
the implementation for the parts that can vary. This approach helps achieve code reuse and flexibility.
In the application, the zoom method is the template method and the zoomIn and zoomOut methods are the primitive
operations that are overridden by subclasses to provide specific zoom functionality.
This design allows to easily extend our application with new types of file viewers with different zoom behaviors.

### Factory (ViewerFactory) - used to create FileViewer objects,
provides a way to encapsulate a group of individual factories that have a common theme,
create viewers for different file types without exposing the creation logic to the client code.
This makes the code more flexible, easier to extend (when new viewer types need to be added), and easier to maintain.

### Singleton - used to make sure that every instace of class that implemets FileViewer is created only once and used 
throughout the whole application.

### Strategy (HightligthStrategy) - allows to switch the syntax highlighting behavior at runtime depending
on the type of content the program is dealing with.

### Composite (
                                          FileViwer 
                                              |
                                              |
                                        ImageBaseVeiwer
                                          |          |
                                          |          |
                                      ImageVeiwer PdfViewer

) - used to create a tree like structured to minimize code duplication for common metods in ImageViewer and PdfViewer,
because both of them rely on displaying data as images

### Command (ZoomCommand - ZoomOutCommand, ZoomInCommand) - allows to encapsulate a request as an object, 
providing an optimized and unified way to impelemt zooming in and out for all the viewers.

## Books Management microservice

### Modle View Control (MVC) - general structure of how the application works.
Model - BookEntity, View - gRpc service, Cotroller - gRpc Service implementation.

### Data Transfer Object (DTO) - used to trasfer data between Request Entity (gRpc message)
and Database Entity. (BookEntity, Book)


# Lab3 (Multithreading)

Used in **manwindow.cpp** to oben the files. Considering that some files can take a lot for time
to be actually opened, mulithreading was introduced to make sure that several files can be 
opened simultaneously and the application remains responsive during the process of file leading.


# Project

## Lite File Viewer

File Reader application that supports proper reading that display of PDF, JSON, SQL, CSV, TXT, XML, HTML, PGN, JPEG, file formats.
Deos not supports modification of files, can only display them. 
For different formats, supports Substring search (JSON, SQL, TXT, XML, HTML) and Pagination (PDF).
All support zoom in\ zoom out functions.
Unit tests located in **test** folder, documentation is provided in **headers**, along with header files,
sources(cpp files) are located in **sources** folder.
