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
        scale: 0.98
    }

    Jobs {
        id: jobs
        objectName: "jobsObject"
        scale: 0.98
    }

    Advanced {
        scale: 0.98
    }
}
