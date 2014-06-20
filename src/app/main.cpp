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

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

    // ?? This always comes back with an error though my platform supports threading ??
    /*
if (!QGuiApplicationPrivate::platform_integration->hasCapability(QPlatformIntegration::ThreadedOpenGL)) {
QQuickView view;
view.setSource(QUrl("error.qml"));
view.show();
return app.exec();
}
*/

    qmlRegisterType<ViewportThread>("FeatherViewport", 1, 0, "Viewport");
    int execReturn = 0;

    {
        QQuickView view;
        view.setPersistentOpenGLContext(true);
        view.setPersistentSceneGraph(true);
        view.setResizeMode(QQuickView::SizeRootObjectToView);
        view.setSource(QUrl("main.qml"));
        view.show();
        execReturn = app.exec();
    }

    foreach (QThread *t, ViewportThread::threads) {
        t->wait();
        delete t;
    }

    return execReturn;

};

