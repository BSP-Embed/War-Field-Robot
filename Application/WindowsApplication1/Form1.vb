Imports System.IO.Ports
Imports System.Data
Imports System.Data.OleDb
Imports System.IO

Public Class Form3

    Private WithEvents comPort As New IO.Ports.SerialPort
    Private dataIn As String
    Private readBuffer As String = String.Empty
    Private Bytenumber As Integer
    Private ByteToRead As Integer
    Private byteEnd(2) As Char
    Private comOpen As Boolean
    Dim DataReceived As Byte
    Dim TmrCount As Byte
    Dim swriter As StreamWriter

    Private Sub Form3_FormClosed(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed
        Disconnect()
    End Sub
    Private Sub Form3_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load
        Timer1.Enabled = True
        System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = False
        swriter = File.AppendText("database.txt")
        swriter.WriteLine("**********************************")
        swriter.WriteLine("WAR  FIELD   ROBOT")
        swriter.WriteLine("**********************************")

        swriter.WriteLine("********************************************")
        swriter.WriteLine("Date         Time     Fire       Metal")
        swriter.WriteLine("********************************************")
        swriter.Close()
        AddHandler comPort.DataReceived, AddressOf comPort_DataReceived
    End Sub
    Public Sub Disconnect()

        If comPort IsNot Nothing AndAlso comPort.IsOpen Then
            comPort.Close()
        End If
    End Sub
    Private Sub comPort_DataReceived(ByVal sender As Object, ByVal e As SerialDataReceivedEventArgs)
        If comOpen Then
            Try
                Dim bytes As Integer = comPort.BytesToRead
                'create a byte array to hold the awaiting data
                Dim comBuffer As Byte() = New Byte(bytes - 1) {}
                'read the data and store it
                comPort.Read(comBuffer, 0, bytes)
                If comBuffer(0) = 1 Then
                    TextBox1.Text = "Detected"
                    MsgBox("Fire Detected")
                    display()
                End If
                If comBuffer(0) = 2 Then
                    TextBox2.Text = "Detected"
                    MsgBox("Metal Detected")
                    display()
                End If
            Catch ex As Exception
                MsgBox("Read " & ex.Message)
            End Try
        End If
    End Sub
    Private Sub Button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles Button1.Click
        Me.Close()
        Me.Dispose()
    End Sub
    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick
        Label6.Text = TimeOfDay
        If DataReceived = 1 Then
            TmrCount = TmrCount + 1
            If TmrCount >= 5 Then
                TextBox1.Text = ""
                TextBox2.Text = ""
                TmrCount = 0
                DataReceived = 0
            End If
        End If
    End Sub
    Private Sub display()
        swriter = File.AppendText("Database.txt")
        swriter.WriteLine(Date.Now() & vbTab & TextBox1.Text & vbTab & vbTab & vbTab & TextBox2.Text)
        swriter.Close()
        DataReceived = 1
    End Sub

    Private Sub Button2_Click(sender As Object, e As EventArgs) Handles Button2.Click
        comPort.Write("*A#")
    End Sub

    Private Sub Button3_Click(sender As Object, e As EventArgs) Handles Button3.Click
        comPort.Write("*B#")
    End Sub

    Private Sub Button4_Click(sender As Object, e As EventArgs) Handles Button4.Click
        comPort.Write("*C#")
    End Sub

    Private Sub Button5_Click(sender As Object, e As EventArgs) Handles Button5.Click
        comPort.Write("*D#")
    End Sub

    Private Sub Button6_Click(sender As Object, e As EventArgs) Handles Button6.Click
        comPort.Write("*E#")
    End Sub

    Private Sub Button7_Click(sender As Object, e As EventArgs) Handles Button7.Click
        With comPort
            .PortName = TextBox3.Text
            .BaudRate = 9600
            .Parity = IO.Ports.Parity.None
            .DataBits = 8
            .StopBits = IO.Ports.StopBits.One
            .Handshake = IO.Ports.Handshake.None
            .RtsEnable = False
            .ReceivedBytesThreshold = 1            'threshold: one byte in buffer > event is fired 
        End With
        Try
            comPort.Open()
            comOpen = comPort.IsOpen
        Catch ex As Exception
            comOpen = False
            Label20.Text = "NOT CONNECTED"
            MsgBox("Error Open: " & ex.Message)
        End Try
        If comOpen = True Then
            Label20.Text = "CONNECTED"
        End If
    End Sub
End Class