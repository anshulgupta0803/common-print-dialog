import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 640
    height: 480
    minimumWidth: 640
    minimumHeight: 480
//    maximumWidth: 650
//    maximumHeight: 530
    title: qsTr("Print Document")

    property alias generalDestinationModel: general.destinationModel
    property alias generalDestinationComboBox: general.destinationComboBox
//    property alias moreOptionsGeneralDestinationModel: moreOptions.generalDestinationModel
//    property alias moreOptionsGeneralDestinationComboBox: moreOptions.generalDestinationComboBox

    function updateDestinationModel(printer) {
        generalDestinationModel.append({destination: printer})
        moreOptionsGeneralDestinationModel.append({destination: printer})
        if (generalDestinationComboBox.count > 0 && generalDestinationComboBox.currentIndex == -1)
            generalDestinationComboBox.currentIndex = 0
//        if (moreOptionsGeneralDestinationComboBox.count > 0 && moreOptionsGeneralDestinationComboBox.currentIndex == -1)
//            moreOptionsGeneralDestinationComboBox.currentIndex = 0
    }

    General {
        id: general
        visible: true
        scale: 0.98
    }

    MoreOptions {
        id: moreOptions
        visible: false
        scale: 0.98
    }
}
