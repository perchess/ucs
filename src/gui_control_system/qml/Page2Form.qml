import QtQuick 2.12
import QtQuick.Controls 2.4
import QtQuick.Window 2.2
import Qt.labs.folderlistmodel 2.1
import QtQml.Models 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import Qt3D.Core 2.9
import ros.rviz 1.0
import MyModule 1.0

Page {
    id: page2
    width: 640
    height: 480
    property alias displayConfig: displayConfig
    title: ""
    font.pointSize: 12
    contentHeight: 5
    contentWidth: 5

    header: Label {
        text: qsTr("Настройки ROS")
        font.pixelSize: Qt.application.font.pixelSize * 2
        padding: 10
    }


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
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: fileBrowser.bottom
        anchors.topMargin: 14
        anchors.leftMargin: 17
        TextField {
            id: textFieldWorld
            height: 40
            text: qsTr("Выберите файл мира")
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
        anchors.left: parent.left
        anchors.leftMargin: 17
        anchors.right: parent.right
        anchors.rightMargin: 19

        TextField {
            id: textFieldUrdf
            height: 40
            text: qsTr("Выберите файл URDF")
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




    Item {
        id: root
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: fileBrowserWorld.bottom
        anchors.bottom: parent.bottom
        anchors.rightMargin: 15
        anchors.leftMargin: 15
        anchors.bottomMargin: 15
        anchors.topMargin: 15
        ///////////////////////////////
        // Функции
        //////////////////////////////
        //////////////////////////////

        Rectangle {
            anchors.fill: parent

            RenderWindow {
                id: renderWindow
                anchors.fill: parent
            }
        }

        VisualizationFrame {
            id: visualizationFrame
            anchors.fill: parent
            renderWindow: renderWindow
        }

        DisplayConfig {
            id: displayConfig
            frame: visualizationFrame
//            source: "/home/den/c_workspaces/ucs/src/robot_gmapping/rviz/turtlebot.rviz"
            //            source: rosWrapper.find("turtlebot3_slam") +
            //                    "/rviz/turtlebot3_gmapping.rviz"
        }

        //////////////////////////////////////
        //             Дисплеи              //
        //////////////////////////////////////
        RvizDisplay {
            id: axesDisplay
            property string activeFrame: "world"
            frame: visualizationFrame
            classLookupName: "rviz/Axes"
            name: "Axes"
            onDisplayCreated: {
                setPropertyValue("Reference Frame", activeFrame)
                setPropertyValue("Length", 0.3)
                setPropertyValue("Radius", 0.03)
            }
        }

        RvizDisplay {
            id: gridDisplay
            property string activeFrame: "world"
            frame: visualizationFrame
            classLookupName: "rviz/Grid"
            name: "Grid"
            onDisplayCreated: {
                setPropertyValue("Reference Frame", activeFrame)
            }
        }

        RvizDisplay {
            id: robotModelDisplay
            property bool visualEnabled: true
            property bool collisionEnabled: false
            property int updateInterval: 0
            property int alpha: 1
            property string robotDescription: "robot_description"
            property string tfPrefix: ""
            frame: visualizationFrame
            classLookupName: "rviz/RobotModel"
            name: "RobotModel"
            enable: false
            onDisplayCreated: {
                setPropertyValue("Visual Enabled", visualEnabled)
                setPropertyValue("Collision Enabled", collisionEnabled)
                setPropertyValue("Update Interval", updateInterval)
                setPropertyValue("Alpha", alpha)
                setPropertyValue("Robot Description", robotDescription)
                setPropertyValue("TF Prefix", tfPrefix)
            }
        }

        RvizDisplay {
            id: tfDisplay
            property bool showNames: true
            property bool showAxes: true
            property bool showArrows: true
            property real test: 0.5
            frame: visualizationFrame
            classLookupName: "rviz/TF"
            name: "TF"
            enable: true
            onDisplayCreated: {
                setPropertyValue("Show Names", showNames)
                setPropertyValue("Show Axes", showAxes)
                setPropertyValue("Show Arrows", showArrows)
                setPropertyValue("Marker Scale", test)
                setPropertyValue("Marker Alpha", 1)
                setPropertyValue("Update Interval", 0)
                setPropertyValue("Frame Timeout", 15)
            }
        }

        RvizTools {
            id: tools
            frame: visualizationFrame
            toolNames: ["rviz/Interact", "rviz/MoveCamera"]

            onToolsCreated: {
                setCurrentTool("rviz/Interact")
            }
        }

        RvizOptions {
            fixedFrame: "base_link"
            backgroundColor: "#303030" // Стандартный цвет rviz
            frame: visualizationFrame
        }

        RvizView {
            frame: visualizationFrame
            onViewCreated: {
                setPropertyValue("Distance", 2.5)
                setPropertyValue("Yaw", Math.PI * 1.75)
                setPropertyValue("Pitch", Math.PI * 0.25)
                setPropertyValue("Focal Point/X", 0.5)
                setPropertyValue("Focal Point/Y", -0.5)
                setPropertyValue("Focal Point/Z", 1.0)
            }
        }
    }

    // end rvizItem
}




/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
