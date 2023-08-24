import QtQuick
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

Window {
    id: root
    width: 720
    height: 700
    visible: true
    title: qsTr("CuteSockets")
    color: "#ffeeeee6"

    TabBar {
        id: tabBar
        anchors {
            top: parent.top
        }

        width: 250

        TabButton {
            text: "Client"
        }

        TabButton {
            text: "Server"
        }

        TabButton {
            text: "Udp"
        }

        TabButton {
            text: "About"
        }
    }

    StackLayout {
        id: stackLayout
        anchors {
            top: tabBar.bottom
            bottom: parent.bottom
            left: parent.left
            right: parent.right
            topMargin: 5
            leftMargin: 5
            rightMargin: 5
            bottomMargin: 5
        }

        currentIndex: tabBar.currentIndex

        ClientTab {

        }

        ServerTab {

        }

        UdpTab {

        }

        AboutTab {

        }
    }
}
