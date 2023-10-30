import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic 2.15
import QtExtensions.Toolkit 1.0

Button {
    property bool disabled: false
    property string contentDescription: ""
    property color normalColor: Theme.io.color(Theme.Surface1)
    property color hoverColor: Theme.io.color(Theme.Overlay1)
    property color disableColor: Theme.io.color(Theme.Base)
    property color textColor: {
        if(!enabled) return Theme.io.color(Theme.Subtext0)
        if(pressed) return Theme.io.color(Theme.Subtext1)
        return Theme.io.color(Theme.Text)
    }
    Accessible.role: Accessible.Button
    Accessible.name: control.text
    Accessible.description: contentDescription
    Accessible.onPressAction: control.clicked()
    id: control
    enabled: !disabled
    horizontalPadding: 12
    font: mainfont
    focusPolicy: Qt.TabFocus
    background: Rectangle {
        implicitWidth: 28
        implicitHeight: 28
        border.color: Theme.io.color(Theme.Surface0)
        border.width: 1
        radius: 4
        color: {
            if(!enabled) return disableColor
            return hovered ? hoverColor : normalColor
        }
        FUIFocusRectangle {
            visible: control.activeFocus
            radius:4
        }
    }
    contentItem: FUIText {
        text: control.text
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font: control.font
        color: control.textColor
    }
}