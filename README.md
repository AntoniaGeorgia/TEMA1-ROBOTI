Documentație tema 1
SAVA ANTONIA-GEORGIA
GRUPA 363


Cerințele :
•	4 LED-uri: Acestea sunt folosite pentru a simula progresul procesului de încărcare. Fiecare LED reprezintă un anumit procent de încărcare (de exemplu, 25%, 50%, 75%, 100%).
•	1 LED RGB: Acest LED indică starea sistemului:
o	Verde: Sistemul este liber, pregătit pentru o nouă încărcare.
o	Roșu: Sistemul este ocupat, adică procesul de încărcare este în desfășurare.
•	2 Butoane:
o	Butonul de Start: Inițiază procesul de încărcare atunci când este apăsat.
o	Butonul de Stop: Oprește procesul de încărcare în orice moment și resetează sistemul.
•	Rezistoare: Acestea sunt utilizate pentru a proteja LED-urile și butoanele de curentul excesiv.
o	6 rezistoare de 220Ω/330Ω sunt conectate în serie cu LED-urile și LED-ul RGB.
o	2 rezistoare de 1kΩ sunt conectate la butoanele de control pentru a preveni fluctuațiile de curent.
•	Breadboard și fire de legătură pentru conectarea componentelor între ele și cu placa Arduino.
3. Componente Utilizate
1.	Placă Arduino: Reprezintă "creierul" sistemului, unde este încărcat și rulează codul de control al LED-urilor și butoanelor.
2.	LED-uri (4 ): Folosite pentru a indica progresul încărcării.
o	Conectate pe pini digitali ai Arduino (pini 10, 9, 8, 7).
o	Fiecare LED este asociat cu un procent de încărcare.
o	LED-urile sunt controlate prin funcția digitalWrite() din cod.
3.	LED RGB (1 ): Este folosit pentru a indica starea sistemului (liber sau ocupat).
o	Conectat pe trei pini ai Arduino (pini 6 pentru roșu, 5 pentru verde, 4 pentru albastru).
o	Combinațiile de culori indică starea sistemului: verde pentru liber, roșu pentru ocupat.
4.	Butoane (2 ):
o	Butonul de Start: Conectat la pinul digital 3, folosit pentru a iniția procesul de încărcare.
o	Butonul de Stop: Conectat la pinul digital 2, folosit pentru a opri încărcarea și a reseta sistemul.
o	Ambele butoane sunt conectate cu rezistoare de 1kΩ pentru stabilitatea semnalului și prevenirea fluctuațiilor necontrolate (debouncing).
5.	Rezistoare:
o	6x rezistoare de 220Ω/330Ω: Conectate în serie cu LED-urile și LED-ul RGB pentru a limita curentul și a preveni deteriorarea acestora.
o	2x rezistoare de 1kΩ: Conectate la butoanele de start și stop pentru a stabiliza intrările digitale de pe placa Arduino.
6.	Breadboard: Utilizată pentru a conecta toate componentele împreună fără a fi nevoie de lipire. Aceasta permite un montaj rapid și ușor de modificat pentru testare și dezvoltare.
7.	Fire de legătură : Folosite pentru a conecta toate componentele de pe breadboard la placa Arduino.
Diagrama Circuitului
1.	LED-uri:
o	Fiecare LED este conectat la un pin digital al Arduino (pini 10, 9, 8, 7) prin intermediul unui rezistor de 220Ω/330Ω.
o	Catodul fiecărui LED este conectat la pământ (GND).
2.	LED RGB:
o	Pinii roșu, verde și albastru ai LED-ului RGB sunt conectați la pinii digitali 6, 5, și 4 ai Arduino, prin rezistoare de 220Ω/330Ω.
o	Catodul comun al LED-ului RGB este conectat la GND.
3.	Butoane:
o	Un capăt al butonului de Start este conectat la pinul digital 3 și la un rezistor de 1kΩ, iar celălalt capăt este conectat la GND.
o	Un capăt al butonului de Stop este conectat la pinul digital 2 și la un rezistor de 1kΩ, iar celălalt capăt este conectat la GND.
4.	Breadboard:
o	Toate componentele sunt montate pe breadboard, iar legăturile dintre acestea și Arduino sunt realizate cu fire de conexiune 
Codul încărcat pe placa Arduino controlează starea LED-urilor și răspunde la acțiunile butoanelor. Iată o prezentare succintă a funcționalităților:
•	Butonul de Start inițiază procesul de încărcare, aprinzând LED-urile pe rând pentru a simula progresul.
•	Butonul de Stop oprește imediat procesul de încărcare și stinge toate LED-urile.
•	LED-ul RGB indică starea curentă:
o	Verde: Sistemul este liber.
o	Roșu: Sistemul este ocupat și procesul de încărcare este în desfășurare.
•	1. Gestionarea Butoanelor: Start și Stop

