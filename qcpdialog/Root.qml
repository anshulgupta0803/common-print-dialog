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

SwipeView {
    id: swipeView
    signal swipeViewIndexChanged(int index)
    property int index: 0
    currentIndex: index
    onCurrentIndexChanged: swipeViewIndexChanged(swipeView.currentIndex)

    width: 320 * 1
    Layout.preferredWidth: 320 * 1
    Layout.minimumWidth: 320 * 1

    height: 408
    Layout.preferredHeight: 408
    Layout.minimumHeight: 408

    General {
        id: general
        objectName: "generalObject"
        scale: 0.98
    }

    PageSetup {
        id: pageSetup
        objectName: "pageSetupObject"
        scale: 0.98
    }

    Options {
        id: options
        objectName: "optionsObject"
        scale: 0.98
    }

    Jobs {
        id: jobs
        objectName: "jobsObject"
        scale: 0.98
    }

    Advanced {
        id: advanced
        objectName: "advancedObject"
        scale: 0.98
    }
}
