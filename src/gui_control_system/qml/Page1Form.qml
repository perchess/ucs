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
        function onValueChanged() { lidarTF.text = "Принято:" + newValue}
    }

    GroupBox {
        id: groupBox
        x: 34
        y: 0
        width: 674
        height: 314
        title: qsTr("Состав системы")

        GridLayout {
            id: columnLayout
            anchors.topMargin: 15
            anchors.fill: parent
            flow: GridLayout.TopToBottom
            rows: 5
            columns: 4


            CheckBox {
                id: imuCB
                text: qsTr("IMU")

                Connections {
                    function onClicked() {
                        cppWrapper.setProperty(imuCB.checked, "imu_turn")
                        cppWrapper.setProperty(imuPackage.editText, "imu_pkg")
                        cppWrapper.setProperty(imuNodeName.editText, "imu_node")
                    }
                }
            }

            CheckBox {
                id: rgbCB
                text: qsTr("RGB камера")
                Connections {
                    function onClicked() {
                        cppWrapper.setProperty(rgbCB.checked, "rgb_turn")
                        cppWrapper.setProperty(rgbPackage.editText, "rgb_pkg")
                        cppWrapper.setProperty(rgbNodeName.editText, "rgb_node")
                    }
                }
            }

            CheckBox {
                id: radarCB
                text: qsTr("Радар")
                Connections {
                    function onClicked() {
                        cppWrapper.setProperty(radarCB.checked, "radar_turn")
                        cppWrapper.setProperty(radarPackage.editText, "radar_pkg")
                        cppWrapper.setProperty(radarNodeName.editText, "radar_node")
                    }
                }
            }

            CheckBox {
                id: rgbdCB
                text: qsTr("RGBD камера")
                Connections {
                    function onClicked() {
                        cppWrapper.setProperty(rgbdCB.checked, "rgbd_turn")
                        cppWrapper.setProperty(rgbdPackage.editText, "rgbd_pkg")
                        cppWrapper.setProperty(rgbdNodeName.editText, "rgbd_node")
                    }
                }
            }

            CheckBox {
                id: lidarCB
                text: qsTr("Лидар")
                Connections {
                    function onClicked() {
                        cppWrapper.setProperty(lidarCB.checked, "lidar_turn")
                        cppWrapper.setProperty(lidarPackage.editText, "lidar_pkg")
                        cppWrapper.setProperty(lidarNodeName.editText, "lidar_node")
                    }
                }
            }

            ComboBox {
                id: imuPackage
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 200
                editable: true
                model: rosWrapper.pacakgeListModel
                Component.onCompleted: rosWrapper.createRosPackageList()
                onAccepted: {
                    if (find(editText) === -1)
                        rosWrapper.appendList(editText)
                }
                onHighlighted: {
                    rosWrapper.createRosPackageList()
                }
            }

            ComboBox {
                id: rgbPackage
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 200
                editable: true
                model: rosWrapper.pacakgeListModel
                Component.onCompleted: rosWrapper.createRosPackageList()
                onAccepted: {
                    if (find(editText) === -1)
                        rosWrapper.appendList(editText)
                }
                onHighlighted: {
                    rosWrapper.createRosPackageList()
                }
            }

            ComboBox {
                id: radarPackage
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 200
                editable: true
                model: rosWrapper.pacakgeListModel
                Component.onCompleted: rosWrapper.createRosPackageList()
                onAccepted: {
                    if (find(editText) === -1)
                        rosWrapper.appendList(editText)
                }
                onHighlighted: {
                    rosWrapper.createRosPackageList()
                }
            }

            ComboBox {
                id: rgbdPackage
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 200
                editable: true
                model: rosWrapper.pacakgeListModel
                Component.onCompleted: rosWrapper.createRosPackageList()
                onAccepted: {
                    if (find(editText) === -1)
                        rosWrapper.appendList(editText)
                }
                onHighlighted: {
                    rosWrapper.createRosPackageList()
                }
            }

            ComboBox {
                id: lidarPackage
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 200
                editable: true
                model: rosWrapper.pacakgeListModel
                Component.onCompleted: rosWrapper.createRosPackageList()
                onAccepted: {
                    if (find(editText) === -1)
                        rosWrapper.appendList(editText)
                }
                onHighlighted: {
                    rosWrapper.createRosPackageList()
                }
            }

            ListModel {
                id: listModel
            }


            ComboBox {
                id: imuNodeName
                model: listModel
                Layout.preferredWidth: 200
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                editable: true
                onAccepted: {
                    if (find(editText) === -1)
                        listModel.append({name: editText})
                }
            }

            ComboBox {
                id: rgbNodeName
                model: listModel
                Layout.preferredWidth: 200
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                editable: true
                onAccepted: {
                    if (find(editText) === -1)
                        listModel.append({name: editText})
                }
            }




            ComboBox {
                id: radarNodeName
                model: listModel
                Layout.preferredWidth: 200
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                editable: true
                onAccepted: {
                    if (find(editText) === -1)
                        listModel.append({name: editText})
                }
            }


            ComboBox {
                id: rgbdNodeName
                model: listModel
                Layout.preferredWidth: 200
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                editable: true
                onAccepted: {
                    if (find(editText) === -1)
                        listModel.append({name: editText})
                }
            }

            ComboBox {
                id: lidarNodeName
                model: listModel
                Layout.preferredWidth: 200
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                editable: true
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

        Label {
            id: label
            x: 228
            y: -10
            text: qsTr("Пакеты")
        }

        Label {
            id: label1
            x: 420
            y: -10
            text: qsTr("Ноды")
        }

        Button {
            id: launchButton
            x: 275
            y: 309
            text: qsTr("Старт")

            Connections {
                property variant args: ["control_module", "start.launch"]
                function onClicked(mouse){
                    if (rosWrapper.isNodeStarted("control_node"))
                        rosWrapper.callService()
                    else
                        cppWrapper.callSystem("roslaunch", args)
//                        cppWrapper.callSystem("roslaunch control_module start.launch")
                }
            }
        }
    }

    TableView {
        id: tableView
        x: 736
        y: 0
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
    D{i:0;formeditorZoom:0.66}D{i:33}
}
##^##*/
