import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 650
    height: 530
    minimumWidth: 650
    minimumHeight: 530
    maximumWidth: 650
    maximumHeight: 530
    title: qsTr("Print Document")

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
