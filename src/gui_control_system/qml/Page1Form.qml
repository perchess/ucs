import QtQuick 2.12
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.0
import QtQuick.Extras 1.4
import Qt.labs.qmlmodels 1.0
import QtQuick.Dialogs 1.2



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

    property variant imuSettings: ({   turn: false,
                                       pkg: "",
                                       node: ""    })
    property variant rgbSettings: ({   turn: false,
                                       pkg: "",
                                       node: ""    })
    property variant rgbdSettings: ({   turn: false,
                                        pkg: "",
                                        node: ""    })
    property variant lidarSettings: ({   turn: false,
                                         pkg: "",
                                         node: ""    })
    property variant radarSettings: ({   turn: false,
                                         pkg: "",
                                         node: ""    })

    Connections {
        target: rosWrapper
        function onValueChanged() { lidarTF.text = "Принято:" + newValue}
    }

    GroupBox {
        id: groupBox
        x: 34
        y: 0
        width: 688
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
                property string sensorType: "imu"
                Component.onCompleted: {
                    cppWrapper.setSensorType(sensorType)
                    imuSettings['turn'] = imuCB.checked
                    cppWrapper.setProperty(imuCB.sensorType, imuSettings)
                }

                Connections {
                    function onClicked() {
                        imuSettings['turn'] = imuCB.checked
                        cppWrapper.setProperty(imuCB.sensorType, imuSettings)
                    }
                }
            }

            CheckBox {
                id: rgbCB
                text: qsTr("RGB камера")
                property string sensorType: "rgb"
                Component.onCompleted: {
                    cppWrapper.setSensorType(sensorType)
                    rgbSettings['turn'] = rgbCB.checked
                    cppWrapper.setProperty(this.sensorType, rgbSettings)
                }
                Connections {
                    function onClicked() {
                        rgbSettings['turn'] = rgbCB.checked
                        cppWrapper.setProperty(rgbCB.sensorType,rgbSettings)
                    }
                }
            }

            CheckBox {
                id: radarCB
                text: qsTr("Радар")
                property string sensorType: "radar"
                Component.onCompleted: {
                    cppWrapper.setSensorType(sensorType)
                    radarSettings['turn'] = radarCB.checked
                    cppWrapper.setProperty(this.sensorType, radarSettings)
                }
                Connections {
                    function onClicked() {
                        radarSettings['turn'] = radarCB.checked
                        cppWrapper.setProperty(radarCB.sensorType, radarSettings)
                    }
                }
            }

            CheckBox {
                id: rgbdCB
                text: qsTr("RGBD камера")
                property string sensorType: "rgbd"
                Component.onCompleted: {
                    cppWrapper.setSensorType(sensorType)
                    rgbdSettings['turn'] = rgbdCB.checked
                    cppWrapper.setProperty(this.sensorType, rgbdSettings)
                }
                Connections {
                    function onClicked() {
                        rgbdSettings['turn'] = rgbdCB.checked
                        cppWrapper.setProperty(rgbdCB.sensorType, rgbdSettings)
                    }
                }
            }

            CheckBox {
                id: lidarCB
                text: qsTr("Лидар")
                property string sensorType: "lidar"
                Component.onCompleted: {
                    cppWrapper.setSensorType(sensorType)
                    lidarSettings['turn'] = lidarCB.checked
                    cppWrapper.setProperty(this.sensorType, lidarSettings)
                }
                Connections {
                    function onClicked() {
                        lidarSettings['turn'] = lidarCB.checked
                        cppWrapper.setProperty(lidarCB.sensorType, lidarSettings)
                    }
                }
            }

            ComboBox {
                id: imuPackage
                flat: false
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 200
                editable: true
                selectTextByMouse: true
                model: rosWrapper.pacakgeListModel

                delegate: ItemDelegate {
                    width: imuPackage.width
                    height: imuPackage.height
                    highlighted: ListView.isCurrentItem
                    text: modelData

                    ToolTip.visible: hovered
                    ToolTip.text: modelData
                    ToolTip.timeout: 3000
                    ToolTip.delay: 1000
                }

                Component.onCompleted: rosWrapper.createRosPackageList()
                onAccepted: {
                    if (find(editText) === -1)
                        rosWrapper.appendList(editText)

                }
                onHighlighted: {
                    rosWrapper.createRosPackageList()
                }
                onEditTextChanged:  {
                    imuSettings["pkg"] = imuPackage.editText
                    cppWrapper.setProperty(imuCB.sensorType, imuSettings)
                }
                onModelChanged: editText = ""
            }

            ComboBox {
                id: rgbPackage
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 200
                editable: true
                model: rosWrapper.pacakgeListModel

                delegate: ItemDelegate {
                    width: imuPackage.width
                    height: imuPackage.height
                    highlighted: ListView.isCurrentItem
                    text: modelData

                    ToolTip.visible: hovered
                    ToolTip.text: modelData
                    ToolTip.timeout: 3000
                    ToolTip.delay: 1000
                }

                Component.onCompleted: rosWrapper.createRosPackageList()
                onAccepted: {
                    if (find(editText) === -1)
                        rosWrapper.appendList(editText)
                }
                onHighlighted: {
                    rosWrapper.createRosPackageList()
                }
                onEditTextChanged:  {
                    rgbSettings["pkg"] = rgbPackage.editText
                    cppWrapper.setProperty(rgbCB.sensorType, imuSettings)
                }
                onModelChanged: editText = ""
            }

            ComboBox {
                id: radarPackage
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 200
                editable: true
                model: rosWrapper.pacakgeListModel
                delegate: ItemDelegate {
                    width: imuPackage.width
                    height: imuPackage.height
                    highlighted: ListView.isCurrentItem
                    text: modelData

                    ToolTip.visible: hovered
                    ToolTip.text: modelData
                    ToolTip.timeout: 3000
                    ToolTip.delay: 1000
                }

                Component.onCompleted: rosWrapper.createRosPackageList()
                onAccepted: {
                    if (find(editText) === -1)
                        rosWrapper.appendList(editText)
                }
                onHighlighted: {
                    rosWrapper.createRosPackageList()
                }
                onEditTextChanged:  {
                    radarSettings["pkg"] = radarPackage.editText
                    cppWrapper.setProperty(radarCB.sensorType, radarSettings)
                }
                onModelChanged: editText = ""
            }

            ComboBox {
                id: rgbdPackage
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 200
                editable: true
                model: rosWrapper.pacakgeListModel
                delegate: ItemDelegate {
                    width: imuPackage.width
                    height: imuPackage.height
                    highlighted: ListView.isCurrentItem
                    text: modelData

                    ToolTip.visible: hovered
                    ToolTip.text: modelData
                    ToolTip.timeout: 3000
                    ToolTip.delay: 1000
                }
                Component.onCompleted: rosWrapper.createRosPackageList()
                onAccepted: {
                    if (find(editText) === -1)
                        rosWrapper.appendList(editText)
                }
                onHighlighted: {
                    rosWrapper.createRosPackageList()
                }
                onEditTextChanged:  {
                    rgbdSettings["pkg"] = rgbdPackage.editText
                    cppWrapper.setProperty(rgbdCB.sensorType, rgbdSettings)
                }
                onModelChanged: editText = ""
            }

            ComboBox {
                id: lidarPackage
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                Layout.preferredWidth: 200
                editable: true
                model: rosWrapper.pacakgeListModel
                delegate: ItemDelegate {
                    width: imuPackage.width
                    height: imuPackage.height
                    highlighted: ListView.isCurrentItem
                    text: modelData

                    ToolTip.visible: hovered
                    ToolTip.text: modelData
                    ToolTip.timeout: 3000
                    ToolTip.delay: 1000
                }
                Component.onCompleted: rosWrapper.createRosPackageList()
                onAccepted: {
                    if (find(editText) === -1)
                        rosWrapper.appendList(editText)
                }
                onHighlighted: {
                    rosWrapper.createRosPackageList()
                }
                onEditTextChanged:  {
                    lidarSettings["pkg"] = lidarPackage.editText
                    cppWrapper.setProperty(lidarCB.sensorType, lidarSettings)
                }
                onModelChanged: editText = ""
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
                onEditTextChanged:   {
                    imuSettings["node"] = imuNodeName.editText
                    cppWrapper.setProperty(imuCB.sensorType, imuSettings)
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
                onEditTextChanged:   {
                    rgbSettings["node"] = rgbNodeName.editText
                    cppWrapper.setProperty(rgbCB.sensorType, rgbSettings)
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
                onEditTextChanged:   {
                    radarSettings["node"] = radarNodeName.editText
                    cppWrapper.setProperty(radarCB.sensorType, radarSettings)
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
                onEditTextChanged:   {
                    rgbdSettings["node"] = rgbdNodeName.editText
                    cppWrapper.setProperty(rgbdCB.sensorType, rgbdSettings)
                }
            }

            ComboBox {
                id: lidarNodeName
                model: listModel
                Layout.preferredWidth: 200
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                editable: true
                onAccepted: {
                    if (find(editText) === -1)
                        listModel.append({name: editText})
                }
                onEditTextChanged:   {
                    lidarSettings["node"] = lidarNodeName.editText
                    cppWrapper.setProperty(lidarCB.sensorType, lidarSettings)
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

        RowLayout {
            id: rowLayout3
            x: 154
            width: 406
            anchors.top: parent.top
            anchors.bottom: columnLayout.top
            anchors.bottomMargin: 2
            anchors.topMargin: -10

            Label {
                id: sensorsLabel1
                text: qsTr("ROS пакет")
                anchors.bottom: columnLayout.top
                anchors.bottomMargin: 2

            }

            Label {
                id: sensorsLabel2
                text: qsTr("ROS нода")
                anchors.bottom: columnLayout.top
                anchors.bottomMargin: 2
            }
        }





    }

    TableView {
        id: tableView
        anchors.left: groupBox.right
        anchors.right: parent.right
        anchors.top: fileBrowserWorld.bottom
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 250
        anchors.rightMargin: 20
        anchors.topMargin: 10
        anchors.leftMargin: 20


        columnWidthProvider: function (column) {
            switch (column){
            case 0:
                return 50;
            case 1:
                return 0;
            case 4:
                return 1000;
            case 5:
                return 0;
            default:
                return 100;
            }
        }
        rowHeightProvider: function (column) { return 30; }
        //        leftMargin: tableView.columnWidthProvider(0)
        topMargin: columnsHeader.implicitHeight
        model: rosbagTableModel
        ScrollBar.horizontal: ScrollBar{}
        ScrollBar.vertical: ScrollBar{id:verticalScrollBar}
        clip: true

        delegate: Rectangle {
            Text {
                text: display
                anchors.fill: parent
                anchors.margins: 10
                color: foreground
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
        //        Column {
        //            id: rowsHeader
        //            x: tableView.contentX
        //            z: 2
        //            Repeater {
        //                model: tableView.rows > 0 ? tableView.rows : 1
        //                Label {
        //                    width: 60
        //                    height: tableView.rowHeightProvider(modelData)
        //                    text: rosbagTableModel.headerData(modelData, Qt.Vertical)
        //                    color: '#aaaaaa'
        //                    font.pixelSize: 15
        //                    padding: 10
        //                    verticalAlignment: Text.AlignVCenter

        //                    background: Rectangle { color: "#333333" }
        //                }
        //            }
        //        }

        ScrollIndicator.horizontal: ScrollIndicator { }
        ScrollIndicator.vertical: ScrollIndicator { }
    }

    RowLayout {
        id: rowLayout
        x: 797
        width: 294
        height: 42
        anchors.top: tableView.bottom
        anchors.horizontalCenter: tableView.horizontalCenter
        anchors.topMargin: 15

        ComboBox {
            id: nodeFilter
            displayText: qsTr("Ноды")
            model: rosWrapper.myNodeModel
            Component.onCompleted: rosWrapper.createRosNodeList()
            onHighlighted: {
                rosWrapper.createRosNodeList()
            }
            onActivated: {
                rosWrapper.node = editText
            }
        }

        ComboBox {
            id: typeFilter
            displayText: qsTr("Статусы")
            textRole: "key"
            valueRole: "value"
            model: ListModel {
                ListElement { key: "DEBUG";     value: 0 }
                ListElement { key: "INFO";      value: 1 }
                ListElement { key: "WARNING";   value: 2 }
                ListElement { key: "ERROR";     value: 3 }
            }
            onActivated: {
                rosWrapper.setSeverity(currentValue)
                verticalScrollBar.position = 0.0
            }
        }
    }

    GroupBox {
        id: groupBox1
        x: 34
        y: 348
        width: 688
        height: 262
        title: qsTr("Управление")



        RowLayout {
            id: rowLayout1
            y: 90
            height: 59
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 5
            anchors.rightMargin: 5

            CheckBox {
                id: checkBox1
                text: qsTr("Ручное")
                checked: false
                onClicked: {
                    hotkey_left.enabled = checkBox1.checked
                    hotkey_right.enabled = checkBox1.checked
                    hotkey_up.enabled = checkBox1.checked
                    hotkey_down.enabled = checkBox1.checked
                    if (checkBox1.checked)
                        rosWrapper.startKeyTeleop()
                }

            }

            TextInput {
                id: textInput
                width: 184
                height: 22
                text: qsTr("Телеуправление с клавиатуры")
                font.pixelSize: 17
            }
        }

        RowLayout {
            y: 17
            height: 60
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.leftMargin: 5
            anchors.rightMargin: 5

            CheckBox {
                id: checkBox
                text: qsTr("Автономная навигация")
                onClicked: {

                    cppWrapper.callSystem("roslaunch", [slamComboBox.editText, "open_rviz:=false"])
                    // КАКОЙ-то ХАРДКОД!!!!!!!!!!
                    page2.displayConfig.setSource(rosWrapper.find("robot_gmapping") +
                                                  "/rviz/turtlebot.rviz")
                }
            }

            FileDialog {
                id: fileDialog3
                x: 0
                y: 0
                title: "Please choose a launch file"
                folder: shortcuts.home
                onAccepted: {
                    slamComboBox.editText = fileDialog3.fileUrl.toString().replace("file:///",
                                                                                   "/")
                    cppWrapper.setProperty(fileDialog3.fileUrl.toString().replace(
                                               "file:///", "/"), "autonomous_launch_path")
                }
                onRejected: {
                    console.log("fileDialog1 rejected")
                }
                Component.onCompleted: visible = false
            }

            ComboBox {
                id: slamComboBox
                Layout.minimumWidth: 200
                Layout.fillWidth: false
                displayText: "Выбрать модуль"
                textRole: "key"
                valueRole: "value"
                editable: false
                model: ListModel{
                    ListElement { key: "SLAM"; value: 0 }
                    ListElement { key: "СТЗ"; value: 1 }
                    ListElement { key: "..."; value: 2 }
                }
                onActivated: {
                    this.displayText = currentText
                    cppWrapper.addListMap(currentText, {turn:true})
                }

                ToolTip.visible: hovered
                ToolTip.text: "Выбрать модуль"
                ToolTip.timeout: 3000
                ToolTip.delay: 1000

            }
        }

        RowLayout {
            id: rowLayout2
            y: 155
            height: 56
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.rightMargin: 5
            anchors.leftMargin: 5

            CheckBox {
                id: simCB
                text: qsTr("Симуляция")
                onCheckedChanged: {
                    cppWrapper.setProperty(simCB.checked, "simulation")
                    if (simCB.checked){
                        sensorsLabel1.text = qsTr("Топик из симулятора")
                        sensorsLabel2.text = qsTr("Название ноды")
                        rosWrapper.createRosTopicList()
                        imuPackage.model = rosWrapper.myTopicModel
                        lidarPackage.model = rosWrapper.myTopicModel
                        rgbPackage.model = rosWrapper.myTopicModel
                        rgbdPackage.model = rosWrapper.myTopicModel
                        radarPackage.model = rosWrapper.myTopicModel
                    }
                    else{
                        sensorsLabel1.text = qsTr("ROS пакет")
                        sensorsLabel2.text = qsTr("ROS нода")
                    }
                }
            }

            Button {
                id: launchButton
                text: qsTr("Старт")
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter


                Connections {
                    property variant args: ["control_module", "start.launch"]
                    function onClicked(mouse){
                        if (rosWrapper.isNodeStarted("control_node"))
                            rosWrapper.callUpdateService()
                        else {
                            cppWrapper.callSystem("roslaunch", args)
                            cppWrapper.callSystem("rosrun", ["diagnostic_hardware","diagnostic_hardware_node"])
                            launchButton.text = qsTr("Обновить состояние")
                        }

                    }
                }

            }

        }

    } // end groupBox1

    FileDialog {
        id: fileDialog
        x: 0
        y: 0
        title: "Please choose a URDF file"
        folder: shortcuts.home
        property variant args: ["robot_description", "description.launch", "xacro_urdf_arg:=" + textFieldUrdf.text]
        onAccepted: {
            textFieldUrdf.text = fileDialog.fileUrl.toString().replace("file:///", "/")
            cppWrapper.setProperty(fileDialog.fileUrl.toString().replace(
                                       "file:///", "/"), "urdf_path")
            cppWrapper.callSystem("roslaunch", args)
            robotModelDisplay.enable = true
        }
        onRejected: {
            console.log("fileDialog rejected")
        }
        Component.onCompleted: visible = false
    }

    FileDialog {
        id: fileDialogWorld
        x: 0
        y: 0
        title: "Please choose a world file"
        folder: shortcuts.home
        onAccepted: {
            textFieldWorld.text = fileDialogWorld.fileUrl.toString().replace("file:///", "/")
            cppWrapper.setProperty(fileDialogWorld.fileUrl.toString().replace(
                                       "file:///", "/"), "world_path")
        }
        onRejected: {
            console.log("fileDialogWorld rejected")
        }
        Component.onCompleted: visible = false
    }

    RowLayout {
        id: fileBrowserWorld
        height: 40
        anchors.left: groupBox.right
        anchors.right: parent.right
        anchors.top: fileBrowser.bottom
        anchors.topMargin: 5
        anchors.leftMargin: 15
        TextField {
            id: textFieldWorld
            height: 40
            text: qsTr("Выберите файл мира")
            Layout.fillWidth: true
            Layout.preferredWidth: 400
            Layout.preferredHeight: 40
        }

        Button {
            id: findButton1
            text: qsTr("browse")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

            Connections {
                function onClicked() { fileDialogWorld.open() }
            }
        }
        anchors.rightMargin: 19
    }

    RowLayout {
        id: fileBrowser
        y: 2
        height: 40
        anchors.left: groupBox.right
        anchors.leftMargin: 15
        anchors.right: parent.right
        anchors.rightMargin: 19

        TextField {
            id: textFieldUrdf
            height: 40
            text: qsTr("Выберите файл URDF")
            Layout.fillWidth: true
            Layout.preferredHeight: 40
            Layout.preferredWidth: 400
        }

        Button {
            id: findButton
            text: qsTr("browse")
            Layout.alignment: Qt.AlignRight | Qt.AlignVCenter

            Connections {
                function onClicked() { fileDialog.open() }
            }
        }
    }

    // end fileBrowser

}





/*##^##
Designer {
    D{i:0;formeditorZoom:1.25}
}
##^##*/
