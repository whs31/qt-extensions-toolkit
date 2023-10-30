import QtQuick 2.15
import QtQuick.Controls 2.15
import QtExtensions.Toolkit 1.0

Item {
    property int radius: 4

    id: control
    anchors.fill: parent
    Rectangle {
        width: control.width
        height: control.height
        anchors.centerIn: parent
        color: "transparent"
        border.width: 2
        radius: control.radius
        border.color: Theme.io.color(Theme.Text)
        z: 65535
    }
}