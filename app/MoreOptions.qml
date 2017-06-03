import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

MoreOptionsForm {
    scale: 0.98

    cancelMoreOptionsButton.onClicked: {
        close()
    }
}
