import QtQuick 2.0
import QtQuick.Window 2.1
import QtQuick.Dialogs 1.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Layouts 1.0

Item {
    id: main
    width: 800
    height: 600

    ApplicationWindow {
        id: main_window
        visibility: Window.Maximized
        visible: true
        title: "Majestic" 

        menuBar: MainMenu{}

        toolBar: MainToolBar{}

        Viewport3D{}

    }
}
