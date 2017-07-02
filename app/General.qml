import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import "."

Item {
    id: generalView
    property alias destinationModel: destinationModel
    property alias destinationComboBox: destinationComboBox

    anchors.fill: parent

    ColumnLayout {
        spacing: 0
        anchors.fill: parent

        RowLayout {
            id: tabs
            spacing: 0
            visible: false

            width: parent.width
            Layout.preferredWidth: parent.width
            Layout.minimumWidth: parent.width

            height: parent.height * 0.07
            Layout.preferredHeight: parent.height * 0.07
            Layout.minimumHeight: parent.height * 0.07

            TabBar {
                id: tabBar
                anchors.fill: parent
                currentIndex: swipeView.currentIndex

                TabButton {
                    text: qsTr("General")
                    height: Style.tabBarHeight
                    font.pixelSize: Style.textSize
                }
                TabButton {
                    text: qsTr("Page Setup")
                    height: Style.tabBarHeight
                    font.pixelSize: Style.textSize
                }
                TabButton {
                    text: qsTr("Options")
                    height: Style.tabBarHeight
                    font.pixelSize: Style.textSize
                }
                TabButton {
                    text: qsTr("Jobs")
                    height: Style.tabBarHeight
                    font.pixelSize: Style.textSize
                }
                TabButton {
                    text: qsTr("Quality")
                    height: Style.tabBarHeight
                    font.pixelSize: Style.textSize
                }
            }
        }

        RowLayout {
            id: generalContainer
            spacing: 0

            width: parent.width
            Layout.preferredWidth: parent.width
            Layout.minimumWidth: parent.width

            height: parent.height * 0.92
            Layout.preferredHeight: parent.height * 0.92
            Layout.minimumHeight: parent.height * 0.92

            GridLayout {
                id: gridLayout
                width: parent.width * 0.5
                Layout.preferredWidth: parent.width * 0.5
                Layout.minimumWidth: parent.width * 0.5

                height: parent.height
                Layout.preferredHeight: parent.height
                Layout.minimumHeight: parent.height

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
                    width: parent.width * 0.7
                    Layout.preferredWidth: parent.width * 0.7
                    Layout.minimumWidth: parent.width * 0.7

                    font.pixelSize: Style.textSize

                    delegate: ItemDelegate {
                        width: destinationComboBox.width
                        font.pixelSize: Style.textSize
                        text: destination
                    }
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
                    to: 999
                    from: 1
                    value: 1
                    font.pixelSize: Style.textSize
                    editable: true
                    validator: IntValidator {}
                }

                Label {
                    id: layoutLabel
                    text: qsTr("Layout")
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    font.pixelSize: Style.textSize
                }

                RowLayout {
                    id: layoutRowLayout
                    spacing: 5

                    RadioButton {
                        id: portraitRadioButton
                        text: qsTr("Portrait")
                        checked: true
                        font.pixelSize: Style.textSize
                        onClicked: generalPreview.orientationChanged("Portrait")
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
                        font.pixelSize: Style.textSize
                    }

                    font.pixelSize: Style.textSize
                    onCurrentIndexChanged: generalPreview.pageSizeChanged(paperSizeComboBox.textAt(paperSizeComboBox.highlightedIndex))
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
                    id: colorLabel
                    text: qsTr("Color")
                    Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                    font.pixelSize: Style.textSize
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
                        font.pixelSize: Style.textSize
                    }
                }
            }

            Rectangle {
                width: parent.width * 0.5
                Layout.preferredWidth: parent.width * 0.5
                Layout.minimumWidth: parent.width * 0.5

                height: parent.height
                Layout.preferredHeight: parent.height
                Layout.minimumHeight: parent.height
                color: "black"

                Preview {
                    id: generalPreview
                    anchors.fill: parent
                    anchors.centerIn: parent
                }
            }
        }

        RowLayout {
            id: buttonsLayout
            spacing: 0

            width: parent.width
            Layout.preferredWidth: parent.width
            Layout.minimumWidth: parent.width

            height: parent.height * 0.08
            Layout.preferredHeight: parent.height * 0.08
            Layout.minimumHeight: parent.height * 0.08

            Rectangle {
                width: parent.width * 0.5
                Layout.preferredWidth: parent.width * 0.5
                Layout.minimumWidth: parent.width * 0.5

                height: parent.height
                Layout.preferredHeight: parent.height
                Layout.minimumHeight: parent.height
                color: "#00000000"

                Button {
                    id: moreOptionsButton
                    text: qsTr("More Options")
                    font.pixelSize: Style.textSize
                    anchors.centerIn: parent
                    onClicked: {
                        //general.visible = false
                        //moreOptions.visible = true
                        generalView.state == "" ? generalView.state = "moreOptions" : generalView.state = ""
                    }
                }
            }

            Rectangle {
                width: parent.width * 0.5
                Layout.preferredWidth: parent.width * 0.5
                Layout.minimumWidth: parent.width * 0.5

                height: parent.height
                Layout.preferredHeight: parent.height
                Layout.minimumHeight: parent.height
                color: "#00000000"

                RowLayout {
                    anchors.centerIn: parent
                    Button {
                        id: cancelGeneralButton
                        text: qsTr("Cancel")
                        font.pixelSize: Style.textSize
                        onClicked: {
                            close()
                        }
                    }

                    Button {
                        id: printGeneralButton
                        text: qsTr("Print")
                        font.pixelSize: Style.textSize
                        highlighted: true
                    }
                }
            }
        }
    }
    states: [
        State {
            name: "moreOptions"

            PropertyChanges {
                target: colorLabel
                visible: false
            }

            PropertyChanges {
                target: colorRowLayout
                visible: false
            }

            PropertyChanges {
                target: twoSidedRowLayout
                visible: false
            }

            PropertyChanges {
                target: twoSidedLabel
                visible: false
            }

            PropertyChanges {
                target: paperSizeComboBox
                visible: false
            }

            PropertyChanges {
                target: paperLabel
                visible: false
            }

            PropertyChanges {
                target: layoutRowLayout
                visible: false
            }

            PropertyChanges {
                target: layoutLabel
                visible: false
            }

            PropertyChanges {
                target: moreOptionsButton
                text: qsTr("Less Options")
            }

            PropertyChanges {
                target: tabs
                visible: true
            }

            PropertyChanges {
                target: generalContainer
                height: parent.height * 0.85
                Layout.preferredHeight: parent.height * 0.85
                Layout.minimumHeight: parent.height * 0.85
            }
        }
    ]
}
