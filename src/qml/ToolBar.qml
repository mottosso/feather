import QtQuick 2.1
import QtQuick.Window 2.1
import QtQuick.Dialogs 1.0
import QtQuick.Controls 1.0
import QtQuick.Controls.Styles 1.0
import QtQuick.Layouts 1.0

ToolBar {

    RowLayout {

        // Layout
        Label { text: "Layout" }

        /*
        ComboBox {
            id: combo_layout
            model: [ "Model","Rig","Animation" ]
        }
        */

        // 3d View settings

        ToolButton {
            width: 16; height: 16
            iconSource: "./icons/64/wire_cube.svg"
            iconName: "wire"
        } 

    }
}
