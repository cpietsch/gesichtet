Bangface
============

##General Settings
- die GUI kann man durch "h" anzeigen und ausblenden, ausgeblendet läuft das programm schneller
- Test Video: läd ein video aus dem data ordner names test.mp4 und lässt das tracking darauf laufen. nach klick auf reinitialize gehts los.
- Horizontal: für die um 90* nach rechts gekippte variante
- Debug View: zeigt das raw face tracking (rechteckig) und die gesmoothe variante (rund) sowie oben rechts das raw image zum tracking. hier sieht man auch wie sich image scale, horizontal und crop top auswirken 

##FaceDetector
- Cascade Scale Factor: um so niedriger der wert um so genauer präziser werden gesichter erkannt, einher vermindert sich auch die performance. ein wert zwischen 1.1 und 1.2 ist opti
- Min Face: die größe des kleinsten zu erkennenden gesichts, performance: nicht zu klein setzen
- Crop Top: im debug view zu sehen, die obere grenze des zu trackenden kamera bereichs
- Mode: Algorithmus zum erkennen der gesichter, 0=BOOST, 1=CANNY...
- Neighbours: ab wievielen erkannten blobs ist es ein gesicht
- Image Scale: vorverkleinerung des kamera bild, um so kleiner um so schneller das tracking aber auch um so ungenauer

##BubleManager
- Line Force: wie langsam ziehen die einzelnen wörter sich hintereinander her

##Installation

- how to set up osx for the installation: http://vormplus.be/blog/article/configuring-mac-os-x-for-interactive-installations
