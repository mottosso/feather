import QtQuick 2.2
import QtQuick.Window 2.0

Window {
    id: scenegraph_window
    width: 800
    height: 600
    color: "black"
    visible: true

    SGNode { id: node_a; color: "indigo"; label: "NODE A"; x: 10; y: 10 }
    SGNode { id: node_b; color: "limegreen"; label: "NODE B"; x: 300; y: 10  }

}
