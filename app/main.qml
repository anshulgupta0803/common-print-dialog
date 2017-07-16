import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 720
    height: 540
    minimumWidth: 720
    minimumHeight: 540
    title: qsTr("Print Document")

    Root {
        id: root
        objectName: "rootObject"
        visible: true
        scale: 0.98
    }
}
