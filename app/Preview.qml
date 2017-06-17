import QtQuick 2.4
import QtQml 2.2
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0

ColumnLayout {
    signal orientationChanged(string orientation)
    property string orient: "Portrait"

    width: 330
    height: 430
    onOrientationChanged: {
        orient = orientation
        var source = String(image.source).split("/")
        var filename = "image://preview"
        var i;
        for (i = 3; i < source.length - 1; i++)
            filename += "/" + source[i]
        image.source = filename + "/" + orient
    }
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
            property alias previewImage: image
            objectName: "image"
            source: "image://preview/tmp/test.pdf/0/Portrait"

            MouseArea {
                id: imageMouseArea
                anchors.fill: parent
                hoverEnabled: true
                onDoubleClicked: { preview_zoom_slider.value = 1 }
                onEntered: { buttons.opacity = 0.5 }
                onExited: { buttons.opacity = 0.8 }
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
                onClicked: {
                    var source = String(image.source).split("/")
                    var filename = "image://preview"
                    var i;
                    for (i = 3; i < source.length - 2; i++)
                        filename += "/" + source[i]
                    var pageNumber = source[i]
                    i++;
                    //var orientation = source[i]
                    var previousPageNumber = parseInt(pageNumber) - 1
                    if (previousPageNumber >= 0)
                        image.source = filename + "/" + String(previousPageNumber) + "/" + orient
                }
            }

            Slider{ // To set the zoom level of the preview image. I should add pan functionality.
                property real previousScaleValue: 1.0
                id: preview_zoom_slider
                to: 5
                from: 1
                value: 1
                onValueChanged: {
                    var scale = preview_zoom_slider.value
                    image.width = (image.width / previousScaleValue) * scale
                    image.height = (image.height / previousScaleValue) * scale
                    flickable.contentWidth = image.width
                    flickable.contentHeight = image.height

                    previousScaleValue = scale

                    flickable.returnToBounds()
                }
            }

            RoundButton {  // Displays the next page in the doument
                id: preview_next_page_button
                text: qsTr('\u25B6')
                highlighted: true
                radius: 15
                onClicked: {
                    var source = String(image.source).split("/")
                    var filename = "image://preview"
                    var i;
                    for (i = 3; i < source.length - 2; i++)
                        filename += "/" + source[i]
                    var pageNumber = source[i]
                    i++;
                    //var orientation = source[i]
                    var nextPageNumber = parseInt(pageNumber) + 1
                    if (nextPageNumber < preview_data.get_number_of_pages(filename.substring(15)))
                        image.source = filename + "/" + String(nextPageNumber) + "/" + orient
                }
            }
        }
    }
}
