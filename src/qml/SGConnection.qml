import QtQuick 2.2


Path {
    id: in_conn 
    startX: out_node.x
    startY: out_node.y
    
    property SGNode in_node: null
    property SGNode out_node: null

    signal update()

    PathLine {
        id: out_conn
        x: in_node.x; y: in_node.y
    }

    Component.onCompleted: { in_node.moved.connect(in_update); out_node.moved.connect(out_update) } 
   
    function in_update(x,y) {
        console.log( in_conn.startX + " " + x )
        in_conn.startX = x
        in_conn.startY = y
        in_conn.update()
    }

    function out_update(x,y) {
        out_conn.x = x
        out_conn.y = y
        in_conn.update()
    }

}
