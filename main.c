#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "include/structure.h"
#include "include/fattura.h"

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Uso: %s <file_xml_fattura>\n", argv[0]);
		return 1;
	}

	xmlDocPtr doc=NULL; 
	Fattura *f = parse_fattura_elettronica(argv[1],&doc);

	freeDoc(doc);
	print_fattura_elettronica(f);
	check_importi(f);
	free(f->d);
	free(f);
	return 0;
}
