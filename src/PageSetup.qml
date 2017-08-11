/****************************************************************************
**
**  $QT_BEGIN_LICENSE:GPL$
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>
**
**  $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import "."

Item {
    property alias portraitRadioButton: portraitRadioButton
    property alias landscapeRadioButton: landscapeRadioButton

    function updatePagesPerSideModel(pages, isDefault) {
        console.log(pages + " Received")
        pagesPerSideModel.append({pages: pages})
        if (isDefault === 0)
            pagesPerSideComboBox.currentIndex = pagesPerSideModel.count - 1
    }

    function clearPagesPerSideModel() {
        pagesPerSideModel.clear()
    }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        GridLayout {
            width: parent.width * 0.5
            Layout.preferredWidth: parent.width * 0.5
            Layout.minimumWidth: parent.width * 0.5

            height: parent.height
            Layout.preferredHeight: parent.height
            Layout.minimumHeight: parent.height

            rows: 12
            columns: 2

            Label {
                id: mainLayoutLabel
                text: qsTr("Layout")
                font.bold: true
                font.pixelSize: Style.textSize
            }

            Label {

            }

            Label {
                id: twoSidedLabel
                text: qsTr("Two Sided")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            RowLayout {
                id: twoSidedRowLayout
                Switch {
                    id: twoSidedSwitch
                    onPressed: {
                        if (twoSidedSwitch.checked) {
                            twoSidedSwitchValue.text = "OFF"
                            twoSidedConfigLabel.visible = false
                            twoSidedConfigComboBox.visible = false
                        }
                        else {
                            twoSidedSwitchValue.text = "ON"
                            twoSidedConfigLabel.visible = true
                            twoSidedConfigComboBox.visible = true
                        }
                    }
                }
                Label {
                    id: twoSidedSwitchValue
                    text: qsTr("OFF")
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                    font.pixelSize: Style.textSize
                }
            }

            Label {
                id: twoSidedConfigLabel
                visible: false
                font.pixelSize: Style.textSize
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
                font.pixelSize: Style.textSize

                delegate: ItemDelegate {
                    width: twoSidedConfigComboBox.width
                    text: qsTr(twoSidedConfig)
                    font.pixelSize: Style.textSize
                }
            }

            Label {
                id: pagesPerSideLabel
                text: qsTr("Pages per Side")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ListModel {
                id: pagesPerSideModel
            }

            ComboBox {
                id: pagesPerSideComboBox
                model: pagesPerSideModel
                font.pixelSize: Style.textSize
                delegate: ItemDelegate {
                    width: pagesPerSideComboBox.width
                    text: qsTr(pages)
                    font.pixelSize: Style.textSize
                }
            }

            Label {
                text: qsTr("Only Print")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: Style.textSize
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
                font.pixelSize: Style.textSize
                delegate: ItemDelegate {
                    width: onlyPrintComboBox.width
                    text: qsTr(pages)
                    font.pixelSize: Style.textSize
                }
            }

            Label {
                text: qsTr("Scale")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            RowLayout {
                SpinBox {
                    id: scaleSpinBox
                    from: 1
                    value: 100
                    to: 100
                    font.pixelSize: Style.textSize
                    editable: true
                }

                Label {
                    text: qsTr("%")
                    font.pixelSize: Style.textSize
                }
            }

            Label {
                id: mainPaperLabel
                text: qsTr("Paper")
                font.bold: true
                font.pixelSize: Style.textSize
            }

            Label {

            }

            Label {
                id: paperSourceLabel
                text: qsTr("Paper Source")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: Style.textSize
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
                font.pixelSize: Style.textSize

                delegate: ItemDelegate {
                    width: paperSourceComboBox.width
                    text: qsTr(paperSource)
                    font.pixelSize: Style.textSize
                }
            }

            Label {
                id: orientationLabel
                text: qsTr("Orientation")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            RowLayout {
                id: orientationRowLayout
                spacing: 5

                RadioButton {
                    id: portraitRadioButton
                    text: qsTr("Portrait")
                    checked: true
                    font.pixelSize: Style.textSize
                }

                RadioButton {
                    id: landscapeRadioButton
                    text: qsTr("Landscape")
                    font.pixelSize: Style.textSize
                }
            }
        }
    }
}
