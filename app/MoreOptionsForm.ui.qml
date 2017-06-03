import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ColumnLayout {
    property alias cancelMoreOptionsButton: cancelMoreOptionsButton

    anchors.fill: parent

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        MoreOptionsGeneral {
            y: 35

        }

        Page {
            Label {
                text: qsTr("Page Setup")
                anchors.centerIn: parent
            }
        }

        Page {
            Label {
                text: qsTr("Options")
                anchors.centerIn: parent
            }
        }

        Page {
            Label {
                text: qsTr("Jobs")
                anchors.centerIn: parent
            }
        }

        Page {
            Label {
                text: qsTr("Quality")
                anchors.centerIn: parent
            }
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
            id: printPreviewButton
            text: qsTr("Preview")
            height: 32
        }

        RowLayout {
            Button {
                id: cancelMoreOptionsButton
                text: qsTr("Cancel")
                height: 32
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
