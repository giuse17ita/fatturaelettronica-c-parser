#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "include/structure.h"
#include "include/fattura.h"


char* get_xml_content(xmlNode* node) {
	if (node == NULL) return NULL;
	xmlChar* content = xmlNodeGetContent(node);
	if (content == NULL) return NULL;
	char* result = strdup((char*)content);
	xmlFree(content);
	return result;
}

xmlNode* find_node(xmlNode* root, const char* name) {
	if (root == NULL) return NULL;
	for (xmlNode* node = root; node; node = node->next) {
		if (node->type == XML_ELEMENT_NODE && strcmp((char*)node->name, name) == 0) {
			return node;
		}
		xmlNode* found = find_node(node->children, name);
		if (found) return found;
	}
	return NULL;
}

IdFiscaleIVA parse_id_fiscale_iva(xmlNode* node) {
	IdFiscaleIVA id = {0};
	if (node == NULL) return id;

	for (xmlNode* cur = node->children; cur; cur = cur->next) {
		if (cur->type == XML_ELEMENT_NODE) {
			if (strcmp((char*)cur->name, "IdPaese") == 0) {
				id.id_paese = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "IdCodice") == 0) {
				id.id_codice = get_xml_content(cur);
			}
		}
	}
	return id;
}

Anagrafica parse_anagrafica(xmlNode* node) {
	Anagrafica ana = {0};
	if (node == NULL) return ana;

	for (xmlNode* cur = node->children; cur; cur = cur->next) {
		if (cur->type == XML_ELEMENT_NODE) {
			if (strcmp((char*)cur->name, "Denominazione") == 0) {
				ana.denominazione = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "Nome") == 0) {
				ana.nome = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "Cognome") == 0) {
				ana.cognome = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "Titolo") == 0) {
				ana.titolo = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "CodEORI") == 0) {
				ana.cod_eori = get_xml_content(cur);
			}
		}
	}
	return ana;
}

Sede parse_sede(xmlNode* node) {
	Sede sede = {0};
	if (node == NULL) return sede;

	for (xmlNode* cur = node->children; cur; cur = cur->next) {
		if (cur->type == XML_ELEMENT_NODE) {
			if (strcmp((char*)cur->name, "Indirizzo") == 0) {
				sede.indirizzo = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "NumeroCivico") == 0) {
				sede.numero_civico = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "CAP") == 0) {
				sede.cap = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "Comune") == 0) {
				sede.comune = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "Provincia") == 0) {
				sede.provincia = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "Nazione") == 0) {
				sede.nazione = get_xml_content(cur);
			}
		}
	}
	return sede;
}

DatiAnagraficiCedentePrestatore parse_dati_anagrafici_cedente(xmlNode* node) {
	DatiAnagraficiCedentePrestatore dati = {0};
	if (node == NULL) return dati;

	for (xmlNode* cur = node->children; cur; cur = cur->next) {
		if (cur->type == XML_ELEMENT_NODE) {
			if (strcmp((char*)cur->name, "IdFiscaleIVA") == 0) {
				dati.id_fiscale_iva = parse_id_fiscale_iva(cur);
			} else if (strcmp((char*)cur->name, "CodiceFiscale") == 0) {
				dati.codice_fiscale = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "Anagrafica") == 0) {
				dati.anagrafica = parse_anagrafica(cur);
			} else if (strcmp((char*)cur->name, "AlboProfessionale") == 0) {
				dati.albo_professionale = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "ProvinciaAlbo") == 0) {
				dati.provincia_albo = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "NumeroIscrizioneAlbo") == 0) {
				dati.numero_iscrizione_albo = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "DataIscrizioneAlbo") == 0) {
				dati.data_iscrizione_albo = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "RegimeFiscale") == 0) {
				dati.regime_fiscale = get_xml_content(cur);
			}
		}
	}
	return dati;
}

CedentePrestatore parse_cedente_prestatore(xmlNode* node) {
	CedentePrestatore cedente = {0};
	if (node == NULL) return cedente;

	for (xmlNode* cur = node->children; cur; cur = cur->next) {
		if (cur->type == XML_ELEMENT_NODE) {
			if (strcmp((char*)cur->name, "DatiAnagrafici") == 0) {
				cedente.dati_anagrafici = parse_dati_anagrafici_cedente(cur);
			} else if (strcmp((char*)cur->name, "Sede") == 0) {
				cedente.sede = parse_sede(cur);
			} else if (strcmp((char*)cur->name, "StabileOrganizzazione") == 0) {
				cedente.stabile_organizzazione = parse_sede(cur);
			}
		}
	}
	return cedente;
}

