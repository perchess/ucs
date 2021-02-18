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
        x: 315
        y: 64
        width: 300
        height: 300
        active: false
        clip: false
        visible: false
        sourceComponent: rvizComp
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

    Button {
        id: showButton
        x: 63
        y: 312
        text: qsTr("on")
    }

    Connections {
        target: showButton
        onClicked: loader.active = true
    }

    Button {
        id: showButton1
        x: 169
        y: 312
        text: qsTr("off")
    }

    Connections {
        target: showButton1
        onClicked: loader.active = false
    }


}



































/*##^## Designer {
    D{i:5;anchors_width:604;anchors_x:17}
}
 ##^##*/
