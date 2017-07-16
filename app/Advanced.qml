import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls.Styles 1.4
import "."

Item {

    ScrollView {
        anchors.fill: parent
        verticalScrollBarPolicy: Qt.ScrollBarAlwaysOn


        GridLayout {
            id: grid_layout
            Layout.fillHeight: true

            width: parent.width
            Layout.preferredWidth: parent.width
            Layout.minimumWidth: parent.width

            rowSpacing: 0
            columns: 2

            Label {
                text: qsTr("Quality")
                Layout.columnSpan: 2
                font.bold: true
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Resolution (dpi)")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "150", "300", "600"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Toner Darkness")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "1", "2", "3"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Brightness")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "-3", "-2", "-1", "0", "1", "2", "3"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Contrast")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "0", "1", "2", "3"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Saturation")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "-3", "-2", "-1", "0", "1", "2", "3"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Enhance Fine Lines")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "On"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Color")
                Layout.columnSpan: 2
                Layout.preferredHeight: 30
                font.bold: true
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Color Correction")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "Auto", "Manual"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Color Saver")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "On"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Monochrome")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "On"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Color Balance")
                Layout.columnSpan: 2
                font.bold: true
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Cyan Balance")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "-3", "-2", "-1", "0", "1", "2", "3"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Magenta Balance")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "-3", "-2", "-1", "0", "1", "2", "3"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Yellow Balance")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "-3", "-2", "-1", "0", "1", "2", "3"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Black Balance")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "-3", "-2", "-1", "0", "1", "2", "3"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Manual Color")
                Layout.columnSpan: 2
                Layout.preferredHeight: 30
                font.bold: true
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("RGB Image")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "Vivid", "sRGB Display", "sRGB Vivid", "Display-true Black"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("RGB Text")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "Vivid", "sRGB Display", "sRGB Vivid", "Display-true Black"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("RGB Graphics")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "Vivid", "sRGB Display", "sRGB Vivid", "Display-true Black"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("CMYK")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "US CMYK", "Euro CMYK"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Finishing")
                Layout.columnSpan: 2
                Layout.preferredHeight: 30
                font.bold: true
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Print Blank Pages")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "On"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Separator Pages")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "None", "Between Jobs", "Between Copies", "Between Pages"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Offset Pages")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "None", "Between Jobs", "Between Copies"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Staple Job")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "On"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Punch Hole")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "On"]
                font.pixelSize: Style.textSize
            }

            Label {
                text: qsTr("Fold")
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                font.pixelSize: Style.textSize
            }

            ComboBox {
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
                model: ["Printer Setting", "Off", "On"]
                font.pixelSize: Style.textSize
            }
        }
    }
}
