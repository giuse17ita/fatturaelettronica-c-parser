# fatturaelettronica-c-parser

parser fattura elettronica italia

---

## Requisiti

- Compilatore C compatibile (es. `gcc`, `clang`)
- **libxml2** installata sul sistema

Su sistemi Debian/Ubuntu:
```bash
sudo apt install libxml2-dev
```

Su macOS (Homebrew):
```bash
brew install libxml2
```

---

## Build

Esempio di compilazione:

```bash
gcc -o nome_progetto main.c $(pkg-config --cflags --libs libxml-2.0)
```

Adatta il comando in base alla struttura del progetto.

---

## Dipendenze e Licenze

Questo progetto **linka dinamicamente** a librerie di sistema e **non include codice sorgente di terze parti**.

### libxml2

- Copyright © Daniel Veillard
- Licenza: MIT

La licenza MIT di libxml2 **non impone obblighi di attribuzione** quando la libreria è utilizzata come dipendenza esterna e non viene redistribuita con il progetto.

### Specifiche OpenAPI

Questo progetto implementa funzionalità basate sulle **specifiche OpenAPI pubbliche di Invoicetronic**.

- Non viene utilizzato né redistribuito alcun SDK ufficiale
- Non viene incluso codice o documentazione proprietaria
- L’implementazione è indipendente e conforme alle specifiche

---

## Licenza

Il codice di questo progetto è rilasciato sotto licenza **MIT**.

Vedi il file `LICENSE` per i dettagli.

---

## Note legali

I nomi di prodotti, servizi e aziende citati appartengono ai rispettivi proprietari e sono utilizzati esclusivamente a scopo descrittivo.

---

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/J3J31RT9MO)
