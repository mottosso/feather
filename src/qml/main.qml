import QtQuick 2.0

import FeatherViewport 1.0

Item {
    width: 800
    height: 600

    Viewport {
        id: renderer
        anchors.fill: parent
        anchors.margins: 10
    }
}
