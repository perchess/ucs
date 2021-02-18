import QtQuick 2.2
import QtQuick.Controls 2.2
import Qt.labs.folderlistmodel 2.1
import QtQml.Models 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import Qt3D.Core 2.9
import ros.rviz 1.0
import MyModule 1.0


Page {
    id: page1
    width: 640
    height: 480
    title: ""
    font.pointSize: 12
    contentHeight: 5
    contentWidth: 5

    header: Label {
        text: qsTr("Настройки ROS")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }

    Loader {
        id: loader
        y: 64
        height: 220
        anchors.left: parent.left
        anchors.leftMargin: 315
        anchors.right: parent.right
        anchors.rightMargin: 25
        active: false
        clip: false
        visible: false
        sourceComponent: rvizComp
    }

    RowLayout {
        id: rowLayout
        x: 337
        width: 256
        height: 67
        anchors.top: loader.bottom
        anchors.topMargin: 6
        visible: true

        Button {
            id: showButton1
            text: qsTr("off")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

        Button {
            id: showButton
            text: qsTr("on")
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
        }

    }

    Component {
        id: rvizComp

        Item {
            VisualizationFrame {
                id: visualizationFrame
                width: 300
                height: 300
                anchors.fill: parent
                renderWindow: renderWindow
            }

            Rectangle {
                anchors.fill: parent
                color: "lightblue"

                RenderWindow {
                    id: renderWindow
                    anchors.fill: parent
                }
            }

            //        SimpleGrid {
            //          id: grid
            //          frame: visualizationFrame
            //          lineWidth: 10
            //          color: "lightblue"
            //        }

            //        RobotModel {
            //            id: robotModel
            //            frame: visualizationFrame
            //        }

            DisplayConfig {
                id: displayConfig
                frame: visualizationFrame
                source: curPath + "config/rviz.rviz"
            }

            Button {
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter
                text: qsTr("reload")
                onClicked: {
                    loader.active = false;
                    loader.active = true;
                }
            }



            //        Row {
            //          anchors.bottom: parent.bottom
            //          anchors.horizontalCenter: parent.horizontalCenter

            //          Button {
            //            text: "Red Grid"
            //            onClicked: grid.color = "red"
            //          }

            //          Button {
            //            text: "Blue Grid"
            //            onClicked: grid.color = "blue"
            //          }
            //        }
        }
    }

    FileDialog {
        id: fileDialog
        x: 0
        y: 0
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            textField.text = fileDialog.fileUrl.toString().replace("file:///","/")
            cppWrapper.setProperty(fileDialog.fileUrl.toString().replace("file:///","/"), "urdf_path")
            cppWrapper.systemCmd("roslaunch robot_description description.launch xacro_urdf_arg:=" + textField.text)
            loader.visible = true
            //            loader.active = true
            //            console.log("You chose: " + fileDialog.fileUrls)
            //            Qt.quit()
        }
        onRejected: {
            console.log("Canceled")
            //            Qt.quit()
        }
        Component.onCompleted: visible = false
    }

    Connections {
        target: findButton
        onClicked: fileDialog.open()
    }

    RowLayout {
        y: 2
        height: 40
        anchors.left: parent.left
        anchors.leftMargin: 17
        anchors.right: parent.right
        anchors.rightMargin: 19

        TextField {
            id: textField
            height: 40
            text: qsTr("Выберите файл")
            Layout.preferredHeight: 40
            Layout.preferredWidth: 400
        }

        Button {
            id: findButton
            text: qsTr("browse")
        }
    }

    Connections {
        target: showButton
        onClicked: loader.active = true
    }

    Connections {
        target: showButton1
        onClicked: loader.active = false
    }




}





































/*##^## Designer {
    D{i:3;anchors_y:225}D{i:2;anchors_width:300;anchors_x:315}D{i:8;anchors_width:604;anchors_x:17}
}
 ##^##*/
