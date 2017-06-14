import QtQuick 2.7

GeneralForm {
    customTextField.onFocusChanged:  {
        var input = customTextField.text.replace(/\s/g, '').split(',')
        if (input !== "") {
            //console.debug(customTextField.text)
            var pages = [];
            for (var i = 0; i < input.length; i++) {
                var pageRange = input[i].split('-');
                if (pageRange.length === 1) {
                    pages.push(parseInt(pageRange[0]));
                }
                else {
                    var low = parseInt(pageRange[0]);
                    var high = parseInt(pageRange[1]);
                    if (low <= high) {
                        for (var j = low; j <= high; j++) {
                            pages.push(j);
                        }
                    }
                    else
                        console.debug("Error in page range: " + input[i]);
                }
            }
            pages = pages.sort(function(a, b){return a - b});
            console.log(pages)
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
            twoSidedConfigLabel.visible = false
            twoSidedConfigComboBox.visible = false
        }
        else {
            twoSidedSwitchValue.text = "ON"
            twoSidedConfigLabel.visible = true
            twoSidedConfigComboBox.visible = true
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
