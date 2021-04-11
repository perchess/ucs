import QtQuick 2.9
import QtQuick.Controls 2.2
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

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page1Form {
            id: page1

        }

        Page2Form {
            id: page2
        }
    }

    footer:TabBar {
        id: tabBar
        x: 0
        y: 440
        width: applicationWindow.width
        height: 50
        position: TabBar.Header
        currentIndex: swipeView.currentIndex

        TabButton {
            id: tabBut1
            x: 0
            y: 0
            height: 50
            text: qsTr("Tab Button")
        }

        TabButton {
            id: tabBut2
            x: 0
            y: 0
            height: 50
            text: qsTr("Tab Button")
        }
    }

    Timer {
        interval: 1
        running: true
        repeat: true
        onTriggered:{
            rosWrapper.spin()
        }
    }

}
