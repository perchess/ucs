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
    }

    TextField {
        id: textField
        x: 37
        y: 146
        text: qsTr("Принято:")
    }

    Connections {
        target: button
        onClicked: print("clicked")
    }

}





/*##^## Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
 ##^##*/
