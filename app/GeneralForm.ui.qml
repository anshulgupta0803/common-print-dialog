import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    property alias twoSidedSwitch: twoSidedSwitch
    property alias twoSidedSwitchValue: twoSidedSwitchValue

    property alias colorSwitch: colorSwitch
    property alias colorSwitchValue: colorSwitchValue

    property alias customLabel: customLabel
    property alias customTextField: customTextField

    property alias pagesComboBox: pagesComboBox

    property alias moreOptionsButton: moreOptionsButton

    property alias cancelGeneralButton: cancelGeneralButton

    RowLayout {
        id: container
        anchors.fill: parent
        spacing: 10

        GridLayout {
            id: gridLayout
            width: parent.width / 2
            height: parent.height
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
                id: paperLabel
                text: qsTr("Paper")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                transformOrigin: Item.Center
                font.pixelSize: 12
            }

            ComboBox {
                id: paperComboBox
                x: 0
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

        RowLayout {
            id: preview
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            spacing: 5

            Rectangle {
                id: rectangle
                width: 320
                height: 430
                color: "#ffffff"
                border.width: 2

                BusyIndicator {
                    id: busyIndicator
                    anchors.centerIn: parent
                }
            }
        }
    }

    RowLayout {
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 150

        Button {
            id: moreOptionsButton
            text: qsTr("More Options")
            height: 32
        }

        RowLayout {
            Button {
                id: cancelGeneralButton
                text: qsTr("Cancel")
                height: 32
            }

            Button {
                id: printGeneralButton
                text: qsTr("Print")
                highlighted: true
                height: 32
            }
        }
    }
}
