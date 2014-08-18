import QtQuick 2.2
import QtQuick.Window 2.0

Window {
    id: scenegraph_window
    width: 800
    height: 600
    color: "black"
    visible: true


    SGNode { id: node_a; color: "indigo"; label: "NODE A"; x: 10; y: 10 }
    SGNode { id: node_b; color: "limegreen"; label: "NODE B"; x: 300; y: 10 }
    SGNode { id: node_c; color: "blue"; label: "NODE B"; x: 300; y: 60 }

    Canvas {
        id: canvas
        width: scenegraph_window.width 
        height: scenegraph_window.height
        contextType: "2d"

        // Connections
        SGConnection { id: connection1; in_node: node_b; out_node: node_a }
        SGConnection { id: connection2; in_node: node_c; out_node: node_a }

        onPaint: {
          context.clearRect(0,0,width,height)
          context.strokeStyle = Qt.rgba(0.4,0.6,0.8);
          context.path = connection1;
          context.stroke();
          context.strokeStyle = Qt.rgba(0.9,0.6,0.8);
          context.path = connection2;
          context.stroke();
        }

        Component.onCompleted: { connection1.update.connect(requestPaint); connection2.update.connect(requestPaint) }
    }

}
