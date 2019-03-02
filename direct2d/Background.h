//	Header Datei für den Hintergrund
/*
	Der Hintergrund funktioniert folgendermassen:
	Es gibt insgesamt zwei Bilder, nämlich das Grass und der weiter entfernte Hintergrund.
	Beide Bilder werden mithilfe der Klasse SpriteSheet und Graphics im Fenster angezeigt.
	Die beiden Bilder werden übereinander gelegt und durch das Aufteilen in zwei Bilder kann erzielt werden,
	dass das eine Bild schneller vorbeizieht als das andere.
	Damit das Ganze realistisch aussieht werden die Bilder mehrfach dargestellt, das heisst, dass sobald das Grass Bild zu Ende ist
	einfach noch ein Grass Bild angehängt wird. So sehen die Übergänge realistischer aus.
	Um dies zu erzielen braucht es für jede Bildposition einen x Wert der sich von Bildposition zu Bildposition um die Länge des Bildes
	unterscheidet.
*/
#pragma once
#include "SpriteSheet.h"
#include "Graphics.h"

class Background {

	Graphics* gfx;

	//	Eigentliche Hintergrund
	SpriteSheet* sprites;
	//	Grass
	SpriteSheet* grass;

	//	Grass und Hintergrund besitzen jeweils drei verschiedene x Werte
	double xScreen1, xScreen2, xScreen3;
	double xgScreen1, xgScreen2, xgScreen3;

public:

	Background(Graphics* gfx);
	~Background();

	//	Darstellen des Hintergrundes
	void draw();
	//	Aktualisieren des Hintergrundes
	void update(double speed);

};