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

Item {
    id: moreOptionsView
    anchors.fill: parent

    ColumnLayout {
        spacing: 0
        anchors.fill: parent

        RowLayout {
            id: tabs
            spacing: 0

            width: parent.width
            Layout.preferredWidth: parent.width
            Layout.minimumWidth: parent.width

            height: parent.height * 0.07
            Layout.preferredHeight: parent.height * 0.07
            Layout.minimumHeight: parent.height * 0.07

            TabBar {
                id: tabBar
                anchors.fill: parent
                currentIndex: swipeView.currentIndex

                TabButton {
                    text: qsTr("General")
                    height: Style.tabBarHeight
                    font.pixelSize: Style.textSize
                }
                TabButton {
                    text: qsTr("Page Setup")
                    height: Style.tabBarHeight
                    font.pixelSize: Style.textSize
                }
                TabButton {
                    text: qsTr("Options")
                    height: Style.tabBarHeight
                    font.pixelSize: Style.textSize
                }
                TabButton {
                    text: qsTr("Jobs")
                    height: Style.tabBarHeight
                    font.pixelSize: Style.textSize
                }
                TabButton {
                    text: qsTr("Quality")
                    height: Style.tabBarHeight
                    font.pixelSize: Style.textSize
                }
            }
        }

        RowLayout {
            id: container
            spacing: 0

            width: parent.width
            Layout.preferredWidth: parent.width
            Layout.minimumWidth: parent.width

            height: parent.height * 0.85
            Layout.preferredHeight: parent.height * 0.85
            Layout.minimumHeight: parent.height * 0.85

            SwipeView {
                id: swipeView
                anchors.fill: parent
                currentIndex: tabBar.currentIndex

                width: parent.width * 0.5
                Layout.preferredWidth: parent.width * 0.5
                Layout.minimumWidth: parent.width * 0.5

                height: parent.height
                Layout.preferredHeight: parent.height
                Layout.minimumHeight: parent.height

                MoreOptionsGeneral {
                    id: moreOptionsGeneral
                    scale: 0.98
                }

                MoreOptionsPageSetup {
                    scale: 0.98
                }

                MoreOptionsOptions {
                    scale: 0.98
                }

                MoreOptionsJobs {
                    scale: 0.98
                }

                MoreOptionsAdvanced {
                    scale: 0.98
                }
            }
        }

        RowLayout {
            id: buttonsLayout
            spacing: 0

            width: parent.width
            Layout.preferredWidth: parent.width
            Layout.minimumWidth: parent.width

            height: parent.height * 0.08
            Layout.preferredHeight: parent.height * 0.08
            Layout.minimumHeight: parent.height * 0.08

            Rectangle {
                width: parent.width * 0.5
                Layout.preferredWidth: parent.width * 0.5
                Layout.minimumWidth: parent.width * 0.5

                height: parent.height
                Layout.preferredHeight: parent.height
                Layout.minimumHeight: parent.height
                color: "#00000000"

                Button {
                    id: moreOptionsButton
                    text: qsTr("Less Options")
                    anchors.centerIn: parent
                    onClicked: {
                        general.visible = true
                        moreOptions.visible = false
                    }
                }
            }

            Rectangle {
                width: parent.width * 0.5
                Layout.preferredWidth: parent.width * 0.5
                Layout.minimumWidth: parent.width * 0.5

                height: parent.height
                Layout.preferredHeight: parent.height
                Layout.minimumHeight: parent.height
                color: "#00000000"

                RowLayout {
                    anchors.centerIn: parent
                    Button {
                        id: cancelGeneralButton
                        text: qsTr("Cancel")
                        onClicked: {
                            close()
                        }
                    }

                    Button {
                        id: printGeneralButton
                        text: qsTr("Print")
                        highlighted: true
                    }
                }
            }
        }
    }
}
