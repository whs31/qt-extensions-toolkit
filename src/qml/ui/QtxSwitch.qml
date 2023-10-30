import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic 2.15
import QtQuick.Layouts 1.15
import QtExtensions.Toolkit 1.0

Button {
    property string contentDescription: ""
    property color disableColor: Theme.io.color(Theme.Surface0)
    property color checkColor: Theme.io.pcolor(Theme.Primary)
    property color hoverColor: Theme.io.color(Theme.Surface2)
    property color normalColor: Theme.io.color(Theme.Base)
    property color borderNormalColor: Theme.io.color(Theme.Overlay0)
    property color borderCheckColor: Theme.io.pcolor(Theme.Primary)
    property color borderDisableColor: Theme.io.color(Theme.Surface2)
    property color dotNormalColor: Theme.io.color(Theme.Surface1)
    property color dotCheckColor: Theme.io.color(Theme.Surface2)
    property color dotDisableColor: Theme.io.color(Theme.Surface0)
    property real textSpacing: 6
    property bool textRight: true
    property alias textColor: btn_text.color
    property var clickListener: function() { checked = !checked }

    id: control
    Accessible.role: Accessible.Button
    Accessible.name: control.text
    Accessible.description: contentDescription
    Accessible.onPressAction: control.clicked()
    enabled: true
    focusPolicy: Qt.TabFocus
    onClicked: clickListener()
    padding: 0
    horizontalPadding: 0
    onCheckableChanged: if(checkable) checkable = false
    background: Item {
        implicitHeight: 20
        implicitWidth: 40
    }
    contentItem: RowLayout {
        spacing: control.textSpacing
        layoutDirection: control.textRight ? Qt.LeftToRight : Qt.RightToLeft
        Rectangle {
            id: control_backgound
            width: background.width
            height: background.height
            radius: height / 2
            FUIFocusRectangle {
                visible: control.activeFocus
                radius: parent.radius
            }
            color: {
                if(!enabled) return disableColor
                if(checked) return checkColor
                if(hovered) return hoverColor
                return normalColor
            }
            border.width: 1
            border.color: {
                if(!enabled) return borderDisableColor
                if(checked) return borderCheckColor
                return borderNormalColor
            }
            // FluIcon {
            //     width: parent.height
            //     x: checked ? control_backgound.width-width : 0
            //     scale: {
            //         if(pressed)
            //             return 5/10
            //         return hovered && enabled ? 7/10 : 6/10
            //     }
            //     iconSource: FluentIcons.FullCircleMask
            //     iconSize: 20
            //     color: {
            //         if(!enabled)
            //             return dotDisableColor
            //         if(checked)
            //             return dotCheckColor
            //         return dotNormalColor
            //     }
            //     Behavior on scale { NumberAnimation { duration: 167; easing.type: Easing.OutCubic } }
            //     Behavior on x { NumberAnimation { duration: 167; easing.type: Easing.OutCubic } }
            // }
        }

        FUIText {
            id: btn_text
            text: control.text
            Layout.alignment: Qt.AlignVCenter
            visible: text !== ""
        }
    }
}