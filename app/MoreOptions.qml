import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ColumnLayout {
    anchors.fill: parent

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        MoreOptionsGeneral {
            y: 35
            scale: 0.98
        }

        MoreOptionsPageSetup {
            y:35
            scale: 0.98
        }

        Page {
            Label {
                text: qsTr("Options")
                anchors.centerIn: parent
            }
        }

        MoreOptionsJobs {
            y: 35
            scale: 0.98
        }

        MoreOptionsAdvanced {
            y: 35
            scale: 0.98
        }
    }
    TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        anchors.horizontalCenter: parent.Center
        anchors.verticalCenter: swipeView.top
        Layout.fillWidth: true
        Layout.fillHeight: true

        TabButton {
            text: qsTr("General")
            height: 32
        }
        TabButton {
            text: qsTr("Page Setup")
            height: 32
        }
        TabButton {
            text: qsTr("Options")
            height: 32
        }
        TabButton {
            text: qsTr("Jobs")
            height: 32
        }
        TabButton {
            text: qsTr("Quality")
            height: 32
        }
    }

    RowLayout {
        anchors.bottom: swipeView.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 150

        Button {
            id: lessOptionsButton
            text: qsTr("Less Options")
            height: 32
            onClicked: {
                general.visible = true
                moreOptions.visible = false
            }
        }

        RowLayout {
            Button {
                id: cancelMoreOptionsButton
                text: qsTr("Cancel")
                height: 32
                onClicked: {
                    close()
                }
            }

            Button {
                id: printMoreOptionsButton
                text: qsTr("Print")
                highlighted: true
                height: 32
            }
        }
    }
}
