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
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import "."

RowLayout {
    spacing: 0

    Item {
        id: gridLayoutContainer
        width: parent.width
        Layout.preferredWidth: parent.width
        Layout.minimumWidth: parent.width

        height: parent.height
        Layout.preferredHeight: parent.height
        Layout.minimumHeight: parent.height

        GridLayout {
            id: gridLayout
            width: parent.width
            Layout.minimumWidth: parent.width
            Layout.preferredWidth: parent.width

            rows: 11
            columns: 2

            Label {
                text: qsTr("Margins")
                font.bold: true
                font.pixelSize: Style.textSize
                Layout.columnSpan: 2
            }

            Label {
                text: qsTr("Top")
                //Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            TextField {
                id: topTextField
                placeholderText: qsTr("Top")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: Style.textSize
                validator: DoubleValidator {}
            }

            Label {
                text: qsTr("Left")
                //Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            TextField {
                id: leftTextField
                placeholderText: qsTr("Left")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: Style.textSize
                validator: DoubleValidator {}
            }
            Label {
                text: qsTr("Right")
                //Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            TextField {
                id: rightTextField
                placeholderText: qsTr("Right")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: Style.textSize
                validator: DoubleValidator {}
            }
            Label {
                text: qsTr("Bottom")
                //Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            TextField {
                id: bottomTextField
                placeholderText: qsTr("Bottom")
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: Style.textSize
                validator: DoubleValidator {}
            }
        }
    }
}
