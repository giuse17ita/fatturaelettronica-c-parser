#ifndef STRUCTURE_H
#define STRUCTURE_H

typedef struct {
    char* id_paese;
    char* id_codice;
} IdFiscaleIVA;

typedef struct {
    char* denominazione;
    char* nome;
    char* cognome;
    char* titolo;
    char* cod_eori;
} Anagrafica;

typedef struct {
    IdFiscaleIVA id_fiscale_iva;
    char* codice_fiscale;
    Anagrafica anagrafica;
    char* albo_professionale;
    char* provincia_albo;
    char* numero_iscrizione_albo;
    char* data_iscrizione_albo;
    char* regime_fiscale;
} DatiAnagraficiCedentePrestatore;

typedef struct {
    char* indirizzo;
    char* numero_civico;
    char* cap;
    char* comune;
    char* provincia;
    char* nazione;
} Sede;

typedef struct {
    char* telefono;
    char* fax;
    char* email;
} Contatti;

typedef struct {
    char* ufficio;
    char* numero_rea;
    double capitale_sociale;
    char* socio_unico;
    char* stato_liquidazione;
} IscrizioneREA;

typedef struct {
    DatiAnagraficiCedentePrestatore dati_anagrafici;
    Sede sede;
    Sede stabile_organizzazione;
    IscrizioneREA iscrizione_rea;
    Contatti contatti;
    char* riferimento_amministrazione;
} CedentePrestatore;

typedef struct {
    IdFiscaleIVA id_fiscale_iva;
    char* codice_fiscale;
    Anagrafica anagrafica;
} DatiAnagraficiCessionarioCommittente;

typedef struct {
    DatiAnagraficiCessionarioCommittente dati_anagrafici;
    Sede sede;
    Sede stabile_organizzazione;
} CessionarioCommittente;

typedef struct {
    char* tipo_documento;
    char* divisa;
    char* data;
    char* numero;
    double importo_totale_documento;
    double arrotondamento;
    char** causale;
    int causale_count;
    char* art73;
} DatiGeneraliDocumento;

typedef struct {
    int numero_linea;
    char* tipo_cessione_prestazione;
    char* descrizione;
    double quantita;
    char* unita_misura;
    char* data_inizio_periodo;
    char* data_fine_periodo;
    double prezzo_unitario;
    double prezzo_totale;
    double aliquota_iva;
    char* ritenuta;
    char* natura;
    char* riferimento_amministrazione;
} DettaglioLinee;

typedef struct {
    double aliquota_iva;
    char* natura;
    double spese_accessorie;
    double arrotondamento;
    double imponibile_importo;
    double imposta;
    char* esigibilita_iva;
    char* riferimento_normativo;
} DatiRiepilogo;

typedef struct {
    DettaglioLinee* linee;
    int linee_count;
    DatiRiepilogo* riepilogo;
    int riepilogo_count;
} DatiBeniServizi;

typedef struct {
    char* beneficiario;
    char* modalita_pagamento;
    char* data_riferimento_termini_pagamento;
    int giorni_termini_pagamento;
    char* data_scadenza_pagamento;
    double importo_pagamento;
    char* iban;
    char* bic;
} DettaglioPagamento;

typedef struct {
    char* condizioni_pagamento;
    DettaglioPagamento* dettagli;
    int dettagli_count;
} DatiPagamento;


/**
 * @internal estrae il testo del nodo
 *
 * @param node parte di xml dove estrarre il testo
 * @return *char
 */
char* get_xml_content(xmlNode* node);

/**
 * @internal Cerca un nodo del documento xml
 *
 * @param root xml dove cercare un nodo
 * @param name nome del nodo da cercare
 * @return nodo xml trovato
 */
xmlNode* find_node(xmlNode* root, const char* name);
/**
 * @internal Parsing partita iva
 *
 * @param node parte di xml dove estrarre i dati
 * @return struct @ref IdFiscaleIVA
 */
IdFiscaleIVA parse_id_fiscale_iva(xmlNode* node);
/**
 * @brief Parsing anagrafica
 *
 * @param node parte di xml dove estrarre i dati
 * @return struct @ref Anagrafica
 */
Anagrafica parse_anagrafica(xmlNode* node);
/**
 * @brief Parsing sede
 *
 * @param node parte di xml dove estrarre i dati
 * @return struct @ref Sede
 */
Sede parse_sede(xmlNode* node);
/**
 * @brief Parsing dei dati anagrafici,
 *
 * @param node parte di xml dove estrarre i dati
 * @return struct @ref DatiAnagraficiCedentePrestatore
 */
DatiAnagraficiCedentePrestatore parse_dati_anagrafici_cedente(xmlNode* node);
/**
 * @brief dal nodo cedente o prestatore fa il parsin delle strutture necessarie
 *
 * @param node parte di xml dove estrarre il cedente o prestatore
 * "CedentePrestatore" o "CessionarioCommittente"
 * @return struct @ref CedentePrestatore
 */
CedentePrestatore parse_cedente_prestatore(xmlNode* node);
/**
 * @brief Parsing dei generali documento:
 *
 * @param node parte di xml dove estrarre i dati
 * @return struct @ref DatiGeneraliDocumento
 */
DatiGeneraliDocumento parse_dati_generali_documento(xmlNode* node);
/**
 * @brief Parsing dettaglio linea singola
 * @param node parte di xml dove estrarre i dati
 * @return struct @ref DettaglioLinee
 */
DettaglioLinee parse_dettaglio_linee(xmlNode* node);

#endif
