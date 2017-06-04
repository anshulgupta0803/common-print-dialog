import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

RowLayout {
    spacing: 5

    property alias pagesComboBox: pagesComboBox
    property alias customLabel: customLabel
    property alias customTextField: customTextField

    GridLayout {
        id: gridLayout
        columnSpacing: 15
        Layout.fillHeight: true
        Layout.fillWidth: true
        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
        rows: 11
        columns: 2

        Label {
            id: destinationLabel
            x: 0
            y: 0
            text: qsTr("Destination")
            font.pixelSize: 12
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            transformOrigin: Item.Center
        }

        ComboBox {
            id: destinationComboBox
            model: ListModel {

            }

            font.pixelSize: 12

            delegate: ItemDelegate {
                width: destinationComboBox.width
                font.pixelSize: 12
                text: qsTr(destination)
            }
        }

        Label {
            id: pagesLabel
            text: qsTr("Pages")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            font.pixelSize: 12
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
                font.pixelSize: 12
            }

            font.pixelSize: 12
        }

        Label {
            id: customLabel
            text: qsTr("Custom")
            font.italic: true
            color: "#ababab"
            visible: false
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            font.pixelSize: 12
        }

        TextField {
            id: customTextField
            font.pixelSize: 12
            visible: false
            placeholderText: "Eg. 2-4, 6, 8, 10-12"
            validator: RegExpValidator { regExp: /((\s*[0-9]+|[0-9]+\s*-\s*[0-9]+)\s*,\s*)*/ }
        }

        Label {
            id: copiesLabel
            text: qsTr("Copies")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            font.pixelSize: 12
        }

        SpinBox {
            id: copiesSpinBox
            to: 999
            from: 1
            value: 1
            font.pixelSize: 12
            editable: true
            validator: IntValidator{}
        }
    }
    Preview {
        height: 400
        Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
    }
}
