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

import QtQuick 2.4
import QtQml 2.2
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import "."

RowLayout {
    spacing: 0

    signal cancelButtonClicked()
    signal printButtonClicked()
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
                onClicked: printButtonClicked()
            }
        }
    }

    Rectangle {
        id: rectangle
        width: 380
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
            Layout.alignment: Qt.AlignHCenter | Qt.AlignBaseline
            anchors.centerIn: parent
            width: parent.width
            height: parent.height

            RowLayout {
                anchors.centerIn: parent

                Button {
                    id: prevButton
                    width: 48
                    text: qsTr("\u25C0")
                    highlighted: true
                    //radius: 15
                    onClicked: prevPageButtonClicked()
                }

                Slider {
                    id: zoomSlider
                    to: 5
                    from: 1
                    value: 1
                    onValueChanged: zoomSliderValueChanged(zoomSlider.value)
                }

                Button {
                    id: nextButton
                    width: 48
                    text: qsTr("\u25B6")
                    highlighted: true
                    //radius: 15
                    onClicked: nextPageButtonClicked()
                }
            }
        }
    }
}
