import QtQuick 2.12
//import QtQuick.Controls 1.6
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.0
import QtQuick.Extras 1.4
import Qt.labs.qmlmodels 1.0



Page {
    id: page1
    width: 1280
    height: 720
    title: ""
    font.pointSize: 12
    contentHeight: 5
    contentWidth: 5

    header: Label {
        text: qsTr("Конфигуратор")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Connections {
        target: rosWrapper
        onValueChanged: lidarTF.text = "Принято:" + newValue
    }

    GroupBox {
        id: groupBox
        x: 34
        y: 15
        width: 573
        height: 299
        title: qsTr("Состав системы")

        GridLayout {
            id: columnLayout
            anchors.topMargin: 15
            anchors.fill: parent
            flow: GridLayout.TopToBottom
            rows: 5
            columns: 3

            CheckBox {
                id: imuCB
                text: qsTr("IMU")

                Connections {
                    target: imuCB
                    onClicked: cppWrapper.setProperty(imuCB.checked, "turn_imu")
                }
            }

            CheckBox {
                id: rgbCB
                text: qsTr("RGB камера")
                Connections {
                    target: rgbCB
                    onClicked: cppWrapper.setProperty(rgbCB.checked, "turn_rgb")
                }
            }

            CheckBox {
                id: radarCB
                text: qsTr("Радар")
                Connections {
                    target: radarCB
                    onClicked: cppWrapper.setProperty(radarCB.checked, "turn_radar")
                }
            }

            CheckBox {
                id: rgbdCB
                text: qsTr("RGBD камера")
                Connections {
                    target: rgbdCB
                    onClicked: cppWrapper.setProperty(rgbdCB.checked, "turn_rgbd")
                }
            }

            CheckBox {
                id: lidarCB
                text: qsTr("Лидар")
                Connections {
                    target: lidarCB
                    onClicked: cppWrapper.setProperty(lidarCB.checked, "turn_lidar")
                }
            }

            ComboBox {
                id: imuComboBox
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 200
                editable: true
                model: rosWrapper.myModel
                onAccepted: {
                    if (find(editText) === -1)
                        rosWrapper.appendList(editText)
                }
                onFocusChanged: {
                    rosWrapper.createRosTopicList()
                }
            }

            ComboBox {
                id: rgbComboBox
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 200
                editable: true
                model: rosWrapper.myModel
                onAccepted: {
                    if (find(editText) === -1)
                        rosWrapper.appendList(editText)
                }
                onFocusChanged: {
                    rosWrapper.createRosTopicList()
                }
            }

            ComboBox {
                id: radarComboBox
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 200
                editable: true
                model: rosWrapper.myModel
                onAccepted: {
                    if (find(editText) === -1)
                        rosWrapper.appendList(editText)
                }
                onFocusChanged: {
                    rosWrapper.createRosTopicList()
                }
            }

            ComboBox {
                id: rgbdComboBox
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 200
                editable: true
                model: rosWrapper.myModel
                onAccepted: {
                    if (find(editText) === -1)
                        rosWrapper.appendList(editText)
                }
                onFocusChanged: {
                    rosWrapper.createRosTopicList()
                }
            }

            ComboBox {
                id: lidarComboBox
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 200
                editable: true
                model: rosWrapper.myModel
                onAccepted: {
                    if (find(editText) === -1)
                        rosWrapper.appendList(editText)
                }
                onFocusChanged: {
                    rosWrapper.createRosTopicList()
                }
            }






            Label {
                id: imuTF
                height: 40
                text: qsTr("Состояние")
                lineHeight: 2
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                wrapMode: Text.NoWrap
                Layout.preferredWidth: 100
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                background: Rectangle {
                    color: "#ed4040"
                    border.color: "#d1c5c5"
                }

            }

            TextField {
                id: rgbTF
                height: 40
                text: qsTr("Состояние")
                Layout.preferredWidth: 100
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
            }

            TextField {
                id: radarTF
                width: 107
                height: 40
                text: qsTr("Состояние")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredWidth: 100
            }

            TextField {
                id: rgbdTF
                width: 107
                height: 40
                text: qsTr("Состояние")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredWidth: 100
            }

            TextField {
                id: lidarTF
                width: 107
                height: 40
                text: qsTr("Состояние")
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                Layout.preferredWidth: 100
            }


        }

    }

    //        TableView {
    //            id: tableView
    //            model: rosbagTableModel
    //            Row {
    //                id: columnsHeader
    //                y: tableView.contentY
    //                width: parent.width
    //                height: 50
    //                z: 2
    //                Repeater {
    //                    model: tableView.columns > 0 ? tableView.columns : 1
    //                    Label {
    //                        width: tableView.columnWidthProvider(modelData)
    //                        height: 35
    //                        text: rosbagTableModel.headerData(modelData, Qt.Horizontal)
    //                        color: '#aaaaaa'
    //                        font.pixelSize: 15
    //                        padding: 10
    //                        verticalAlignment: Text.AlignVCenter

    //                        background: Rectangle { color: "#333333" }
    //                    }
    //                }
    //            }
    //            Column {
    //                id: rowsHeader
    //                x: tableView.contentX
    //                width: 50
    //                height: parent.height
    //                z: 2
    //                Repeater {
    //                    model: tableView.rows > 0 ? tableView.rows : 1
    //                    Label {
    //                        width: 60
    //                        height: tableView.rowHeightProvider(modelData)
    //                        text: rosbagTableModel.headerData(modelData, Qt.Vertical)
    //                        color: '#aaaaaa'
    //                        font.pixelSize: 15
    //                        padding: 10
    //                        verticalAlignment: Text.AlignVCenter

    //                        background: Rectangle { color: "#333333" }
    //                    }
    //                }
    //            }
    //        }


    TableView {
        id: tableView
        x: 700
        y: 50
        width: 500
        height: 600

        columnWidthProvider: function (column) { return 100; }
        rowHeightProvider: function (column) { return 60; }
        leftMargin: rowsHeader.implicitWidth
        topMargin: columnsHeader.implicitHeight
        model: rosbagTableModel
        ScrollBar.horizontal: ScrollBar{}
        ScrollBar.vertical: ScrollBar{}
        clip: true
        delegate: Rectangle {
            Text {
                text: display
                anchors.fill: parent
                anchors.margins: 10
                color: 'black'
                font.pixelSize: 15
                verticalAlignment: Text.AlignVCenter
            }
        }
        Rectangle { // mask the headers
            z: 3
            color: "#222222"
            y: tableView.contentY
            x: tableView.contentX
            width: tableView.leftMargin
            height: tableView.topMargin
        }

        Row {
            id: columnsHeader
            y: tableView.contentY
            z: 2
            Repeater {
                model: tableView.columns > 0 ? tableView.columns : 1
                Label {
                    width: tableView.columnWidthProvider(modelData)
                    height: 35
                    text: rosbagTableModel.headerData(modelData, Qt.Horizontal)
                    color: '#aaaaaa'
                    font.pixelSize: 15
                    padding: 10
                    verticalAlignment: Text.AlignVCenter

                    background: Rectangle { color: "#333333" }
                }
            }
        }
        Column {
            id: rowsHeader
            x: tableView.contentX
            z: 2
            Repeater {
                model: tableView.rows > 0 ? tableView.rows : 1
                Label {
                    width: 60
                    height: tableView.rowHeightProvider(modelData)
                    text: rosbagTableModel.headerData(modelData, Qt.Vertical)
                    color: '#aaaaaa'
                    font.pixelSize: 15
                    padding: 10
                    verticalAlignment: Text.AlignVCenter

                    background: Rectangle { color: "#333333" }
                }
            }
        }

        ScrollIndicator.horizontal: ScrollIndicator { }
        ScrollIndicator.vertical: ScrollIndicator { }
    }









}



















/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}
}
##^##*/
