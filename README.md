Calcolatori Elettronici—Prova di programmazione in C 24 gennaio 2022

Si vuole realizzare una variante interattiva del gioco dell’impiccato, 
agiocatore singolo. In questo gioco, il giocatore deve indovinare una parola, 
inserendo un carattere per volta, avendo a disposizione un numero limitato di 
tentativi. Per ciascuna parola, è possibile fornire dei suggerimenti, ossia un 
numero arbitrario di caratteri della parola già inseriti.
 
Il gioco funziona a turni: ogni turno richiede al giocatore di indovinare una 
parola differente. Il numero di parole in una partita non è definito a priori. 
Ogni volta che viene inserito un carattere non presente nella parola, il 
giocatore perde una“vita”. Se viene indovinata la parola del turno, si 
guadagnano un certo numero di“vite”. 

Il gioco è quindi configurabile: il programma accetta in input (come unico 
parametro obbligatorio) il percorso ad un file di testo nel formato: pAroLa;n 
in cui ogni riga rappresenta un turno.  In ciascuna riga, prima del carattere 
‘;’ si trova la parola da indovinare. Dopo il ‘;’ si trova il numero di 
tentativi aggiuntivi (“vite”) che si guadagnano qualora la parola sia stata 
indovinata (un numero intero positivo). Si facciariferimento al file config.txt 
fornito per un esempio di file di configurazione. Le parole da indovinare, nel 
file di configurazione, hanno alcuni caratteri maiuscoli: questi sono i
suggerimenti, ossia i caratteri che vengono automaticamente inseriti e resi 
visibili all’inizio del turno. 


Il programma da realizzare quindi, deve seguire i seguenti passi:

	1. Il file di configurazione viene analizzato ed i turni di gioco 
	vengono caricati in memoria (in una struttura dati a scelta dello 
	studente);
	
	2. Viene mostrata la parola, sostituendo ai caratteri in minuscolo dei
	trattini bassi (rispetto all’esempio precedente, verrà mostrato:“_A__L_”);

	3. Il giocatore inserisce un input da tastiera: se vengono inseriti più
	caratteri, soltanto il primo sarà considerato come lettera da verificare;
	
	4. Se la lettera inserita è tra quelle da indovinare, viene aggiunta 
	all’insieme delle lettere indovinate (ad esempio, se il giocatore digita
	‘p’o‘P’, verrà mostrato “PA__L_”);
	
	5. Se la lettera inserita non è tra quelle da indovinare, o se è una
	lettera già indovinata in precedenza, si perde un punto vita;
	
	6. Se i punti vita sono terminati, il giocatore perde la partita;
	
	7. Se la parola è stata indovinata, viene aggiunto n ai punti vita e si 
	passa al turno successivo (ripartendo dal punto2);
	
	8. Quando sono state indovinate tutte le parole, il giocatore ha vinto la 
	partita.


Per semplicità, si assuma che il contenuto del file di configurazion è ben 
formato, ovvero senza errori: non è necessario effettuare alcun controllo sulla 
correttezza del formato del file di configurazione.
