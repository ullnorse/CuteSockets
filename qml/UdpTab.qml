import QtQuick 2.15
import QtQuick.Controls.Universal
import QtQuick.Layouts

import UdpServer 1.0

Item {
    id: udpTab

    property bool serverListening: false

    Connections {
        target: UdpServer

        function onStartedListening() {
            serverListening = true
        }

        function onStoppedListening() {
            serverListening = false
        }
    }

    GroupBox {
        id: groupBoxServer
        title: "Server"

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
                id: textFieldIPAddress
                Layout.fillWidth: true
                text: "127.0.0.1"

                enabled: !serverListening
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
                    id: textFieldPort
                    Layout.fillWidth: true
                    text: "8585"

                    enabled: !serverListening
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
                    text: serverListening ? "Stop Listening" : "Start Listening"

                    onClicked: if (serverListening) {
                        UdpServer.stopServer()
                    } else {
                        UdpServer.startServer(textFieldIPAddress.text, textFieldPort.text);
                    }
                }
            }
        }
    }

    GroupBox {
        id: groupBoxConversation

        title: "Conversation"
        anchors.top: groupBoxServer.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.topMargin: 10

        ColumnLayout {
            anchors.fill: parent

            ScrollView {
                Layout.minimumHeight: 150
                Layout.fillWidth: true
                Layout.fillHeight: true
                ScrollBar.vertical.policy: ScrollBar.AlwaysOn

                TextArea {
                    id: textArea
                    readOnly: true

                    background: Rectangle {
                        color: "white"
                    }

                    Connections {
                        target: UdpServer

                        function onStartedListening() {
                            textArea.append("> Server Started on Port: " + textFieldPort.text)
                            textArea.append("> ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n")
                        }

                        function onStoppedListening() {
                            textArea.append("> Server Stopped")
                            textArea.append("> ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n")
                        }

                        function onDataReceived(data) {
                            textArea.insert(textArea.length, "R[" + textFieldIPAddress.text + ":" + textFieldPort.text + "]: " + data)
                        }
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true

                GroupBox {
                    title: "Client"
                    Layout.fillWidth: true

                    GridLayout {
                        anchors.fill: parent

                        rows: 2
                        columns: 2

                        Text {
                            text: "IP Address"
                        }

                        RowLayout {
                            TextField {
                                id: textFieldIPAddressSend
                                text: "127.0.0.1"
                                Layout.fillWidth: true
                            }

                            Text {
                                text: "Port"
                            }

                            TextField {
                                id: textFieldPortSend
                                text: "8585"
                            }

                            Button {
                                text: "Port"
                                Layout.minimumWidth: 60
                                Layout.maximumWidth: 60
                            }
                        }

                        Text {
                            text: "Message"
                        }

                        RowLayout {
                            TextField {
                                id: textField
                                Layout.fillWidth: true

                                Keys.enabled: true
                                Keys.onReturnPressed: {
                                    UdpServer.sendMessage(textField.text + "\r\n", textFieldIPAddressSend.text, textFieldPortSend.text)
                                    textArea.insert(textArea.length, "S[" + textFieldIPAddressSend.text + ":" + textFieldPortSend.text + "]: " + textField.text + "\r\n")
                                    textField.clear()
                                }
                            }

                            Button {
                                text: "Send"
                                Layout.minimumWidth: 60
                                Layout.maximumWidth: 60

                                onClicked: {
                                    UdpServer.sendMessage(textField.text + "\r\n", textFieldIPAddressSend.text, textFieldPortSend.text)
                                    textArea.insert(textArea.length, "S[" + textFieldIPAddressSend.text + ":" + textFieldPortSend.text + "]: " + textField.text + "\r\n")
                                    textField.clear()
                                }
                            }
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
