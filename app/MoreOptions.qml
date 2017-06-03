import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

MoreOptionsForm {
    scale: 0.98

    lessOptionsButton.onClicked: {
        general.visible = true
        moreOptions.visible = false
    }

    cancelMoreOptionsButton.onClicked: {
        Qt.quit()
    }
}