•	Butonul de Start (BSTART)
Pinul corespunzător butonului de Start este definit ca intrare digitală cu rezistență internă de pull-up activată (INPUT_PULLUP), ceea ce înseamnă că, în mod implicit, butonul va citi HIGH, iar când este apăsat, va citi LOW.
o	Explicație:
	Atunci când butonul este apăsat (când digitalRead(BSTART) este LOW), și procesul de încărcare nu este deja activ (!chargingActive), variabila chargingActive devine true, semnalând că încărcarea a început.
	Funcția incarcare() este apelată pentru a simula procesul de încărcare.
	După finalizarea procesului de încărcare, variabila chargingActive este resetată la false, indicând faptul că sistemul este din nou pregătit.
Butonul de Stop (BSTOP)
•	Rol: Oprește procesul de încărcare în orice moment și resetează starea sistemului, inclusiv oprirea tuturor LED-urilor.
Pinul corespunzător butonului de Stop este de asemenea definit ca INPUT_PULLUP, iar starea butonului este citită în timpul fiecărei bucle.
o	Explicație:
	Când butonul de Stop este apăsat (digitalRead(BSTOP) == LOW), funcția turnOffAllLEDs() este apelată, care stinge toate LED-urile, inclusiv LED-ul RGB.
	Variabila chargingActive este setată la false, ceea ce resetează starea procesului de încărcare și permite pornirea unui nou ciclu de încărcare după apăsarea butonului de Start.
2. Gestionarea LED-urilor)
•	Rol: Cele 4 LED-uri sunt folosite pentru a simula progresul încărcării în 4 etape, fiecare LED reprezentând un procent de încărcare: 25%, 50%, 75%, 100% .
o	Explicație:
	În funcția incarcare(), fiecare LED este aprins pe rând folosind digitalWrite() cu o întârziere de 1 secundă între ele (delay(1000)).
	LED-ul roșu al RGB-ului este aprins la începutul funcției pentru a indica faptul că sistemul este în proces de încărcare.
	După ce toate LED-urile s-au aprins (simulând încărcarea completă), LED-ul roșu este stins și LED-ul verde este reaprins pentru a semnala că procesul de încărcare este finalizat.
LED-ul RGB pentru Indicația Stării Sistemului
•	Rol: LED-ul RGB este folosit pentru a indica dacă sistemul este liber sau ocupat:
o	Verde: Sistemul este pregătit pentru o nouă încărcare (stare liberă).
o	Roșu: Sistemul este ocupat, adică încărcarea este în curs.
o	Explicație:
	LED-ul RGB utilizează trei pini diferiți pentru a controla culorile roșu (pin 6), verde (pin 5) și albastru (pin 4). In cazul nostru, doar culorile roșu și verde sunt folosite:
	Roșu: Apare în timpul procesului de încărcare (încărcare activă).
	Verde: Apare atunci când sistemul este pregătit pentru o nouă încărcare sau după ce încărcarea s-a terminat.
3. Oprirea LED-urilor (Resetare la Apăsarea Butonului de Stop)
Pentru a opri toate LED-urile atunci când butonul de Stop este apăsat, am creat funcția turnOffAllLEDs(). Această funcție resetează toate LED-urile la starea LOW (oprit).
Explicație:
•	Când funcția este apelată (prin apăsarea butonului de Stop), toate LED-urile folosite pentru simularea încărcării (led1, led2, led3, led4) și LED-ul roșu al RGB-ului sunt oprite.
•	LED-ul verde este reaprins pentru a indica faptul că sistemul este liber și pregătit pentru o nouă operațiune.
•	Schema electrica (WOKWY) :
 
![Uploading image.png…]()


•	Poze ale setup ului fizic :

 ![image](https://github.com/user-attachments/assets/a559f651-fad0-4ba4-9a7e-9fc4e3dca557)

 ![image](https://github.com/user-attachments/assets/0298ac41-9560-492b-8c6b-6b3fd9667e68)
![image](https://github.com/user-attachments/assets/47216617-f817-4657-bd79-d63cbb403c7f)


 
