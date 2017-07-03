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
    title: qsTr("Print Document")

    property alias generalDestinationModel: general.destinationModel
    property alias generalDestinationComboBox: general.destinationComboBox

    function updateDestinationModel(printer) {
        generalDestinationModel.append({destination: printer})
        if (generalDestinationComboBox.count > 0 && generalDestinationComboBox.currentIndex == -1)
            generalDestinationComboBox.currentIndex = 0
    }

    General {
        id: general
        visible: true
        scale: 0.98
    }
}
