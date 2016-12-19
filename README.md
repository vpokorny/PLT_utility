## UVOD

Prave pred sebou mate projekt, kde je vytvoren program, ktery provede rez skrz _nestrukturovanou trojuhlenikovou sit_, kterou je dobre umistit ve vstupnim adresari __vstupni_data__ ve formatu _.plt_, rez jakozto vysledek je ulozen tak, aby bylo mozne jej vizualizovat programem [Gnuplot](http://gnuplot.info).

## Postup instalace:
1. Klonovani repozitare:
* Prejdete do slozky, kde chcete mit ulozena zdrojova data (Dobra volba muze byt _/opt_.). Zde si naklonujete repozitar prikazem:

	```bash
	git clone https://github.com/vpokorny/ProvedRez.git
	```

2. Priprava adresaru:
	* Prejdete do slozky _ProvedRez_ a vytvorte slozku _bin_ nasledujicim prikazy:

		```bash
		cd ProvedRez
		mkdir bin
		```

3. Kompilace:
	* Prejdete do slozky _src_ v adresari _ProvedRez_ prikazem:

		```bash
		cd src
		```

	* Zde je vytvoreny soubor __Makefile__, ktery slouzi ke zkompilovani programu a vytvoreni spustitelneho souboru __ProvedRez__ v adresari _ProvedRez/bin_. Kompilaci provedem prikazem:

		```bash
		make
		```

	* Nyni se v adresari _ProvedRez/bin_ vytvoril spustitelny soubor __ProvedRez__. Jeho volani ma specifickou strukturu pro spravnou funkcnost programu je potreba ji dodrzet!!!

## Volani programu:
1. Program ocekava vstup z prikazove radky takto:

	```bash
	./ProvedRez "Cesta/Nazev PLT souboru" "vertikalni rez X, nebo Horizontalni rez Y"="Hodnota X nebo Y" "Cesta/Nazev Vystupniho Souboru"*
	```

2. Priklad: Mam soubor __solution4000.plt__ ve stejne slozce jako je spustitelny soubor __ProvedRez__ a chci provest vertikalni rez pro _x=0.01_. Vystupni soubor chci aby se jmenoval __solution4000-X-0.01.dat__. Toto provedu zadanim prikazu:

	```bash
	./ProvedRez solution4000.plt X=0.01 solution4000-X-0.01.dat*
	```

3. Poznamka: Pokud se chcete takovemu zadavani vyhnout, pak je v adresari _ProvedRez/skripty_ pripraven skript __ProvedSekvenciRezu.sh__, kterym je mozne provest vicero rezu automatizovane s tim, ze je potreba zachovat adresarovou strukturu priblizne takto

- ProvedRez
	* src _(zdrojove kody)_
	* vstupni_data _(vase vstupni .plt soubory)_
	* bin _(adresar s binarkami)_
	* skripty _(zde je ulozen skript ProvedRez.sh)_

zbytek bude dotvoren skriptem. Skript je treba menit pouze v rozsahu _For_ cyklu a nazvu vstupnich dat a pozadovanych rezu. Snaha byla udelat to tak srozumitelne, ze nebude prakticky potreba k tomu nic dodavat.

## Vystupni soubory:
- Vystupni soubory, pokud pouzijete skript, jsou ulozeny v adresari _vystup_gnuplot_. Jednotlive vysledky lze vizualizovat programem [Gnuplot](http://gnuplot.info).

## Zpetna vazba:
Pokud se v programu vyskytne chyba, nebo mate napad na zlepseni, pak je mozne me kontaktovat:
- Jmeno: Vaclav Pokorny
- Email: pokorny.vena@gmail.com

#### Necht je Vam program uzitecny.
