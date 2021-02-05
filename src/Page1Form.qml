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
        onValueChanged: textField.text = "Принято:" + newValue
    }

    GroupBox {
        id: groupBox
        x: 72
        y: 46
        width: 497
        height: 283
        title: qsTr("Состав системы")

        CheckBox {
            id: checkBox
            x: 0
            y: 16
            text: qsTr("Лидар")
        }

        CheckBox {
            id: checkBox1
            x: 0
            y: 62
            text: qsTr("RGBD камера")
        }

        CheckBox {
            id: checkBox2
            x: 0
            y: 110
            text: qsTr("Радар")
        }

        CheckBox {
            id: checkBox3
            x: 0
            y: 156
            text: qsTr("RGB камера")
        }

        CheckBox {
            id: checkBox4
            x: 0
            y: 202
            text: qsTr("IMU")
        }

        TextField {
            id: textField
            x: 273
            y: 16
            text: qsTr("Состояние")
        }

        TextField {
            id: textField1
            x: 273
            y: 62
            text: qsTr("Состояние")
        }

        TextField {
            id: textField2
            x: 273
            y: 110
            text: qsTr("Состояние")
        }

        TextField {
            id: textField3
            x: 273
            y: 156
            text: qsTr("Состояние")
        }

        TextField {
            id: textField4
            x: 273
            y: 202
            text: qsTr("Состояние")
        }
    }

}



















/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:3;anchors_width:413;anchors_x:37}
}
 ##^##*/
