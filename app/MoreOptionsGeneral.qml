import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import "."

RowLayout {
    spacing: 0
    objectName: "moreOptionsGeneralObjectName"
    property alias paperSizeModel: paperSizeModel
    property alias paperSizeComboBox: paperSizeComboBox
    property int maximumCopies: 2

    signal newPrinterSelected(string printer)
    signal remotePrintersToggled(string enabled)

    function clearDestinationModel() {
        destinationModel.clear()
    }

    function updateDestinationModel(printer) {
        destinationModel.append({destination: printer})
        if (destinationComboBox.count > 0 && destinationComboBox.currentIndex == -1)
            destinationComboBox.currentIndex = 0
    }

    function clearPaperSizeModel() {
        paperSizeModel.clear()
    }

    function updatePaperSizeModel(media) {
        paperSizeModel.append({pageSize: media})
        if (paperSizeComboBox.count > 0 && paperSizeComboBox.currentIndex == -1)
            paperSizeComboBox.currentIndex = 0
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
                ListElement {
                    destination: "A-Very-Long-Random-Name-Of-A-Printer-From-CUPS"
                }

                ListElement {
                    destination: "Short-Name"
                }
            }

            ComboBox {
                id: destinationComboBox
                model: destinationModel
                width: parent.width * 0.65
                Layout.minimumWidth: parent.width * 0.65
                Layout.preferredWidth: parent.width * 0.65

                font.pixelSize: Style.textSize

                delegate: ItemDelegate {
                    width: destinationComboBox.width
                    font.pixelSize: Style.textSize
                    text: destination
                }

                onCurrentIndexChanged: newPrinterSelected(destinationComboBox.textAt(destinationComboBox.currentIndex))
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
                        console.log(pages)
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
                    onClicked: {
                        generalPreview.orientationChanged("Portrait")

                    }
                }

                RadioButton {
                    id: landscapeRadioButton
                    text: qsTr("Landscape")
                    font.pixelSize: Style.textSize
                    onClicked: generalPreview.orientationChanged("Landscape")
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
                delegate: ItemDelegate {
                    width: paperSizeComboBox.width
                    text: qsTr(pageSize)
                    font.pixelSize: Style.textSize
                }

                font.pixelSize: Style.textSize
            }
        }
    }
}
