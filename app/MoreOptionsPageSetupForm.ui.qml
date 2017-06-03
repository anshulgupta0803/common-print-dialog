import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ColumnLayout {
    property alias twoSidedSwitch: twoSidedSwitch
    property alias twoSidedSwitchValue: twoSidedSwitchValue
    property alias twoSidedConfigLabel: twoSidedConfigLabel
    property alias twoSidedConfigComboBox: twoSidedConfigComboBox
    spacing: 5

    GridLayout {
        rows: 6
        columns: 2
        anchors.fill: parent

        Label {
            id: mainLayoutLabel
            text: qsTr("Layout")
            font.bold: true
            font.pixelSize: 12
        }

        Label {

        }

        Label {
            id: layoutLabel
            text: qsTr("Layout")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            font.pixelSize: 12
        }

        RowLayout {
            id: layoutRowLayout
            spacing: 5

            RadioButton {
                id: portraitRadioButton
                text: qsTr("Portrait")
                checked: true
                font.pixelSize: 12
            }

            RadioButton {
                id: landscapeRadioButton
                text: qsTr("Landscape")
                font.pixelSize: 12
            }
        }

        Label {
            id: twoSidedLabel
            text: qsTr("Two Sided")
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
            id: twoSidedConfigLabel
            visible: false
            font.pixelSize: 12
        }

        ComboBox {
            id: twoSidedConfigComboBox
            model: ["Long Edge (Standard)", "Short Edge (Flip)"]
            visible: false
            font.pixelSize: 12
        }

        Label {
            text: qsTr("Pages per Sheet")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            font.pixelSize: 12
        }

        ComboBox {
            id: pagesPerSheetComboBox
            model: [1, 2, 4, 6, 9, 16]
            font.pixelSize: 12
        }

        Label {
            text: qsTr("Scale")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            font.pixelSize: 12
        }

        RowLayout {
            SpinBox {
                id: scaleSpinBox
                from: 1
                value: 100
                to: 100
                font.pixelSize: 12
            }

            Label {
                text: qsTr("%")
                font.pixelSize: 12
            }
        }
    }
}
