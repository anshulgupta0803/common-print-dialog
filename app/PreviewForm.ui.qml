import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ColumnLayout {
    property alias preview_zoom_slider: preview_zoom_slider
    property alias image: image
    property alias flickable: flickable
    property real previousScaleValue: 1.0
    property alias imageMouseArea: imageMouseArea

    width: 330
    height: 430
    Flickable {
        id: flickable
        boundsBehavior: Flickable.StopAtBounds
        flickableDirection: Flickable.HorizontalAndVerticalFlick
        anchors.fill: parent
        interactive: true

        Image {
            id: image
            anchors.fill: parent
            source: "image://preview/pdf"

            MouseArea {
                id: imageMouseArea
                anchors.fill: parent
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
        opacity: 0.5
        anchors.bottom: flickable.bottom

        RowLayout {
            scale: 0.90
            anchors.centerIn: parent
            Button { // Displays the previous page in the doument
                id: preview_previous_page_button
                text: qsTr("\u25C0")
            }

            Slider{ // To set the zoom level of the preview image. I should add pan functionality.
                id: preview_zoom_slider
                to: 3
                from: 1
                value: 1
                stepSize: 0.5
            }

            Button {  // Displays the next page in the doument
                id: preview_next_page_button
                text: qsTr('\u25B6')
            }
        }
    }
}
