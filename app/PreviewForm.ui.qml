import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0

ColumnLayout {
    property alias preview_zoom_slider: preview_zoom_slider
    property alias image: image
    property alias flickable: flickable
    property real previousScaleValue: 1.0
    property alias imageMouseArea: imageMouseArea
    property alias buttons: buttons
    property alias preview_previous_page_button: preview_previous_page_button
    property alias preview_next_page_button: preview_next_page_button

    width: 330
    height: 430
    Flickable {
        id: flickable
        boundsBehavior: Flickable.StopAtBounds
        flickableDirection: Flickable.HorizontalAndVerticalFlick
        anchors.fill: parent
        interactive: true
        clip: true
        contentWidth: image.width
        contentHeight: image.height

        Image {
            id: image
            objectName: "image"
            source: "image://preview/tmp/test.pdf/0"

            MouseArea {
                id: imageMouseArea
                anchors.fill: parent
                hoverEnabled: true
            }
        }
    }

    Rectangle {
        id: buttons
        color: "#000"
        radius: 15
        Layout.alignment: Qt.AlignHCenter | Qt.AlignBaseline
        width: 320
        height: 48
        border.color: "#000"
        opacity: 0.8
        anchors.bottom: flickable.bottom

        RowLayout {
            anchors.centerIn: parent
            RoundButton { // Displays the previous page in the doument
                id: preview_previous_page_button
                text: qsTr("\u25C0")
                highlighted: true
                radius: 15
            }

            Slider{ // To set the zoom level of the preview image. I should add pan functionality.
                id: preview_zoom_slider
                to: 5
                from: 1
                value: 1
                //stepSize: 0.5
            }

            RoundButton {  // Displays the next page in the doument
                id: preview_next_page_button
                text: qsTr('\u25B6')
                highlighted: true
                radius: 15
            }
        }
    }

}
