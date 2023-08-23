import QtQuick 2.15
import QtQuick.Controls.Universal
import QtQuick.Layouts

import TcpServer 1.0

Item {
    id: serverTab

    GroupBox {
        id: groupBoxConnectTo
        title: "Listen On"

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
                    hoverEnabled: true

                    ToolTip.text: "View Standard Ports"
                    ToolTip.visible: hovered
                    ToolTip.delay: 1000
                    ToolTip.timeout: 5000
                }

                Button {
                    property bool startedListening: false

                    text: startedListening ? "Stop Listening" : "Start Listening"

                    onClicked: if (startedListening) {
                        TcpServer.stopServer()
                        startedListening = false
                    } else {
                        TcpServer.startServer("127.0.0.1", 8585);
                        startedListening = true
                    }
                }
            }
        }
    }

    GroupBox {
        id: groupBoxConnectedTo

        property string clientAddress: TcpServer.client ? TcpServer.clientAddress() : "NONE"

        title: "Connected Client : < [" + clientAddress + "] >"
        anchors.top: groupBoxConnectTo.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 10

        ColumnLayout {
            anchors.fill: parent

            Text {
                text: "Conversation with Client"
            }

            ScrollView {
                Layout.minimumHeight: 150
                Layout.fillWidth: true
                Layout.fillHeight: true
                ScrollBar.vertical.policy: ScrollBar.AlwaysOn

                TextArea {
                    id: textArea
                    anchors.fill: parent
                    readOnly: true

                    background: Rectangle {
                        color: "white"
                    }

                    Connections {
                        target: TcpServer

                        function onStartedListening() {
                            textArea.append("> Server Started on Port:")
                            textArea.append("> ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n")
                        }

                        function onStoppedListening() {
                            textArea.append("> Server Stopped")
                            textArea.append("> ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n")
                        }

                        function onDataReceived(data) {
                            textArea.insert(textArea.length, data)
                        }

                        function onClientConnected(address) {
                            textArea.insert(textArea.length, "> New Client: " + address + "\n")
                        }

                        function onServerClosedClientConnection() {
                            textArea.insert(textArea.length, "> Server closed Client connection\n")
                        }

                        function onClientDisconnected() {
                            textArea.insert(textArea.length, "> Client Closed connection\n")
                        }
                    }
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
                            id: textField
                            Layout.fillWidth: true
                            enabled: TcpServer.client

                            Keys.enabled: true
                            Keys.onReturnPressed: {
                                TcpServer.sendMessageToClient(textField.text + "\r\n")
                                textArea.insert(textArea.length, "S: " + textField.text + "\r\n")
                                textField.clear()
                            }
                        }

                        Button {
                            text: "Send"
                            enabled: TcpServer.client

                            onClicked: {
                                TcpServer.sendMessageToClient(textField.text + "\r\n")
                                textArea.insert(textArea.length, "S: " + textField.text + "\r\n")
                                textField.clear()
                            }
                        }

                        Button {
                            text: "Disconnect"
                            enabled: TcpServer.client

                            onClicked: TcpServer.disconnectClient()
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

                        onClicked: textArea.clear()
                    }
                }
            }
        }
    }
}
