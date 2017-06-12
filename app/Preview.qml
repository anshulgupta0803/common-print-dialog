import QtQuick 2.4
import QtQml 2.2

PreviewForm {
    preview_zoom_slider.onValueChanged: {
        var scale = preview_zoom_slider.value
        image.width = (image.width / previousScaleValue) * scale
        image.height = (image.height / previousScaleValue) * scale
        flickable.contentWidth = image.width
        flickable.contentHeight = image.height
        //flickable.resizeContent((image.width / previousScaleValue) * scale , (image.height / previousScaleValue) * scale, 0)

        previousScaleValue = scale

        flickable.returnToBounds()
    }

    imageMouseArea.onDoubleClicked: {
        preview_zoom_slider.value = 1
    }

    imageMouseArea.onEntered: {
        buttons.opacity = 0.5
    }

    imageMouseArea.onExited: {
        buttons.opacity = 0.8
    }

    preview_previous_page_button.onClicked: {
        var source = String(image.source)
        var filenameLength = source.lastIndexOf("/")
        var filename = source.substring(0, filenameLength)
        var pageNumber = source.substring(filenameLength + 1, source.length)
        var previousPageNumber = parseInt(pageNumber) - 1
        if (previousPageNumber >= 0) {
            image.source = filename + "/" + String(previousPageNumber)
        }
    }

    preview_next_page_button.onClicked: {
        var source = String(image.source)
        var filenameLength = source.lastIndexOf("/")
        var filename = source.substring(0, filenameLength)
        var pageNumber = source.substring(filenameLength + 1, source.length)
        var nextPageNumber = parseInt(pageNumber) + 1
        if (nextPageNumber < preview_data.get_number_of_pages(source.substring(15, filenameLength))) {
            image.source = filename + "/" + String(nextPageNumber)
        }
    }
}
