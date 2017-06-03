import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ColumnLayout {
    property alias twoSidedSwitch: twoSidedSwitch
    property alias twoSidedSwitchValue: twoSidedSwitchValue
    property alias twoSidedConfigLabel: twoSidedConfigLabel
    property alias twoSidedConfigComboBox: twoSidedConfigComboBox
    spacing: 5

    RowLayout {
        id: rowLayout
        spacing: 35
        anchors.top: parent.top
        GridLayout {
            rows: 6
            columns: 2

            Label {
                id: mainLayoutLabel
                text: qsTr("Layout")
                font.bold: true
                font.pixelSize: 12
            }

            Label {

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
                model: ListModel {
                    ListElement {
                        twoSidedConfig: "Long Edge (Standard)"
                    }
                    ListElement {
                        twoSidedConfig: "Short Edge (Flip)"
                    }
                }
                visible: false
                font.pixelSize: 12

                delegate: ItemDelegate {
                    width: twoSidedConfigComboBox.width
                    text: qsTr(twoSidedConfig)
                    font.pixelSize: 12
                }
            }

            Label {
                text: qsTr("Pages per Side")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: 12
            }

            ComboBox {
                id: pagesPerSideComboBox
                model: ListModel {
                    ListElement {
                        pages: "1"
                    }
                    ListElement {
                        pages: "2"
                    }
                    ListElement {
                        pages: "4"
                    }
                    ListElement {
                        pages: "6"
                    }
                    ListElement {
                        pages: "9"
                    }
                    ListElement {
                        pages: "16"
                    }
                }
                font.pixelSize: 12
                delegate: ItemDelegate {
                    width: pagesPerSideComboBox.width
                    text: qsTr(pages)
                    font.pixelSize: 12
                }
            }

            Label {
                text: qsTr("Only Print")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: 12
            }

            ComboBox {
                id: onlyPrintComboBox
                model: ListModel {
                    ListElement {
                        pages: "All Sheets"
                    }
                    ListElement {
                        pages: "Even Sheets"
                    }
                    ListElement {
                        pages: "Odd Sheets"
                    }
                }
                font.pixelSize: 12
                delegate: ItemDelegate {
                    width: onlyPrintComboBox.width
                    text: qsTr(pages)
                    font.pixelSize: 12
                }
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
                    editable: true
                }

                Label {
                    text: qsTr("%")
                    font.pixelSize: 12
                }
            }
        }

        GridLayout {
            rows: 6
            columns: 2
            anchors.top: parent.top

            Label {
                id: mainPaperLabel
                text: qsTr("Paper")
                font.bold: true
                font.pixelSize: 12
            }

            Label {

            }

            Label {
                id: paperSourceLabel
                text: qsTr("Paper Source")
                font.pixelSize: 12
            }

            ComboBox {
                id: paperSourceComboBox
                model: ListModel {
                    ListElement {
                        paperSource: "Printer Default"
                    }
                    ListElement {
                        paperSource: "Upper Tray"
                    }
                    ListElement {
                        paperSource: "Middle Tray"
                    }
                    ListElement {
                        paperSource: "Lower Tray"
                    }
                    ListElement {
                        paperSource: "Multipurpose Tray"
                    }
                    ListElement {
                        paperSource: "Automatic"
                    }
                    ListElement {
                        paperSource: "Manual Feeder"
                    }
                }
                font.pixelSize: 12

                delegate: ItemDelegate {
                    width: paperSizeComboBox.width
                    text: qsTr(paperSource)
                    font.pixelSize: 12
                }
            }

            Label {
                id: paperSizeLabel
                text: qsTr("Paper Size")
                font.pixelSize: 12
            }

            ComboBox {
                id: paperSizeComboBox
                model: ListModel {
                    ListElement {
                        pageSize: "A4"
                    }
                    ListElement {
                        pageSize: "A3"
                    }
                    ListElement {
                        pageSize: "A5"
                    }
                    ListElement {
                        pageSize: "Legal"
                    }
                    ListElement {
                        pageSize: "Letter"
                    }
                    ListElement {
                        pageSize: "Custom"
                    }
                }
                delegate: ItemDelegate {
                    width: paperSizeComboBox.width
                    text: qsTr(pageSize)
                    font.pixelSize: 12
                }

                font.pixelSize: 12
            }

            Label {
                id: orientationLabel
                text: qsTr("Orientation")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: 12
            }

            RowLayout {
                id: orientationRowLayout
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
        }
    }
}
