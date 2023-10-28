import QtQuick
import QtQuick.Controls

import QtExtensions.Toolkit

Loader {
    required property Item rootItem

    id: loader_reveal
    anchors.fill: parent

    function distance(x1, y1, x2, y2){ return Math.sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) }

    function toggleTheme(button)
    {
        loader_reveal.sourceComponent = __reveal
        var target = rootItem
        var pos = button.mapToItem(target, 0, 0)
        var mouseX = pos.x
        var mouseY = pos.y
        var radius = Math.max(distance(mouseX, mouseY, 0, 0), distance(mouseX, mouseY, target.width, 0),
            distance(mouseX, mouseY, 0, target.height), distance(mouseX, mouseY, target.width, target.height))
        var reveal = loader_reveal.item
        reveal.start(reveal.width * Screen.devicePixelRatio, reveal.height * Screen.devicePixelRatio, Qt.point(mouseX, mouseY), radius)
    }

    Component {
        id: __reveal

        QtxCircularReveal {
            id: reveal
            target: rootItem
            anchors.fill: parent
            onAnimationFinished: {
                loader_reveal.sourceComponent = undefined
            }
            onImageChanged: {
                if(Theme.darkMode === Theme.Dark) Theme.darkMode = Theme.Light
                else Theme.darkMode = Theme.Dark
            }
        }
    }
}