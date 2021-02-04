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

    Button {
        id: button
        x: 37
        y: 38
        text: qsTr("Отправить")
        onClicked: rosStringPub.setConstMsg()
    }

    TextField {
        id: textField
        y: 278
        height: 44
        text: qsTr("Принято:")
        anchors.left: parent.left
        anchors.leftMargin: 44
        anchors.right: parent.right
        anchors.rightMargin: 183
    }

    Connections {
        target: rosStringPub
        onValueChanged: textField.text = "Принято:" + newValue
    }

}

















/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:3;anchors_width:413;anchors_x:37}
}
 ##^##*/
