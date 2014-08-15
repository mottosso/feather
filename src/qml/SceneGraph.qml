import QtQuick 2.2
import QtQuick.Window 2.0

Window {
    id: scenegraph_window
    width: 800
    height: 600
    color: "white"
    visible: true

    SGNode { id: node_a; color: "indigo"; label: "NODE A"; x: 10; y: 10 }
    SGNode { id: node_b; color: "limegreen"; label: "NODE B"; x: 300; y: 10 }


    Canvas {
        width: 800
        height: 600
        contextType: "2d"

        // Connections
        SGConnection { id: connection; in_node: node_b; out_node: node_a }
 
        onPaint: {
           update();
            //context.stroke();
        }

        function update() {
            context.strokeSize = Qt.rgba(0.4,0.6,0.8);
            context.path = connection;
            context.stroke();
        }

        Component.onCompleted: { connection.update.connect(update) }
    }

}
