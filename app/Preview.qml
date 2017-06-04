import QtQuick 2.4

PreviewForm {
    preview_zoom_slider.onValueChanged: {
        var scale = preview_zoom_slider.value
        flickable.resizeContent((image.width / previousScaleValue) * scale , (image.height / previousScaleValue) * scale, 0)

        previousScaleValue = scale

        flickable.returnToBounds()
    }

    imageMouseArea.onDoubleClicked: {
        preview_zoom_slider.value = 1
    }
}
