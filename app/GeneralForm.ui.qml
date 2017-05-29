import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    property alias twoSidedSwitch: twoSidedSwitch
    property alias twoSidedSwitchValue: twoSidedSwitchValue
    property alias colorSwitch: colorSwitch
    property alias colorSwitchValue: colorSwitchValue
    property alias pageNumberLabel: pageNumberLabel
    property alias pageNumberSpinBox: pageNumberSpinBox
    property alias fromLabel: fromLabel
    property alias fromSpinBox: fromSpinBox
    property alias toLabel: toLabel
    property alias toSpinBox: toSpinBox
    property alias copiesSpinBox: copiesSpinBox
    property alias pagesComboBox: pagesComboBox
    height: 530
    property alias cancelButton: cancelButton

    RowLayout {
        id: container
        width: 640
        height: 480
        clip: false
        anchors.fill: parent
        spacing: 10

        GridLayout {
            id: gridLayout
            x: 0
            width: 320
            height: 480
            columnSpacing: 15
            rowSpacing: 5
            Layout.fillHeight: false
            Layout.fillWidth: false
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            rows: 11
            columns: 2

            Label {
                id: destinationLabel
                x: 0
                y: 0
                text: qsTr("Destination")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                transformOrigin: Item.Center
                font.pixelSize: 12
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
                model: ["All", "Single", "Range"]
            }

            Label {
                id: pageNumberLabel
                text: qsTr("Page #")
                font.italic: true
                color: "#ababab"
                visible: false
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: 12
            }

            SpinBox {
                id: pageNumberSpinBox
                visible: false
                to: 999
                from: 1
                value: 1
            }

            Label {
                id: fromLabel
                text: qsTr("from")
                font.italic: true
                color: "#ababab"
                visible: false
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: 12
            }

            SpinBox {
                id: fromSpinBox
                visible: false
                to: 999
                from: 1
                value: 1
            }

            Label {
                id: toLabel
                text: qsTr("to")
                font.italic: true
                color: "#ababab"
                visible: false
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: 12
            }

            SpinBox {
                id: toSpinBox
                visible: false
                to: 999
                from: 1
                value: 1
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
                id: layoutLabel
                text: qsTr("Layout")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: 12
            }

            RowLayout {
                id: layoutRowLayout
                width: 100
                height: 100
                spacing: 5

                RadioButton {
                    id: portraitRadioButton
                    text: qsTr("Portrait")
                    checked: true
                }

                RadioButton {
                    id: landscapeRadioButton
                    text: qsTr("Landscape")
                }
            }

            Label {
                id: paperLabel
                x: 0
                y: 0
                text: qsTr("Paper")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                transformOrigin: Item.Center
                font.pixelSize: 12
            }

            ComboBox {
                id: paperComboBox
                x: 0
                y: 220
                width: 140
            }

            Label {
                id: twoSidedLabel
                text: qsTr("Two-Sided")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: 12
            }

            RowLayout {
                id: twoSidedRowLayout
                width: 100
                height: 100
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
                width: 100
                height: 100
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

        RowLayout {
            id: preview
            x: 320
            y: 0
            width: 320
            height: 480
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            spacing: 5

            Rectangle {
                id: rectangle
                width: 320
                height: 480
                color: "#ffffff"
                border.width: 2

                BusyIndicator {
                    id: busyIndicator
                    x: 115
                    y: 200
                }
            }
        }
    }

    RowLayout {
        id: buttonsLayout
        width: 508
        spacing: 190
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom

        Button {
            id: moreOptionsButton
            height: 41
            text: qsTr("More Options")
        }

        RowLayout {
            id: cancelPrintRowLayout
            width: 100
            height: 100

            Button {
                id: cancelButton
                text: "Cancel"
            }

            Button {
                id: printButton
                height: 40
                text: qsTr("Print")
                highlighted: true
            }
        }
    }
}
