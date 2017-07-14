import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: applicationWindow
    objectName: "applicationWindowObjectName"
    visible: true
    width: 640
    height: 480
    minimumWidth: 640
    minimumHeight: 480
    title: qsTr("Print Document")

    property alias generalPaperSizeModel: general.paperSizeModel
    property alias generalPaperSizeComboBox: general.paperSizeComboBox
    property alias generalPreview: general.generalPreview


    function updatePaperSizeModel(media) {
        generalPaperSizeModel.append({pageSize: media})
        if (generalPaperSizeComboBox.count > 0 && generalPaperSizeComboBox.currentIndex == -1)
            generalPaperSizeComboBox.currentIndex = 0
    }

    General {
        id: general
        visible: true
        scale: 0.98
    }
}
