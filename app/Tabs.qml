import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import "."

TabBar {
    id: tabBar
    signal tabBarIndexChanged(int index)
    property int index: 0
    currentIndex: index
    onCurrentIndexChanged: tabBarIndexChanged(tabBar.currentIndex)

    width: 640
    height: 32
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
