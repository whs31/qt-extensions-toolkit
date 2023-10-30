import QtQuick 2.15
import QtQuick.Controls.impl 2.15
import QtQuick.Templates 2.15 as T
import QtExtensions.Toolkit 1.0

T.ToolTip {
    id: control
    x: parent ? (parent.width - implicitWidth) / 2 : 0
    y: -implicitHeight - 3
    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset, contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset, contentHeight + topPadding + bottomPadding)
    margins: 6
    padding: 6
    font: mainfont
    closePolicy: T.Popup.CloseOnEscape | T.Popup.CloseOnPressOutsideParent | T.Popup.CloseOnReleaseOutsideParent
    contentItem: FluentText {
        text: control.text
        font: control.font
        wrapMode: Text.Wrap
    }
    background: Rectangle {
        color: Theme.io.color(Theme.Mantle)
        radius: 3
        FluentShadow { radius: 3 }
    }
}