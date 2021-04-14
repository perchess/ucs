import QtQuick 2.15
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.11
import MyModule 1.0

ApplicationWindow {
    id: applicationWindow
    visible: true
    width: 1280
    height: 720
    title: qsTr("Tabs")

    Shortcut {
        sequence: StandardKey.Quit
        onActivated: Qt.quit()
    }
    Shortcut {
        id: hotkey_left
        enabled: false
        sequence: "Left"
        onActivated: rosWrapper.sendTeleopCmd(sequence)
    }
    Shortcut {
        id: hotkey_right
        enabled: false
        sequence: "Right"
        onActivated: rosWrapper.sendTeleopCmd(sequence)
    }
    Shortcut {
        id: hotkey_up
        enabled: false
        sequence: "Up"
        onActivated: rosWrapper.sendTeleopCmd(sequence)
    }
    Shortcut {
        id: hotkey_down
        enabled: false
        sequence: "Down"
        onActivated: rosWrapper.sendTeleopCmd(sequence)
    }


    StackLayout {
        id: windows__stack
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1Form {id: page1}
        Page2Form {id: page2}
    }

    footer:TabBar {
        id: tabBar
        x: 0
        y: 440
        width: applicationWindow.width
        height: 50
        position: TabBar.Header
        currentIndex: windows__stack.currentIndex

        TabButton {
            id: tabBut1
            x: 0
            y: 0
            height: 50
            text: qsTr("Конфигуратор")
        }

        TabButton {
            id: tabBut2
            x: 0
            y: 0
            height: 50
            text: qsTr("Визуализатор")
        }
    }


}
