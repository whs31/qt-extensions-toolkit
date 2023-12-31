import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Universal 2.15

import QtExtensions.Toolkit 1.0

import "qrc:/qtx/FileExtensions.js" as FileExtensions

Popup {
    parent: Overlay.overlay
    width: parent.width / 1.5
    height: parent.height / 1.5
    modal: true
    closePolicy: Popup.CloseOnPressOutside | Popup.CloseOnEscape
    visible: true
    clip: true
    padding: 0

    Overlay.modal: Rectangle { color: "#66000000" }
    enter: Transition { NumberAnimation { property: "opacity"; from: 0.0; to: 1.0; duration: 100 } }
    exit: Transition { NumberAnimation { property: "opacity"; from: 1.0; to: 0.0; duration: 100 } }

    Page {
        anchors.fill: parent
        padding: 0
        leftInset: 0
        rightInset: 0
        topInset: 0
        bottomInset: 0
        header: ToolBar {
            height: 24
            contentHeight: 24
            RowLayout {
                spacing: 0
                anchors.fill: parent
                ToolButton {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 24
                    text: "Имя"
                }
                ToolButton {
                    Layout.preferredHeight: 24
                    Layout.preferredWidth: 200
                    text: "Дата изменения"
                }
                ToolButton {
                    Layout.preferredHeight: 24
                    Layout.preferredWidth: 200
                    text: "Тип"
                }
                ToolButton {
                    Layout.preferredHeight: 24
                    Layout.preferredWidth: 200
                    text: "Размер"
                }
            }
        }

        ListView {
            id: __view
            anchors.fill: parent
            model: XFileDialogModel { id: __model }
            ScrollBar.vertical: ScrollBar { active: true; policy: ScrollBar.AlwaysOn }
            boundsBehavior: Flickable.StopAtBounds
            delegate: ItemDelegate {
                required property int index
                required property bool isDirectory
                required property string name
                required property string size
                required property date lastChanged
                required property string extension

                width: __view.width
                height: 24

                function getIcon(ext, is_dir)
                {
                    if(is_dir)
                        return "qrc:/qtx/icons/file-types/folder.svg"
                    if(FileExtensions.iconPaths[ext])
                        return FileExtensions.iconPaths[ext]
                    return "qrc:/qtx/icons/file-types/file.svg"
                }

                RowLayout {
                    anchors.fill: parent
                    spacing: 0

                    Button {
                        Layout.preferredHeight: 24
                        Layout.preferredWidth: 30
                        display: Button.IconOnly
                        flat: true
                        //enabled: false
                        icon {
                            source: getIcon(extension, isDirectory)
                        }
                    }

                    Label {
                        Layout.leftMargin: 30
                        Layout.fillWidth: true
                        Layout.preferredHeight: 24
                        text: name
                        font {
                            weight: Font.DemiBold
                        }
                        elide: Text.ElideRight
                    }

                    Label {
                        function convertDate(date)
                        {
                            let d = date.toLocaleDateString(Qt.locale("ru_RU"), "dd.MM.yyyy")
                            let t = date.toLocaleTimeString(Qt.locale("ru_RU"), "hh:mm")
                            return `${d} ${t}`
                        }

                        Layout.preferredHeight: 24
                        Layout.preferredWidth: 200
                        text: convertDate(lastChanged)
                        elide: Text.ElideRight
                    }

                    Label {
                        function getExtensionName(extension)
                        {
                            if(extension.length === 0)
                                return "Файл"
                            if(FileExtensions.extensions[extension])
                                return FileExtensions.extensions[extension]
                            return "Файл " + extension.toUpperCase()
                        }

                        Layout.preferredHeight: 24
                        Layout.preferredWidth: 200
                        text: isDirectory ? "Папка с файлами" : getExtensionName(extension)
                        elide: Text.ElideRight
                    }

                    Label {
                        Layout.preferredHeight: 24
                        Layout.preferredWidth: 180
                        Layout.rightMargin: 20
                        text: size
                        horizontalAlignment: Text.AlignRight
                        elide: Text.ElideRight
                    }
                }
            }
        }
    }
}
