# Adatszerk3
Adatszerkezetek és Algoritmusok - 3. házi feladat
Szövegszerkesztő program szimulálása Rope
adatszerkezet segítségével (50 p)
A feladat egy szövegszerkesztő program szimulálása. A programhoz egy Rope adatszerkezet
készítése szükséges. Ezen felül a program tárolja a kurzor aktuális helyzetét, ami segíteni fogja a
bonyolultabb szerkesztéseket. A csúcsokat egy beágyazott Node osztállyal kell megvalósítani.
Ajánlott egy enum , vagy egy bool mezővel jelölni, hogy az aktuális Node levél, vagy közbenső
csúcs (vagy akár a Node osztályból leszármaztatni egy Leaf osztályt).
Rope (35 p)
A Rope egy olyan bináris fa, melynek a levelei karaktertömböket tárolnak, illetve egy unsigned
int súlyt, ami a karaktertömb hosszával egyenlő (a karaktertömb bármilyen STL tároló lehet).
Ennek a hossznak van egy maximuma, melynek értéke értelmes keretek között tetszőleges lehet,
legyen e feladatban az egy levélen tárolható karakterek száma három. A közbenső csúcsok
tárolják a bal részfájukban lévő levelek súlyának összegét.
Szövegszerkesztés (15 p)
A TextEditor szövegszerkesztő program egy Rope adatszerkezetből és néhány
segédváltozóból áll. Tárolni kell a kurzor aktuális indexét, illetve a kijelölés aktuális indexét (egy
kijelölés mindig a kurzor és egy másik index között jön létre). Ezen felül legyen egy vágólap is,
amire lehet másolni, így megvalósítva bonyolultabb műveleteket (ajánlott a vágólapot egy
std::string pufferrel kezelni).
Követelmények
Rope specifikációi
Legyen paraméter nélküli és paraméteres konstruktor is ( std::string paraméter). A
konstruktorban a szöveg elosztása a levelek között (így a felépített fastruktúra) tetszőleges
lehet (például lehet a szöveget három karakterenként felosztani, vagy lehet hosszfelezéssel
felépíteni a fát).
A Rope tárolja a benne lévő karakterek számát, amit az unsigned int Rope::length()
const függvény ad vissza. A hosszt O(1) időben kell karbantartani.
char Rope::index(const unsigned int) const visszaadja a kapott indexű karaktert.
static Rope Rope::concat(Rope& r1, Rope& r2) konkatenál két Rope -t. Ehhez létre kell
hozni egy új gyökérelemet, aminek a bal gyereke lesz az r1 gyökere, jobb gyereke az r2
gyökere. A visszaadott Rope tartalmazza r1, r2 tartalmát, az r1, r2 fák pedig üresek a
művelet után. Ennek a műveletnek a komplexitása O(1).
static std::pair<Rope, Rope> Rope::split(Rope&, const unsigned int) egy Rope -t
kettévág adott indexű karakternél. A visszaadott fák tartalmazzák a beadott Rope tartalmát,
ami üres lesz a művelet után. A vágásnak több esete is van, érdemes átgondolni a
lehetőségeket.
std::string Rope::report(unsigned int, unsigned int) const visszaadja a kapott két
index közötti szövegrészt.
A törlést és a beszúrást a TextEditor osztály fogja menedzselni a Rope::concat és a
Rope::split függvények segítségével.
Figyelj arra, hogy milyen operátorokra és konstruktorokra van szükséged a megvalósításhoz
(assignment operátor, copy-, move konstruktor). Amelyiket nem írod meg, azt delete -eld.
TextEditor specifikációi
Legyen paraméter nélkülis és paraméteres konstruktor is ( std::string paraméter).
unsigned int TextEditor::length() const visszaadja a szövegszerkesztőben lévő
szöveg hosszát (pontosabban a Rope mezőben lévő szöveg hosszát).
void TextEditor::stepLeft() eggyel balra lépteti a kurzort.
void TextEditor::stepRight() eggyel jobbra lépteti a kurzort.
void TextEditor::moveCursor(const unsigned int) a kapott indexre állítja a kurzort.
void TextEditor::select(const unsigned int) kijelöli a kurzor és a kapott index közötti
szövegrészt. A TextEditor osztály a kijelölésnél csak tárolja kurzortól különböző végének
indexét, a szöveget lekérni az adatszerkezetből elég akkor, amikor valamilyen műveletet is el
kell végezni vele. Ekkor egyrészt nincs felesleges fabejárás, másrészt könnyen tudjuk
vizsgálni, hogy éppen ki van-e jelölve valami (ugyanis üres kijelölésnél cursorIndex ==
selectionIndex ). Ezen felül a kurzor mozgatása a stepLeft, stepRight, moveCursor
függvényekkel megszünteti a kijelölést. Végül figyelj, hogy az egyes műveletek után (lásd
lentebb) mindig frissítsd a kijelölő index pozícióját is.
std::string TextEditor::report() const visszaadja az éppen kijelölt szövegrészt. Ha
nincs kijelölve semmi, akkor a függvény üres stringet ad vissza.
void TextEditor::insert(const std::string) az éppen kijelölt szövegrész helyére
beszúrja a kapott karaktertömböt. Ha nincs kijelölve semmi, akkor a kurzor aktuális
pozíciójára szúr be.
void TextEditor::remove() kitörli az éppen kijelölt szövegrészt. Ha nincs kijelölve semmi,
akkor a kurzortól jobbra lévő karaktert törli.
void TextEditor::ctrlC() a vágólapra másolja az éppen kijelölt szövegrészt. Ha nincs
kijelölve semmi, akkor a függvénynek nincs hatása.
void TextEditor::ctrlV() az éppen kijelölt szövegrész helyére beszúrja az utolsó lemásolt
szövegrészt. Ha nincs ilyen, akkor a függvénynek nincs hatása.
void TextEditor::ctrlX() kivágja az éppen kijelölt szövegrészt, illetve a vágólapra
másolja azt. Ha nincs kijelölve semmi, akkor a függvénynek nincs hatása.
void TextEditor::ctrlA() kijelöli az egész szöveget.
void TextEditor::ctrlD() a kijelölt szövegrészt megduplázza. Ha nincs kijelölve semmi,
akkor a függvénynek nincs hatása.
std::vector<unsigned int> TextEditor::ctrlF(const std::string) rákeres a kapott
karaktertömbre a szövegben és visszatér az összes előfordulás indexével. A keresést először
a kurzor utáni, majd a kurzor előtti részben végezzük el. A keresésre elegendő egy naiv
megoldást adni (tehát egy karaktertömböt kell létrehozni a kurzor utáni és kurzor előtti
szövegrész összefűzésével, majd ezen végigshiftelni a keresett karaktertömböt, egyesével
megnézve, hogy minden egyes karakter megegyezik-e).
Egyéb követelmények
Az elkészített struktúra meg kell, hogy feleljen a fenti leírásnak.
A megoldásnak le kell fordulnia a kiadott unit tesztekkel. Ehhez szükséges egy Rope és egy
TextEditor nevű osztály, illetve szükségesek a szövegszerkesztős műveletek.
Forduljon -Werror -Wall -Wextra -pedantic kapcsolókkal.
Ne legyen memóriaszivárgás, segfault és hasonlók.
A tesztek nem ellenőrzik az összes esetet az egyes műveleteknél, ennek megfelelően
érdemes a tesztektől függetlenül átgondolni minden lehetséges esetet, illetve a tesztek
pontszámai csak tájékoztató jellegűek.
A feladatot önállóan kell megoldani.
A unit teszteket nem szabad módosítani (pontosabban csak bővíteni lehet a tesztek
halmazát, ellenőrzés céljából). Ennek ellenére a fejlesztés közben érdemes inkrementálisan
haladni, azaz érdemes kikommentelni azon unit teszteket, amik még meg nem írt
függvényeket tesztelnek. Minden egyéb jellegű módosítás pontlevonással jár.
Az adatszerkezet felfogható az std::string alternatívájaként. Ennek az elvnek megfelelően
std::string belső használata a Rope adatszerkezetben karaktertömb helyett komoly
pontlevonással jár.
A szövegszerkesztős műveleteket (illetve egyes Rope függvényeket) a Rope függvényeinek
használatával kell megírni ( concat , split és report mindenre elég), egyéb esetben nem
adható maximális pontszám.
Plusz pontos kiegészítések
Bonyolultabb string matching algoritmus (5-10 p)
A keresés során használt naiv megközelítés komplexitása igen előnytelen. A javított
komplexitástól függően egy bonyolultabb string matching algoritmus implementásáért pluszpont
jár.
Fa kiegyensúlyozása (10 p)
Természetesen a különböző műveletek során a Rope adatszerkezet is kiegyensúlyozatlanná
válik. Egy könnyű kiegyensúlyozó algoritmus:
Minden csúcshoz hozzárendelünk egy mélységet. A levelek mélysége 0, majd felfelé haladva
minden Node mélysége a legmélyebb gyerekének mélysége plusz 1. Egy n mélységú Rope
kiegyensúlyozott, hogyha a benne tárolt szöveg hossza legalább Fn+2
, ahol Fn
az n-edik
Fibonacci szám. Tehát egy 1 mélységű Rope -ban hosszának legalább 2-nek kell lennie.
Fontos megjegyezni, hogy egy kiegyensúlyozott fában lehetnek kiegyensúlyozatlan részfák.
Vegyünk egy n+1 méretű tömböt, illetve a Fibonacci sorozat első n+1 elemét. A tömb k-adik
eleme feleljen meg az [Fk+2
,Fk+3
) intervallumnak.
Balról jobbra végigiteráljuk a leveleket és a hosszuk alapján beszúrjuk őket a tömb megfelelő
indexére. Tegyük fel, hogy egy beszúrandó fa hossza az [Fk+2
,Fk+3
) intervallumban van, ami
alapján a k-adik indexre kéne beszúrni. Ha a tömb összes k-nál kisebb vagy egyenlő indexe
üres, akkor a fát beszúrjuk a k-adik indexre. Ha ez nem teljesül, akkor konkatenáljuk a 0,…,k
indexen lévő fákat (balról jobbra, hogy a sorrend megmaradjon), majd az eredményhez
konkatenáljuk a beszúrandó fát. Ezek után a hossz újraszámolása után beszúrjuk a
megfelelő indexre.
Az algoritmus utolsó lépéseként balról jobbra konkatenáljuk a tömbben lévő fákat.
Természetesen van lehetőség magasság alapú kiegyensúlyozásra is, önálló utánajárás után
lehetőség van másmilyen kiegyensúlyozás implementására is (kivéve az eddig tanultakat).
Undo és redo (10 p)
void TextEditor::ctrlZ() függvény visszavonja az utolsó műveletet.
void TextEditor::ctrlY() függvény megismétli az utolsó műveletet.
Beadási határidő 2018. december 5. 23:59:59
