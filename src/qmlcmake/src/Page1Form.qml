import QtQuick 2.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import QtQuick.Extras 1.4


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
            }

            CheckBox {
                id: rgbCB
                text: qsTr("RGB камера")
            }

            CheckBox {
                id: radarCB
                text: qsTr("Радар")
            }

            CheckBox {
                id: rgbdCB
                text: qsTr("RGBD камера")
            }

            CheckBox {
                id: lidarCB
                text: qsTr("Лидар")
            }

            ComboBox {
                id: imuComboBox
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
                anchors.right: parent.right
                anchors.rightMargin: 0
            }

            TextField {
                id: radarTF
                width: 107
                height: 40
                text: qsTr("Состояние")
                Layout.preferredWidth: 100
                anchors.right: parent.right
                anchors.rightMargin: 0
            }

            TextField {
                id: rgbdTF
                width: 107
                height: 40
                text: qsTr("Состояние")
                Layout.preferredWidth: 100
                anchors.right: parent.right
                anchors.rightMargin: 0
            }

            TextField {
                id: lidarTF
                width: 107
                height: 40
                text: qsTr("Состояние")
                Layout.preferredWidth: 100
                anchors.right: parent.right
                anchors.rightMargin: 0
            }


        }

    }

    Connections {
        target: lidarCB
        onClicked: cppWrapper.setProperty(lidarCB.checked, "turn_lidar")
    }

    Connections {
        target: radarCB
        onClicked: cppWrapper.setProperty(radarCB.checked, "turn_radar")
    }
    Connections {
        target: rgbdCB
        onClicked: cppWrapper.setProperty(rgbdCB.checked, "turn_rgbd")
    }
    Connections {
        target: rgbCB
        onClicked: cppWrapper.setProperty(rgbCB.checked, "turn_rgb")
    }
    Connections {
        target: imuCB
        onClicked: cppWrapper.setProperty(imuCB.checked, "turn_imu")
    }



}















/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
