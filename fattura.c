#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "include/fattura.h"

int add_linea(Fattura* f, DettaglioLinee* linea) {
	if (f->count >=f->capacity) {
		f->capacity*=2;

		DettaglioLinee* temp =
			realloc(f->d, f->capacity * sizeof(DettaglioLinee));

		f->d = temp;
	}

	f->d[f->count] = *linea;  // Scrittura nella posizione corrente
	f->count++;
	return 1;
}

Fattura* init_fattura(void) {
	Fattura *f = malloc(sizeof(Fattura));
	f->d = malloc(sizeof(DettaglioLinee));
	f->count=1;
	f->capacity=1;
	return f;
}

void print_fattura_elettronica(Fattura* f) {
	printf("\n=== CEDENTE/PRESTATORE ===\n");
	printf("P.IVA: %s%s\n", 
			f->cedente.dati_anagrafici.id_fiscale_iva.id_paese ? f->cedente.dati_anagrafici.id_fiscale_iva.id_paese : "",
			f->cedente.dati_anagrafici.id_fiscale_iva.id_codice ? f->cedente.dati_anagrafici.id_fiscale_iva.id_codice : "");
	printf("Denominazione: %s\n", f->cedente.dati_anagrafici.anagrafica.denominazione);
	printf("Sede: %s %s, %s %s (%s)\n",
			f->cedente.sede.indirizzo ? f->cedente.sede.indirizzo : "",
			f->cedente.sede.numero_civico ? f->cedente.sede.numero_civico : "",
			f->cedente.sede.cap ? f->cedente.sede.cap : "",
			f->cedente.sede.comune ? f->cedente.sede.comune : "",
			f->cedente.sede.provincia ? f->cedente.sede.provincia : "");

	printf("\n=== DATI GENERALI DOCUMENTO ===\n");
	printf("Tipo: %s\n", f->data.tipo_documento);
	printf("Numero: %s\n", f->data.numero);
	printf("Data: %s\n", f->data.data);
	printf("Divisa: %s\n", f->data.divisa);
	printf("Importo Totale: %.2f\n", f->data.importo_totale_documento);

	printf("\n=== CESSIONARIO/COMMITTENTE ===\n");
	//TODO

	printf("\n=== DETTAGLIO LINEE ===\n");
	for (int i = 1 ; i < f->count ; ++i) {
		printf("\nlinea%d\n",i);
		printf("  Descrizione: %s\n", f->d[i].descrizione);
		printf("  Quantità: %.2f\n", f->d[i].quantita);
		printf("  Prezzo Unitario: %.3f\n", f->d[i].prezzo_unitario);
		printf("  Prezzo Totale: %.2f\n", f->d[i].prezzo_totale);
		printf("  Aliquota IVA: %.2f%%\n", f->d[i].aliquota_iva);
	}
}
int check_importi(Fattura* f) {
	float t = 0;
	for (int i = 1 ; i < f->count ; ++i) {
		t+=f->d[i].prezzo_totale * (1+f->d[i].aliquota_iva/100);
	}
	// controllo solo sulla parte intera per evitare
	// difformità in caso di arrotondamenti
	if ( (int)t == (int)f->data.importo_totale_documento )
		return 1;
	else
		return 0;
}

