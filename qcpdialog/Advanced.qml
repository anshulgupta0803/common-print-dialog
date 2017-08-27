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
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import "."

Item {
    signal newResolutionSelected(string resolution)

    function addResolution(resolution, isDefault) {
        resolutionModel.append({resolution: resolution})
        if (isDefault === 0)
            resolutionComboBox.currentIndex = resolutionModel.count - 1
    }

    function clearResolutionModel() {
        resolutionModel.clear()
    }

    ScrollView {
        anchors.fill: parent
        verticalScrollBarPolicy: Qt.ScrollBarAlwaysOn


        GridLayout {
            id: grid_layout
            Layout.fillHeight: true

            width: parent.width
            Layout.preferredWidth: parent.width
            Layout.minimumWidth: parent.width

            rowSpacing: 0
            columns: 2

            Label {
                text: qsTr("Quality")
                Layout.columnSpan: 2
                font.bold: true
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Resolution (dpi)")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ListModel {
                id: resolutionModel
            }

            ComboBox {
                id: resolutionComboBox
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: resolutionModel
                font.pixelSize: Style.textSize
                delegate: ItemDelegate {
                    width: resolutionComboBox.width
                    text: resolution
                    font.pixelSize: Style.textSize
                }
                onCurrentIndexChanged: {
                    if (resolutionComboBox.currentIndex >= 0)
                        newResolutionSelected(resolutionModel.get(resolutionComboBox.currentIndex).resolution)
                }
            }

            Label {
                text: qsTr("Toner Darkness")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "1", "2", "3"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Brightness")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "-3", "-2", "-1", "0", "1", "2", "3"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Contrast")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "0", "1", "2", "3"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Saturation")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "-3", "-2", "-1", "0", "1", "2", "3"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Enhance Fine Lines")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "On"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Color")
                Layout.columnSpan: 2
                font.bold: true
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Color Correction")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "Auto", "Manual"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Color Saver")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "On"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Monochrome")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "On"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Color Balance")
                Layout.columnSpan: 2
                font.bold: true
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Cyan Balance")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "-3", "-2", "-1", "0", "1", "2", "3"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Magenta Balance")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "-3", "-2", "-1", "0", "1", "2", "3"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Yellow Balance")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "-3", "-2", "-1", "0", "1", "2", "3"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Black Balance")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "-3", "-2", "-1", "0", "1", "2", "3"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Manual Color")
                Layout.columnSpan: 2
                font.bold: true
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("RGB Image")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "Vivid", "sRGB Display", "sRGB Vivid", "Display-true Black"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("RGB Text")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "Vivid", "sRGB Display", "sRGB Vivid", "Display-true Black"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("RGB Graphics")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "Vivid", "sRGB Display", "sRGB Vivid", "Display-true Black"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("CMYK")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "US CMYK", "Euro CMYK"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Finishing")
                Layout.columnSpan: 2
                font.bold: true
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Print Blank Pages")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "On"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Separator Pages")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "None", "Between Jobs", "Between Copies", "Between Pages"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Offset Pages")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "None", "Between Jobs", "Between Copies"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Staple Job")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "On"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Punch Hole")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "On"]
                font.pixelSize: Style.textSize
                enabled: false
            }

            Label {
                text: qsTr("Fold")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "On"]
                font.pixelSize: Style.textSize
                enabled: false
            }
        }
    }
}
