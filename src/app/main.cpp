/***********************************************************************
 *
 * Filename: main.cpp
 *
 * Description: Entry point of the program.
 *
 * Copyright (C) 2015 Richard Layman, rlayman2000@yahoo.com 
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ***********************************************************************/

#include "deps.hpp"
#include "viewportthread.hpp"
#include "sg_editor.hpp"
#include "field_model.hpp"
#include "layer_model.hpp"
#include "tree_model.hpp" // is this being used ????
#include "qml.hpp"
#include "commands.hpp"
#include <QApplication>
#include <QQmlApplicationEngine>

// callback function for scenegraph singleton
static QObject *get_scenegraph(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    SceneGraph *sg = new SceneGraph();
    return sg;
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    qmlRegisterType<ViewportThread>("feather.viewport", 1, 0, "Viewport");
    qmlRegisterType<SceneGraphEditor>("feather.editors", 1, 0, "SceneGraphEditor");
    qmlRegisterSingletonType<SceneGraph>("feather.scenegraph", 1, 0, "SceneGraph", get_scenegraph);
    qmlRegisterType<TreeModel>("feather.outliner", 1, 0, "OutlinerModel");
    qmlRegisterType<Node>("feather.node", 1, 0, "Node");
    qmlRegisterType<Field>("feather.field", 1, 0, "Field");
    qmlRegisterType<FieldModel>("feather.field", 1, 0, "FieldModel");
    qmlRegisterType<LayerModel>("feather.layer", 1, 0, "LayerModel");
    qmlRegisterType<Parameter>("feather.command", 1, 0, "Parameter");
    qmlRegisterType<Command>("feather.command", 1, 0, "Command");
    qmlRegisterType<Plugins>("feather.plugin", 1, 0, "Plugins");
    qmlRegisterType<Tools>("feather.tools", 1, 0, "Tools");


    // Add the Root node to the scenegraph and setup the scene
    feather::qml::command::init();

    int execReturn = 0;

    {
        QQmlApplicationEngine view("ui/main.qml");
        execReturn = app.exec();
    }

    foreach (QThread *t, ViewportThread::threads) {
        t->wait();
        delete t;
    }

    return execReturn;
};
