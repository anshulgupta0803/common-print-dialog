import QtQuick 2.4
import QtQml 2.2
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0

Rectangle {
    signal nextPageButtonClicked()
    signal prevPageButtonClicked()
    signal zoomSliderValueChanged(real value)
    property real previousScaleValue: 1.0

    id: buttons
    color: "#00000000"
    radius: 15
    Layout.alignment: Qt.AlignHCenter | Qt.AlignBaseline
    width: parent.width
    height: parent.height

    RowLayout {
        anchors.centerIn: parent

        RoundButton {
            id: prevButton
            text: qsTr("\u25C0")
            highlighted: true
            radius: 15
            onClicked: nextPageButtonClicked()
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