DatiGeneraliDocumento parse_dati_generali_documento(xmlNode* node) {
	DatiGeneraliDocumento dati = {0};
	if (node == NULL) return dati;

	for (xmlNode* cur = node->children; cur; cur = cur->next) {
		if (cur->type == XML_ELEMENT_NODE) {
			if (strcmp((char*)cur->name, "TipoDocumento") == 0) {
				dati.tipo_documento = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "Divisa") == 0) {
				dati.divisa = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "Data") == 0) {
				dati.data = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "Numero") == 0) {
				dati.numero = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "ImportoTotaleDocumento") == 0) {
				char* content = get_xml_content(cur);
				if (content) {
					dati.importo_totale_documento = atof(content);
					free(content);
				}
			}
		}
	}
	return dati;
}

DettaglioLinee parse_dettaglio_linee(xmlNode* node) {
	DettaglioLinee linea = {0};
	if (node == NULL) return linea;

	for (xmlNode* cur = node->children; cur; cur = cur->next) {
		if (cur->type == XML_ELEMENT_NODE) {
			if (strcmp((char*)cur->name, "NumeroLinea") == 0) {
				char* content = get_xml_content(cur);
				if (content) {
					linea.numero_linea = atoi(content);
					free(content);
				}
			} else if (strcmp((char*)cur->name, "Descrizione") == 0) {
				linea.descrizione = get_xml_content(cur);
			} else if (strcmp((char*)cur->name, "Quantita") == 0) {
				char* content = get_xml_content(cur);
				if (content) {
					linea.quantita = atof(content);
					free(content);
				}
			} else if (strcmp((char*)cur->name, "PrezzoUnitario") == 0) {
				char* content = get_xml_content(cur);
				if (content) {
					linea.prezzo_unitario = atof(content);
					free(content);
				}
			} else if (strcmp((char*)cur->name, "PrezzoTotale") == 0) {
				char* content = get_xml_content(cur);
				if (content) {
					linea.prezzo_totale = atof(content);
					free(content);
				}
			} else if (strcmp((char*)cur->name, "AliquotaIVA") == 0) {
				char* content = get_xml_content(cur);
				if (content) {
					linea.aliquota_iva = atof(content);
					free(content);
				}
			}
		}
	}
	return linea;
}

Fattura* parse_fattura_elettronica(const char* filename, xmlDocPtr* doc) {
	//TODO controllare se allocazione ok
	Fattura* f = init_fattura();

	xmlNode* root = NULL;

	LIBXML_TEST_VERSION

		*doc = xmlReadFile(filename, NULL, 0);
	if (doc == NULL) {
		fprintf(stderr, "Errore: impossibile parsare il file %s\n", filename);
		return NULL;
	}

	root = xmlDocGetRootElement(*doc);

	// Estrazione FatturaElettronicaHeader
	xmlNode* header = find_node(root, "FatturaElettronicaHeader");
	if (header) {
		xmlNode* cedente_node = find_node(header, "CedentePrestatore");
		if (cedente_node) {
			CedentePrestatore cedente = parse_cedente_prestatore(cedente_node);
			f->cedente = cedente;

		}

		xmlNode* cessionario_node = find_node(header, "CessionarioCommittente");
		if (cessionario_node) {
			// TODO CESSIONARIO/COMMITTENTE
			// Parsing simile al cedente...
		}
	}

	// Estrazione FatturaElettronicaBody
	xmlNode* body = find_node(root, "FatturaElettronicaBody");
	if (body) {
		xmlNode* dati_gen = find_node(body, "DatiGeneraliDocumento");
		if (dati_gen) {
			DatiGeneraliDocumento doc_data = parse_dati_generali_documento(dati_gen);
			f->data = doc_data;

		}

		xmlNode* dati_beni = find_node(body, "DatiBeniServizi");
		if (dati_beni) {
			for (xmlNode* linea_node = dati_beni->children; linea_node; linea_node = linea_node->next) {
				if (linea_node->type == XML_ELEMENT_NODE 
						&& strcmp((char*)linea_node->name, "DettaglioLinee") == 0)
				{
					DettaglioLinee linea = parse_dettaglio_linee(linea_node);

					//TODO controllare se allocazione ok
					add_linea(f,&linea);

				}
			}

		}
	}

	return f;
}

void freeDoc(xmlDoc *doc) {
	xmlFreeDoc(doc);
	xmlCleanupParser();
}

