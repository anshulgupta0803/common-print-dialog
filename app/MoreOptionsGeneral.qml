import QtQuick 2.4

MoreOptionsGeneralForm {
    scale: 0.98

    pagesComboBox.onActivated: {
        if (pagesComboBox.currentText == "Custom") {
            customLabel.visible = true
            customTextField.visible = true
        }
        else {
            customLabel.visible = false
            customTextField.visible = false
        }
    }
}
