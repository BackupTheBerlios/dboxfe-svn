Seit Version 0.65 können Sie mit DOSBox Videoclips aus der Bildschirmausgabe
erstellen (Screen-Capturing).

Drücken Sie Strg-Alt-F5, um die Aufnahme zu starten.
Um die Aufnahme anzuhalten/zu beenden, drücken Sie erneut Strg-Alt-F5.

Um den aufgenommenen Clip abspielen zu können, benötigen Sie einen Movie
Player und den installierten ZMBV-Codec. Windows-Anwender finden diesen Codec
im Startmenü-Ordner von DOSBox. Anwender von Linux und anderen Betriebs-
systemen sollten einen Movie Player benutzen, der auf der ffmpeg-Bibliothek
aufbaut (unter Umständen benötigen Sie ein Update oder ihre Distribution muss
upgegraded werden).

FAQ:

F: Beim Abspielen der Clips sind Bild und Ton asynchron ("der Ton hängt").
A: Überprüfen Sie, ob in Ihren Anzeige-Einstellungen die Bildschirmaktuali-
   sierungsrate auf mindestens 70 Hertz eingestellt ist. Versuchen Sie, den
   Clip mit virtualdub abzuspielen (http://virtualdub.sf.net).

F: Warum wird der Clip in mehreren Dateien abgespeichert?
A: Wenn sich die Auflösung ändert, muss DOSBox jedesmal eine neue Datei
   anlegen, weil innerhalb eines Clips immer dieselbe Auflösung vorliegen
   muss.

F: Kann ich während der Aufnahme mehr Cycles einstellen, als mein Rechner
   verarbeiten kann?
A: Ja. Auch wenn das Spiel während der Aufnahme langsam läuft oder stottert,
   sollte sich der aufgenommene Clip ohne Stottern in der beabsichtigten
   Geschwindigkeit abspielen lassen.

F: Unter Linux wird mit der Kombination Strg-Alt-F5 die Konsole gestartet...
A: Gehen Sie folgendermaßen vor:
    1. Starten Sie DOSBox mit: dosbox -startmapper
    2. Klicken Sie auf "Video" und "Add"
    3. Drücken Sie die gewünschte Taste (z.B. "Rollen" oder "Druck")
    4. Klicken Sie auf "Exit"
    5. Erstellen Sie Ihre Clips durch Drücken der eingestellten Taste.

F: Die Farbdarstellung ist fehlerhaft. Ich benutze eine 64-bit-Version von
   Windows.
A: Versuchen Sie das: http://vogons.zetafleet.com/viewtopic.php?t=12133
