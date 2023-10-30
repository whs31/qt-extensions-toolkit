import QtQuick 2.15
import QtQuick.Controls 2.15
import QtExtensions.Toolkit 1.0

Item {
    property color color: Theme.io.color(Theme.Subtext1)
    property int elevation: 6
    property int radius: 4
    id: control
    anchors.fill: parent
    Repeater {
        model: elevation
        Rectangle {
            anchors.fill: parent
            color: "#00000000"
            opacity: 0.01 * (elevation - index + 1)
            anchors.margins: -index
            radius: control.radius + index
            border.width: index
            border.color: control.color
        }
    }
}