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

RowLayout {
    spacing: 0
    property alias paperSizeModel: paperSizeModel
    property alias paperSizeComboBox: paperSizeComboBox
    property int maximumCopies: 2

    signal newPrinterSelected(string printer)
    signal remotePrintersToggled(string enabled)
    signal orientationChanged(string orientation)
    signal newPageSizeSelected(string pageSize)
    signal numCopiesChanged(int copies)
    signal collateToggled(string enabled)
    signal newPageRangeSet(string pageRange)

    function addToDestinationModel(printer_name, printer_id, backend_name) {
        destinationModel.append({destination: printer_name, printerID: printer_id, backend: backend_name})
        if (destinationComboBox.currentIndex == -1 && destinationComboBox.count > 0)
            destinationComboBox.currentIndex = 0
    }

    function removeFromDestinationModel(printer_name) {
        var removed = false
        for (var i = 0; i < destinationModel.count; i++) {
            if (destinationModel.get(i).destination === printer_name) {
                destinationModel.remove(i)
                removed = true
                break
            }
        }
        if (!removed)
            console.log("Unable to delete Printer " + printer_name)
    }

    function clearDestinationModel() {
        destinationModel.clear()
    }

    function updatePaperSizeModel(name, pwg_name, isDefault) {

        paperSizeModel.append({pageName: name, pageSize: pwg_name})
        if (isDefault === 0)
            paperSizeComboBox.currentIndex = paperSizeModel.count - 1
    }

    function clearPaperSizeModel() {
        paperSizeModel.clear()
    }


    Item {
        id: leftGridLayoutContainer
        width: parent.width// * 0.5
        Layout.preferredWidth: parent.width// * 0.5
        Layout.minimumWidth: parent.width// * 0.5

        height: parent.height
        Layout.preferredHeight: parent.height
        Layout.minimumHeight: parent.height

        GridLayout {
            id: leftGridLayout
            width: parent.width
            Layout.minimumWidth: parent.width
            Layout.preferredWidth: parent.width

            rows: 11
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
//                ListElement {
//                    destination: "printer_name"
//                    printerID: "printer_id"
//                    backend: "backend_name"
//                }
            }

            ComboBox {
                id: destinationComboBox
                model: destinationModel
                width: parent.width * 0.65
                Layout.minimumWidth: parent.width * 0.65
                Layout.preferredWidth: parent.width * 0.65
                textRole: "destination"

                font.pixelSize: Style.textSize

                delegate: ItemDelegate {
                    width: destinationComboBox.width
                    font.pixelSize: Style.textSize
                    text: destination
                }

                onCurrentIndexChanged: {
                    var element = destinationModel.get(destinationComboBox.currentIndex)
                    newPrinterSelected(element.printerID + "#" + element.backend)
                }
            }

            Label {
                id: remotePrintersLabel
                text: qsTr("Remote Printers")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            Switch {
                id: remotePrintersSwitch
                checked: true
                onCheckedChanged: remotePrintersToggled(remotePrintersSwitch.checked)
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
                validator: RegExpValidator { regExp: /^[0-9]+(?:(?:\s*,\s*|\s*-\s*)[0-9]+)*$/ }
                onFocusChanged:  {
                    var input = customTextField.text.replace(/\s/g, '').split(',')
                    if (input !== "") {
                        //console.debug(customTextField.text)
                        var pages = [];
                        for (var i = 0; i < input.length; i++) {
                            var pageRange = input[i].split('-');
                            if (pageRange.length === 1) {
                                pages.push(parseInt(pageRange[0]));
                            }
                            else {
                                var low = parseInt(pageRange[0]);
                                var high = parseInt(pageRange[1]);
                                if (low <= high) {
                                    for (var j = low; j <= high; j++) {
                                        pages.push(j);
                                    }
                                }
                                else
                                    console.debug("Error in page range: " + input[i]);
                            }
                        }
                        pages = pages.sort(function(a, b){return a - b});
                        newPageRangeSet(pages)
                    }
                }
            }

            Label {
                id: copiesLabel
                text: qsTr("Copies")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            SpinBox {
                id: copiesSpinBox
                objectName: "copiesSpinBoxObjectName"
                to: maximumCopies
                from: 1
                value: 1
                font.pixelSize: Style.textSize
                editable: true
                validator: IntValidator {}

                onValueChanged: {
                    if (copiesSpinBox.value > 1) {
                        collateCheckBox.visible = true
                        collateCheckBox.checked = true
                    } else {
                        collateCheckBox.visible = false
                    }
                    numCopiesChanged(copiesSpinBox.value)
                }
            }

            Label {
                id: pageHandlingLabel
                text: qsTr("Page Handling")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            RowLayout {
                id: pageHandlingRowLayout
                spacing: 5

                CheckBox {
                    id: collateCheckBox
                    text: qsTr("Collate")
                    font.pixelSize: Style.textSize
                    visible: false

                    onCheckedChanged: collateToggled(collateCheckBox.checked)
                }

                CheckBox {
                    id: reverseCheckBox
                    text: qsTr("Reverse")
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
                    onClicked: orientationChanged("portrait")
                }

                RadioButton {
                    id: landscapeRadioButton
                    text: qsTr("Landscape")
                    font.pixelSize: Style.textSize
                    onClicked: orientationChanged("landscape")
                }
            }

            Label {
                id: paperLabel
                text: qsTr("Paper")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                transformOrigin: Item.Center
                font.pixelSize: Style.textSize
            }

            ListModel {
                id: paperSizeModel
            }

            ComboBox {
                id: paperSizeComboBox
                model: paperSizeModel
                textRole: "pageName"
                delegate: ItemDelegate {
                    width: paperSizeComboBox.width
                    text: pageName
                    font.pixelSize: Style.textSize
                }

                font.pixelSize: Style.textSize

                onCurrentIndexChanged: {
                    var element = paperSizeModel.get(paperSizeComboBox.currentIndex)
                    newPageSizeSelected(element.pageSize)
                }
            }
        }
    }
}
