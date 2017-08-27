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
import QtQuick.Dialogs 1.2
import "."

ColumnLayout{
    property int selectedRow: -1
    property int selectedJobID: -1
    property string selectedPrinter: ""
    property string selectedBackend: ""

    signal refreshJobs()
    signal cancelJob(string printer, string backend_name, string jobID)

    function addJob(jobID, printer, location, status, backend_name) {
        jobs_model.append({jobID: jobID,
                              printer: printer,
                              location: location,
                              status: status,
                              backend_name: backend_name})
    }

    function clearJobModel() {
        jobs_model.clear()
    }

    function updateStartJobsModel(startJobOption) {
        startJobModel.append({startJobOption: startJobOption})
        if (startJobComboBox.count > 0 && startJobComboBox.currentIndex == -1)
            startJobComboBox.currentIndex = 0
    }

    function clearStartJobsModel() {
        startJobModel.clear()
    }

    Layout.fillWidth: true

    Label {
        text: qsTr("Active Jobs")
        font.bold: true
        font.pixelSize: Style.textSize
    }

    ListModel{
        id: jobs_model
    }

    TableView {
        id: jobs_view
        currentRow: 0
        highlightOnFocus: true
        Layout.minimumHeight: parent.height / 2
        Layout.fillWidth: true

        onClicked: {
            if (row == selectedRow) {
                cancelJobButton.enabled = false
                selectedRow = -1
                selectedJobID = -1
                selectedPrinter = ""
                selectedBackend = ""
                jobs_view.selection.clear()
            }
            else {
                cancelJobButton.enabled = true
                selectedRow = row
                var current_row = jobs_model.get(row)
                selectedJobID = current_row.jobID
                selectedPrinter = current_row.printer
                selectedBackend = current_row.backend_name
            }
        }
        TableViewColumn {
            role: "printer"
            title: qsTr("Printer")
            width: 105
        }
        TableViewColumn {
            role: "location"
            title: qsTr("Location")
            width: 105
        }
        TableViewColumn {
            role: "status"
            title: qsTr("Status")
            width: 105
        }
        model: jobs_model
    }

    RowLayout {
        Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
        Button {
            id: refreshJobsButton
            Layout.maximumHeight: 40
            Layout.maximumWidth: 40
            text: qsTr("\u27F3")
            font.pixelSize: Style.textSize
            onClicked: {
                jobs_view.selection.clear()
                refreshJobs()
            }
        }

        Button {
            id: cancelJobButton
            Layout.maximumHeight: 40
            Layout.maximumWidth: 40
            text: qsTr("\u2716")
            highlighted: true
            enabled: false
            font.pixelSize: Style.textSize
            onClicked: {
                if (selectedRow != -1)
                    cancelJob(selectedPrinter, selectedBackend, selectedJobID)
                else cancelJobButton.enabled = false
            }
        }
    }

    RowLayout {
        id: startJobRowLayout

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
        id: saveJobRowLayouts
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
