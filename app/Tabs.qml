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

TabBar {
    id: tabBar
    signal tabBarIndexChanged(int index)
    property int index: 0
    currentIndex: index
    onCurrentIndexChanged: tabBarIndexChanged(tabBar.currentIndex)

    width: 700
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
