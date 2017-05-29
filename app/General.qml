import QtQuick 2.7

GeneralForm {
    width: 640
    height: 530

    cancelButton.onClicked: {
        close()
    }

    pagesComboBox.onActivated: {
        if (pagesComboBox.currentText == "Single") {
            fromLabel.visible = false
            fromSpinBox.visible = false
            toLabel.visible = false
            toSpinBox.visible = false
            pageNumberLabel.visible = true
            pageNumberSpinBox.visible = true
        }
        else if (pagesComboBox.currentText == "Range") {
            pageNumberLabel.visible = false
            pageNumberSpinBox.visible = false
            fromLabel.visible = true
            fromSpinBox.visible = true
            toLabel.visible = true
            toSpinBox.visible = true
        }
        else {
            pageNumberLabel.visible = false
            pageNumberSpinBox.visible = false
            fromLabel.visible = false
            fromSpinBox.visible = false
            toLabel.visible = false
            toSpinBox.visible = false
        }
    }

    scale: 0.98

    twoSidedSwitch.onPressed: {
        if (twoSidedSwitch.checked) {
            twoSidedSwitchValue.text = "OFF"
        }
        else {
            twoSidedSwitchValue.text = "ON"
        }
    }

    colorSwitch.onPressed: {
        if (colorSwitch.checked) {
            colorSwitchValue.text = "OFF"
        }
        else {
            colorSwitchValue.text = "ON"
        }
    }
}
