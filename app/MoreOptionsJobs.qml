import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2


ColumnLayout{
    Layout.fillWidth: true

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

    Menu { //Should this menu be for every job or is there some other way?
        id: menu
        width: 108

        MenuItem{ text: qsTr("Pause"); font.pixelSize: 12; height: 24; }
        MenuItem{ text: qsTr("Stop"); font.pixelSize: 12; height: 24; }
        MenuItem{ text: qsTr("Cancel"); font.pixelSize: 12; height: 24 }
        MenuItem{ text: qsTr("Repeat"); font.pixelSize: 12; height: 24; }
    }


    TableView {
        id: jobs_view
        highlightOnFocus: true
        Layout.minimumHeight: parent.height / 2
        sortIndicatorVisible: true
        Layout.fillWidth: true
        anchors.top: parent.top
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.RightButton
            hoverEnabled: true
            onClicked: {
                menu.x = mouseX
                menu.y = mouseY
                menu.open()
            }
        }
        TableViewColumn {
            role: "printer"
            title: qsTr("Printer")
            width: 210
        }
        TableViewColumn {
            role: "location"
            title: qsTr("Location")
            width: 210
        }
        TableViewColumn {
            role: "status"
            title: qsTr("Status")
            width: 210
        }
        model: jobs_model
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
                ListElement { startJobOption: qsTr("Immediately") }
                ListElement { startJobOption: qsTr("After a delay of") }
                ListElement { startJobOption: qsTr("Never") }
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
        title: qsTr("Please choose a folder")
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
