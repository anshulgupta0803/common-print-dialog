import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

Item {
    property alias twoSidedSwitch: twoSidedSwitch
    property alias twoSidedSwitchValue: twoSidedSwitchValue
    property alias twoSidedConfigLabel: twoSidedConfigLabel
    property alias twoSidedConfigComboBox: twoSidedConfigComboBox

    property alias colorSwitch: colorSwitch
    property alias colorSwitchValue: colorSwitchValue

    property alias customLabel: customLabel
    property alias customTextField: customTextField

    property alias pagesComboBox: pagesComboBox

    property alias moreOptionsButton: moreOptionsButton

    property alias cancelGeneralButton: cancelGeneralButton

    anchors.fill: parent
    RowLayout {
        id: container
        anchors.fill: parent

        GridLayout {
            id: gridLayout
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop
            anchors.left: parent.left
            width: parent.width / 2
            height: parent.height
            columnSpacing: 15
            rowSpacing: 5
            rows: 11
            columns: 2

            Label {
                id: destinationLabel
                text: qsTr("Destination")
                font.pixelSize: 12
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                transformOrigin: Item.Center
            }

            ComboBox {
                id: destinationComboBox
                model: destinationModel

                font.pixelSize: 12

//                delegate: ItemDelegate {
//                    width: destinationComboBox.width
//                    font.pixelSize: 12
//                    text: qsTr(destination)
//                }
            }

            Label {
                id: pagesLabel
                text: qsTr("Pages")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: 12
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
                    font.pixelSize: 12
                }

                font.pixelSize: 12

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
                font.pixelSize: 12
            }

            TextField {
                id: customTextField
                font.pixelSize: 12
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
                font.pixelSize: 12
            }

            SpinBox {
                id: copiesSpinBox
                to: 999
                from: 1
                value: 1
                font.pixelSize: 12
                editable: true
                validator: IntValidator {}
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
                    onClicked: generalPreview.orientationChanged("Portrait")
                }

                RadioButton {
                    id: landscapeRadioButton
                    text: qsTr("Landscape")
                    font.pixelSize: 12
                    onClicked: generalPreview.orientationChanged("Landscape")
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
                id: paperSizeComboBox
                model: ListModel {
                    ListElement {
                        pageSize: "A4"
                    }
                    ListElement {
                        pageSize: "Letter"
                    }
                }
                delegate: ItemDelegate {
                    width: paperSizeComboBox.width
                    text: qsTr(pageSize)
                    font.pixelSize: 12
                }

                font.pixelSize: 12
                onCurrentIndexChanged: generalPreview.pageSizeChanged(paperSizeComboBox.textAt(paperSizeComboBox.highlightedIndex))
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
                id: colorLabel
                text: qsTr("Color")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: 12
            }

            RowLayout {
                id: colorRowLayout
                Switch {
                    id: colorSwitch
                    onPressed: {
                        if (colorSwitch.checked) {
                            colorSwitchValue.text = "OFF"
                        }
                        else {
                            colorSwitchValue.text = "ON"
                        }
                    }
                }
                Label {
                    id: colorSwitchValue
                    text: qsTr("OFF")
                    Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                    font.pixelSize: 12
                }
            }
        }

        Preview {
            id: generalPreview
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
        }
    }
    RowLayout {
        id: buttonsLayout
        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 150

        Button {
            id: moreOptionsButton
            text: qsTr("More Options")
            height: 32
            onClicked: {
                general.visible = false
                moreOptions.visible = true
            }
        }

        RowLayout {
            Button {
                id: cancelGeneralButton
                text: qsTr("Cancel")
                height: 32
                onClicked: {
                    close()
                }
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
