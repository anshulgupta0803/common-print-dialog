import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    GridLayout {
        id: gridLayout
        //width: parent.width
        //height: parent.height
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
        }

        Label {
            id: pagesLabel
            text: qsTr("Pages")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            font.pixelSize: 12
        }

        ComboBox {
            id: pagesComboBox
            model: ["All", "Custom"]
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
            visible: false
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
        }

        Label {
            id: twoSidedLabel
            text: qsTr("Two-Sided")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            font.pixelSize: 12
        }

        RowLayout {
            id: twoSidedRowLayout
            Switch {
                id: twoSidedSwitch
            }
            Label {
                id: twoSidedSwitchValue
                text: qsTr("OFF")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: 12
            }
        }

        Label {
            id: colorLabel
            text: qsTr("Color")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            font.pixelSize: 12
        }

        RowLayout {
            id: colorRowLayout
            Switch {
                id: colorSwitch
            }
            Label {
                id: colorSwitchValue
                text: qsTr("OFF")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: 12
            }
        }
    }
}
