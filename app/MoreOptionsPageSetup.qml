import QtQuick 2.4

MoreOptionsPageSetupForm {
    scale: 0.98
    twoSidedSwitch.onPressed: {
        if (twoSidedSwitch.checked) {
            twoSidedSwitchValue.text = "OFF"
            twoSidedConfigLabel.visible = false
            twoSidedConfigComboBox.visible = false
        }
        else {
            twoSidedSwitchValue.text = "ON"
            twoSidedConfigLabel.visible = true
            twoSidedConfigComboBox.visible = true
        }
    }
}
