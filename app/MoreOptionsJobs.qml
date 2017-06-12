import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2

ColumnLayout{
    Layout.fillWidth: true

    Rectangle {
        id: headerRectangle
        height: 20
        color: "#868686"
        Layout.alignment: Qt.AlignLeft | Qt.AlignTop
        Layout.fillWidth: true
        RowLayout {
            anchors.leftMargin: 20
            anchors.fill: parent
            Layout.alignment: Qt.AlignLeft | Qt.AlignTop

            Label {
                text: qsTr("Printer")
                font.bold: true
                wrapMode: Text.Wrap
                x: 20
                width: parent.width / 3 - 20
            }

            /* Better to create a visual separator like a vertical
           straight line between columns for more comprehensive look */

            Label {
                id: location_heading
                text: qsTr("Location")
                font.bold: true
                wrapMode: Text.Wrap
                x: parent.width / 3 + 20
                width: parent.width / 3 - 20
            }

            Label {
                text: qsTr("Status")
                font.bold: true
                wrapMode: Text.Wrap
                x: 2 * parent.width / 3 + 20
                width: parent.width / 3 - 20
            }
        }
    }

    /* Move from listmodel to a context property
    obtained from backend */

    ListModel{
        id: jobs_model

        ListElement{
            printer: "Canon Pixma"
            location: "Office Desk"
            status: "Completed"
        }

        ListElement{
            printer: "HP Laser Jet"
            location: "Home"
            status: "Running"
        }

        ListElement{
            printer: "Xerox"
            location: "Office Reception"
            status: "Pending"
        }

        ListElement{
            printer: "Xerox"
            location: "Office Reception"
            status: "Pending"
        }

        ListElement{
            printer: "Xerox"
            location: "Office Reception"
            status: "Pending"
        }

        ListElement{
            printer: "Xerox"
            location: "Office Reception"
            status: "Pending"
        }

        ListElement{
            printer: "Xerox"
            location: "Office Reception"
            status: "Pending"
        }

        ListElement{
            printer: "Xerox"
            location: "Office Reception"
            status: "Pending"
        }

        ListElement{
            printer: "Xerox"
            location: "Office Reception"
            status: "Pending"
        }

        ListElement{
            printer: "Xerox"
            location: "Office Reception"
            status: "Pending"
        }

        ListElement{
            printer: "Xerox"
            location: "Office Reception"
            status: "Pending"
        }

        ListElement{
            printer: "Xerox1"
            location: "Office Reception"
            status: "Pending"
        }

        ListElement{
            printer: "Xerox"
            location: "Office Reception"
            status: "Pending"
        }

        ListElement{
            printer: "Xerox"
            location: "Office Reception"
            status: "Pending"
        }

        ListElement{
            printer: "Xerox"
            location: "Office Reception"
            status: "Pending"
        }

        ListElement{
            printer: "Xerox"
            location: "Office Reception"
            status: "Pending"
        }

        ListElement{
            printer: "Xerox"
            location: "Office Reception"
            status: "Pending"
        }

        ListElement{
            printer: "Xerox"
            location: "Office Reception"
            status: "Pending"
        }
    }

    ListView {
        id: jobs_view
        y: 20
        z: -5
        width: parent.width
        height: parent.height / 2
        model: jobs_model
        anchors.top: headerRectangle.bottom
        //y: location_heading.contentHeight + 20

        delegate: Rectangle {
            width: parent.width
            height: Math.max(printer_text.contentHeight, location_text.contentHeight, status_text.contentHeight) + 10
            color: (model.index % 2 == 0) ? "#EEEEEE" : "white"

            Menu { //Should this menu be for every job or is there some other way?
                id: menu
                width: 108

                MenuItem{ text: qsTr("Pause"); font.pixelSize: 12; height: 24 }
                MenuItem{ text: qsTr("Stop"); font.pixelSize: 12; height: 24 }
                MenuItem{ text: qsTr("Cancel"); font.pixelSize: 12; height: 24 }
                MenuItem{ text: qsTr("Repeat"); font.pixelSize: 12; height: 24 }
            }

            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.RightButton
                hoverEnabled: true

                onEntered: { parent.color = "#BDBDBD"}
                onExited:  { parent.color = (model.index % 2 == 0) ? "#EEEEEE" : "white"}
                onClicked: { //Add color to indicate right-clicked job
                    menu.x = mouseX
                    menu.y = mouseY
                    menu.open()
                }
            }

            Text {
                id: printer_text
                x: 20
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width / 3 - 20
                text: qsTr(printer)
                wrapMode: Text.Wrap
            }

            Text {
                id: location_text
                x: parent.width / 3 + 20
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width / 3 - 20
                text: qsTr(location)
                wrapMode: Text.Wrap
            }

            Text {
                id: status_text
                x: 2 * parent.width / 3 + 20
                anchors.verticalCenter: parent.verticalCenter
                width: parent.width / 3 - 20
                text: qsTr(status)
                wrapMode: Text.Wrap
            }
        }
    }

    RowLayout {
        id: startJobRowLayout
        anchors.top: jobs_view.bottom
        anchors.topMargin: 20
        anchors.leftMargin: 20

        Label {
            text: qsTr("Start Job: ")
            font.pixelSize: 12
        }

        ComboBox {
            id: start_job_combobox
            font.pixelSize: 12
            model: ListModel {
                ListElement { startJobOption: "Immediately" }
                ListElement { startJobOption: "After a delay of" }
                ListElement { startJobOption: "Never" }
            }

            delegate: ItemDelegate {
                width: start_job_combobox.width
                text: qsTr(startJobOption)
                font.pixelSize: 12
            }
        }

        TextField {
            font.pixelSize: 12
            visible: (start_job_combobox.currentIndex==1) ? true : false
        }

        Label {
            text: qsTr("Minutes")
            font.pixelSize: 12
            visible: (start_job_combobox.currentIndex==1) ? true : false
        }

    }

    RowLayout {
        id: saveJobRowLayout
        anchors.top: startJobRowLayout.bottom
        Label {
            text: qsTr("Save Job: ")
            font.pixelSize: 12
        }

        Switch {
            id: save_job_switch
        }

        Button {
            text: qsTr("Browse")
            font.pixelSize: 12
            visible: (save_job_switch.checked) ? true : false
            onClicked: { file_dialog.open() }
        }
    }

    RowLayout {
        anchors.top: saveJobRowLayout.bottom
        Label {
            text: qsTr("Location: ")
            font.pixelSize: 12
            visible: (save_job_switch.checked) ? true : false
        }

        Text {
            id: save_job_location
            text: qsTr("None")
            font.pixelSize: 12
            visible: (save_job_switch.checked) ? true : false
        }
    }

    FileDialog {
        id: file_dialog
        title: "Please choose a folder"
        folder: shortcuts.home
        selectFolder: true
        onAccepted: {
            save_job_location.text = file_dialog.fileUrl.toString().substring(7)
            file_dialog.close()
        }
        onRejected: {
            file_dialog.close()
        }
    }
}
