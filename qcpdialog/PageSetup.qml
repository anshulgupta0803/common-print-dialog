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
    signal setDuplexOption(string option)

    function enableTwoSided(option) {
        if (option === "one-sided") {
            twoSidedSwitch.enabled = false
        }
        else if (option === "two-sided-long-edge") {
            twoSidedSwitch.enabled = true
            twoSidedConfigComboBoxModel.append({twoSidedConfigDisplay: "Long Edge (Standard)",
                                                   twoSidedConfigValue: option})
            twoSidedConfigComboBox.currentIndex = 0
        }
        else if (option === "two-sided-short-edge") {
            twoSidedSwitch.enabled = true
            twoSidedConfigComboBoxModel.append({twoSidedConfigDisplay: "Short Edge (Flip)",
                                                   twoSidedConfigValue: option})
            twoSidedConfigComboBox.currentIndex = 0
        }
    }

    function clearTwoSidedSwitch() {
        twoSidedSwitch.enabled = false
        twoSidedConfigComboBoxModel.clear()
    }

    function updatePagesPerSideModel(pages, isDefault) {
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
                    enabled: false
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
            ListModel {
                id: twoSidedConfigComboBoxModel
                //                ListElement {
                //                    twoSidedConfigDisplay: "Long Edge (Standard)"
                //                    twoSidedConfigValue: "two-sided-long-edge"
                //                }
            }

            ComboBox {
                id: twoSidedConfigComboBox
                model: twoSidedConfigComboBoxModel
                visible: false
                font.pixelSize: Style.textSize
                textRole: "twoSidedConfigDisplay"

                delegate: ItemDelegate {
                    width: twoSidedConfigComboBox.width
                    text: qsTr(twoSidedConfigDisplay)
                    font.pixelSize: Style.textSize
                }

                onCurrentIndexChanged: {
                    if (twoSidedConfigComboBox.currentIndex >= 0) {
                        var option = twoSidedConfigComboBoxModel.get(twoSidedConfigComboBox.currentIndex)
                        setDuplexOption(option.twoSidedConfigValue)
                    }
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
