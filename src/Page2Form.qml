import QtQuick 2.2
import QtQuick.Controls 2.2
import Qt.labs.folderlistmodel 2.1
import QtQml.Models 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.0
import Qt3D.Core 2.9


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

    FileDialog {
        id: fileDialog
        x: 0
        y: 0
        title: "Please choose a file"
        folder: shortcuts.home
        onAccepted: {
            textField.text = fileDialog.fileUrl
            cppWrapper.setProperty(fileDialog.fileUrl.toString().replace("file:///","/"), "urdf_path")
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

}








/*##^## Designer {
    D{i:4;anchors_width:604;anchors_x:17}
}
 ##^##*/
