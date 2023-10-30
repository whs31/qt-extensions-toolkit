import QtQuick 2.15
import QtQuick.Controls 2.15
import QtExtensions.Toolkit 1.0

Text {
    required property int iconSource
    property int iconSize: 20
    id: control
    font.family: "Segoe Fluent Icons"
    font.pixelSize: iconSize
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    color: Theme.io.color(Theme.Text)
    text: (String.fromCharCode(iconSource).toString(16))
    FontLoader { source: "qrc:/qtx/fonts/FluentIcons.ttf" }
}