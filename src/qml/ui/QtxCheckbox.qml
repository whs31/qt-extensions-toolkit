import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Basic 2.15
import QtQuick.Layouts 1.15
import QtExtensions.Toolkit 1.0

Button {
    property string contentDescription: ""
    property color borderNormalColor: Theme.io.color(Theme.Overlay1)
    property color bordercheckedColor: Theme.io.pcolor(Theme.PrimaryLight)
    property color borderHoverColor: Theme.io.color(Theme.Overlay2)
    property color borderDisableColor: Theme.io.color(Theme.Overlay0)
    property color borderPressedColor: Theme.io.color(Theme.Surface2)
    property color normalColor: Theme.io.color(Theme.Base)
    property color checkedColor: Theme.io.pcolor(Theme.Primary)
    property color hoverColor: Theme.io.color(Theme.Surface0)
    property color checkedHoverColor: Theme.darkMode === Theme.Dark ? Qt.darker(checkedColor,1.15) : Qt.lighter(checkedColor,1.15)
    property color checkedPreesedColor: Theme.darkMode === Theme.Dark ? Qt.darker(checkedColor,1.3) : Qt.lighter(checkedColor,1.3)
    property color checkedDisableColor: Theme.io.color(Theme.Overlay0)
    property color disableColor: Theme.io.color(Theme.Overlay0)
    property real size: 18
    property alias textColor: btn_text.color
    property bool textRight: true
    property real textSpacing: 6
    property var clickListener: function() { checked = !checked }
    property bool indeterminate : false
    id: control
    enabled: true
    onClicked: clickListener()
    background: Item { FluentFocusRectangle { radius: 4; visible: control.activeFocus } }
    horizontalPadding:0
    verticalPadding: 0
    padding: 0
    Accessible.role: Accessible.Button
    Accessible.name: control.text
    Accessible.description: contentDescription
    Accessible.onPressAction: control.clicked()
    focusPolicy: Qt.TabFocus
    contentItem: RowLayout {
        spacing: control.textSpacing
        layoutDirection: control.textRight ? Qt.LeftToRight : Qt.RightToLeft

        Rectangle {
            width: control.size
            height: control.size
            radius: 4
            border.color: {
                if(!enabled) return borderDisableColor
                if(checked) return bordercheckedColor
                if(pressed) return borderPressedColor
                if(hovered) return borderHoverColor
                return borderNormalColor
            }
            border.width: 1
            color: {
                if(checked){
                    if(!enabled) return checkedDisableColor
                    if(pressed) return checkedPreesedColor
                    if(hovered) return checkedHoverColor
                    return checkedColor
                }
                if(!enabled) return disableColor
                if(hovered) return hoverColor
                return normalColor
            }
            Behavior on color { ColorAnimation{ duration: 83 } }

            FluentTTFIcon {
                anchors.centerIn: parent
                iconSource: FluentIcons.CheckboxIndeterminate
                iconSize: 14
                visible: indeterminate
                color: Theme.io.color(Theme.Base)
            }

            FluentTTFIcon {
                anchors.centerIn: parent
                iconSource: FluentIcons.AcceptMedium
                iconSize: 14
                visible: checked && !indeterminate
                color: Theme.io.color(Theme.Base)
            }
        }
        FluentText {
            id: btn_text
            text: control.text
            Layout.alignment: Qt.AlignVCenter
            visible: text !== ""
        }
    }
}