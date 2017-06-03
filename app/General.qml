import QtQuick 2.7

GeneralForm {
    customTextField.onFocusChanged:  {
        if (customTextField.text != "") {
            console.debug(customTextField.text)
        }
    }

    anchors.fill: parent
    moreOptionsButton.onClicked: {
        general.visible = false
        moreOptions.visible = true
    }

    cancelGeneralButton.onClicked: {
        Qt.quit()
    }

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
