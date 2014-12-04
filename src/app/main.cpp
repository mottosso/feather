// =====================================================================================
// 
//       Filename:  main.cpp
// 
//    Description:  
// 
//        Version:  1.0
//        Created:  06/11/2014 05:01:19 AM
//       Revision:  none
//       Compiler:  g++
// 
//         Author:  Richard Layman (), rlayman2000@yahoo.com
//        Company:  
// 
// =====================================================================================
#include "deps.hpp"
#include "viewportthread.hpp"
#include "qml.hpp"
#include "commands.hpp"
#include <QApplication>
#include <QQmlApplicationEngine>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    qmlRegisterType<ViewportThread>("FeatherViewport", 1, 0, "Viewport");
    qmlRegisterType<feather::qml::SceneGraph>("feather.scenegraph", 1, 0, "SceneGraph");
    qmlRegisterType<feather::qml::Node>("feather.nodes", 1, 0, "Node");
    qmlRegisterType<feather::qml::Field>("feather.feilds", 1, 0, "Field");

    // Add the Root ndoe to the scenegraph and setup the scene
    feather::qml::command::init();

    int execReturn = 0;

    {
        QQmlApplicationEngine view("main.qml");
        execReturn = app.exec();
    }

    foreach (QThread *t, ViewportThread::threads) {
        t->wait();
        delete t;
    }

    return execReturn;
};

