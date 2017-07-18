import QtQuick 2.4
import QtQml 2.2
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0
import "."

RowLayout {
    spacing: 0

    signal cancelButtonClicked()
    signal nextPageButtonClicked()
    signal prevPageButtonClicked()
    signal zoomSliderValueChanged(real value)

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

        Rectangle {
            property real previousScaleValue: 1.0

            id: buttons
            color: "#00000000"
            radius: 15
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBaseline
            anchors.centerIn: parent
            width: parent.width
            height: parent.height

            RowLayout {
                anchors.centerIn: parent

                RoundButton {
                    id: prevButton
                    text: qsTr("\u25C0")
                    highlighted: true
                    radius: 15
                    onClicked: prevPageButtonClicked()
                }

                Slider {
                    id: zoomSlider
                    to: 5
                    from: 1
                    value: 1
                    onValueChanged: zoomSliderValueChanged(zoomSlider.value)
                }

                RoundButton {
                    id: nextButton
                    text: qsTr("\u25B6")
                    highlighted: true
                    radius: 15
                    onClicked: nextPageButtonClicked()
                }
            }
        }
    }
}
