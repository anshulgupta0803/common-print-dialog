import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.2
import "."

ColumnLayout{
    function updateStartJobsModel(startJobOption) {
        startJobModel.append({startJobOption: startJobOption})
        if (startJobComboBox.count > 0 && startJobComboBox.currentIndex == -1)
            startJobComboBox.currentIndex = 0
    }

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

        MenuItem{ text: qsTr("Pause"); font.pixelSize: Style.textSize; height: 24; }
        MenuItem{ text: qsTr("Stop"); font.pixelSize: Style.textSize; height: 24; }
        MenuItem{ text: qsTr("Cancel"); font.pixelSize: Style.textSize; height: 24 }
        MenuItem{ text: qsTr("Repeat"); font.pixelSize: Style.textSize; height: 24; }
    }


    TableView {
        id: jobs_view
        currentRow: 1
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
            font.pixelSize: Style.textSize
        }

        ListModel {
            id: startJobModel
        }

        ComboBox {
            id: startJobComboBox
            font.pixelSize: Style.textSize
            model: startJobModel

            delegate: ItemDelegate {
                width: startJobComboBox.width
                text: qsTr(startJobOption)
                font.pixelSize: Style.textSize
            }
        }
    }

    RowLayout {
        id: saveJobRowLayout
        anchors.top: startJobRowLayout.bottom
        Label {
            text: qsTr("Save Job: ")
            font.pixelSize: Style.textSize
        }

        Switch {
            id: save_job_switch
        }

        Button {
            text: qsTr("Browse")
            font.pixelSize: Style.textSize
            visible: (save_job_switch.checked) ? true : false
            onClicked: { file_dialog.open() }
        }
    }

    RowLayout {
        anchors.top: saveJobRowLayout.bottom
        Label {
            text: qsTr("Location: ")
            font.pixelSize: Style.textSize
            visible: (save_job_switch.checked) ? true : false
        }

        Text {
            id: save_job_location
            text: qsTr("None")
            font.pixelSize: Style.textSize
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
