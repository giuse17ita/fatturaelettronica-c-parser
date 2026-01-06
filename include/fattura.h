#ifndef FATTURA_H
#define FATTURA_H

#include "structure.h"

/**
 * @brief è possibile considerarlo quasi un oggetto
 * count e capacity sono variabili per l'allocazione
 * dinamica dei @ref DettaglioLinee
 *
 */
typedef struct {
	CedentePrestatore cedente;
	CessionarioCommittente cessionario;
	DatiGeneraliDocumento data;
	size_t count;
	size_t capacity;
	DettaglioLinee *d;
} Fattura;

/**
 *
 * @brief allocazione dinamica array di DettaglioLinee
 *
 * @return 1 if ok
 */
int add_linea(Fattura* f, DettaglioLinee* linea);

/**
 *
 * @brief alloca memoria per @ref Fattura
 * e inizializza i contatori per i @ref DettaglioLinee
 *
 * @return f 
 */
Fattura* init_fattura(void);
/**
 * @brief Parse completo di una fattura elettronica in 
 * formato XML
 * @ref freeDoc per liberare la memoria
 * @param filename is path to file
 * @param doc for mem alloc, remember to free
 * @return 1 if ok
 */
Fattura* parse_fattura_elettronica(const char* filename,xmlDocPtr* doc);
/**
 * @brief libera la memoria
 *
 * @param doc
 */
void freeDoc(xmlDocPtr doc);
/**
 * @brief stampa su terminale tutti i dati della fattura
 *
 * @param f
 */
void print_fattura_elettronica(Fattura* f);
/**
 * @brief controlla gli importi delle righe del documento,
 * e le confronta con il totale
 *
 * @param f
 * @return 1 if ok
 */
int check_importi(Fattura* f);

#endif
