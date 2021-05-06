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
    property alias tools: tools
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


    Item {
        id: root
        anchors.fill: parent
        anchors.margins: 15

        Rectangle {
            id: rectangle
            anchors.fill: parent

            RenderWindow {
                id: renderWindow
                anchors.fill: parent
            }

            RowLayout {
                id: rowLayout
                height: 40
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.leftMargin: 0
                anchors.rightMargin: 0

                Button {
                    id: button
                    text: qsTr("Задать целевую точку")
                    Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                    onClicked: tools.setCurrentTool("rviz/SetGoal")
                }
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
            source: ""
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
            toolNames: ["rviz/Interact", "rviz/MoveCamera", "rviz/SetGoal"]

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
    D{i:0;formeditorZoom:0.66;height:720;width:1280}D{i:15}
}
##^##*/
