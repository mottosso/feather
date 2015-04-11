Feather
=======

3d polygon modeller based off of Wings3d

![Feather UI](https://raw.githubusercontent.com/richardlayman/feather/master/assets/images/ui_v0_1.png)

Introduction
---------------
Feather is 3d polygon modeling application based on Wings3d with some influences from Maya. Feather has a C++ core while it's interface is written in Qt's QML language making it easy for the user to modify it or create new tools. Feather's scenegraph depends on nodes which are created by C++ plugins that can be coded by the user or other developers outside of Feather (you don't need to recompile Feather to build the plugin). Feather also has commands for doing one-time processes. These commands can be written into the C++ plugin or at the interface level using the QML scripting language. The application will have the ability to model polygon objects with the ease of Wings3D and while having the flexiblity of Maya due to having a scenegraph that connects nodes together to give the model a history which you can go back and modify, connect fields from different nodes together, create your own node fields and use them to drive other nodes. Feather is currently only targeted for Linux but others may be added later.

v0.1 Features
---------------
* C++ core
* QtQuick interface
* Open/Save feather project files
* DAG with field connections between different nodes
* Users can add custom node fields to any node and connect this field to any other field of the same type in another node
* Plugin architecture
* Import/Export obj files
* Outliner Editor
* SceneGraph Editor
* Field Editor
* 3D Viewport Editor
* Polygon Tools - Bevel, Extrude, Inset
* Selection Tools - Pick, Box, Ring, Loop
* Component Selection - Vertex, Edge, Face, Object
* Transformation Tools (all components) - Translate, Rotate, Scale

v1.0 Target Features
---------------
These are some addition features that are targeted to be included in the final 1.0 version. This is set to change at any time.
* Full clone of Wings tools for all components (vertex, edge, face and object)
* Layer Editor
* Material Editor
* LuxRender support
* PTex support
* Support for 3DConnexion SpaceNavigator

Current Status
---------------
Currently Feather is getting closer to a v0.1 release but there is still some work left to do before it's ready. Once the project gets to a point where it's usable (you can open, modify and save your changes) I'll post instructions on how to build and install the application. 

