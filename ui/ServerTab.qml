import QtQuick 2.15
import QtQuick.Controls.Universal
import QtQuick.Layouts

Item {
    id: serverTab

    GroupBox {
        id: groupBoxConnectTo
        title: "Listen on"

        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }

        GridLayout {
            anchors.fill: parent

            columns: 2
            rows: 2

            Text {
                id: labelIPAddress
                text: "IP Address"
                Layout.maximumWidth: 70
                Layout.minimumWidth: 70
            }

            TextField {
                Layout.fillWidth: true
                text: "127.0.0.1"
            }

            Text {
                text: "Port"
                Layout.fillWidth: true
                horizontalAlignment: Text.AlignRight
                Layout.maximumWidth: 70
                Layout.minimumWidth: 70
            }

            RowLayout {
                id: rowLayout2

                TextField {
                    Layout.fillWidth: true
                    text: "8585"
                }

                Button {
                    text: "Port"
                }

                Button {
                    text: "Start Listening"
                }
            }
        }
    }

    GroupBox {
        id: groupBoxConnectedTo
        title: "Connected Client < None>"
        anchors.top: groupBoxConnectTo.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 10

        ColumnLayout {
            anchors.fill: parent

            Text {
                text: "Conversation with client"
            }

            TextArea {
                Layout.minimumHeight: 150
                Layout.fillWidth: true
                Layout.fillHeight: true
                readOnly: true

                background: Rectangle {
                    color: "white"
                }
            }

            RowLayout {
                Layout.fillWidth: true

                GroupBox {
                    title: "Send"
                    Layout.fillWidth: true

                    RowLayout {
                        anchors.fill: parent

                        Text {
                            text: "Message"
                        }

                        TextField {
                            Layout.fillWidth: true
                        }

                        Button {
                            text: "Send"
                        }

                        Button {
                            text: "Disconnect"
                        }
                    }
                }

                ColumnLayout {
                    Layout.topMargin: 20
                    Button {
                        text: "Save"
                        Layout.minimumWidth: 60
                        Layout.maximumWidth: 60
                    }

                    Button {
                        text: "Clear"
                        Layout.minimumWidth: 60
                        Layout.maximumWidth: 60
                    }
                }
            }
        }
    }
}
