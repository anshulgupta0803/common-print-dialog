import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import "."

RowLayout {
    spacing: 0

    signal cancelButtonClicked()

    Rectangle {
        width: 320
        //Layout.preferredWidth: 320
        //Layout.minimumWidth: 320

        height: 40
        //Layout.preferredHeight: 40
        //Layout.minimumHeight: 40
        color: "#00000000"

        RowLayout {
            anchors.centerIn: parent
            Button {
                id: cancelGeneralButton
                text: qsTr("Cancel")
                font.pixelSize: Style.textSize
                onClicked: cancelButtonClicked()
            }

            Button {
                id: printGeneralButton
                text: qsTr("Print")
                font.pixelSize: Style.textSize
                highlighted: true
            }
        }
    }

    Rectangle {
        id: rectangle
        width: 320
        //Layout.preferredWidth: 320
        //Layout.minimumWidth: 320

        height: 40
        //Layout.preferredHeight: 40
        //Layout.minimumHeight: 40
        color: "#00000000"

        Preview {
            anchors.centerIn: parent.Center
        }
    }
}
