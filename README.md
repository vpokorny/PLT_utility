## UVOD

Prave pred sebou mate projekt s utilitami pro data ve formatu .plt s trojuhelnikovou 2D nestrukturovanou siti. Soucasti jsou zatim tyto tri programy:
1. ProvedRez:
Program __ProvedRez__ provede vertikalni nebo horizontalni rez skrz _nestrukturovanou trojuhlenikovou sit_, kterou je dobre umistit ve vstupnim adresari __vstupni_data__ ve formatu _.plt_, rez jakozto vysledek je ulozen tak, aby bylo mozne jej vizualizovat programem [Gnuplot](http://gnuplot.info).

2. PLT2VTK:
Utilita, ktera slouzi ke konversi mezi formatem _.plt_ a formatem _.vtk_. Dosazovana souradnice pro ulozeni do _.vtk_ je __Z = 0.0__.

3. VKT2PLT:
Utilita, ktera slouzi k inversni konversi nez vyse uvedena utilita. Tedy nacteni nestrukturovane trojuhelnikove site probehne z formatu _.vtk_ a sit je exportovana do formatu _.plt_.

## Postup instalace:
1. Klonovani repozitare:
	* Prejdete do slozky, kde chcete mit ulozena zdrojova data (Dobra volba muze byt _/opt_.). Zde si naklonujete repozitar prikazem:

	```bash
	git clone https://github.com/vpokorny/PLT_utility.git
	```

2. Priprava adresaru:
	* Prejdete do slozky _PLT_utility_ a vytvorte slozku _bin_ nasledujicim prikazy:

		```bash
		cd PLT_utility
		mkdir bin
		```

3. Kompilace:
	* Ve slozce _PLT_utility_ je vytvoreny soubor __Makefile__, ktery slouzi ke zkompilovani programu a vytvoreni spustitelnych souboru v adresari _PLT_utility/bin_. Kompilaci provedeme prikazem:

		```bash
		make
		```

	* Nyni se v adresari _PLT_utility/bin_ vytvorily spustitelne soubory __ProvedRez__, __PLT2VTK__ a __VTK2PLT__. Jejich volani ma specifickou strukturu pro spravnou funkcnost programu je potreba ji dodrzet!!!

## Volani spustitelnych souboru:
#### ProvedRez
1. Program ocekava vstup z prikazove radky takto:

	```bash
	./ProvedRez "Cesta/Nazev PLT souboru" "vertikalni rez X, nebo Horizontalni rez Y"="Hodnota X nebo Y" "Cesta/Nazev Vystupniho Souboru"*
	```

2. Priklad: Mam soubor __solution4000.plt__ ve stejne slozce jako je spustitelny soubor __ProvedRez__ a chci provest vertikalni rez pro _x=0.01_. Vystupni soubor chci aby se jmenoval __solution4000-X-0.01.dat__. Toto provedu zadanim prikazu:

	```bash
	./ProvedRez solution4000.plt X=0.01 solution4000-X-0.01.dat*
	```

3. Poznamka: Pokud se chcete takovemu zadavani vyhnout, pak je v adresari _PLT_utility/skripty_ pripraven skript __ProvedSekvenciRezu.sh__, kterym je mozne provest vicero rezu automatizovane s tim, ze je potreba zachovat adresarovou strukturu priblizne takto

- ProvedRez
	* src _(zdrojove kody)_
	* include _(hlavickove soubory)_
	* vstupni_data _(vase vstupni .plt soubory)_
	* bin _(adresar s binarkami)_
	* skripty _(zde je ulozen skript ProvedRez.sh)_

	zbytek bude dotvoren skriptem. Skript je treba menit pouze v rozsahu _For_ cyklu a nazvu vstupnich dat a pozadovanych rezu. Snaha byla udelat to tak srozumitelne, ze nebude prakticky potreba k tomu nic dodavat.

4. Vystupni soubory:
- Vystupni soubory, pokud pouzijete skript, jsou ulozeny v adresari _vystup_gnuplot_. Jednotlive vysledky lze vizualizovat programem [Gnuplot](http://gnuplot.info).

#### PLT2VTK, VTK2PTL
1. Tyto utility maji stejnou volaci strukturu. Volani je nastaveno takto:

	```bash
	./PLT2VTK "Input Filename" "Output Filename"
	./VTK2PLT "Input Filename" "Output Filename"
	```

## Zpetna vazba:
Pokud se v programu vyskytne chyba, nebo mate napad na zlepseni, pak je mozne me kontaktovat:
- Jmeno: Vaclav Pokorny
- Email: pokorny.vena@gmail.com

#### Necht je Vam program uzitecny.
