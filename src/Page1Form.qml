import QtQuick 2.0
import QtQuick.Controls 2.0

Page {
    id: page1
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
        target: rosStringPub
        onValueChanged: lidarTF.text = "Принято:" + newValue
    }

    GroupBox {
        id: groupBox
        x: 72
        y: 46
        width: 497
        height: 283
        title: qsTr("Состав системы")

        CheckBox {
            id: lidarCB
            x: 0
            y: 16
            text: qsTr("Лидар")
        }

        CheckBox {
            id: rgbdCB
            x: 0
            y: 62
            text: qsTr("RGBD камера")
        }

        CheckBox {
            id: radarCB
            x: 0
            y: 110
            text: qsTr("Радар")
        }

        CheckBox {
            id: rgbCB
            x: 0
            y: 156
            text: qsTr("RGB камера")
        }

        CheckBox {
            id: imuCB
            x: 0
            y: 202
            text: qsTr("IMU")
        }

        TextField {
            id: lidarTF
            x: 273
            y: 16
            text: qsTr("Состояние")
        }

        TextField {
            id: rgbdTF
            x: 273
            y: 62
            text: qsTr("Состояние")
        }

        TextField {
            id: radarTF
            x: 273
            y: 110
            text: qsTr("Состояние")
        }

        TextField {
            id: rgbTF
            x: 273
            y: 156
            text: qsTr("Состояние")
        }

        TextField {
            id: imuTF
            x: 273
            y: 202
            text: qsTr("Состояние")
        }
    }

    Connections {
        target: lidarCB
        onClicked: cppWrapper.setProperty(lidarCB.checked, "turn_lidar")
    }

    Connections {
        target: radarCB
        onClicked: cppWrapper.setProperty(lidarCB.checked, "turn_radar")
    }
    Connections {
        target: rgbdCB
        onClicked: cppWrapper.setProperty(lidarCB.checked, "turn_rgbd")
    }
    Connections {
        target: rgbCB
        onClicked: cppWrapper.setProperty(lidarCB.checked, "turn_rgb")
    }
    Connections {
        target: imuCB
        onClicked: cppWrapper.setProperty(lidarCB.checked, "turn_imu")
    }

}





































/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:3;anchors_width:413;anchors_x:37}
}
 ##^##*/
