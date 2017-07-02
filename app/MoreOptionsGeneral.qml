import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import "."

RowLayout {
    spacing: 0
    property alias destinationModel: destinationModel
    property alias destinationComboBox: destinationComboBox

    Rectangle {
        id: gridLayout
        width: parent.width * 0.5
        Layout.preferredWidth: parent.width * 0.5
        Layout.minimumWidth: parent.width * 0.5

        height: parent.height
        Layout.preferredHeight: parent.height
        Layout.minimumHeight: parent.height

        color: "#00000000"

        GridLayout {
            rows: 6
            columns: 2

            Label {
                id: destinationLabel
                text: qsTr("Destination")
                font.pixelSize: Style.textSize
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                transformOrigin: Item.Center
            }

            ListModel {
                id: destinationModel
            }

            ComboBox {
                id: destinationComboBox
                model: destinationModel

                font.pixelSize: Style.textSize

                delegate: ItemDelegate {
                    width: destinationComboBox.width
                    font.pixelSize: Style.textSize
                    text: destination
                }
            }

            Label {
                id: pagesLabel
                text: qsTr("Pages")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                id: pagesComboBox
                model: ListModel {
                    ListElement {
                        pages: "All"
                    }
                    ListElement {
                        pages: "Custom"
                    }
                }

                delegate: ItemDelegate {
                    width: pagesComboBox.width
                    text: qsTr(pages)
                    font.pixelSize: Style.textSize
                }

                font.pixelSize: Style.textSize
                onActivated: {
                    if (pagesComboBox.currentText == "Custom") {
                        customLabel.visible = true
                        customTextField.visible = true
                    }
                    else {
                        customLabel.visible = false
                        customTextField.visible = false
                    }
                }
            }

            Label {
                id: customLabel
                text: qsTr("Custom")
                font.italic: true
                color: "#ababab"
                visible: false
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            TextField {
                id: customTextField
                font.pixelSize: Style.textSize
                visible: false
                placeholderText: "Eg. 2-4, 6, 8, 10-12"
                validator: RegExpValidator { regExp: /((\s*[0-9]+|[0-9]+\s*-\s*[0-9]+)\s*,\s*)*/ }
            }

            Label {
                id: copiesLabel
                text: qsTr("Copies")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            SpinBox {
                id: copiesSpinBox
                to: 999
                from: 1
                value: 1
                font.pixelSize: Style.textSize
                editable: true
                validator: IntValidator{}
            }
        }
    }

    Rectangle {
        width: parent.width * 0.5
        Layout.preferredWidth: parent.width * 0.5
        Layout.minimumWidth: parent.width * 0.5

        height: parent.height
        Layout.preferredHeight: parent.height
        Layout.minimumHeight: parent.height
        color: "black"

        Preview {
            id: moreOptionsGeneralPreview
            anchors.fill: parent
            anchors.centerIn: parent
        }
    }
}
