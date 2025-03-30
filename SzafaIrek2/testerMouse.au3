
$PosX = 1
$PosY = 1
$pid = 0


Sleep(1000)

Local $file = FileOpen("c:\log\test.txt", 1 or 8)

while(1)
   
   MouseMove( $PosX, $PosY , 9000 )
   $PosX = Random (1, 1024)
   $PosY = Random (10, 768)
   
   Sleep(300)
   
   MouseClick("left")
   
   if (False==ProcessExists ( "szafa.exe" )) Then
	  ExitLoop
   EndIf
   
   Local $mem = MemGetStats()
   FileWriteLine($file, String($mem[0]))

WEnd



$txt = String(@HOUR) + String(@MIN) + String(@SEC)
MsgBox(0, "SzafaCrashed", $txt)