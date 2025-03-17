# Geometria Obliczeniowa - Program

## Wymagania
- Kompilator gcc
- Program gnuplot (wymagany do generowania wykresów)
- Make

## Kompilacja i uruchomienie

### Kompilacja programu
```bash
make
```

### Uruchomienie testów
```bash
make test
```

### Czyszczenie plików skompilowanych
```bash
make clean
```

## Format danych wejściowych

Program oczekuje danych w następującym formacie:

```
*NODES id x y
1 0.0 0.0
2 1.0 0.0
3 0.0 1.0
...

*ELEMENTS id id_node id_node ...
1 1 2 3
2 2 3 4
...
```

### Opis formatu:
- `*NODES` - sekcja zawierająca węzły, gdzie:
    - `id` - numer identyfikacyjny węzła
    - `x y` - współrzędne węzła
- `*ELEMENTS` - sekcja zawierająca elementy, gdzie:
    - `id` - numer identyfikacyjny elementu
    - `id_node` - numery identyfikacyjne węzłów tworzących element

## Kompatybilność
Dziala na windows.